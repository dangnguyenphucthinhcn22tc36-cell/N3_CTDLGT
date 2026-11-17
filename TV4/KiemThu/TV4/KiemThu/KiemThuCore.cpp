#include "DoublyLinkedList.h"
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
