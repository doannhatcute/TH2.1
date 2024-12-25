#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

bool danh_gia_bieu_thuc(const string& bieu_thuc, const map<char, bool>& bien, int& vi_tri) {
    if (vi_tri >= bieu_thuc.size()) {
        return false;
    }
    char c = bieu_thuc[vi_tri];
    vi_tri++;

    cout << "Vi tri: " << vi_tri - 1  << ", Xử lý ký tự: " << c << endl;

    if (isalpha(c)) {
        return bien.at(c);
    } else if (c == '!') {
        return !danh_gia_bieu_thuc(bieu_thuc, bien, vi_tri);
    } else if (c == '(') {
        bool trai = danh_gia_bieu_thuc(bieu_thuc, bien, vi_tri);
        char s = bieu_thuc[vi_tri];
        vi_tri++;
        bool phai = danh_gia_bieu_thuc(bieu_thuc, bien, vi_tri);
        vi_tri++;
        if (s == '&') {
            return trai && phai;
        } else if (s == '|') {
            return trai || phai;
        } else if (s == '>') {
            return !trai || phai;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int main() {
    string bieu_thuc;
    cout << "Nhập biểu thức logic: ";
    getline(cin, bieu_thuc);

    int count = 0;
    for (char c : bieu_thuc) {
        if (c == '(') count++;
        else if (c == ')') count--;
        if (count < 0) {
            cout << "Biểu thức không hợp lệ (dấu ngoặc đóng thừa)" << endl;
            return 1;
        }
    }
    if (count != 0) {
        cout << "Biểu thức không hợp lệ (dấu ngoặc mở thừa)" << endl;
        return 1;
    }

    map<char, bool> bang_bien;
    char ten_bien;
    bool gia_tri;
    cout << "Nhập giá trị cho các biến (ví dụ: A 1, B 0, nhập 0 để kết thúc):" << endl;
    while (true) {
        cin >> ten_bien;
        if (ten_bien == '0') break;
        cin >> gia_tri;
        bang_bien[ten_bien] = gia_tri;
    }

    int vi_tri = 0;
    bool ket_qua = danh_gia_bieu_thuc(bieu_thuc, bang_bien, vi_tri);

    if (vi_tri != bieu_thuc.size()) {
        cout << "Biểu thức không hợp lệ (ký tự thừa)" << endl;
    } else {
        cout << "Kết quả của biểu thức là: " << (ket_qua ? "True" : "False") << endl;
    }

    return 0;
}