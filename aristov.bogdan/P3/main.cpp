#include <iostream>
#include <fstream>
#include <limits>

namespace aristov
{
    const std::size_t MAX_SIZE = 10000;

    bool processMatrix(std::istream& input, std::ostream& output,
                       int* matrix, std::size_t rows,
                       std::size_t cols)
    {
        for (std::size_t i = 0; i < rows * cols; ++i)
        {
            if (!(input >> matrix[i]))
            {
                return false;
            }
        }

        long long minSum = 0;
        bool hasDiagonal = false;

        for (std::size_t startCol = 0; startCol < cols; ++startCol)
        {
            long long sum = 0;
            std::size_t r = 0;
            std::size_t c = startCol;

            while (r < rows && c < cols)
            {
                sum += matrix[r * cols + c];
                ++r;
                ++c;
            }

            if (!hasDiagonal || sum < minSum)
            {
                minSum = sum;
                hasDiagonal = true;
            }
        }

        for (std::size_t startRow = 1; startRow < rows; ++startRow)
        {
            long long sum = 0;
            std::size_t r = startRow;
            std::size_t c = 0;

            while (r < rows && c < cols)
            {
                sum += matrix[r * cols + c];
                ++r;
                ++c;
            }

            if (!hasDiagonal || sum < minSum)
            {
                minSum = sum;
                hasDiagonal = true;
            }
        }

        std::size_t bestColumn = 0;
        std::size_t bestLength = 0;

        for (std::size_t c = 0; c < cols; ++c)
        {
            std::size_t currentLength = 1;

            if (rows > 0 && currentLength > bestLength)
            {
                bestLength = currentLength;
                bestColumn = c + 1;
            }

            for (std::size_t r = 1; r < rows; ++r)
            {
                if (matrix[r * cols + c] == matrix[(r - 1) * cols + c])
                {
                    ++currentLength;
                }
                else
                {
                    currentLength = 1;
                }

                if (currentLength > bestLength)
                {
                    bestLength = currentLength;
                    bestColumn = c + 1;
                }
            }
        }

        if (!hasDiagonal)
        {
            minSum = 0;
        }

        output << minSum << '\n';
        output << bestColumn << '\n';

        return output.good();
    }

    bool run(std::istream& input, std::ostream& output, int mode)
    {
        long long rowsInput = 0;
        long long colsInput = 0;

        if (!(input >> rowsInput >> colsInput) ||
            rowsInput < 0 || colsInput < 0)
        {
            return false;
        }

        std::size_t rows = static_cast<std::size_t>(rowsInput);
        std::size_t cols = static_cast<std::size_t>(colsInput);

        if (cols != 0 &&
            rows > std::numeric_limits<std::size_t>::max() / cols)
        {
            return false;
        }

        std::size_t size = rows * cols;

        if (mode == 1)
        {
            if (size > MAX_SIZE)
            {
                return false;
            }

            int matrix[MAX_SIZE];

            return processMatrix(input, output, matrix, rows, cols);
        }

        if (mode == 2)
        {
            int* matrix = new int[size];

            bool result = processMatrix(input, output, matrix, rows, cols);

            delete[] matrix;

            return result;
        }

        return false;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Error: expected 3 arguments\n";
        return 1;
    }

    int mode;

    if (argv[1][0] == '1' && argv[1][1] == '\0')
    {
        mode = 1;
    }
    else if (argv[1][0] == '2' && argv[1][1] == '\0')
    {
        mode = 2;
    }
    else
    {
        std::cerr << "Error: mode must be 1 or 2\n";
        return 1;
    }

    std::ifstream input(argv[2]);

    if (!input)
    {
        std::cerr << "Error cannot open input file\n";
        return 1;
    }

    std::ofstream output(argv[3]);

    if (!output)
    {
        std::cerr << "Error: cannot open output file\n";
        return 1;
    }

    if (!aristov::run(input, output, mode))
    {
        std::cerr << "Error: invalid matrix or processing failed\n";
        return 2;
    }

    return 0;
}