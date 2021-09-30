#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;

void hanoi(int, char, char, char, int*);

int main() {
    int num=0;
    hanoi(3, 'A', 'B', 'C', &num);

    return 0;
}

void hanoi(int n, char a, char b, char c, int* times) {
    if (n == 1) {
        cout << a << " -> " << c << endl;
        (*times)++;
    } else {
        hanoi(n-1, a, c, b, times);
        cout << a << " -> " << c << endl;
        (*times)++;
        hanoi(n-1, b, a, c, times);
    }
}
