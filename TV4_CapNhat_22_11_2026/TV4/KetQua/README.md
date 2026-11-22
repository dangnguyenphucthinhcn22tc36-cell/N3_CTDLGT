# Kết quả thực nghiệm phần lõi CodeNote

- ket_qua_chi_tiet.csv: 120 lượt đo.
- ket_qua_trung_binh.csv: 12 giá trị trung bình.
- Mỗi phép đo trên mỗi kích thước được ghi nhận 10 lần.
- Đơn vị: micro giây (µs).

Bốn phép đo:
1. Nạp tệp vào danh sách liên kết.
2. Tìm từ khóa không tồn tại.
3. Tìm tất cả từ khóa int.
4. Thay tất cả int bằng long.

Kết quả thuộc phần lõi DoublyLinkedList, chưa đại diện
cho thời gian đáp ứng toàn bộ giao diện hoặc Undo/Redo.

## Kiểm thử chức năng mở rộng C01–C14

Bản cập nhật ngày 22/11/2026 giữ C01–C10 và kiểm tra thêm:

| Ca | Nội dung |
|---|---|
| C11 | ActionStack: giới hạn k, LIFO, lấy phần tử đáy, sao chép độc lập, Stack rỗng |
| C12 | Áp dụng Action Undo/Redo lên tài liệu; xóa Redo khi chỉnh sửa mới; k = 3 |
| C13 | Ngoặc cân bằng, sai thứ tự, thiếu/dư; chuỗi, chú thích, xuống dòng CRLF |
| C14 | Duyệt 50.000 dòng bằng checkDocument, đếm ngoặc; thêm dòng 50.001 có lỗi |

Kết quả chạy lại: **14 PASS, 0 FAIL** trên Linux x86_64, GCC 14.2.0,
C++17, `-O2 -Wall -Wextra`. Đây là lần chạy mới trong môi trường kiểm tra;
không coi là kết quả chạy giao diện Windows hoặc lần chạy trên máy Mac của TV4.
Các mô-đun sản xuất được đối chiếu tại commit `c7d3f205d9d67b14c676e14af8e119794da7236d`.

Các tệp minh chứng:

- `ket_qua_kiem_thu_core.csv`: 14 dòng kết quả C01–C14.
- `ket_qua_kiem_thu_core.log`: đầu ra của lần chạy thông thường.
- `moi_truong_kiem_thu_core.txt`: hệ điều hành, trình biên dịch, cờ và mã thoát.
- `ket_qua_kiem_thu_core_sanitizer.log`: cùng 14 ca chạy với AddressSanitizer và UndefinedBehaviorSanitizer, không có chẩn đoán lỗi trong lần chạy này.
- `kiem_thu_core_manifest.json`: phiên bản gốc và SHA-256 các tệp được kiểm tra.

Chạy từ thư mục gốc dự án trên Mac hoặc Linux:

```sh
bash TV4/KiemThu/chay_kiem_thu_core.sh
```

Script biên dịch bốn mô-đun lõi và ghi lại CSV, log, môi trường vào thư mục này.
Nếu chạy trên máy khác, ba tệp đó phản ánh lần chạy tại máy đó; giữ đúng
thông tin môi trường khi cập nhật báo cáo. Tệp log sanitizer và manifest
đi kèm gói này ghi nhận lần kiểm tra Linux đã nêu, không được coi là log của máy khác.
14 ca này không bao phủ toàn bộ mã C++ hay thay thế TC01–TC17 trên Windows.
