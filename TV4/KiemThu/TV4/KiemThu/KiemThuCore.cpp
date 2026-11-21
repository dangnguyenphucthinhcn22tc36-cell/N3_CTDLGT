#include "DoublyLinkedList.h"
#include "ActionStack.h"
#include "UndoRedoManager.h"
#include "SyntaxChecker.h"
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>

int main() {
    std::ofstream csv("ket_qua_kiem_thu_core.csv");

    if (!csv) {
        std::cerr << "Khong tao duoc CSV\n";
        return 1;
    }

    csv << "id,test,result\n";
    int tong = 0, loi = 0;

    auto thu = [&](const char* id, const char* ten,
                   bool (*ham)()) {
        ++tong;
        bool dat = false;

        try {
            dat = ham();
        }
        catch (const std::exception& e) {
            std::cerr << id << ": " << e.what() << '\n';
        }

        if (!dat) ++loi;

        csv << id << ',' << ten << ','
            << (dat ? "PASS" : "FAIL") << '\n';

        std::cout << id << " "
                  << (dat ? "PASS" : "FAIL")
                  << " - " << ten << '\n';
    };

    thu("C01", "Them_xoa_dong", +[]() {
        DoublyLinkedList d;
        d.appendLine("a");
        d.appendLine("c");
        d.insertLine(1, "b");

        if (d.getAllText() != "a\r\nb\r\nc") return false;

        d.deleteLine(1);

        return d.getSize() == 2
            && d.getAllText() == "a\r\nc"
            && d.getHead()->next == d.getTail()
            && d.getTail()->prev == d.getHead()
            && !d.getHead()->prev
            && !d.getTail()->next;
    });

    thu("C02", "Tach_gop_dong", +[]() {
        DoublyLinkedList d;
        d.appendLine("abcdef");
        d.splitLine(0, 3);

        if (d.getAllText() != "abc\r\ndef") return false;

        d.mergeLines(1);

        return d.getSize() == 1
            && d.getLine(0) == "abcdef";
    });

    thu("C03", "Chen_Delete_Backspace", +[]() {
        DoublyLinkedList d;
        d.appendLine("ac");
        d.insertChar(0, 1, 'b');

        if (d.getLine(0) != "abc") return false;

        d.deleteChar(0, 1);

        if (d.getLine(0) != "ac") return false;

        d.backspaceChar(0, 1);

        return d.getLine(0) == "c";
    });

    thu("C04", "Chen_xoa_nhieu_dong", +[]() {
        DoublyLinkedList d;
        d.appendLine("abcd");
        d.insertTextAt(0, 2, "X\nY");

        if (d.getAllText() != "abX\r\nYcd") return false;

        d.deleteRange(0, 2, 1, 1);

        return d.getSize() == 1
            && d.getLine(0) == "abcd";
    });

    thu("C05", "Sao_chep_doc_lap", +[]() {
        DoublyLinkedList a;
        a.appendLine("abc");

        DoublyLinkedList b(a), c;
        c = a;
        b.setLine(0, "xyz");
        a.clear();

        return a.isEmpty()
            && b.getLine(0) == "xyz"
            && c.getLine(0) == "abc";
    });

    thu("C06", "Tim_kiem_hoa_thuong_ASCII", +[]() {
        DoublyLinkedList d;
        d.appendLine("abc XYZ abc");
        int dong = -1, cot = -1;

        if (!d.findFirst("XYZ", dong, cot, true)
            || dong != 0 || cot != 4) return false;

        if (d.findFirst("xyz", dong, cot, true))
            return false;

        if (!d.findFirst("xyz", dong, cot, false)
            || dong != 0 || cot != 4) return false;

        return !d.findFirst("zzz", dong, cot, true);
    });

    thu("C07", "Tim_tat_ca_khong_chong_lan", +[]() {
        DoublyLinkedList d;
        d.appendLine("aaaaa");

        int n = 0;
        SearchResult* p = d.findAll("aa", n, true);

        bool dat = n == 2
            && p && p->line == 0 && p->col == 0
            && p->length == 2
            && p->next && p->next->line == 0
            && p->next->col == 2
            && p->next->length == 2
            && !p->next->next;

        DoublyLinkedList::freeSearchResults(p);
        return dat;
    });

    thu("C08", "Thay_the_tat_ca", +[]() {
        DoublyLinkedList d;
        d.appendLine("int a; int b;");

        int n = d.replaceAll("int", "long", true);

        return n == 2
            && d.getLine(0) == "long a; long b;"
            && d.replaceAll("zzz", "x", true) == 0;
    });

    thu("C09", "Ranh_gioi_dong", +[]() {
        DoublyLinkedList d;
        d.appendLine("ab");
        d.appendLine("cd");
        d.deleteChar(0, 2);

        if (d.getSize() != 1
            || d.getLine(0) != "abcd") return false;

        d.splitLine(0, 2);
        d.backspaceChar(1, 0);

        if (d.getSize() != 1
            || d.getLine(0) != "abcd") return false;

        d.deleteLine(0);

        return d.isEmpty() && d.getSize() == 0
            && !d.getHead() && !d.getTail();
    });

    thu("C10", "Luu_mo_lai_UTF8", +[]() {
        const char* tep = "tv4_roundtrip_test.tmp";
        DoublyLinkedList a, b;

        a.loadFromText("Xin chào\nDòng thứ hai");

        bool dat = a.saveToFile(tep)
            && b.loadFromFile(tep)
            && b.getSize() == 2
            && b.getAllText() == a.getAllText();

        std::remove(tep);
        return dat;
    });

    thu("C11", "ActionStack_Deque_GioiHanK", +[]() {
        ActionStack s(3);
        s.push(UndoRedoManager::makeInsertChar(TextPosition(0, 0), 'a', TextPosition(0, 0), TextPosition(0, 1)));
        s.push(UndoRedoManager::makeInsertChar(TextPosition(0, 1), 'b', TextPosition(0, 1), TextPosition(0, 2)));
        s.push(UndoRedoManager::makeInsertChar(TextPosition(0, 2), 'c', TextPosition(0, 2), TextPosition(0, 3)));
        s.push(UndoRedoManager::makeInsertChar(TextPosition(0, 3), 'd', TextPosition(0, 3), TextPosition(0, 4)));

        Action bot, top;
        if (s.getSize() != 3 || !s.isFull()) return false;
        if (!s.peekBottom(bot) || bot.content != "b") return false;
        if (!s.peek(top) || top.content != "d") return false;
        if (!s.getTopNode() || s.getTopNode()->next != nullptr) return false;
        if (!s.getBottomNode() || s.getBottomNode()->prev != nullptr) return false;

        if (!s.setMaxCapacity(2) || s.getSize() != 2) return false;
        if (!s.peekBottom(bot) || bot.content != "c") return false;
        if (s.setMaxCapacity(-1) || s.getMaxCapacity() != 2 || s.getSize() != 2) return false;

        ActionStack copy(s);
        ActionStack assigned;
        assigned = s;
        s.clear();

        if (!s.isEmpty() || !s.setMaxCapacity(0) || !s.isUnlimited()) return false;

        return copy.getSize() == 2
            && assigned.getSize() == 2
            && copy.peek(top) && top.content == "d"
            && assigned.peekBottom(bot) && bot.content == "c";
    });

    thu("C12", "UndoRedo_Va_XoaRedo", +[]() {
        DoublyLinkedList d;
        d.appendLine("");
        UndoRedoManager m;
        Action act;

        d.pasteText(0, 0, "abc");
        if (!m.recordAction(UndoRedoManager::makeInsertText(
                TextPosition(0, 0), "abc", TextPosition(0, 0), TextPosition(0, 3)))) {
            return false;
        }

        if (!m.undo(act) || act.type != ActionType::DELETE_TEXT
            || act.cursorAfter.line != 0 || act.cursorAfter.col != 0) {
            return false;
        }
        d.deleteRange(act.startPos.line, act.startPos.col, act.endPos.line, act.endPos.col);
        if (!d.getAllText().empty() || !m.canRedo()) return false;

        if (!m.redo(act) || act.type != ActionType::INSERT_TEXT
            || act.cursorAfter.line != 0 || act.cursorAfter.col != 3) {
            return false;
        }
        d.insertTextAt(act.startPos.line, act.startPos.col, act.content);
        if (d.getAllText() != "abc") return false;

        if (!m.undo(act)) return false;
        d.deleteRange(act.startPos.line, act.startPos.col, act.endPos.line, act.endPos.col);
        d.pasteText(0, 0, "xyz");
        if (!m.recordAction(UndoRedoManager::makeInsertText(
                TextPosition(0, 0), "xyz", TextPosition(0, 0), TextPosition(0, 3)))) {
            return false;
        }
        if (m.canRedo() || m.redo(act)) return false;

        if (m.recordAction(UndoRedoManager::makeInsertChar(
                TextPosition(-1, 0), 'z', TextPosition(0, 0), TextPosition(0, 1)))) {
            return false;
        }

        m.onDocumentOpened();
        return !m.canUndo() && !m.canRedo()
            && m.getUndoCount() == 0 && m.getRedoCount() == 0;
    });

    thu("C13", "SyntaxChecker_CanBang_Va_Loi", +[]() {
        BracketCheckResult ok = SyntaxChecker::checkText("([]{})");
        if (!ok.isBalanced || ok.errorType != BracketErrorType::NONE
            || ok.roundOpenCount != 1 || ok.roundCloseCount != 1
            || ok.curlyOpenCount != 1 || ok.curlyCloseCount != 1
            || ok.squareOpenCount != 1 || ok.squareCloseCount != 1) {
            return false;
        }

        BracketCheckResult mis = SyntaxChecker::checkText("([)]");
        if (mis.isBalanced || mis.errorType != BracketErrorType::MISMATCHED_PAIR
            || mis.errorLine != 0 || mis.errorCol != 2
            || mis.foundChar != ')' || mis.expectedChar != ']') {
            return false;
        }

        BracketCheckResult unclosed = SyntaxChecker::checkText("(()");
        if (unclosed.isBalanced || unclosed.errorType != BracketErrorType::UNCLOSED_OPENING
            || unclosed.errorLine != 0 || unclosed.errorCol != 0) {
            return false;
        }

        BracketCheckResult extra = SyntaxChecker::checkText("int x = 0;\n}");
        if (extra.isBalanced || extra.errorType != BracketErrorType::UNMATCHED_CLOSING
            || extra.errorLine != 1 || extra.errorCol != 0) {
            return false;
        }

        const std::string code =
            "int f() {\n"
            "    // ngoac du ((( ]]]\n"
            "    /* comment { [ ( */\n"
            "    const char* s = \"abc { [ ( \\\" \";\n"
            "    char c = '(';\n"
            "    return 0;\n"
            "}\n";

        return SyntaxChecker::checkText(code, true).isBalanced
            && !SyntaxChecker::checkText(code, false).isBalanced;
    });

    thu("C14", "SyntaxChecker_TepLon_DSLK", +[]() {
        DoublyLinkedList d;
        for (int i = 1; i <= 100; ++i) {
            d.appendLine("void ham_" + std::to_string(i) + "() { int a[3] = {1, 2, 3}; }");
        }

        BracketCheckResult ok = SyntaxChecker::checkDocument(d, true);
        if (!ok.isBalanced || ok.errorType != BracketErrorType::NONE
            || ok.roundOpenCount != 100 || ok.roundCloseCount != 100
            || ok.curlyOpenCount != 200 || ok.curlyCloseCount != 200
            || ok.squareOpenCount != 100 || ok.squareCloseCount != 100) {
            return false;
        }

        d.appendLine("void loi( {");
        BracketCheckResult err = SyntaxChecker::checkDocument(d, true);
        return !err.isBalanced
            && err.errorType == BracketErrorType::UNCLOSED_OPENING
            && err.errorLine == 100;
    });

    csv.close();

    if (!csv) {
        std::cerr << "Loi ghi CSV\n";
        return 1;
    }

    std::cout << "Tong: " << tong
              << "; PASS: " << tong - loi
              << "; FAIL: " << loi << '\n';

    return loi ? 1 : 0;
}
