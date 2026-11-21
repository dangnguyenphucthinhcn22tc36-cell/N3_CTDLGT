#ifndef UNDO_REDO_MANAGER_H
#define UNDO_REDO_MANAGER_H

#include "ActionStack.h"
#include <cstdint>
#include <string>

// ============================================================================
// BÀI TẬP LỚN CẤU TRÚC DỮ LIỆU & GIẢI THUẬT - ĐỀ TÀI 5: TRÌNH SOẠN THẢO VĂN BẢN
// PHÂN CÔNG: THÀNH VIÊN 3 (CORE DEV 2: BỘ ĐIỀU PHỐI UNDO / REDO)
// ============================================================================
// Mô hình tách biệt (Chế độ b):
// - UndoRedoManager chỉ quản lý 2 ngăn xếp undoStack và redoStack (ActionStack).
// - Không giữ con trỏ hay trực tiếp sửa đổi DoublyLinkedList.
// - Khi Undo/Redo, trả về Action cần thực thi (kèm cursorBefore / cursorAfter)
//   để tầng gọi (TV1 / TV2) áp dụng lên văn bản và khôi phục vị trí con trỏ.
// Quy ước tọa độ tầng TV3: 0-based (dòng >= 0, cột >= 0), đồng bộ trực tiếp
// với DoublyLinkedList và TextPosition của TV2.
// ============================================================================

class UndoRedoManager {
private:
    ActionStack undoStack; // Ngăn xếp lưu lịch sử các thao tác có thể hoàn tác
    ActionStack redoStack; // Ngăn xếp lưu lịch sử các thao tác có thể làm lại

public:
    // Khởi tạo bộ điều phối: maxUndoSteps = 0 (không giới hạn mặc định) hoặc k > 0
    explicit UndoRedoManager(int maxUndoSteps = 0);
    ~UndoRedoManager() = default;
    UndoRedoManager(const UndoRedoManager& other) = default;
    UndoRedoManager& operator=(const UndoRedoManager& other) = default;

    // --- KIỂM TRA HỢP LỆ & ĐIỀU PHỐI UNDO / REDO ---
    // Kiểm tra bản ghi thao tác có hợp lệ về tọa độ 0-based và dữ liệu hay không
    static bool isValidAction(const Action& action);

    // Ghi nhận một thao tác mới: đẩy vào undoStack và XÓA SẠCH redoStack.
    // Trả về false nếu action không hợp lệ.
    bool recordAction(const Action& action);

    // Hoàn tác (Ctrl + Z):
    // Pop từ undoStack -> đẩy bản gốc sang redoStack -> trả về hành động nghịch đảo.
    // Người gọi áp dụng outInverseAction lên văn bản và đặt con trỏ tới outInverseAction.cursorAfter.
    bool undo(Action& outInverseAction);
    bool undo(Action& outInverseAction, Action& outOriginalAction);

    // Làm lại (Ctrl + Y):
    // Pop từ redoStack -> đẩy lại vào undoStack -> trả về bản gốc cần thực thi lại.
    // Người gọi áp dụng outActionToApply lên văn bản và đặt con trỏ tới outActionToApply.cursorAfter.
    bool redo(Action& outActionToApply);

    // Xóa sạch cả hai ngăn xếp lịch sử (gọi khi tạo mới hoặc mở tệp khác)
    void clearHistory();
    void onDocumentOpened();

    // --- CẤU HÌNH GIỚI HẠN K BƯỚC ĐỘNG (NÂNG CAO) ---
    // k = 0: không giới hạn; k > 0: giới hạn tối đa k bước Undo (tự bỏ bước cũ nhất).
    // Trả về false nếu k < 0.
    bool setMaxUndoSteps(int k);
    int getMaxUndoSteps() const;
    bool isUndoUnlimited() const;

    // --- THÔNG TIN TRẠNG THÁI ---
    bool canUndo() const;
    bool canRedo() const;
    int getUndoCount() const;
    int getRedoCount() const;

    bool peekUndo(Action& outAction) const;
    bool peekRedo(Action& outAction) const;

    // --- HÀM TÍNH TOÁN & TẠO BẢN GHI THAO TÁC (FACTORY HELPERS) ---
    // Tính tọa độ kết thúc khi chèn/xóa chuỗi từ startPos (xử lý '\n', bỏ qua '\r')
    static TextPosition computeEndPosition(const TextPosition& startPos, const std::string& text);

    // Tạo hành động nghịch đảo cho 1 bản ghi Action (đồng thời hoán đổi cursorBefore <-> cursorAfter)
    static Action createInverseAction(const Action& action);

    static Action makeInsertChar(const TextPosition& pos,
                                 char ch,
                                 const TextPosition& cursorBefore,
                                 const TextPosition& cursorAfter);

    static Action makeDeleteChar(const TextPosition& pos,
                                 char deletedCh,
                                 const TextPosition& cursorBefore,
                                 const TextPosition& cursorAfter);

    static Action makeInsertText(const TextPosition& startPos,
                                 const std::string& text,
                                 const TextPosition& cursorBefore,
                                 const TextPosition& cursorAfter);

    static Action makeDeleteText(const TextPosition& startPos,
                                 const std::string& deletedText,
                                 const TextPosition& cursorBefore,
                                 const TextPosition& cursorAfter);

    static Action makeInsertLine(int lineIndex,
                                 const std::string& lineText,
                                 const TextPosition& cursorBefore,
                                 const TextPosition& cursorAfter);

    static Action makeDeleteLine(int lineIndex,
                                 const std::string& deletedLineText,
                                 const TextPosition& cursorBefore,
                                 const TextPosition& cursorAfter);

    static Action makeSplitLine(const TextPosition& splitPos,
                                const TextPosition& cursorBefore,
                                const TextPosition& cursorAfter);

    static Action makeMergeLine(const TextPosition& mergePoint,
                                const TextPosition& cursorBefore,
                                const TextPosition& cursorAfter);

    static Action makeReplaceText(const TextPosition& startPos,
                                  const std::string& oldText,
                                  const std::string& newText,
                                  const TextPosition& cursorBefore,
                                  const TextPosition& cursorAfter);

    // --- TRUY XUẤT CHỈ ĐỌC PHỤC VỤ TRỰC QUAN HÓA (VISUALIZER CHO THÀNH VIÊN 1) ---
    const ActionStack& getUndoStack() const;
    const ActionStack& getRedoStack() const;

    bool getUndoVisualInfo(int indexFromTop,
                           std::string& summary,
                           uintptr_t& selfAddr,
                           uintptr_t& prevAddr,
                           uintptr_t& nextAddr) const;

    bool getRedoVisualInfo(int indexFromTop,
                           std::string& summary,
                           uintptr_t& selfAddr,
                           uintptr_t& prevAddr,
                           uintptr_t& nextAddr) const;

    std::string getStatusText() const;
    void printHistory() const;
};

#endif // UNDO_REDO_MANAGER_H
