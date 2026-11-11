#include "DoublyLinkedList.h"
#include <fstream>
#include <cctype>

// ============================================================================
// 1. KHỞI TẠO, HỦY VÀ SAO CHÉP (CONSTRUCTOR, DESTRUCTOR & RULE OF THREE)
// ============================================================================

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear(); // Giải phóng toàn bộ bộ nhớ động khi hủy đối tượng
}

// Deep Copy Constructor: Sao chép sâu để tránh lỗi con trỏ trùng lặp (Double Free)
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other)
    : head(nullptr), tail(nullptr), size(0) {
    Node* curr = other.head;
    while (curr != nullptr) {
        appendLine(curr->lineData);
        curr = curr->next;
    }
}

// Deep Copy Assignment Operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other) {
    if (this == &other) {
        return *this; // Tránh tự gán chính mình
    }
    clear(); // Dọn sạch bộ nhớ hiện tại
    Node* curr = other.head;
    while (curr != nullptr) {
        appendLine(curr->lineData);
        curr = curr->next;
    }
    return *this;
}

// Thu hồi RAM của toàn bộ các Node trong DSLK
void DoublyLinkedList::clear() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        delete curr; // Giải phóng Node hiện tại
        curr = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// ============================================================================
// 2. CÁC HÀM TRUY XUẤT THÔNG TIN CƠ BẢN
// ============================================================================

int DoublyLinkedList::getSize() const {
    return size;
}

bool DoublyLinkedList::isEmpty() const {
    return size == 0;
}

Node* DoublyLinkedList::getHead() const {
    return head;
}

Node* DoublyLinkedList::getTail() const {
    return tail;
}

// Tối ưu hóa truy cập theo chỉ số dòng (0-indexed):
// Nếu dòng ở nửa đầu -> duyệt từ Head xuôi xuống: O(N/2)
// Nếu dòng ở nửa sau -> duyệt từ Tail ngược lên: O(N/2)
Node* DoublyLinkedList::getNodeAt(int lineIndex) const {
    if (lineIndex < 0 || lineIndex >= size) return nullptr;

    if (lineIndex < size / 2) {
        Node* curr = head;
        for (int i = 0; i < lineIndex; ++i) {
            curr = curr->next;
        }
        return curr;
    } else {
        Node* curr = tail;
        for (int i = size - 1; i > lineIndex; --i) {
            curr = curr->prev;
        }
        return curr;
    }
}

std::string DoublyLinkedList::getLine(int lineIndex) const {
    Node* node = getNodeAt(lineIndex);
    if (node != nullptr) {
        return node->lineData;
    }
    return "";
}

bool DoublyLinkedList::setLine(int lineIndex, const std::string& text) {
    Node* node = getNodeAt(lineIndex);
    if (node != nullptr) {
        node->lineData = text;
        return true;
    }
    return false;
}

// ============================================================================
// 3. THAO TÁC THÊM VÀ XÓA DÒNG (NODE OPERATIONS)
// ============================================================================

