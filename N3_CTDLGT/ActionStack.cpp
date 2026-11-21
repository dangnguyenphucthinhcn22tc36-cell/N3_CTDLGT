#include "ActionStack.h"
#include <iostream>

namespace {

// Định dạng chuỗi xem trước ngắn gọn, thoát các ký tự điều khiển phổ biến
std::string formatPreview(const std::string& text, size_t maxLen = 12) {
    std::string escaped;
    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (c == '\n') {
            escaped += "\\n";
        } else if (c == '\r') {
            escaped += "\\r";
        } else if (c == '\t') {
            escaped += "\\t";
        } else {
            escaped += c;
        }
        if (escaped.length() > maxLen) {
            return escaped.substr(0, maxLen) + "...";
        }
    }
    return escaped;
}

} // namespace

// ============================================================================
// 1. KHỞI TẠO, HỦY VÀ SAO CHÉP (RULE OF THREE)
// ============================================================================

ActionStack::ActionStack(int maxCap)
    : topNode(nullptr),
      bottomNode(nullptr),
      count(0),
      maxCapacity(maxCap < 0 ? 0 : maxCap) {}

ActionStack::~ActionStack() {
    clear();
}

ActionStack::ActionStack(const ActionStack& other)
    : topNode(nullptr),
      bottomNode(nullptr),
      count(0),
      maxCapacity(other.maxCapacity) {
    copyFrom(other);
}

ActionStack& ActionStack::operator=(const ActionStack& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    maxCapacity = other.maxCapacity;
    copyFrom(other);
    return *this;
}

void ActionStack::copyFrom(const ActionStack& other) {
    // Duyệt từ đáy lên đỉnh để giữ nguyên thứ tự các thao tác khi push lại
    const ActionNode* curr = other.bottomNode;
    while (curr != nullptr) {
        push(curr->data);
        curr = curr->next;
    }
}

// ============================================================================
// 2. CÁC THAO TÁC NGĂN XẾP & HÀNG ĐỢI HAI ĐẦU O(1)
// ============================================================================

void ActionStack::push(const Action& action) {
    ActionNode* newNode = new ActionNode(action);
    if (isEmpty()) {
        topNode = bottomNode = newNode;
    } else {
        newNode->prev = topNode;
        topNode->next = newNode;
        topNode = newNode;
    }
    count++;

    // Khi giới hạn k > 0 bước được bật, loại bỏ phần tử cũ nhất ở đáy trong O(1)
    while (maxCapacity > 0 && count > maxCapacity) {
        popBottom();
    }
}

bool ActionStack::pop(Action& outAction) {
    if (isEmpty()) {
        return false;
    }

    ActionNode* target = topNode;
    outAction = target->data;

    if (topNode == bottomNode) {
        topNode = bottomNode = nullptr;
    } else {
        topNode = topNode->prev;
        topNode->next = nullptr;
    }

    delete target;
    count--;
    return true;
}

bool ActionStack::peek(Action& outAction) const {
    if (isEmpty()) {
        return false;
    }
    outAction = topNode->data;
    return true;
}

bool ActionStack::popBottom(Action& outAction) {
    if (isEmpty()) {
        return false;
    }

    ActionNode* target = bottomNode;
    outAction = target->data;

    if (topNode == bottomNode) {
        topNode = bottomNode = nullptr;
    } else {
        bottomNode = bottomNode->next;
        bottomNode->prev = nullptr;
    }

    delete target;
    count--;
    return true;
}

bool ActionStack::popBottom() {
    Action discarded;
    return popBottom(discarded);
}

bool ActionStack::peekBottom(Action& outAction) const {
    if (isEmpty()) {
        return false;
    }
    outAction = bottomNode->data;
    return true;
}

