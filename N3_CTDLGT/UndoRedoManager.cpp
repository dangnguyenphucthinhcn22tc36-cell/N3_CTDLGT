#include "UndoRedoManager.h"
#include <iostream>

// ============================================================================
// 1. KHỞI TẠO
// ============================================================================

UndoRedoManager::UndoRedoManager(int maxUndoSteps)
    : undoStack(maxUndoSteps < 0 ? 0 : maxUndoSteps),
      redoStack(0) {}

// ============================================================================
// 2. KIỂM TRA HỢP LỆ & ĐIỀU PHỐI UNDO / REDO
// ============================================================================

bool UndoRedoManager::isValidAction(const Action& action) {
    if (!action.startPos.isValid() ||
        !action.cursorBefore.isValid() ||
        !action.cursorAfter.isValid()) {
        return false;
    }

    switch (action.type) {
        case ActionType::INSERT_CHAR:
        case ActionType::DELETE_CHAR:
            return action.content.length() == 1;

        case ActionType::INSERT_TEXT:
        case ActionType::DELETE_TEXT:
            if (action.content.empty() || !action.endPos.isValid()) {
                return false;
            }
            return (action.startPos.line < action.endPos.line) ||
                   (action.startPos.line == action.endPos.line &&
                    action.startPos.col <= action.endPos.col);

        case ActionType::INSERT_LINE:
        case ActionType::DELETE_LINE:
            // Nội dung dòng có thể rỗng nếu là dòng trống; tọa độ dòng bắt đầu từ 0
            return action.startPos.line >= 0;

        case ActionType::SPLIT_LINE:
        case ActionType::MERGE_LINE:
            return action.endPos.isValid() &&
                   action.endPos.line == action.startPos.line + 1;

        case ActionType::REPLACE_TEXT:
            return !(action.previousContent.empty() && action.content.empty());

        default:
            return false;
    }
}

bool UndoRedoManager::recordAction(const Action& action) {
    if (!isValidAction(action)) {
        return false;
    }
    undoStack.push(action);
    redoStack.clear(); // Thao tác mới sau Undo xóa sạch ngăn xếp Redo
    return true;
}

bool UndoRedoManager::undo(Action& outInverseAction) {
    Action original;
    return undo(outInverseAction, original);
}

bool UndoRedoManager::undo(Action& outInverseAction, Action& outOriginalAction) {
    if (!undoStack.pop(outOriginalAction)) {
        return false;
    }
    redoStack.push(outOriginalAction);
    outInverseAction = createInverseAction(outOriginalAction);
    return true;
}

bool UndoRedoManager::redo(Action& outActionToApply) {
    if (!redoStack.pop(outActionToApply)) {
        return false;
    }
    undoStack.push(outActionToApply);
    return true;
}

void UndoRedoManager::clearHistory() {
    undoStack.clear();
    redoStack.clear();
}

void UndoRedoManager::onDocumentOpened() {
    clearHistory();
}

// ============================================================================
// 3. CẤU HÌNH GIỚI HẠN K BƯỚC ĐỘNG
// ============================================================================

bool UndoRedoManager::setMaxUndoSteps(int k) {
    return undoStack.setMaxCapacity(k);
}

int UndoRedoManager::getMaxUndoSteps() const {
    return undoStack.getMaxCapacity();
}

bool UndoRedoManager::isUndoUnlimited() const {
    return undoStack.isUnlimited();
}

// ============================================================================
// 4. THÔNG TIN TRẠNG THÁI
// ============================================================================

bool UndoRedoManager::canUndo() const {
    return !undoStack.isEmpty();
}

bool UndoRedoManager::canRedo() const {
    return !redoStack.isEmpty();
}

int UndoRedoManager::getUndoCount() const {
    return undoStack.getSize();
}

int UndoRedoManager::getRedoCount() const {
    return redoStack.getSize();
}

bool UndoRedoManager::peekUndo(Action& outAction) const {
    return undoStack.peek(outAction);
}

bool UndoRedoManager::peekRedo(Action& outAction) const {
    return redoStack.peek(outAction);
}

// ============================================================================
// 5. TÍNH TOÁN TỌA ĐỘ, NGHỊCH ĐẢO & HÀM TẠO BẢN GHI
// ============================================================================

TextPosition UndoRedoManager::computeEndPosition(const TextPosition& startPos, const std::string& text) {
    int line = startPos.line;
    int col = startPos.col;

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (c == '\r') {
            continue;
        }
        if (c == '\n') {
            line++;
            col = 0; // Đầu dòng mới theo quy ước 0-based là cột 0
        } else {
            col++;
        }
    }

    return TextPosition(line, col);
}

Action UndoRedoManager::createInverseAction(const Action& action) {
    Action inv = action;
    inv.cursorBefore = action.cursorAfter;
    inv.cursorAfter = action.cursorBefore;

    switch (action.type) {
        case ActionType::INSERT_CHAR:
            inv.type = ActionType::DELETE_CHAR;
            break;

        case ActionType::DELETE_CHAR:
            inv.type = ActionType::INSERT_CHAR;
            break;

        case ActionType::INSERT_TEXT:
            inv.type = ActionType::DELETE_TEXT;
            break;

        case ActionType::DELETE_TEXT:
            inv.type = ActionType::INSERT_TEXT;
            break;

        case ActionType::INSERT_LINE:
            inv.type = ActionType::DELETE_LINE;
            break;

        case ActionType::DELETE_LINE:
            inv.type = ActionType::INSERT_LINE;
            break;

        case ActionType::SPLIT_LINE:
            inv.type = ActionType::MERGE_LINE;
            break;

        case ActionType::MERGE_LINE:
            inv.type = ActionType::SPLIT_LINE;
            break;

        case ActionType::REPLACE_TEXT:
            inv.type = ActionType::REPLACE_TEXT;
            inv.content = action.previousContent;
            inv.previousContent = action.content;
            inv.endPos = computeEndPosition(action.startPos, inv.content);
            break;

        default:
            break;
    }

    return inv;
}