void DoublyLinkedList::appendLine(const std::string& text) {
    Node* newNode = new Node(text);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

void DoublyLinkedList::prependLine(const std::string& text) {
    Node* newNode = new Node(text);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

void DoublyLinkedList::insertLine(int lineIndex, const std::string& text) {
    if (lineIndex <= 0) {
        prependLine(text);
    } else if (lineIndex >= size) {
        appendLine(text);
    } else {
        Node* curr = getNodeAt(lineIndex); // Node hiện tại đang ở vị trí lineIndex
        Node* newNode = new Node(text);

        // Chèn newNode vào giữa curr->prev và curr
        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev->next = newNode;
        curr->prev = newNode;

        size++;
    }
}

void DoublyLinkedList::deleteLine(int lineIndex) {
    Node* curr = getNodeAt(lineIndex);
    if (curr == nullptr) return;

    if (curr == head && curr == tail) {
        head = tail = nullptr;
    } else if (curr == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (curr == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    delete curr; // Thu hồi RAM lập tức
    size--;
}

// ============================================================================
// 4. CÁC THAO TÁC CỐT LÕI CỦA TRÌNH SOẠN THẢO (SPLIT, MERGE, CHAR EDITING)
// ============================================================================

// Tách dòng tại vị trí cột colIndex (Mô phỏng phím Enter)
// Độ phức tạp: O(1) sau khi trỏ tới Node
void DoublyLinkedList::splitLine(int lineIndex, int colIndex) {
    Node* curr = getNodeAt(lineIndex);
    if (curr == nullptr) return;

    int lineLen = (int)curr->lineData.length();
    if (colIndex < 0) colIndex = 0;
    if (colIndex > lineLen) colIndex = lineLen;

    // Cắt chuỗi thành 2 phần
    std::string firstPart = curr->lineData.substr(0, colIndex);
    std::string secondPart = curr->lineData.substr(colIndex);

    curr->lineData = firstPart;

    // Tạo Node mới chứa phần sau và nối trực tiếp sau curr (O(1))
    Node* newNode = new Node(secondPart);
    newNode->prev = curr;
    newNode->next = curr->next;

    if (curr->next != nullptr) {
        curr->next->prev = newNode;
    } else {
        tail = newNode;
    }
    curr->next = newNode;
    size++;
}

// Gộp dòng lineIndex vào cuối dòng lineIndex - 1 (Mô phỏng phím Backspace đầu dòng)
// Độ phức tạp: O(1) sau khi trỏ tới Node
void DoublyLinkedList::mergeLines(int lineIndex) {
    if (lineIndex <= 0 || lineIndex >= size) return;

    Node* prevNode = getNodeAt(lineIndex - 1);
    if (prevNode == nullptr) return;
    Node* currNode = prevNode->next;
    if (currNode == nullptr) return;

    // Nối nội dung
    prevNode->lineData += currNode->lineData;

    // Tách currNode ra khỏi liên kết
    prevNode->next = currNode->next;
    if (currNode->next != nullptr) {
        currNode->next->prev = prevNode;
    } else {
        tail = prevNode;
    }

    delete currNode; // Thu hồi RAM
    size--;
}

// Chèn 1 ký tự tại (lineIndex, colIndex)
void DoublyLinkedList::insertChar(int lineIndex, int colIndex, char ch) {
    if (size == 0) {
        appendLine(std::string(1, ch));
        return;
    }
    Node* curr = getNodeAt(lineIndex);
    if (curr == nullptr) return;

    int lineLen = (int)curr->lineData.length();
    if (colIndex < 0) colIndex = 0;
    if (colIndex > lineLen) colIndex = lineLen;

    curr->lineData.insert(colIndex, 1, ch);
}

// Xóa ký tự tại vị trí con trỏ (Delete key)
void DoublyLinkedList::deleteChar(int lineIndex, int colIndex) {
    Node* curr = getNodeAt(lineIndex);
    if (curr == nullptr) return;

    int lineLen = (int)curr->lineData.length();
    if (colIndex >= 0 && colIndex < lineLen) {
        curr->lineData.erase(colIndex, 1);
    } else if (colIndex == lineLen && lineIndex < size - 1) {
        // Con trỏ đang ở cuối dòng, bấm Delete -> gộp dòng kế tiếp lên
        mergeLines(lineIndex + 1);
    }
}

// Xóa lùi ký tự trước vị trí con trỏ (Backspace key)
void DoublyLinkedList::backspaceChar(int lineIndex, int colIndex) {
    Node* curr = getNodeAt(lineIndex);
    if (curr == nullptr) return;

    if (colIndex > 0 && colIndex <= (int)curr->lineData.length()) {
        curr->lineData.erase(colIndex - 1, 1);
    } else if (colIndex == 0 && lineIndex > 0) {
        // Con trỏ ở đầu dòng, bấm Backspace -> gộp dòng hiện tại vào dòng trước
        mergeLines(lineIndex);
    }
}

// Chèn chuỗi tại (lineIndex, colIndex), hỗ trợ chuỗi có ký tự xuống dòng '\n'
void DoublyLinkedList::insertTextAt(int lineIndex, int colIndex, const std::string& text) {
    if (text.empty()) return;
    if (size == 0) {
        appendLine("");
    }
    Node* curr = getNodeAt(lineIndex);
    if (curr == nullptr) return;

    int lineLen = (int)curr->lineData.length();
    if (colIndex < 0) colIndex = 0;
    if (colIndex > lineLen) colIndex = lineLen;

    // Kiểm tra xem chuỗi có chứa ký tự xuống dòng hay không
    bool hasNewline = false;
    for (char c : text) {
        if (c == '\n') {
            hasNewline = true;
            break;
        }
    }

    if (!hasNewline) {
        curr->lineData.insert(colIndex, text);
        return;
    }

    // Nếu có xuống dòng: Tách dòng tại colIndex, sau đó chèn các dòng trung gian
    std::string prefix = curr->lineData.substr(0, colIndex);
    std::string suffix = curr->lineData.substr(colIndex);

    std::string currentLineText = "";
    bool isFirstLine = true;
    Node* insertPoint = curr;

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (c == '\r') continue; // Bỏ qua ký tự carriage return

        if (c == '\n') {
            if (isFirstLine) {
                curr->lineData = prefix + currentLineText;
                isFirstLine = false;
            } else {
                Node* nextNode = new Node(currentLineText);
                nextNode->prev = insertPoint;
                nextNode->next = insertPoint->next;
                if (insertPoint->next != nullptr) {
                    insertPoint->next->prev = nextNode;
                } else {
                    tail = nextNode;
                }
                insertPoint->next = nextNode;
                insertPoint = nextNode;
                size++;
            }
            currentLineText.clear();
        } else {
            currentLineText += c;
        }
    }

    // Dòng cuối cùng được ghép với suffix
    if (isFirstLine) {
        curr->lineData = prefix + currentLineText + suffix;
    } else {
        Node* nextNode = new Node(currentLineText + suffix);
        nextNode->prev = insertPoint;
        nextNode->next = insertPoint->next;
        if (insertPoint->next != nullptr) {
            insertPoint->next->prev = nextNode;
        } else {
            tail = nextNode;
        }
        insertPoint->next = nextNode;
        size++;
    }
}

// Xóa một đoạn văn bản từ (startLine, startCol) đến (endLine, endCol)
void DoublyLinkedList::deleteRange(int startLine, int startCol, int endLine, int endCol) {
    if (startLine > endLine || (startLine == endLine && startCol >= endCol)) return;
    if (startLine < 0 || endLine >= size) return;

    Node* startNode = getNodeAt(startLine);
    Node* endNode = getNodeAt(endLine);
    if (startNode == nullptr || endNode == nullptr) return;

    if (startLine == endLine) {
        if (startCol < 0) startCol = 0;
        if (endCol > (int)startNode->lineData.length()) endCol = (int)startNode->lineData.length();
        startNode->lineData.erase(startCol, endCol - startCol);
        return;
    }

    // Khác dòng: ghép đầu startLine với đuôi endLine, xóa tất cả các dòng ở giữa
    std::string prefix = (startCol < (int)startNode->lineData.length())
                         ? startNode->lineData.substr(0, startCol) : startNode->lineData;
    std::string suffix = (endCol < (int)endNode->lineData.length())
                         ? endNode->lineData.substr(endCol) : "";

    startNode->lineData = prefix + suffix;

    // Xóa từ dòng startLine + 1 đến endLine (tổng cộng endLine - startLine dòng)
    for (int i = 0; i < (endLine - startLine); ++i) {
        deleteLine(startLine + 1);
    }
}

// ============================================================================
// 5. SAO CHÉP, CẮT VÀ DÁN (CLIPBOARD OPERATIONS)
// ============================================================================

std::string DoublyLinkedList::copyRange(int startLine, int startCol, int endLine, int endCol) const {
    if (startLine > endLine || (startLine == endLine && startCol >= endCol)) return "";
    if (startLine < 0 || endLine >= size) return "";

    std::string result = "";
    Node* curr = getNodeAt(startLine);
    if (curr == nullptr) return "";

    if (startLine == endLine) {
        int lineLen = (int)curr->lineData.length();
        if (startCol < 0) startCol = 0;
        if (endCol > lineLen) endCol = lineLen;
        return curr->lineData.substr(startCol, endCol - startCol);
    }

    // Dòng đầu
    int lineLen = (int)curr->lineData.length();
    if (startCol < lineLen) {
        result += curr->lineData.substr(startCol);
    }
    result += "\n";
    curr = curr->next;

    // Các dòng ở giữa
    for (int l = startLine + 1; l < endLine && curr != nullptr; ++l) {
        result += curr->lineData;
        result += "\n";
        curr = curr->next;
    }

    // Dòng cuối
    if (curr != nullptr) {
        int endLen = (int)curr->lineData.length();
        if (endCol > endLen) endCol = endLen;
        if (endCol > 0) {
            result += curr->lineData.substr(0, endCol);
        }
    }

    return result;
}

std::string DoublyLinkedList::cutRange(int startLine, int startCol, int endLine, int endCol) {
    std::string text = copyRange(startLine, startCol, endLine, endCol);
    deleteRange(startLine, startCol, endLine, endCol);
    return text;
}

void DoublyLinkedList::pasteText(int lineIndex, int colIndex, const std::string& text) {
    insertTextAt(lineIndex, colIndex, text);
}

// ============================================================================
// 6. ĐIỀU HƯỚNG CON TRỎ (CURSOR NAVIGATION)
// ============================================================================

void DoublyLinkedList::clampCursor(int& line, int& col) const {
    if (size == 0) {
        line = 0;
        col = 0;
        return;
    }
    if (line < 0) line = 0;
    if (line >= size) line = size - 1;

    Node* node = getNodeAt(line);
    int maxCol = node ? (int)node->lineData.length() : 0;
    if (col < 0) col = 0;
    if (col > maxCol) col = maxCol;
}

void DoublyLinkedList::moveCursorUp(int& line, int& col) const {
    if (line > 0) {
        line--;
        clampCursor(line, col);
    }
}

void DoublyLinkedList::moveCursorDown(int& line, int& col) const {
    if (line < size - 1) {
        line++;
        clampCursor(line, col);
    }
}

void DoublyLinkedList::moveCursorLeft(int& line, int& col) const {
    if (col > 0) {
        col--;
    } else if (line > 0) {
        // Lùi về cuối dòng phía trên
        line--;
        Node* node = getNodeAt(line);
        col = node ? (int)node->lineData.length() : 0;
    }
}

void DoublyLinkedList::moveCursorRight(int& line, int& col) const {
    Node* node = getNodeAt(line);
    int maxCol = node ? (int)node->lineData.length() : 0;
    if (col < maxCol) {
        col++;
    } else if (line < size - 1) {
        // Tiến tới đầu dòng phía dưới
        line++;
        col = 0;
    }
}

// ============================================================================
// 7. TÌM KIẾM VÀ THAY THẾ (TỰ CÀI ĐẶT THUẬT TOÁN, KHÔNG DÙNG STL FIND)
// ============================================================================

// Thuật toán so khớp chuỗi con (String Pattern Matching)
// Không dùng std::find, kiểm tra từng ký tự, hỗ trợ case-sensitive và case-insensitive
int DoublyLinkedList::customStringFind(const std::string& source, const std::string& pattern, int startPos, bool matchCase) {
    int n = (int)source.length();
    int m = (int)pattern.length();

    if (m == 0) return startPos <= n ? startPos : -1;
    if (n == 0 || m > n || startPos < 0 || startPos > n - m) return -1;

    for (int i = startPos; i <= n - m; ++i) {
        bool match = true;
        for (int j = 0; j < m; ++j) {
            char c1 = source[i + j];
            char c2 = pattern[j];
            if (!matchCase) {
                c1 = (char)std::tolower((unsigned char)c1);
                c2 = (char)std::tolower((unsigned char)c2);
            }
            if (c1 != c2) {
                match = false;
                break;
            }
        }
        if (match) return i; // Tìm thấy vị trí bắt đầu
    }
    return -1; // Không tìm thấy
}

bool DoublyLinkedList::findFirst(const std::string& keyword, int& foundLine, int& foundCol, bool matchCase) const {
    if (keyword.empty()) return false;

    Node* curr = head;
    int lineIdx = 0;
    while (curr != nullptr) {
        int pos = customStringFind(curr->lineData, keyword, 0, matchCase);
        if (pos != -1) {
            foundLine = lineIdx;
            foundCol = pos;
            return true;
        }
        curr = curr->next;
        lineIdx++;
    }
    return false;
}

// Tìm vị trí tiếp theo từ con trỏ hiện tại (Hỗ trợ nút "Tìm tiếp" / Find Next trên GUI)
bool DoublyLinkedList::findNext(const std::string& keyword, int currentLine, int currentCol, int& foundLine, int& foundCol, bool matchCase) const {
    if (keyword.empty() || size == 0) return false;

    if (currentLine < 0) currentLine = 0;
    if (currentLine >= size) return false;

    Node* curr = getNodeAt(currentLine);
    if (curr == nullptr) return false;

    // 1. Tìm trên phần còn lại của dòng hiện tại (bắt đầu từ currentCol + 1)
    int searchStart = currentCol + 1;
    if (searchStart < (int)curr->lineData.length()) {
        int pos = customStringFind(curr->lineData, keyword, searchStart, matchCase);
        if (pos != -1) {
            foundLine = currentLine;
            foundCol = pos;
            return true;
        }
    }

    // 2. Tìm tiếp ở các dòng kế tiếp
    int lineIdx = currentLine + 1;
    curr = curr->next;
    while (curr != nullptr) {
        int pos = customStringFind(curr->lineData, keyword, 0, matchCase);
        if (pos != -1) {
            foundLine = lineIdx;
            foundCol = pos;
            return true;
        }
        curr = curr->next;
        lineIdx++;
    }

    // 3. Vòng tròn lại từ đầu văn bản (Wrap around) đến vị trí bắt đầu
    curr = head;
    lineIdx = 0;
    while (curr != nullptr && lineIdx <= currentLine) {
        int endPos = (lineIdx == currentLine) ? currentCol : (int)curr->lineData.length();
        int pos = customStringFind(curr->lineData, keyword, 0, matchCase);
        if (pos != -1 && (lineIdx < currentLine || pos <= endPos)) {
            foundLine = lineIdx;
            foundCol = pos;
            return true;
        }
        curr = curr->next;
        lineIdx++;
    }

    return false;
}

// Tìm tất cả vị trí: Lưu trong danh sách liên kết đơn SearchResult tự quản lý RAM
SearchResult* DoublyLinkedList::findAll(const std::string& keyword, int& totalCount, bool matchCase) const {
    totalCount = 0;
    if (keyword.empty()) return nullptr;

    SearchResult* headRes = nullptr;
    SearchResult* tailRes = nullptr;

    Node* curr = head;
    int lineIdx = 0;
    int kwLen = (int)keyword.length();

    while (curr != nullptr) {
        int startPos = 0;
        int lineLen = (int)curr->lineData.length();

        while (startPos <= lineLen - kwLen) {
            int pos = customStringFind(curr->lineData, keyword, startPos, matchCase);
            if (pos == -1) break;

            SearchResult* newRes = new SearchResult(lineIdx, pos, kwLen);
            if (headRes == nullptr) {
                headRes = tailRes = newRes;
            } else {
                tailRes->next = newRes;
                tailRes = newRes;
            }
            totalCount++;
            startPos = pos + kwLen; // Chuyển qua từ khóa vừa tìm thấy
        }

        curr = curr->next;
        lineIdx++;
    }

    return headRes;
}

void DoublyLinkedList::freeSearchResults(SearchResult* headList) {
    SearchResult* curr = headList;
    while (curr != nullptr) {
        SearchResult* temp = curr;
        curr = curr->next;
        delete temp; // Giải phóng RAM kết quả tìm kiếm
    }
}

// Thay thế chuỗi tại vị trí cụ thể (Hỗ trợ nút "Thay thế" trên GUI)
bool DoublyLinkedList::replaceAt(int lineIndex, int colIndex, int length, const std::string& replacement) {
    Node* node = getNodeAt(lineIndex);
    if (node == nullptr) return false;

    int lineLen = (int)node->lineData.length();
    if (colIndex < 0 || colIndex + length > lineLen) return false;

    node->lineData.replace(colIndex, length, replacement);
    return true;
}

// Thay thế tất cả (Hỗ trợ nút "Thay thế tất cả" trên GUI)
int DoublyLinkedList::replaceAll(const std::string& target, const std::string& replacement, bool matchCase) {
    if (target.empty()) return 0;

    int replaceCount = 0;
    Node* curr = head;
    int targetLen = (int)target.length();
    int repLen = (int)replacement.length();

    while (curr != nullptr) {
        int pos = 0;
        while (pos <= (int)curr->lineData.length() - targetLen) {
            int foundPos = customStringFind(curr->lineData, target, pos, matchCase);
            if (foundPos == -1) break;

            curr->lineData.replace(foundPos, targetLen, replacement);
            pos = foundPos + repLen;
            replaceCount++;
        }
        curr = curr->next;
    }

    return replaceCount;
}

// ============================================================================
// 8. THỐNG KÊ VĂN BẢN (STATISTICS)
// ============================================================================

TextStatistics DoublyLinkedList::getStatistics() const {
    TextStatistics stats;
    stats.lineCount = size;
    stats.wordCount = 0;
    stats.charCount = 0;
    stats.charNoSpaceCount = 0;

    Node* curr = head;
    while (curr != nullptr) {
        const std::string& line = curr->lineData;
        int len = (int)line.length();

        stats.charCount += len;
        // Mỗi dòng có 1 ký tự xuống dòng (trừ dòng cuối)
        if (curr != tail) {
            stats.charCount += 1;
        }

        bool inWord = false;
        for (int i = 0; i < len; ++i) {
            char c = line[i];
            if (std::isspace((unsigned char)c)) {
                inWord = false;
            } else {
                stats.charNoSpaceCount++;
                if (!inWord) {
                    inWord = true;
                    stats.wordCount++; // Bắt đầu một từ mới
                }
            }
        }

        curr = curr->next;
    }

    return stats;
}

int DoublyLinkedList::getWordCount() const {
    return getStatistics().wordCount;
}

int DoublyLinkedList::getLineCount() const {
    return size;
}

int DoublyLinkedList::getCharCount(bool includeWhitespace) const {
    TextStatistics s = getStatistics();
    return includeWhitespace ? s.charCount : s.charNoSpaceCount;
}

// ============================================================================
// 9. ĐỌC / GHI FILE VÀ ĐỒNG BỘ VĂN BẢN
// ============================================================================

bool DoublyLinkedList::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    clear(); // Dọn sạch nội dung cũ

    std::string line;
    while (std::getline(file, line)) {
        // Loại bỏ ký tự '\r' nếu tệp có định dạng Windows CRLF
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        appendLine(line);
    }

    file.close();

    // Luôn đảm bảo có ít nhất 1 dòng rỗng nếu mở file trống
    if (isEmpty()) {
        appendLine("");
    }

    return true;
}

bool DoublyLinkedList::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    Node* curr = head;
    while (curr != nullptr) {
        file << curr->lineData;
        if (curr->next != nullptr) {
            file << "\n";
        }
        curr = curr->next;
    }

    file.close();
    return true;
}

// Nạp toàn bộ nội dung thành 1 chuỗi ký tự (sử dụng định dạng \r\n tương thích Windows Forms)
std::string DoublyLinkedList::getAllText() const {
    std::string result = "";
    Node* curr = head;
    while (curr != nullptr) {
        result += curr->lineData;
        if (curr->next != nullptr) {
            result += "\r\n";
        }
        curr = curr->next;
    }
    return result;
}

// Cập nhật DSLK kép từ chuỗi văn bản nhận được từ RichTextBox
void DoublyLinkedList::loadFromText(const std::string& fullText) {
    clear();
    if (fullText.empty()) {
        appendLine("");
        return;
    }

    std::string currentLine = "";
    for (size_t i = 0; i < fullText.length(); ++i) {
        char c = fullText[i];
        if (c == '\r') continue; // Bỏ qua \r
        if (c == '\n') {
            appendLine(currentLine);
            currentLine.clear();
        } else {
            currentLine += c;
        }
    }
    appendLine(currentLine);
}

// ============================================================================
// 10. HỖ TRỢ TRỰC QUAN HÓA (VISUALIZER CHO THÀNH VIÊN 1)
// ============================================================================

bool DoublyLinkedList::getNodeVisualInfo(int lineIndex, std::string& text, uintptr_t& selfAddr, uintptr_t& prevAddr, uintptr_t& nextAddr) const {
    Node* node = getNodeAt(lineIndex);
    if (node == nullptr) return false;

    text = node->lineData;
    selfAddr = reinterpret_cast<uintptr_t>(node);
    prevAddr = reinterpret_cast<uintptr_t>(node->prev);
    nextAddr = reinterpret_cast<uintptr_t>(node->next);
    return true;
}

// ============================================================================
// 11. IN CONSOLE KIỂM THỬ (TEST CONSOLE)
// ============================================================================

void DoublyLinkedList::printAllLines() const {
    std::cout << "--- NOI DUNG VAN BAN (Tong: " << size << " dong) ---" << std::endl;
    Node* curr = head;
    int lineNum = 1;
    while (curr != nullptr) {
        std::cout << "Dong " << lineNum << " [" << curr << " | Prev:" << curr->prev << " | Next:" << curr->next << "]: "
                  << "\"" << curr->lineData << "\"" << std::endl;
        curr = curr->next;
        lineNum++;
    }
    std::cout << "---------------------------------------------------------" << std::endl;
}
