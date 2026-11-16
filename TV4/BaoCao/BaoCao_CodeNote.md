# CHƯƠNG 1. GIỚI THIỆU ĐỀ TÀI

## 1.1. Lý do lựa chọn đề tài

Trình soạn thảo văn bản là công cụ thường xuyên được sử dụng
trong học tập và lập trình. Trong quá trình chỉnh sửa, người dùng
có thể nhập sai, xóa nhầm hoặc thay đổi một đoạn nội dung.
Chức năng hoàn tác (Undo) và làm lại (Redo) giúp người dùng
khôi phục những thay đổi này.

Nhóm lựa chọn đề tài “Trình soạn thảo văn bản có Undo/Redo”
và đặt tên ứng dụng là CodeNote. Đề tài tạo điều kiện vận dụng
danh sách liên kết kép để quản lý các dòng văn bản, đồng thời
sử dụng ngăn xếp để quản lý lịch sử thao tác.

Đối với nội dung mã nguồn, kiểm tra tính cân bằng của các cặp
ngoặc là một tiện ích phù hợp. Chức năng này cũng là một
ứng dụng điển hình của cấu trúc ngăn xếp.

## 1.2. Mục tiêu

Các mục tiêu của dự án gồm:

- Quản lý các dòng văn bản bằng danh sách liên kết kép.
- Hỗ trợ chèn, xóa, tách dòng và gộp dòng.
- Hỗ trợ tìm kiếm và thay thế nội dung.
- Xây dựng cơ chế Undo/Redo bằng cấu trúc tự cài đặt.
- Giới hạn số bước hoàn tác được lưu trong lịch sử.
- Kiểm tra tính cân bằng của các cặp ngoặc (), [] và {}.
- Xây dựng giao diện Windows Forms bằng C++/CLI.
- Kiểm thử chức năng và đánh giá thời gian thực hiện.

Đây là các mục tiêu của đề tài. Mức độ hoàn thành từng mục
được xác định bằng mã nguồn và kết quả kiểm thử thực tế.

## 1.3. Phạm vi thực hiện

Ứng dụng tập trung vào soạn thảo văn bản và các đoạn mã nguồn.
Giao diện sử dụng Windows Forms C++/CLI, trong khi tầng lõi
quản lý văn bản được tổ chức riêng bằng C++.

Các cấu trúc dữ liệu chính được tự cài đặt bằng con trỏ.
Không sử dụng std::vector, std::list hoặc std::stack để thay
thế phần cấu trúc dữ liệu được yêu cầu. Chức năng Undo/Redo
cần được xây dựng riêng, không sử dụng Undo có sẵn của
Windows Forms thay cho thuật toán của nhóm.

Kiểm tra ngoặc chỉ xác định sự phù hợp của các cặp ngoặc
trong phạm vi mà chương trình hỗ trợ. Chức năng này không
thay thế trình biên dịch hoặc bộ kiểm tra toàn bộ cú pháp
của một ngôn ngữ lập trình.

## 1.4. Phương pháp thực hiện

Nhóm chia công việc thành các phần: thiết kế giao diện,
quản lý văn bản, quản lý lịch sử và kiểm thử.

Các thành phần được xây dựng độc lập trước khi tích hợp.
Phần kiểm thử chức năng sử dụng các ca có đầu vào, thao tác
và kết quả mong đợi rõ ràng.

Dữ liệu thực nghiệm gồm tệp mẫu 30 dòng và các tệp lớn
10.000, 20.000, 50.000 dòng. Thời gian xử lý được dự kiến
đo bằng std::chrono. Việc phân tích hiệu năng phải dựa trên
kết quả chạy thực tế trong điều kiện được ghi nhận.


# CHƯƠNG 2. CƠ SỞ LÝ THUYẾT

## 2.1. Danh sách liên kết kép

Danh sách liên kết kép gồm các nút được kết nối theo hai chiều.
Mỗi nút chứa dữ liệu, con trỏ đến nút trước và con trỏ đến
nút sau.

Trong CodeNote, một nút đại diện cho một dòng văn bản.
Cấu trúc Node trong mã nguồn gồm:

- lineData: nội dung dòng, sử dụng std::string.
- prev: con trỏ đến dòng trước.
- next: con trỏ đến dòng sau.

Lớp DoublyLinkedList quản lý head, tail và size, tương ứng
với nút đầu, nút cuối và số dòng hiện tại.

Ví dụ:

NULL ← [Dòng 1] ⇄ [Dòng 2] ⇄ [Dòng 3] → NULL

Danh sách cho phép duyệt theo cả hai chiều. Khi đã có
con trỏ tới vị trí cần xử lý, việc cập nhật các liên kết
để chèn hoặc xóa một nút có chi phí O(1).

Tuy nhiên, nếu đầu vào là chỉ số dòng, chương trình phải
tìm nút tương ứng. Trong mã nguồn của nhóm, getNodeAt
chọn duyệt từ head hoặc tail tùy vị trí. Cách này giảm
số nút cần duyệt nhưng độ phức tạp trường hợp xấu nhất
vẫn là O(n).