Action UndoRedoManager::makeInsertChar(const TextPosition& pos,
                                       char ch,
                                       const TextPosition& cursorBefore,
                                       const TextPosition& cursorAfter) {
    return Action(ActionType::INSERT_CHAR,
                  pos,
                  TextPosition(pos.line, pos.col + 1),
                  std::string(1, ch),
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeDeleteChar(const TextPosition& pos,
                                       char deletedCh,
                                       const TextPosition& cursorBefore,
                                       const TextPosition& cursorAfter) {
    return Action(ActionType::DELETE_CHAR,
                  pos,
                  TextPosition(pos.line, pos.col + 1),
                  std::string(1, deletedCh),
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeInsertText(const TextPosition& startPos,
                                       const std::string& text,
                                       const TextPosition& cursorBefore,
                                       const TextPosition& cursorAfter) {
    return Action(ActionType::INSERT_TEXT,
                  startPos,
                  computeEndPosition(startPos, text),
                  text,
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeDeleteText(const TextPosition& startPos,
                                       const std::string& deletedText,
                                       const TextPosition& cursorBefore,
                                       const TextPosition& cursorAfter) {
    return Action(ActionType::DELETE_TEXT,
                  startPos,
                  computeEndPosition(startPos, deletedText),
                  deletedText,
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeInsertLine(int lineIndex,
                                       const std::string& lineText,
                                       const TextPosition& cursorBefore,
                                       const TextPosition& cursorAfter) {
    return Action(ActionType::INSERT_LINE,
                  TextPosition(lineIndex, 0),
                  TextPosition(lineIndex, static_cast<int>(lineText.length())),
                  lineText,
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeDeleteLine(int lineIndex,
                                       const std::string& deletedLineText,
                                       const TextPosition& cursorBefore,
                                       const TextPosition& cursorAfter) {
    return Action(ActionType::DELETE_LINE,
                  TextPosition(lineIndex, 0),
                  TextPosition(lineIndex, static_cast<int>(deletedLineText.length())),
                  deletedLineText,
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeSplitLine(const TextPosition& splitPos,
                                      const TextPosition& cursorBefore,
                                      const TextPosition& cursorAfter) {
    return Action(ActionType::SPLIT_LINE,
                  splitPos,
                  TextPosition(splitPos.line + 1, 0),
                  "",
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeMergeLine(const TextPosition& mergePoint,
                                      const TextPosition& cursorBefore,
                                      const TextPosition& cursorAfter) {
    return Action(ActionType::MERGE_LINE,
                  mergePoint,
                  TextPosition(mergePoint.line + 1, 0),
                  "",
                  "",
                  cursorBefore,
                  cursorAfter);
}

Action UndoRedoManager::makeReplaceText(const TextPosition& startPos,
                                        const std::string& oldText,
                                        const std::string& newText,
                                        const TextPosition& cursorBefore,
                                        const TextPosition& cursorAfter) {
    return Action(ActionType::REPLACE_TEXT,
                  startPos,
                  computeEndPosition(startPos, newText),
                  newText,
                  oldText,
                  cursorBefore,
                  cursorAfter);
}

// ============================================================================
// 6. TRUY XUẤT CHỈ ĐỌC PHỤC VỤ VISUALIZER & CONSOLE
// ============================================================================

const ActionStack& UndoRedoManager::getUndoStack() const {
    return undoStack;
}

const ActionStack& UndoRedoManager::getRedoStack() const {
    return redoStack;
}

bool UndoRedoManager::getUndoVisualInfo(int indexFromTop,
                                        std::string& summary,
                                        uintptr_t& selfAddr,
                                        uintptr_t& prevAddr,
                                        uintptr_t& nextAddr) const {
    return undoStack.getNodeVisualInfo(indexFromTop, summary, selfAddr, prevAddr, nextAddr);
}

bool UndoRedoManager::getRedoVisualInfo(int indexFromTop,
                                        std::string& summary,
                                        uintptr_t& selfAddr,
                                        uintptr_t& prevAddr,
                                        uintptr_t& nextAddr) const {
    return redoStack.getNodeVisualInfo(indexFromTop, summary, selfAddr, prevAddr, nextAddr);
}

std::string UndoRedoManager::getStatusText() const {
    std::string limitStr = isUndoUnlimited()
        ? "Không giới hạn"
        : (std::to_string(getMaxUndoSteps()) + " bước");

    return "Undo: " + std::to_string(getUndoCount())
         + " | Redo: " + std::to_string(getRedoCount())
         + " | Giới hạn: " + limitStr;
}

void UndoRedoManager::printHistory() const {
    undoStack.printStack("UndoStack");
    redoStack.printStack("RedoStack");
}
