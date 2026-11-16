#include "DoublyLinkedList.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using Clock = std::chrono::steady_clock;

template<class F>
double doThoiGian(F ham) {
    auto batDau = Clock::now();
    ham();
    auto ketThuc = Clock::now();

    return std::chrono::duration<double, std::micro>(
        ketThuc - batDau
    ).count();
}

void kiemTra(bool dung, const std::string& thongBao) {
    if (!dung) {
        throw std::runtime_error(thongBao);
    }
}

void kiemTraNoiDung(
    const DoublyLinkedList& ds,
    int soDong,
    const std::string& kieu
) {
    kiemTra(ds.getSize() == soDong, "Sai so dong");

    Node* p = ds.getHead();

    for (int i = 1; i <= soDong; ++i) {
        std::string mongDoi =
            "void ham_" + std::to_string(i)
            + "() { " + kieu + " a[3] = {1, 2, 3}; }";

        kiemTra(p && p->lineData == mongDoi,
                "Sai noi dung dong " + std::to_string(i));

        p = p->next;
    }

    kiemTra(p == nullptr, "Du dong");
}

int main(int argc, char* argv[]) {
    try {
        std::string thuMuc = argc > 1 ? argv[1] : "..";
        const int kichThuoc[] = {10000, 20000, 50000};
        const int soLan = 10;

        const char* tenPhepDo[] = {
            "loadFromFile",
            "findFirst_missing",
            "findAll_int",
            "replaceAll_int_long"
        };

        std::ofstream chiTiet("ket_qua_chi_tiet.csv");
        std::ofstream trungBinh("ket_qua_trung_binh.csv");

        kiemTra(bool(chiTiet) && bool(trungBinh),
                "Khong tao duoc tep ket qua");

        chiTiet << "operation,lines,run,time_us\n";
        trungBinh << "operation,lines,runs,mean_us\n";

        chiTiet << std::fixed << std::setprecision(3);
        trungBinh << std::fixed << std::setprecision(3);

        for (int n : kichThuoc) {
            std::string duongDan = thuMuc + "/mau_"
                + std::to_string(n) + "_dong.cpp";

            DoublyLinkedList goc;
            kiemTra(goc.loadFromFile(duongDan),
                    "Khong mo duoc " + duongDan);
            kiemTraNoiDung(goc, n, "int");

            double tong[4] = {};

            // Luot 0 lam nong, khong tinh vao ket qua.
            for (int lan = 0; lan <= soLan; ++lan) {
                double tg[4] = {};

                DoublyLinkedList nap;
                bool napOK = false;

                tg[0] = doThoiGian([&] {
                    napOK = nap.loadFromFile(duongDan);
                });

                kiemTra(napOK, "Loi nap tep");
                kiemTraNoiDung(nap, n, "int");

                int dong = -1, cot = -1;
                bool timThay = false;

                tg[1] = doThoiGian([&] {
                    timThay = goc.findFirst(
                        "KHONG_CO_TU_KHOA_NAY", dong, cot, true
                    );
                });

                kiemTra(!timThay, "Ket qua findFirst sai");

                int soKetQua = 0;
                SearchResult* ketQua = nullptr;

                tg[2] = doThoiGian([&] {
                    ketQua = goc.findAll("int", soKetQua, true);
                });

                int dem = 0;
                bool dungViTri = true;

                for (SearchResult* p = ketQua; p; p = p->next) {
                    int cotMongDoi = static_cast<int>(
                        ("void ham_" + std::to_string(dem + 1)
                         + "() { ").size()
                    );

                    if (p->line != dem || p->col != cotMongDoi
                        || p->length != 3) {
                        dungViTri = false;
                    }

                    ++dem;
                }

                DoublyLinkedList::freeSearchResults(ketQua);

                kiemTra(soKetQua == n && dem == n && dungViTri,
                        "Ket qua findAll sai");

                // Sao chep ngoai vung do, moi lan dung du lieu goc.
                DoublyLinkedList banSao(goc);
                int soThayThe = 0;

                tg[3] = doThoiGian([&] {
                    soThayThe = banSao.replaceAll(
                        "int", "long", true
                    );
                });

                kiemTra(soThayThe == n, "Sai so lan thay the");
                kiemTraNoiDung(banSao, n, "long");

                if (lan > 0) {
                    for (int j = 0; j < 4; ++j) {
                        tong[j] += tg[j];

                        chiTiet << tenPhepDo[j] << ','
                                << n << ',' << lan << ','
                                << tg[j] << '\n';
                    }
                }
            }

            for (int j = 0; j < 4; ++j) {
                trungBinh << tenPhepDo[j] << ','
                          << n << ',' << soLan << ','
                          << tong[j] / soLan << '\n';
            }

            std::cout << "Da do va kiem tra: "
                      << n << " dong\n";
        }

        chiTiet.close();
        trungBinh.close();

        kiemTra(bool(chiTiet) && bool(trungBinh),
                "Loi ghi tep ket qua");

        std::cout << "Hoan tat! Da tao hai tep CSV.\n";
        return 0;
    }
    catch (const std::exception& loi) {
        std::cerr << "LOI: " << loi.what()
                  << "\nKhong dung CSV chua hoan tat.\n";
        return 1;
    }
}