#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <string>
#include <cstdint>

// ============================================================================
// BÀI TẬP LỚN CẤU TRÚC DỮ LIỆU & GIẢI THUẬT - ĐỀ TÀI 5: TRÌNH SOẠN THẢO VĂN BẢN
// PHÂN CÔNG: THÀNH VIÊN 2 (CORE DEV 1: DANH SÁCH LIÊN KẾT KÉP - DSLK KÉP)
// ============================================================================
// TUÂN THỦ NGHIÊM NGẶT NỘI QUY:
// 1. Chuẩn C++17 thuần, không dùng STL (vector, list, map, v.v.), không dùng std::sort, std::find.
// 2. Tự cài đặt 100% bằng con trỏ, quản lý bộ nhớ động chặt chẽ, chống rò rỉ RAM (Zero Memory Leak).
// 3. Tách biệt hoàn toàn tầng Lõi (Core) khỏi giao diện (GUI).
// ============================================================================

// 1. Cấu trúc Node - Đại diện cho một dòng văn bản trong Trình soạn thảo
struct Node {
    std::string lineData; // Nội dung văn bản của dòng hiện tại
    Node* prev;           // Con trỏ trỏ đến dòng phía trước (phía trên)
    Node* next;           // Con trỏ trỏ đến dòng phía sau (phía dưới)

    // Constructor khởi tạo Node
    explicit Node(const std::string& data = "")
        : lineData(data), prev(nullptr), next(nullptr) {}
};

// 2. Cấu trúc vị trí con trỏ (Dòng, Cột)
struct TextPosition {
    int line; // Chỉ số dòng (0-based)
    int col;  // Chỉ số cột (0-based)

    TextPosition(int l = 0, int c = 0) : line(l), col(c) {}
    bool isValid() const { return line >= 0 && col >= 0; }
};

// 3. Cấu trúc danh sách liên kết đơn lưu kết quả tìm kiếm (KHÔNG DÙNG std::vector)
struct SearchResult {
    int line;            // Chỉ số dòng tìm thấy
    int col;             // Chỉ số cột bắt đầu từ khóa
    int length;          // Độ dài từ khóa
    SearchResult* next;  // Con trỏ tới kết quả tiếp theo

    SearchResult(int l = 0, int c = 0, int len = 0)
        : line(l), col(c), length(len), next(nullptr) {}
};

// 4. Cấu trúc thống kê văn bản
struct TextStatistics {
    int lineCount;        // Tổng số dòng
    int wordCount;        // Tổng số từ
    int charCount;        // Tổng số ký tự (gồm khoảng trắng & xuống dòng)
    int charNoSpaceCount; // Tổng số ký tự (không tính khoảng trắng)
};

