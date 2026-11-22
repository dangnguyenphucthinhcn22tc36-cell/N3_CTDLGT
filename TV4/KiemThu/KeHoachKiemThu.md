# Kế hoạch kiểm thử CodeNote

## 1. Mục tiêu

Kiểm tra các chức năng chỉnh sửa văn bản, Undo/Redo,
tìm kiếm, thay thế, kiểm tra ngoặc và giới hạn lịch sử.

## 2. Dữ liệu kiểm thử

Các tệp nằm trong thư mục TV4/DuLieuTest:

- mau_30_dong.cpp
- mau_10000_dong.cpp
- mau_20000_dong.cpp
- mau_50000_dong.cpp

## 3. Quy định thực hiện

- Mỗi ca kiểm thử bắt đầu với tài liệu và lịch sử mới.
- Chỉ ghi Đạt hoặc Không đạt sau khi chạy thực tế.
- Nếu chưa chạy, giữ trạng thái Chưa thực hiện.
- Ghi phiên bản mã nguồn, môi trường chạy và ảnh minh chứng.
- Khi kiểm thử Undo/Redo, mỗi lần dán là một thao tác riêng.

## 4. Bảng ca kiểm thử

| Mã | Thao tác kiểm thử | Kết quả mong đợi | Kết quả thực tế | Trạng thái |
|---|---|---|---|---|
| TC01 | Mở mau_30_dong.cpp | Hiển thị đủ nội dung và đúng thứ tự dòng | Chưa ghi nhận | Chưa thực hiện |
| TC02 | Dán abc vào tài liệu trống | Nội dung là abc | Chưa ghi nhận | Chưa thực hiện |
| TC03 | Dán abc, chọn b rồi xóa | Nội dung là ac | Chưa ghi nhận | Chưa thực hiện |
| TC04 | Dán ab, đặt con trỏ giữa a và b rồi nhấn Enter | Có hai dòng, dòng đầu là a, dòng sau là b | Chưa ghi nhận | Chưa thực hiện |
| TC05 | Dán abc vào tài liệu trống rồi nhấn Undo | Tài liệu trở lại trống | Chưa ghi nhận | Chưa thực hiện |
| TC06 | Dán abc, nhấn Undo rồi Redo | Nội dung trở lại abc | Chưa ghi nhận | Chưa thực hiện |
| TC07 | Dán abc, chọn b rồi xóa, sau đó Undo | Nội dung trở lại abc | Chưa ghi nhận | Chưa thực hiện |
| TC08 | Dán abc, Undo, dán xyz rồi nhấn Redo | Nội dung vẫn là xyz, không phục hồi abc | Chưa ghi nhận | Chưa thực hiện |
| TC09 | Nhấn Undo và Redo khi lịch sử trống | Không phát sinh lỗi, văn bản không đổi | Chưa ghi nhận | Chưa thực hiện |
| TC10 | Dán abc xyz rồi tìm xyz | Tìm đúng đoạn xyz | Chưa ghi nhận | Chưa thực hiện |
| TC11 | Dán abc rồi tìm zzz | Không có kết quả, văn bản không đổi | Chưa ghi nhận | Chưa thực hiện |
| TC12 | Dán abc xyz rồi thay xyz bằng 123 | Nội dung là abc 123 | Chưa ghi nhận | Chưa thực hiện |
| TC13 | Nhập ([]{}) rồi kiểm tra ngoặc | Báo ngoặc cân bằng | Chưa ghi nhận | Chưa thực hiện |
| TC14 | Nhập ([)] rồi kiểm tra ngoặc | Báo ngoặc không cân bằng | Chưa ghi nhận | Chưa thực hiện |
| TC15 | Nhập (() rồi kiểm tra ngoặc | Báo ngoặc không cân bằng | Chưa ghi nhận | Chưa thực hiện |
| TC16 | Đặt giới hạn k = 3; dán a, b, c, d thành bốn thao tác riêng; nhấn Undo bốn lần | Chỉ hoàn tác ba thao tác mới nhất, nội dung cuối là a | Chưa ghi nhận | Chưa thực hiện |
| TC17 | Lưu rồi mở lại văn bản nhiều dòng có tiếng Việt | Giữ nguyên nội dung, dấu tiếng Việt và xuống dòng | Chưa ghi nhận | Chưa thực hiện |

## 5. Kiểm thử dữ liệu lớn

Thực hiện lần lượt với các tệp:
- mau_10000_dong.cpp
- mau_20000_dong.cpp
- mau_50000_dong.cpp

Với mỗi tệp:
1. Mở tệp và kiểm tra nội dung được nạp đầy đủ.
2. Tìm tên hàm cuối cùng tương ứng:
   ham_10000(), ham_20000() hoặc ham_50000().
3. Chạy kiểm tra ngoặc, kết quả mong đợi là cân bằng.
4. Ghi nhận lỗi hoặc việc ứng dụng thoát bất thường.

## 6. Đo thời gian thực nghiệm

Phần đo thời gian sẽ dùng std::chrono và gọi các hàm
xử lý thực tế của tầng lõi sau khi xác định giao diện hàm.

Ghi lại:
- Phiên bản mã nguồn.
- Cấu hình máy và chế độ biên dịch.
- Thuật toán được đo.
- Kích thước dữ liệu.
- Số lần chạy và kết quả từng lần.
- Nhận xét so với độ phức tạp lý thuyết.

Không dùng thời gian sinh tệp dữ liệu thay cho thời gian
thực hiện thuật toán của CodeNote.

## 7. Kiểm thử tự động phần lõi C01–C14

Bộ tự động được lưu tại `TV4/KiemThu/TV4/KiemThu/KiemThuCore.cpp`.
Đây là bộ riêng với TC01–TC17 trên giao diện Windows.

- C01–C10: quản lý dòng, chỉnh sửa, sao chép, tìm/thay thế và lưu/mở UTF-8.
- C11: ActionStack, thứ tự LIFO, lấy phần tử đáy, giới hạn k, sao chép và Stack rỗng.
- C12: áp dụng Action Undo/Redo lên DoublyLinkedList, xóa nhánh Redo, xóa lịch sử khi mở tài liệu và giới hạn k = 3.
- C13: ngoặc cân bằng/sai/thiếu/dư, bỏ qua chuỗi/chú thích và tọa độ dòng CRLF.
- C14: kiểm tra 50.000 dòng bằng checkDocument, đếm ngoặc và phát hiện dòng lỗi thêm vào.

Chạy từ thư mục gốc dự án:

```sh
bash TV4/KiemThu/chay_kiem_thu_core.sh
```

Kết quả được xuất vào `TV4/KetQua/ket_qua_kiem_thu_core.csv`, kèm log
và thông tin môi trường. Mỗi dòng CSV là một ca kiểm thử, có thể gồm nhiều
điều kiện kiểm tra. Mã thoát 0 chỉ khi các ca đều đạt và ghi CSV thành công.
Bản mở rộng ngày 22/11/2026 đã chạy trên Linux x86_64, GCC 14.2.0:
14 PASS, 0 FAIL. Không dùng kết quả này để đánh dấu TC01–TC17 là đã đạt.
