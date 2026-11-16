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

## Slide 10. Dữ liệu và kiểm thử

- Mẫu 30 dòng.
- Dữ liệu 10.000, 20.000, 50.000 dòng.
- Đã xác nhận số dòng ba tệp lớn bằng wc -l.
- Đã xây dựng 17 ca kiểm thử chức năng.

Kết quả chạy chức năng:
Chưa ghi nhận đầy đủ, cần cập nhật trước khi nộp.

---

## Slide 11. Thực nghiệm hiệu năng

Thiết kế phép đo:
- Công cụ: std::chrono::steady_clock.
- Một lượt làm nóng, 10 lượt ghi nhận.
- Đơn vị: micro giây.
- Đo nạp tệp, tìm kiếm và thay thế.

Chưa có số liệu hoàn tất.
Sau khi chạy: thêm bảng trung bình và biểu đồ.
Không đưa số liệu giả vào slide.

---

## Slide 12. Kết luận và hỏi đáp

Hiện có:
- Thiết kế giao diện.
- Mã lõi danh sách liên kết kép.
- Dữ liệu và kế hoạch kiểm thử.

Cần hoàn thiện:
- Tích hợp và kiểm thử các chức năng.
- Kết quả đo và phân tích.
- Minh chứng cho các kết luận.

Cảm ơn thầy/cô và các bạn.