Ngoài chi phí liên kết, thao tác với nội dung dòng còn
có chi phí sao chép hoặc dịch chuyển ký tự trong chuỗi.
Vì vậy, không thể kết luận mọi thao tác chèn hoặc xóa
văn bản đều có độ phức tạp O(1).

## 2.2. Ngăn xếp

Ngăn xếp (Stack) hoạt động theo nguyên tắc LIFO:
phần tử được đưa vào sau cùng sẽ được lấy ra trước.

Các thao tác cơ bản:

- Push: đưa phần tử lên đỉnh.
- Pop: lấy phần tử ở đỉnh ra.
- Top: xem phần tử ở đỉnh.
- IsEmpty: kiểm tra ngăn xếp rỗng.

Với cách cài đặt bằng danh sách liên kết và quản lý
con trỏ đỉnh, Push và Pop có thể thực hiện trong O(1),
không tính chi phí sao chép dữ liệu của phần tử.

## 2.3. Nguyên lý Undo/Redo

Một cách tổ chức lịch sử là sử dụng hai ngăn xếp:
UndoStack và RedoStack.

Khi người dùng thực hiện thao tác mới:

1. Lưu thông tin cần thiết để hoàn tác thao tác.
2. Đưa bản ghi vào UndoStack.
3. Xóa lịch sử Redo cũ.

Khi thực hiện Undo:

1. Kiểm tra UndoStack có rỗng không.
2. Lấy thao tác gần nhất.
3. Thực hiện thao tác nghịch đảo.
4. Chuyển thông tin thao tác sang RedoStack.

Khi thực hiện Redo:

1. Kiểm tra RedoStack có rỗng không.
2. Lấy thao tác gần nhất đã hoàn tác.
3. Thực hiện lại thao tác.
4. Chuyển thông tin sang UndoStack.

Ví dụ, người dùng dán abc vào tài liệu trống bằng một
thao tác. Undo đưa tài liệu về trạng thái trống; Redo
đưa nội dung abc trở lại.

Thông tin trong bản ghi hành động phải đủ để phục hồi
văn bản, chẳng hạn loại hành động, vị trí và nội dung
đã chèn hoặc xóa.

Cách lưu bản ghi cụ thể sẽ được mô tả theo mã cài đặt
thực tế của thành viên phụ trách.

## 2.4. Giới hạn lịch sử hoàn tác

Giới hạn k bước nhằm kiểm soát số hành động được giữ lại.
Khi thêm hành động mới làm số bản ghi vượt quá k,
bản ghi cũ nhất cần được loại bỏ.

Một phương án là dùng danh sách liên kết kép để quản lý
hai đầu: một đầu phục vụ thao tác mới nhất, đầu còn lại
phục vụ loại bỏ thao tác cũ nhất.

Giới hạn số bản ghi không đồng nghĩa với giới hạn chính xác
số byte bộ nhớ, vì mỗi bản ghi có thể chứa lượng văn bản
khác nhau.

## 2.5. Kiểm tra ngoặc bằng ngăn xếp

Thuật toán cơ bản duyệt lần lượt các ký tự:

1. Gặp ngoặc mở thì đưa vào Stack.
2. Gặp ngoặc đóng thì kiểm tra Stack.
3. Nếu Stack rỗng hoặc đỉnh không cùng loại, kết luận sai.
4. Nếu cùng loại, lấy ngoặc mở khỏi Stack.
5. Kết thúc duyệt, chỉ chấp nhận nếu Stack rỗng.

Ví dụ:

- ([]{}) là cân bằng.
- ([)] không cân bằng vì sai thứ tự đóng ngoặc.
- (() không cân bằng vì thiếu ngoặc đóng.

Với N ký tự, thuật toán cơ bản có thời gian O(N)
và bộ nhớ phụ O(N) trong trường hợp xấu nhất.

Khi áp dụng cho mã nguồn, cần xác định rõ cách xử lý
ngoặc trong chuỗi ký tự và chú thích. Không mặc nhiên
coi thuật toán cơ bản là bộ phân tích cú pháp hoàn chỉnh.

## 2.6. Đo thời gian bằng std::chrono

std::chrono cung cấp các công cụ đo khoảng thời gian.
Có thể dùng steady_clock để lấy thời điểm trước và sau
một lời gọi hàm, sau đó tính hiệu hai thời điểm.

Để phép đo có ý nghĩa:

- Ghi rõ dữ liệu, môi trường và cờ biên dịch.
- Chạy nhiều lần và giữ lại kết quả từng lần.
- Chuẩn bị dữ liệu ngoài khoảng đo nếu không đo bước đó.
- Kiểm tra kết quả để bảo đảm hàm thực hiện đúng.
- Khôi phục dữ liệu đầu vào giữa các lần đo có thay đổi dữ liệu.
- Phân biệt thời gian thuật toán với thời gian giao diện.
- Ghi nhận ảnh hưởng của bộ nhớ đệm đối với đọc tệp.

Không suy ra độ phức tạp chỉ từ một lần chạy. Cần kết hợp
phân tích mã nguồn với xu hướng số liệu thực nghiệm.
