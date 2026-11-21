#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include "DoublyLinkedList.h"
#include <string>

// ============================================================================
// BÀI TẬP LỚN CẤU TRÚC DỮ LIỆU & GIẢI THUẬT - ĐỀ TÀI 5: TRÌNH SOẠN THẢO VĂN BẢN
// PHÂN CÔNG: THÀNH VIÊN 3 (CORE DEV 2: KIỂM TRA CẶP NGOẶC BẰNG STACK)
// ============================================================================
// Tính năng nâng cao: Kiểm tra cặp ngoặc (), [], {} cân bằng trong tệp mã nguồn.
// Tự cài đặt BracketStack bằng danh sách liên kết đơn, chuẩn C++17 thuần,
// không dùng STL (vector, stack, list, ...), không phụ thuộc WinForms.
// Quy ước tọa độ: 0-based (dòng >= 0, cột >= 0; -1 nếu cân bằng/không có lỗi),
// đồng bộ với TV2. Chuỗi message hiển thị quy đổi +1 sang 1-based cho người dùng.
// ============================================================================

// 1. Phần tử lưu thông tin một ngoặc mở trên Ngăn xếp
struct BracketItem {
    char bracket; // Ký tự ngoặc mở: '(', '{', '['
    int line;     // Chỉ số dòng (0-based)
    int col;      // Chỉ số cột (0-based)

    BracketItem(char b = '\0', int l = 0, int c = 0)
        : bracket(b), line(l), col(c) {}
};

// 2. Nút danh sách liên kết cho Ngăn xếp kiểm tra ngoặc
struct BracketNode {
    BracketItem data;
    BracketNode* next;

    explicit BracketNode(const BracketItem& item)
        : data(item), next(nullptr) {}
};

// 3. Lớp Ngăn xếp tự cài đặt dùng kiểm tra ngoặc
class BracketStack {
private:
    BracketNode* topNode; // Đỉnh ngăn xếp
    int count;            // Số lượng ngoặc đang mở trên ngăn xếp

    void copyFrom(const BracketStack& other);

public:
    BracketStack();
    ~BracketStack();
    BracketStack(const BracketStack& other);
    BracketStack& operator=(const BracketStack& other);

    void push(const BracketItem& item);
    bool pop(BracketItem& outItem);
    bool peek(BracketItem& outItem) const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
};

// 4. Loại lỗi mất cân bằng ngoặc
enum class BracketErrorType {
    NONE,              // Cân bằng hợp lệ
    UNMATCHED_CLOSING, // Dư ngoặc đóng (ngăn xếp rỗng khi gặp ngoặc đóng)
    MISMATCHED_PAIR,   // Ngoặc đóng không khớp với ngoặc mở trên đỉnh ngăn xếp
    UNCLOSED_OPENING   // Còn dư ngoặc mở khi kết thúc văn bản
};

// 5. Kết quả kiểm tra cặp ngoặc () [] {}
struct BracketCheckResult {
    bool isBalanced;             // true nếu mọi cặp ngoặc đều cân bằng
    BracketErrorType errorType;  // Loại lỗi (NONE nếu cân bằng)
    int errorLine;               // Dòng xảy ra lỗi đầu tiên (0-based, -1 nếu cân bằng)
    int errorCol;                // Cột xảy ra lỗi đầu tiên (0-based, -1 nếu cân bằng)
    char foundChar;              // Ký tự ngoặc gây lỗi ('\0' nếu cân bằng)
    char expectedChar;           // Ký tự ngoặc được kỳ vọng ('\0' nếu cân bằng)
    int openLine;                // Dòng của ngoặc mở liên quan (0-based, -1 nếu không có)
    int openCol;                 // Cột của ngoặc mở liên quan (0-based, -1 nếu không có)

    int roundOpenCount;          // Tổng số '('
    int roundCloseCount;         // Tổng số ')'
    int curlyOpenCount;          // Tổng số '{'
    int curlyCloseCount;         // Tổng số '}'
    int squareOpenCount;         // Tổng số '['
    int squareCloseCount;        // Tổng số ']'

    std::string message;         // Thông báo chi tiết kết quả kiểm tra

    BracketCheckResult()
        : isBalanced(true),
          errorType(BracketErrorType::NONE),
          errorLine(-1),
          errorCol(-1),
          foundChar('\0'),
          expectedChar('\0'),
          openLine(-1),
          openCol(-1),
          roundOpenCount(0),
          roundCloseCount(0),
          curlyOpenCount(0),
          curlyCloseCount(0),
          squareOpenCount(0),
          squareCloseCount(0),
          message("") {}
};

// 6. Lớp kiểm tra cân bằng ngoặc (), [], {}
class SyntaxChecker {
private:
    struct ScannerState {
        BracketStack stack;
        BracketCheckResult result;
        bool ignoreStringsAndComments;
        bool inBlockComment;
        bool hasFirstError;

        explicit ScannerState(bool ignoreStrAndCmt)
            : ignoreStringsAndComments(ignoreStrAndCmt),
              inBlockComment(false),
              hasFirstError(false) {}
    };

    static void scanLine(const std::string& lineText, int lineIndex, ScannerState& state);
    static void finalizeResult(ScannerState& state);

public:
    static bool isOpeningBracket(char ch);
    static bool isClosingBracket(char ch);
    static char getMatchingClosing(char openBracket);
    static char getMatchingOpening(char closeBracket);
    static bool isMatchingPair(char openBracket, char closeBracket);

    // Kiểm tra trên một chuỗi văn bản thô (hỗ trợ nhiều dòng)
    static BracketCheckResult checkText(const std::string& text,
                                        bool ignoreStringsAndComments = true);

    // Kiểm tra trực tiếp trên DoublyLinkedList của TV2 (O(N), không copy toàn bộ tệp)
    static BracketCheckResult checkDocument(const DoublyLinkedList& doc,
                                            bool ignoreStringsAndComments = true);
};

#endif // SYNTAX_CHECKER_H
