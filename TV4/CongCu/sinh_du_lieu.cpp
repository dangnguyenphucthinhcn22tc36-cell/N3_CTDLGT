#include <iostream>
#include <fstream>
#include <string>

bool taoTep(int soDong) {
    std::string tenTep =
        "mau_" + std::to_string(soDong) + "_dong.cpp";

    std::ofstream tep(tenTep);
    if (!tep) {
        std::cerr << "Khong tao duoc: " << tenTep << '\n';
        return false;
    }

    for (int i = 1; i <= soDong; ++i) {
        tep << "void ham_" << i
            << "() { int a[3] = {1, 2, 3}; }\n";
    }

    tep.close();
    if (!tep) {
        std::cerr << "Loi ghi: " << tenTep << '\n';
        return false;
    }

    std::cout << "Da tao " << tenTep
              << " gom " << soDong << " dong.\n";
    return true;
}

int main() {
    const int kichThuoc[] = {10000, 20000, 50000};
    bool thanhCong = true;

    for (int n : kichThuoc) {
        if (!taoTep(n)) {
            thanhCong = false;
        }
    }

    return thanhCong ? 0 : 1;
}
