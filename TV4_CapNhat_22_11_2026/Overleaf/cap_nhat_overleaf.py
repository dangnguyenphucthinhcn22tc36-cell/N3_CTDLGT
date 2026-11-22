#!/usr/bin/env python3
"""Cap nhat cac muc da doi chieu trong ZIP nguon Overleaf, khong ghi de ZIP goc."""
from pathlib import Path
import json
import re
import sys
import zipfile


def replace_section(text, number, replacement):
    starts = list(re.finditer(
        r'(?:\\section\*?\{\s*' + re.escape(number) + r'\.\s'
        r'|\\#\\#\s+' + re.escape(number) + r'\.\s)', text))
    if len(starts) != 1:
        raise ValueError(f'Can dung mot muc {number}; tim thay {len(starts)}. Chua ghi tep moi.')
    start = starts[0].start()
    after = starts[0].end()
    # Also recognize the old exported literal "## 4.12" so the GUI is preserved.
    boundary = re.search(r'\\(?:chapter|section)\*?\{|\\#\\#\s+\d+\.\d+\.', text[after:])
    if not boundary:
        raise ValueError(f'Khong tim thay diem ket thuc muc {number}.')
    end = after + boundary.start()
    return text[:start] + replacement.strip() + '\n\n' + text[end:]


def update(text, payload):
    for number, latex in payload['sections'].items():
        text = replace_section(text, number, latex)

    # Replace only the outdated opening paragraphs of 3.2.2; keep its diagram.
    match = re.search(r'\\subsection\*?\{3\.2\.2\.[^}]*\}(?:\\label\{[^}]*\})?', text)
    if match:
        start = match.end()
        diagram = re.search(r'\\begin\{figure\}', text[start:])
        next_section = re.search(r'\\(?:chapter|section)\*?\{', text[start:])
        if diagram and next_section and diagram.start() < next_section.start():
            text = (text[:start] + '\n\n' + payload['core_design']
                    + '\n\n' + text[start + diagram.start():])

    text = text.replace('kết quả 10 ca kiểm thử lõi.', 'kết quả 14 ca C01–C14.')
    text = re.sub(
        r'Các phép đo phần lõi và bộ kiểm thử tự động được thực hiện trên môi\s+trường sau:',
        'Môi trường Mac của 120 lượt đo và lần kiểm thử C01--C10 ban đầu được ghi nhận\n'
        'như sau. Lần chạy C01--C14 trên Linux được mô tả riêng tại mục 5.3:',
        text, count=1)

    # Preserve member names/IDs while reflecting the latest division of work.
    roles = {
        'TV1': 'Giao diện Windows Forms, tích hợp tầng lõi, trực quan hóa và tổng hợp PPT',
        'TV3': 'ActionStack, Undo/Redo, giới hạn lịch sử và lõi kiểm tra ngoặc',
        'TV4': 'Dữ liệu, kiểm thử, đo thời gian, phân tích và báo cáo LaTeX',
    }
    for member, role in roles.items():
        pattern = re.compile(r'^(' + member + r' & [^&]+ & [^&]+ &)[^&]*?\\\\', re.M)
        text = pattern.sub(lambda m: m.group(1) + ' ' + role + r' \\', text, count=1)

    # 12 pt text remains; a modest line-spacing adjustment makes room for the update.
    text = re.sub(r'\\setstretch\{1\.15\}', r'\\setstretch{1.05}', text, count=1)
    return text


def main():
    if len(sys.argv) != 2:
        raise ValueError('Cach dung: python3 cap_nhat_overleaf.py DUONG_DAN_ZIP_NGUON_OVERLEAF')
    source = Path(sys.argv[1]).expanduser().resolve()
    payload = json.loads((Path(__file__).resolve().parent / 'cap_nhat_overleaf.json').read_text())
    with zipfile.ZipFile(source) as archive:
        entries = archive.infolist()
        mains = [x for x in entries if not x.is_dir() and Path(x.filename).name == 'main.tex'
                 and '__MACOSX' not in x.filename]
        if len(mains) != 1:
            raise ValueError('ZIP phai chua dung mot tep main.tex.')
        main_entry = mains[0]
        original = archive.read(main_entry).decode('utf-8-sig')
        updated = update(original, payload).encode('utf-8')
        output = source.with_name(source.stem + '-capnhat-TV4.zip')
        number = 2
        while output.exists():
            output = source.with_name(source.stem + f'-capnhat-TV4-{number}.zip')
            number += 1
        with zipfile.ZipFile(output, 'w', zipfile.ZIP_DEFLATED) as target:
            for entry in entries:
                data = updated if entry.filename == main_entry.filename else archive.read(entry)
                target.writestr(entry, data)
    print('Da tao:', output)
    print('Da cap nhat 3.5, 4.11, 5.3, 5.4, 6.1, 6.2, 6.3 va mo ta tang loi.')
    print('Anh, muc giao dien 4.12 va ZIP goc duoc giu lai.')
    print('Tai ZIP moi len Overleaf, chon XeLaTeX, Recompile va kiem tra so trang.')


if __name__ == '__main__':
    try:
        main()
    except (OSError, ValueError, KeyError, zipfile.BadZipFile, UnicodeDecodeError) as error:
        print('LOI:', error, file=sys.stderr)
        sys.exit(1)
