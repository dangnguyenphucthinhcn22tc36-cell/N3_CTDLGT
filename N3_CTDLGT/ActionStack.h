#ifndef ACTION_STACK_H
#define ACTION_STACK_H

#include "DoublyLinkedList.h"
#include <cstdint>
#include <string>

// ============================================================================
// BÀI TẬP LỚN CẤU TRÚC DỮ LIỆU & GIẢI THUẬT - ĐỀ TÀI 5: TRÌNH SOẠN THẢO VĂN BẢN
// PHÂN CÔNG: THÀNH VIÊN 3 (CORE DEV 2: STACK, UNDO/REDO & KIỂM TRA NGOẶC)
// ============================================================================
// Tầng Lõi (Core) C++17 thuần, tách biệt hoàn toàn khỏi giao diện (GUI).
// Tự cài đặt Ngăn xếp hai đầu (Deque-backed Stack) bằng Danh sách liên kết kép,
// không dùng STL (vector, list, stack, queue, deque, map, set, ...).
// Quy ước tọa độ: 0-based (dòng bắt đầu từ 0, cột bắt đầu từ 0), đồng bộ trực tiếp với TextPosition của TV2.
// ============================================================================

// 1. Các loại thao tác soạn thảo hỗ trợ hoàn tác / làm lại (Undo / Redo)
enum class ActionType {
    INSERT_CHAR,   // Chèn 1 ký tự tại startPos
    DELETE_CHAR,   // Xóa 1 ký tự tại startPos
    INSERT_TEXT,   // Chèn / dán đoạn chuỗi (1 hoặc nhiều dòng) từ startPos đến endPos
    DELETE_TEXT,   // Xóa / cắt đoạn chuỗi (1 hoặc nhiều dòng) từ startPos đến endPos
    INSERT_LINE,   // Chèn 1 dòng tại startPos.line
    DELETE_LINE,   // Xóa 1 dòng tại startPos.line
    SPLIT_LINE,    // Tách dòng tại startPos (tạo dòng mới tại endPos = (line + 1, 0))
    MERGE_LINE,    // Gộp dòng endPos.line (line + 1) vào cuối dòng startPos.line tại startPos.col
    REPLACE_TEXT   // Thay thế chuỗi tại 1 vị trí (previousContent -> content)
};

// 2. Bản ghi một thao tác chỉnh sửa (Action Record)
struct Action {
    ActionType type;             // Loại thao tác
    TextPosition startPos;       // Vị trí bắt đầu vùng tác động (0-based)
    TextPosition endPos;         // Vị trí kết thúc vùng tác động (0-based)
    std::string content;         // Nội dung chính (hoặc chuỗi mới với REPLACE_TEXT)
    std::string previousContent; // Chuỗi cũ bị thay thế (dùng cho REPLACE_TEXT)
    TextPosition cursorBefore;   // Vị trí con trỏ trước thao tác (0-based, khôi phục khi Undo)
    TextPosition cursorAfter;    // Vị trí con trỏ sau thao tác (0-based, khôi phục khi Redo)

    Action()
        : type(ActionType::INSERT_CHAR),
          startPos(0, 0),
          endPos(0, 0),
          content(""),
          previousContent(""),
          cursorBefore(0, 0),
          cursorAfter(0, 0) {}

    Action(ActionType actionType,
           const TextPosition& start,
           const TextPosition& end,
           const std::string& text,
           const std::string& prevText,
           const TextPosition& curBefore,
           const TextPosition& curAfter)
        : type(actionType),
          startPos(start),
          endPos(end),
          content(text),
          previousContent(prevText),
          cursorBefore(curBefore),
          cursorAfter(curAfter) {}
};

// 3. Nút trong Danh sách liên kết kép của ActionStack (Deque Node)
struct ActionNode {
    Action data;      // Dữ liệu bản ghi thao tác
    ActionNode* prev; // Con trỏ trỏ về thao tác cũ hơn (hướng đáy bottomNode)
    ActionNode* next; // Con trỏ trỏ về thao tác mới hơn (hướng đỉnh topNode)

    explicit ActionNode(const Action& action)
        : data(action), prev(nullptr), next(nullptr) {}
};

// 4. Lớp Ngăn xếp thao tác cài đặt bằng DSLK kép làm Hàng đợi hai đầu (Deque)
// - Đỉnh (topNode): thao tác mới nhất -> push / pop / peek trong O(1).
// - Đáy (bottomNode): thao tác cũ nhất -> popBottom trong O(1) khi vượt giới hạn k bước.
// - maxCapacity == 0: chế độ không giới hạn số bước (chức năng bắt buộc).
// - maxCapacity > 0 : chế độ giới hạn k bước (chức năng nâng cao).
class ActionStack {
private:
    ActionNode* topNode;    // Đỉnh ngăn xếp (thao tác mới nhất)
    ActionNode* bottomNode; // Đáy ngăn xếp (thao tác cũ nhất)
    int count;              // Số phần tử hiện có
    int maxCapacity;        // 0 = không giới hạn; > 0 = giới hạn tối đa k phần tử

    // Lấy con trỏ nút theo chỉ số tính từ đỉnh (0 = topNode), O(N/2)
    ActionNode* getNodeAtFromTop(int indexFromTop) const;

    // Sao chép sâu toàn bộ chuỗi nút từ stack khác (theo thứ tự từ đáy lên đỉnh)
    void copyFrom(const ActionStack& other);

public:
    // --- QUẢN LÝ VÒNG ĐỜI & BỘ NHỚ (RULE OF THREE) ---
    explicit ActionStack(int maxCap = 0);
    ~ActionStack();
    ActionStack(const ActionStack& other);
    ActionStack& operator=(const ActionStack& other);

    // --- CÁC THAO TÁC NGĂN XẾP & HÀNG ĐỢI HAI ĐẦU O(1) ---
    void push(const Action& action);
    bool pop(Action& outAction);
    bool peek(Action& outAction) const;

    bool popBottom();
    bool popBottom(Action& outAction);
    bool peekBottom(Action& outAction) const;

    void clear(); // Thu hồi toàn bộ RAM của các nút

    // --- TRẠNG THÁI & CẤU HÌNH GIỚI HẠN ĐỘNG ---
    bool isEmpty() const;
    int getSize() const;
    bool isFull() const;
    bool isUnlimited() const;
    int getMaxCapacity() const;

    // Đặt giới hạn k mới (k = 0: không giới hạn, k > 0: cắt bỏ nút cũ nhất ở đáy nếu vượt k)
    // Trả về false nếu newLimit < 0 và không thay đổi trạng thái hiện tại.
    bool setMaxCapacity(int newLimit);

    // --- HỖ TRỢ ĐỌC CHỈ ĐỌC & TRỰC QUAN HÓA (VISUALIZER CHO THÀNH VIÊN 1) ---
    const ActionNode* getTopNode() const;
    const ActionNode* getBottomNode() const;
    bool getActionAtFromTop(int indexFromTop, Action& outAction) const;
    bool getNodeVisualInfo(int indexFromTop,
                           std::string& summary,
                           uintptr_t& selfAddr,
                           uintptr_t& prevAddr,
                           uintptr_t& nextAddr) const;

    static std::string actionTypeToString(ActionType type);
    static std::string formatActionSummary(const Action& action);

    // In ngăn xếp ra console phục vụ kiểm thử độc lập
    void printStack(const std::string& label = "ActionStack") const;
};

#endif // ACTION_STACK_H
