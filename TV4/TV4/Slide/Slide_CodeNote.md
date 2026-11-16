# NỘI DUNG THUYẾT TRÌNH CODENOTE

Bản nội dung gồm 12 slide.
Những kết quả chưa chạy thực tế phải được cập nhật trước khi nộp.

---

## Slide 1. Giới thiệu đề tài

**CodeNote — Trình soạn thảo văn bản có Undo/Redo**

- Môn: Cấu trúc dữ liệu và giải thuật.
- Nhóm 3.
- Thành viên và giảng viên: bổ sung thông tin thật.

---

## Slide 2. Bài toán và mục tiêu

- Quản lý và chỉnh sửa văn bản.
- Khôi phục thao tác bằng Undo/Redo.
- Tìm kiếm và thay thế nội dung.
- Kiểm tra tính cân bằng của ngoặc.
- Vận dụng cấu trúc dữ liệu tự cài đặt.

---

## Slide 3. Phân công thực hiện

- TV1: Giao diện, tích hợp và trực quan hóa.
- TV2: Danh sách liên kết kép, chỉnh sửa, tìm kiếm/thay thế.
- TV3: Stack, Undo/Redo và kiểm tra ngoặc.
- TV4: Dữ liệu, kiểm thử, thực nghiệm, báo cáo và slide.

---

## Slide 4. Kiến trúc chương trình

- Giao diện: Windows Forms C++/CLI.
- Tầng lõi: các cấu trúc và thuật toán C++.
- DoublyLinkedList quản lý các dòng văn bản.
- Các thành phần lịch sử và kiểm tra ngoặc theo kế hoạch.

Lưu ý thuyết trình:
Phân biệt kiến trúc dự kiến và mức tích hợp đã kiểm chứng.

---

## Slide 5. Danh sách liên kết kép

- Mỗi Node lưu một dòng.
- prev và next liên kết hai chiều.
- head, tail và size quản lý toàn danh sách.
- Truy xuất theo chỉ số có trường hợp xấu nhất O(n).
- Cập nhật liên kết khi đã có con trỏ là O(1).

Minh họa:
[Dòng 1] ⇄ [Dòng 2] ⇄ [Dòng 3]

---

## Slide 6. Chỉnh sửa, tìm kiếm và thay thế

- Thêm/xóa dòng; tách/gộp dòng.
- customStringFind so khớp trực tiếp.
- findFirst tìm kết quả đầu tiên.
- findAll lưu các kết quả không chồng lấn.
- replaceAll tìm và thay lần lượt.

Bổ sung demo khi chức năng đã chạy và được kiểm tra.

---

## Slide 7. Nguyên lý Undo/Redo

- UndoStack giữ các thao tác có thể hoàn tác.
- RedoStack giữ các thao tác đã hoàn tác.
- Thao tác mới làm mất nhánh Redo cũ.
- Giới hạn k bước loại bỏ lịch sử cũ nhất.

Đây là nguyên lý thiết kế.
Cần đối chiếu cách cài đặt thực tế trước khi trình bày demo.

---

## Slide 8. Kiểm tra ngoặc

- Gặp ngoặc mở: Push.
- Gặp ngoặc đóng: đối chiếu với đỉnh Stack.
- Sai loại hoặc thiếu ngoặc mở: không cân bằng.
- Kết thúc: Stack phải rỗng.

Ví dụ:
- ([]{}) → cân bằng.
- ([)] → sai thứ tự.
- (() → thiếu ngoặc đóng.

Nêu rõ phạm vi xử lý chuỗi và chú thích của bản thực tế.

---

## Slide 9. Giao diện

Bổ sung ảnh giao diện từ phiên bản nhóm đang dùng.

Các khu vực:
- Vùng soạn thảo.
- Thanh công cụ.
- Tìm kiếm/thay thế.
- Thống kê.
- Lịch sử và kết quả kiểm tra ngoặc.

Không dùng nhãn thông báo đặt sẵn làm minh chứng chức năng đúng.

---

## Slide 10. Dữ liệu và kết quả kiểm thử

**Dữ liệu chuẩn bị:**
- Mẫu 30 dòng.
- Các tệp 10.000, 20.000 và 50.000 dòng.
- Số dòng ba tệp lớn đã được kiểm tra bằng wc -l.

**Kiểm thử tự động phần lõi:**
- 10 ca C01–C10.
- Kết quả: 10 PASS, 0 FAIL.
- Kiểm tra chỉnh sửa, sao chép, tìm kiếm, thay thế
  và lưu/mở lại văn bản.

**Phạm vi:**
Chưa bao gồm Undo/Redo, kiểm tra ngoặc và giao diện Windows.

---

## Slide 11. Kết quả thực nghiệm hiệu năng

**Phương pháp:**
- std::chrono::steady_clock.
- Một lượt làm nóng trước khi ghi nhận.
- 10 lần đo cho mỗi phép đo trên mỗi kích thước.
- Tổng cộng 120 lượt đo được ghi nhận.

**Thời gian trung bình — đơn vị µs:**

| Phép đo | 10.000 dòng | 20.000 dòng | 50.000 dòng |
|---|---:|---:|---:|
| Nạp tệp | 591.712 | 797.412 | 1903.350 |
| Tìm từ không tồn tại | 247.533 | 375.721 | 1020.213 |
| Tìm tất cả int | 555.654 | 827.029 | 1960.696 |
| Thay int bằng long | 631.258 | 849.704 | 2040.383 |

Dấu chấm là dấu thập phân. 1.000 µs bằng 1 ms.

**Nhận xét:**
- Thời gian tăng khi kích thước dữ liệu tăng.
- Từ 20.000 lên 50.000 dòng, thời gian tăng khoảng
  2,37–2,72 lần, khi số dòng tăng 2,5 lần.
- Nhóm 10.000 dòng có dao động lớn giữa các lượt.
- Kết quả thuộc phần lõi trên Mac, chưa phải toàn ứng dụng.

---

## Slide 12. Kết luận và hỏi đáp

**Kết quả đã ghi nhận:**
- Có dữ liệu mẫu và ba bộ dữ liệu lớn.
- Đã xây dựng kế hoạch kiểm thử toàn ứng dụng.
- Bộ kiểm thử lõi: 10/10 ca đạt.
- Có 120 lượt đo và 12 giá trị thời gian trung bình.
- Đã phân tích kết quả theo mã nguồn và dữ liệu thực tế.

**Nội dung còn cần phối hợp với nhóm:**
- Đối chiếu và kiểm thử Undo/Redo, giới hạn lịch sử,
  kiểm tra ngoặc.
- Kiểm thử tích hợp trên giao diện Windows.
- Bổ sung thông tin môi trường và hoàn thiện bản trình chiếu.

Cảm ơn thầy/cô và các bạn.
