#include <iostream>
using namespace std;

int tongMang(const int a[], int n) {
    int tong = 0;
    for (int i = 0; i < n; ++i) {
        tong += a[i];
    }
    return tong;
}

int timMax(const int a[], int n) {
    int lonNhat = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] > lonNhat) {
            lonNhat = a[i];
        }
    }
    return lonNhat;
}

int main() {
    int a[] = {2, 4, 6, 8, 10};
    int n = 5;
    cout << "CodeNote demo" << endl;
    cout << tongMang(a, n) << endl;
    cout << timMax(a, n) << endl;
    return 0;
}
// Ket thuc tep mau
