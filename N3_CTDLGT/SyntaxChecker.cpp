#include "SyntaxChecker.h"

// ============================================================================
// 1. CÀI ĐẶT NGĂN XẾP BRACKETSTACK (RULE OF THREE)
// ============================================================================

BracketStack::BracketStack() : topNode(nullptr), count(0) {}

BracketStack::~BracketStack() {
    clear();
}

BracketStack::BracketStack(const BracketStack& other) : topNode(nullptr), count(0) {
    copyFrom(other);
}

BracketStack& BracketStack::operator=(const BracketStack& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    copyFrom(other);
    return *this;
}

void BracketStack::copyFrom(const BracketStack& other) {
    // Giữ đúng thứ tự từ đỉnh xuống đáy bằng cách nối tiếp ở đuôi bản sao
    BracketNode* tailCopy = nullptr;
    const BracketNode* curr = other.topNode;

    while (curr != nullptr) {
        BracketNode* newNode = new BracketNode(curr->data);
        if (topNode == nullptr) {
            topNode = tailCopy = newNode;
        } else {
            tailCopy->next = newNode;
            tailCopy = newNode;
        }
        count++;
        curr = curr->next;
    }
}

void BracketStack::push(const BracketItem& item) {
    BracketNode* newNode = new BracketNode(item);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

bool BracketStack::pop(BracketItem& outItem) {
    if (isEmpty()) {
        return false;
    }

    BracketNode* target = topNode;
    outItem = target->data;
    topNode = topNode->next;

    delete target;
    count--;
    return true;
}

bool BracketStack::peek(BracketItem& outItem) const {
    if (isEmpty()) {
        return false;
    }
    outItem = topNode->data;
    return true;
}

bool BracketStack::isEmpty() const {
    return count == 0;
}

int BracketStack::getSize() const {
    return count;
}

void BracketStack::clear() {
    BracketNode* curr = topNode;
    while (curr != nullptr) {
        BracketNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    topNode = nullptr;
    count = 0;
}

// ============================================================================
// 2. HÀM TIỆN ÍCH KIỂM TRA KÝ TỰ NGOẶC
// ============================================================================

bool SyntaxChecker::isOpeningBracket(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

bool SyntaxChecker::isClosingBracket(char ch) {
    return ch == ')' || ch == '}' || ch == ']';
}

char SyntaxChecker::getMatchingClosing(char openBracket) {
    switch (openBracket) {
        case '(': return ')';
        case '{': return '}';
        case '[': return ']';
        default:  return '\0';
    }
}

char SyntaxChecker::getMatchingOpening(char closeBracket) {
    switch (closeBracket) {
        case ')': return '(';
        case '}': return '{';
        case ']': return '[';
        default:  return '\0';
    }
}

bool SyntaxChecker::isMatchingPair(char openBracket, char closeBracket) {
    return (openBracket == '(' && closeBracket == ')') ||
           (openBracket == '{' && closeBracket == '}') ||
           (openBracket == '[' && closeBracket == ']');
}

// ============================================================================
// 3. GIẢI THUẬT QUÉT VÀ KIỂM TRA CÂN BẰNG NGOẶC () [] {}
// ============================================================================

void SyntaxChecker::scanLine(const std::string& lineText, int lineIndex, ScannerState& state) {
    size_t len = lineText.length();
    bool inString = false;
    bool inChar = false;
    bool escaped = false;
    int col = -1; // Cột 0-based (bỏ qua '\r')

    for (size_t i = 0; i < len; ++i) {
        char c = lineText[i];
        if (c == '\r') {
            continue;
        }
        col++;

        if (state.ignoreStringsAndComments) {
            if (state.inBlockComment) {
                if (c == '*' && i + 1 < len && lineText[i + 1] == '/') {
                    state.inBlockComment = false;
                    i++;
                    col++;
                }
                continue;
            }

            if (inString) {
                if (escaped) {
                    escaped = false;
                } else if (c == '\\') {
                    escaped = true;
                } else if (c == '"') {
                    inString = false;
                }
                continue;
            }

            if (inChar) {
                if (escaped) {
                    escaped = false;
                } else if (c == '\\') {
                    escaped = true;
                } else if (c == '\'') {
                    inChar = false;
                }
                continue;
            }

            if (c == '/' && i + 1 < len) {
                if (lineText[i + 1] == '/') {
                    // Phần còn lại của dòng là chú thích //
                    break;
                }
                if (lineText[i + 1] == '*') {
                    state.inBlockComment = true;
                    i++;
                    col++;
                    continue;
                }
            }

            if (c == '"') {
                inString = true;
                continue;
            }

            if (c == '\'') {
                inChar = true;
                continue;
            }
        }

        // Đếm số lượng từng loại ngoặc hợp lệ ngoài chuỗi/chú thích
        if (c == '(') state.result.roundOpenCount++;
        else if (c == ')') state.result.roundCloseCount++;
        else if (c == '{') state.result.curlyOpenCount++;
        else if (c == '}') state.result.curlyCloseCount++;
        else if (c == '[') state.result.squareOpenCount++;
        else if (c == ']') state.result.squareCloseCount++;

        if (isOpeningBracket(c)) {
            state.stack.push(BracketItem(c, lineIndex, col));
        } else if (isClosingBracket(c)) {
            if (state.stack.isEmpty()) {
                if (!state.hasFirstError) {
                    state.hasFirstError = true;
                    state.result.isBalanced = false;
                    state.result.errorType = BracketErrorType::UNMATCHED_CLOSING;
                    state.result.errorLine = lineIndex;
                    state.result.errorCol = col;
                    state.result.foundChar = c;
                    state.result.expectedChar = getMatchingOpening(c);
                    state.result.openLine = -1;
                    state.result.openCol = -1;
                }
            } else {
                BracketItem topItem;
                state.stack.peek(topItem);
                if (isMatchingPair(topItem.bracket, c)) {
                    BracketItem popped;
                    state.stack.pop(popped);
                } else {
                    if (!state.hasFirstError) {
                        state.hasFirstError = true;
                        state.result.isBalanced = false;
                        state.result.errorType = BracketErrorType::MISMATCHED_PAIR;
                        state.result.errorLine = lineIndex;
                        state.result.errorCol = col;
                        state.result.foundChar = c;
                        state.result.expectedChar = getMatchingClosing(topItem.bracket);
                        state.result.openLine = topItem.line;
                        state.result.openCol = topItem.col;
                    }
                }
            }
        }
    }
}

void SyntaxChecker::finalizeResult(ScannerState& state) {
    if (!state.hasFirstError) {
        if (state.stack.isEmpty()) {
            state.result.isBalanced = true;
            state.result.errorType = BracketErrorType::NONE;
            state.result.message = "Ngoặc cân bằng!";
            return;
        }

        BracketItem unclosed;
        state.stack.peek(unclosed);

        state.result.isBalanced = false;
        state.result.errorType = BracketErrorType::UNCLOSED_OPENING;
        state.result.errorLine = unclosed.line;
        state.result.errorCol = unclosed.col;
        state.result.foundChar = unclosed.bracket;
        state.result.expectedChar = getMatchingClosing(unclosed.bracket);
        state.result.openLine = unclosed.line;
        state.result.openCol = unclosed.col;
    }

    // errorLine, errorCol, openLine, openCol là 0-based; cộng 1 khi tạo thông báo cho người dùng
    std::string lineStr = std::to_string(state.result.errorLine + 1);
    std::string colStr = std::to_string(state.result.errorCol + 1);

    if (state.result.errorType == BracketErrorType::UNMATCHED_CLOSING) {
        state.result.message = "Dư ngoặc đóng '" + std::string(1, state.result.foundChar)
            + "' tại dòng " + lineStr + ", cột " + colStr
            + " (không có ngoặc mở '" + std::string(1, state.result.expectedChar) + "' tương ứng).";
    } else if (state.result.errorType == BracketErrorType::MISMATCHED_PAIR) {
        state.result.message = "Sai cặp ngoặc tại dòng " + lineStr + ", cột " + colStr
            + ": gặp '" + std::string(1, state.result.foundChar)
            + "', cần '" + std::string(1, state.result.expectedChar)
            + "' (mở tại dòng " + std::to_string(state.result.openLine + 1)
            + ", cột " + std::to_string(state.result.openCol + 1) + ").";
    } else if (state.result.errorType == BracketErrorType::UNCLOSED_OPENING) {
        state.result.message = "Thiếu ngoặc đóng '" + std::string(1, state.result.expectedChar)
            + "' cho ngoặc mở '" + std::string(1, state.result.foundChar)
            + "' tại dòng " + lineStr + ", cột " + colStr + ".";
    }
}

BracketCheckResult SyntaxChecker::checkText(const std::string& text, bool ignoreStringsAndComments) {
    ScannerState state(ignoreStringsAndComments);

    size_t start = 0;
    int lineIndex = 0;
    while (start <= text.length()) {
        size_t nlPos = text.find('\n', start);
        if (nlPos == std::string::npos) {
            scanLine(text.substr(start), lineIndex, state);
            break;
        }
        scanLine(text.substr(start, nlPos - start), lineIndex, state);
        start = nlPos + 1;
        lineIndex++;
    }

    finalizeResult(state);
    return state.result;
}

BracketCheckResult SyntaxChecker::checkDocument(const DoublyLinkedList& doc, bool ignoreStringsAndComments) {
    ScannerState state(ignoreStringsAndComments);

    const Node* curr = doc.getHead();
    int lineIndex = 0;
    while (curr != nullptr) {
        scanLine(curr->lineData, lineIndex, state);
        curr = curr->next;
        lineIndex++;
    }

    finalizeResult(state);
    return state.result;
}