// 5. Lớp Danh sách liên kết kép quản lý tập hợp các dòng văn bản
class DoublyLinkedList {
private:
    Node* head; // Con trỏ trỏ đến dòng đầu tiên
    Node* tail; // Con trỏ trỏ đến dòng cuối cùng
    int size;   // Tổng số dòng hiện tại

public:
    // --- QUẢN LÝ VÒNG ĐỜI & BỘ NHỚ (RULE OF THREE) ---
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);            // Deep Copy Constructor
    DoublyLinkedList& operator=(const DoublyLinkedList& other); // Deep Copy Assignment Operator

    // --- CÁC HÀM THÔNG TIN CƠ BẢN ---
    int getSize() const;
    bool isEmpty() const;
    Node* getHead() const;
    Node* getTail() const;
    Node* getNodeAt(int lineIndex) const; // Lấy Node tại dòng lineIndex (Tối ưu duyệt O(N/2))
    std::string getLine(int lineIndex) const;
    bool setLine(int lineIndex, const std::string& text);

    // --- THAO TÁC THÊM, XÓA DÒNG ---
    void insertLine(int lineIndex, const std::string& text);
    void appendLine(const std::string& text);
    void prependLine(const std::string& text);
    void deleteLine(int lineIndex);
    void clear(); // Thu hồi toàn bộ RAM của tất cả Node

    // --- CÁC THAO TÁC ĐẶC THÙ CỦA TRÌNH SOẠN THẢO (CORE EDITOR) ---
    // 1. Tách dòng (Nhấn phím Enter tại vị trí colIndex trên dòng)
    void splitLine(int lineIndex, int colIndex);

    // 2. Gộp dòng (Nhấn Backspace tại đầu dòng để gộp dòng hiện tại vào cuối dòng trước)
    void mergeLines(int lineIndex);

    // 3. Chèn ký tự đơn tại vị trí (line, col)
    void insertChar(int lineIndex, int colIndex, char ch);

    // 4. Xóa ký tự tại vị trí (Delete key: xóa tại col, nếu cuối dòng thì gộp dòng kế tiếp)
    void deleteChar(int lineIndex, int colIndex);

    // 5. Xóa lùi ký tự (Backspace key: xóa trước col, nếu đầu dòng thì gộp dòng với dòng trước)
    void backspaceChar(int lineIndex, int colIndex);

    // 6. Chèn đoạn chuỗi tại vị trí (hỗ trợ cả chuỗi nhiều dòng có chứa '\n')
    void insertTextAt(int lineIndex, int colIndex, const std::string& text);

    // 7. Xóa một đoạn văn bản từ vị trí bắt đầu đến kết thúc
    void deleteRange(int startLine, int startCol, int endLine, int endCol);

    // --- SAO CHÉP, CẮT, DÁN (CLIPBOARD OPERATIONS) ---
    std::string copyRange(int startLine, int startCol, int endLine, int endCol) const;
    std::string cutRange(int startLine, int startCol, int endLine, int endCol);
    void pasteText(int lineIndex, int colIndex, const std::string& text);

    // --- DI CHUYỂN CON TRỎ (CURSOR NAVIGATION) ---
    void moveCursorUp(int& line, int& col) const;
    void moveCursorDown(int& line, int& col) const;
    void moveCursorLeft(int& line, int& col) const;
    void moveCursorRight(int& line, int& col) const;
    void clampCursor(int& line, int& col) const;

    // --- TÌM KIẾM & THAY THẾ (FIND & REPLACE - TỰ CÀI ĐẶT THUẬT TOÁN, KHÔNG DÙNG STL FIND) ---
    // Thuật toán so khớp chuỗi con tự viết (Hỗ trợ phân biệt hoa/thường)
    static int customStringFind(const std::string& source, const std::string& pattern, int startPos = 0, bool matchCase = true);

    // Tìm kiếm vị trí đầu tiên xuất hiện
    bool findFirst(const std::string& keyword, int& foundLine, int& foundCol, bool matchCase = true) const;

    // Tìm kiếm vị trí tiếp theo từ con trỏ hiện tại
    bool findNext(const std::string& keyword, int currentLine, int currentCol, int& foundLine, int& foundCol, bool matchCase = true) const;

    // Tìm tất cả vị trí (trả về danh sách liên kết đơn SearchResult, tự quản lý bộ nhớ)
    SearchResult* findAll(const std::string& keyword, int& totalCount, bool matchCase = true) const;
    static void freeSearchResults(SearchResult* headList);

    // Thay thế tại vị trí cụ thể
    bool replaceAt(int lineIndex, int colIndex, int length, const std::string& replacement);

    // Thay thế tất cả các lần xuất hiện
    int replaceAll(const std::string& target, const std::string& replacement, bool matchCase = true);

    // --- THỐNG KÊ VĂN BẢN (STATISTICS) ---
    TextStatistics getStatistics() const;
    int getWordCount() const;
    int getLineCount() const;
    int getCharCount(bool includeWhitespace = true) const;

    // --- ĐỌC & GHI FILE (FILE I/O) ---
    bool loadFromFile(const std::string& filePath);
    bool saveToFile(const std::string& filePath) const;
    std::string getAllText() const; // Nạp toàn bộ văn bản thành string (nối bằng \r\n cho GUI)
    void loadFromText(const std::string& fullText); // Cập nhật DSLK từ chuỗi RichTextBox

    // --- HỖ TRỢ TRỰC QUAN HÓA (VISUALIZER CHO THÀNH VIÊN 1) ---
    bool getNodeVisualInfo(int lineIndex, std::string& text, uintptr_t& selfAddr, uintptr_t& prevAddr, uintptr_t& nextAddr) const;

    // --- IN CONSOLE KIỂM THỬ ---
    void printAllLines() const;
};

#endif // DOUBLY_LINKED_LIST_H
