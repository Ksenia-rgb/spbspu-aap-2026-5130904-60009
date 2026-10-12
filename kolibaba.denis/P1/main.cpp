#include <iostream>

int main() {
    int x, mx, a = 0, b = 0, n = 0, after_max = 0, sum_dup = 0;
    bool started = false, terminated = false;

    while (std::cin >> x) {
        if (x == 0) {
            terminated = true;
            break;
        }
        if (!started) {
            mx = x;
            started = true;
        } else if (x > mx) {
            mx = x;
            after_max = 0;
        } else {
            after_max++;
        }
        if (n >= 2 && (long long)a + b == x)
            sum_dup++;
        a = b;
        b = x;
        n++;
    }

    if (!terminated) {
        std::cerr << "Error: not a sequence\n";
        return 1;
    }

    if (n == 0) {
        std::cerr << "Error: empty sequence\n";
        return 2;
    }

    if (started)
        std::cout << after_max << "\n";
    if (n >= 3)
        std::cout << sum_dup << "\n";

    if (n < 3) {
        std::cerr << "Error: sequence too short\n";
        return 2;
    }

    return 0;
}