void ActionStack::clear() {
    ActionNode* curr = bottomNode;
    while (curr != nullptr) {
        ActionNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    topNode = nullptr;
    bottomNode = nullptr;
    count = 0;
}

// ============================================================================
// 3. TRẠNG THÁI VÀ CẤU HÌNH GIỚI HẠN ĐỘNG
// ============================================================================

bool ActionStack::isEmpty() const {
    return count == 0;
}

int ActionStack::getSize() const {
    return count;
}

bool ActionStack::isFull() const {
    return maxCapacity > 0 && count >= maxCapacity;
}

bool ActionStack::isUnlimited() const {
    return maxCapacity == 0;
}

int ActionStack::getMaxCapacity() const {
    return maxCapacity;
}

bool ActionStack::setMaxCapacity(int newLimit) {
    if (newLimit < 0) {
        return false;
    }
    maxCapacity = newLimit;
    if (maxCapacity > 0) {
        while (count > maxCapacity) {
            popBottom();
        }
    }
    return true;
}

// ============================================================================
// 4. HỖ TRỢ TRỰC QUAN HÓA (VISUALIZER) & KIỂM THỬ CONSOLE
// ============================================================================

ActionNode* ActionStack::getNodeAtFromTop(int indexFromTop) const {
    if (indexFromTop < 0 || indexFromTop >= count) {
        return nullptr;
    }

    if (indexFromTop <= count / 2) {
        ActionNode* curr = topNode;
        for (int i = 0; i < indexFromTop; ++i) {
            curr = curr->prev;
        }
        return curr;
    }

    ActionNode* curr = bottomNode;
    int stepsFromBottom = count - 1 - indexFromTop;
    for (int i = 0; i < stepsFromBottom; ++i) {
        curr = curr->next;
    }
    return curr;
}

const ActionNode* ActionStack::getTopNode() const {
    return topNode;
}

const ActionNode* ActionStack::getBottomNode() const {
    return bottomNode;
}

bool ActionStack::getActionAtFromTop(int indexFromTop, Action& outAction) const {
    ActionNode* node = getNodeAtFromTop(indexFromTop);
    if (node == nullptr) {
        return false;
    }
    outAction = node->data;
    return true;
}

bool ActionStack::getNodeVisualInfo(int indexFromTop,
                                    std::string& summary,
                                    uintptr_t& selfAddr,
                                    uintptr_t& prevAddr,
                                    uintptr_t& nextAddr) const {
    ActionNode* node = getNodeAtFromTop(indexFromTop);
    if (node == nullptr) {
        return false;
    }

    summary = formatActionSummary(node->data);
    selfAddr = reinterpret_cast<uintptr_t>(node);
    prevAddr = reinterpret_cast<uintptr_t>(node->prev);
    nextAddr = reinterpret_cast<uintptr_t>(node->next);
    return true;
}

std::string ActionStack::actionTypeToString(ActionType type) {
    switch (type) {
        case ActionType::INSERT_CHAR:  return "INSERT_CHAR";
        case ActionType::DELETE_CHAR:  return "DELETE_CHAR";
        case ActionType::INSERT_TEXT:  return "INSERT_TEXT";
        case ActionType::DELETE_TEXT:  return "DELETE_TEXT";
        case ActionType::INSERT_LINE:  return "INSERT_LINE";
        case ActionType::DELETE_LINE:  return "DELETE_LINE";
        case ActionType::SPLIT_LINE:   return "SPLIT_LINE";
        case ActionType::MERGE_LINE:   return "MERGE_LINE";
        case ActionType::REPLACE_TEXT: return "REPLACE_TEXT";
        default:                       return "UNKNOWN";
    }
}

std::string ActionStack::formatActionSummary(const Action& action) {
    std::string res = "[" + actionTypeToString(action.type) + "] ("
        + std::to_string(action.startPos.line) + ","
        + std::to_string(action.startPos.col) + ")";

    if (action.type == ActionType::REPLACE_TEXT) {
        res += " '" + formatPreview(action.previousContent) + "'->'" + formatPreview(action.content) + "'";
    } else if (action.type == ActionType::SPLIT_LINE || action.type == ActionType::MERGE_LINE) {
        res += "->(" + std::to_string(action.endPos.line) + ","
            + std::to_string(action.endPos.col) + ")";
    } else {
        res += " '" + formatPreview(action.content) + "'";
    }
    return res;
}

void ActionStack::printStack(const std::string& label) const {
    std::cout << "--- " << label << " (size=" << count
              << ", limit=" << (maxCapacity == 0 ? std::string("Unlimited") : std::to_string(maxCapacity))
              << ") ---" << std::endl;

    if (isEmpty()) {
        std::cout << "  <empty>" << std::endl;
        return;
    }

    const ActionNode* curr = topNode;
    int idx = 0;
    while (curr != nullptr) {
        std::cout << "  [" << idx << "] " << formatActionSummary(curr->data)
                  << " @" << curr << " (prev=" << curr->prev << ", next=" << curr->next << ")"
                  << std::endl;
        curr = curr->prev;
        idx++;
    }
}
