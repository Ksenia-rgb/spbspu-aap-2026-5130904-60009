#include <iostream>
#include <fstream>
#include <cstddef>

namespace kolibaba {

void process_data(int** mat, size_t r, size_t c, std::ostream& out) {
    int max_sum = 0;
    bool first = true;
    
    for (size_t k = 0; k <= r + c - 2; ++k) {
        if (k == c - 1) continue; 
        
        int sum = 0;
        for (size_t i = 0; i < r; ++i) {
            size_t j = k - i;
            if (j < c) {
                sum += mat[i][j];
            }
        }
        if (first || sum > max_sum) {
            max_sum = sum;
            first = false;
        }
    }
    if (first) max_sum = 0;
    out << max_sum << "\n";

    int cnt = 0;
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            bool is_min = true;
            for (size_t k = 0; k < c; ++k) {
                if (mat[i][k] < mat[i][j]) is_min = false;
            }
            bool is_max = true;
            for (size_t k = 0; k < r; ++k) {
                if (mat[k][j] > mat[i][j]) is_max = false;
            }
            if (is_min && is_max) {
                cnt++;
            }
        }
    }
    out << cnt << "\n";
}

} 

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Error: invalid arguments\n";
        return 1;
    }

    if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2')) {
        std::cerr << "Error: invalid mode\n";
        return 1;
    }
    int mode = argv[1][0] - '0';

    std::ifstream in(argv[2]);
    if (!in) {
        std::cerr << "Error: cannot open input file\n";
        return 2;
    }

    std::ofstream out(argv[3]);
    if (!out) {
        std::cerr << "Error: cannot open output file\n";
        return 2;
    }

    size_t r = 0, c = 0;
    if (!(in >> r >> c) || r == 0 || c == 0) {
        std::cerr << "Error: invalid matrix size\n";
        return 2;
    }

    if (mode == 1) {
        if (r > 100 || c > 100) {
            std::cerr << "Error: too big for fixed size\n";
            return 2;
        }
        int mat[100][100];
        for (size_t i = 0; i < r; ++i) {
            for (size_t j = 0; j < c; ++j) {
                if (!(in >> mat[i][j])) {
                    std::cerr << "Error: invalid matrix data\n";
                    return 2;
                }
            }
        }
        
        int* ptrs[100];
        for (size_t i = 0; i < r; ++i) {
            ptrs[i] = mat[i];
        }
        
        kolibaba::process_data(ptrs, r, c, out);
    } else if (mode == 2) {
        int** mat = new int*[r];
        for (size_t i = 0; i < r; ++i) {
            mat[i] = new int[c];
        }

        for (size_t i = 0; i < r; ++i) {
            for (size_t j = 0; j < c; ++j) {
                if (!(in >> mat[i][j])) {
                    std::cerr << "Error: invalid matrix data\n";
                    for (size_t k = 0; k < r; ++k) delete[] mat[k];
                    delete[] mat;
                    return 2;
                }
            }
        }

        kolibaba::process_data(mat, r, c, out);

        for (size_t i = 0; i < r; ++i) delete[] mat[i];
        delete[] mat;
    }

    return 0;
}
