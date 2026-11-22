#!/bin/sh
# Chay tu bat ky thu muc nao; ho tro macOS va Linux.
set -eu

thu_muc_script=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
thu_muc_repo=$(CDPATH= cd -- "$thu_muc_script/../.." && pwd)
thu_muc_core="$thu_muc_repo/N3_CTDLGT"
thu_muc_ket_qua="$thu_muc_repo/TV4/KetQua"
thu_muc_build=$(mktemp -d "${TMPDIR:-/tmp}/codenote-tv4.XXXXXX")
trap 'rm -rf "$thu_muc_build"' EXIT HUP INT TERM

if [ -n "${CXX:-}" ]; then
    trinh_bien_dich=$CXX
elif command -v clang++ >/dev/null 2>&1; then
    trinh_bien_dich=clang++
else
    trinh_bien_dich=c++
fi

mkdir -p "$thu_muc_ket_qua"
"$trinh_bien_dich" -std=c++17 -O2 -Wall -Wextra \
    -I "$thu_muc_core" \
    "$thu_muc_script/TV4/KiemThu/KiemThuCore.cpp" \
    "$thu_muc_core/DoublyLinkedList.cpp" \
    "$thu_muc_core/ActionStack.cpp" \
    "$thu_muc_core/UndoRedoManager.cpp" \
    "$thu_muc_core/SyntaxChecker.cpp" \
    -o "$thu_muc_build/kiem_thu_core"

cd "$thu_muc_build"
ma_thoat=0
./kiem_thu_core > ket_qua_kiem_thu_core.log 2>&1 || ma_thoat=$?
cat ket_qua_kiem_thu_core.log
cp ket_qua_kiem_thu_core.csv "$thu_muc_ket_qua/ket_qua_kiem_thu_core.csv"
cp ket_qua_kiem_thu_core.log "$thu_muc_ket_qua/ket_qua_kiem_thu_core.log"
{
    printf 'Thoi diem UTC: '
    date -u '+%Y-%m-%dT%H:%M:%SZ'
    printf 'He dieu han: '
    uname -srm
    printf 'Trinh bien dich: '
    "$trinh_bien_dich" --version
    printf 'Co bien dich: -std=c++17 -O2 -Wall -Wextra\n'
    printf 'Ma thoat bo kiem thu: %s\n' "$ma_thoat"
    printf 'Pham vi: 14 ca C++ thuan C01-C14; khong chay WinForms.\n'
} > "$thu_muc_ket_qua/moi_truong_kiem_thu_core.txt"

printf '\nCSV: %s/ket_qua_kiem_thu_core.csv\n' "$thu_muc_ket_qua"
exit "$ma_thoat"
