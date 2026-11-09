#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>

long long minAntiDiagonalSum(const long long* a, long long R, long long C) {
	if (R == 0 || C == 0)
	{
		return 0;
	}
	long long best = std::numeric_limits<long long>::max();
	for (long long s = 0; s <= R + C - 2; s++)
  {
		long long sum = 0;
		bool has = false;
		for (long long i = 0; i < R; i++) {
			long long j = s - i;
			if (j >= 0 && j < C)
			{
				sum += a[i * C + j];
				has = true;
			}
		}
		if (has && sum < best)
		{
		  best = sum;
		}
	}
	return best == std::numeric_limits<long long>::max() ? 0 : best;
}

void spiralProcess(long long* matrix, bool* visited, long long R, long long C, long long total) 
{
  if (total <= 0) 
  {
    return;
  }
  for (long long i = 0; i < total; i++)
  {
    visited[i] = false;
  }
	const int dr[4] = { -1, 0, 1, 0 };
	const int dc[4] = { 0, 1, 0, -1 };
	long long r = R - 1, c = 0;
	int dir = 0;
	matrix[r * C + c] -= 1;
	visited[r * C + c] = true;
	long long count = 1, dec = 2;
	while (count < total) 
  {
		long long nr = r + dr[dir];
		long long nc = c + dc[dir];
		bool moved = false;
		if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr * C + nc]) 
    {
			r = nr; 
      c = nc; 
      moved = true;
		}
		else 
    {
			dir = (dir + 1) % 4;
			nr = r + dr[dir];
			nc = c + dc[dir];
			if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr * C + nc]) 
      {
				r = nr; c = nc;
        moved = true;
			}
		}
		if (!moved)
		{
			break;
		}
		matrix[r * C + c] -= dec;
		visited[r * C + c] = true;
		count++;
		dec++;
	}
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    return 1;
  }
  const char* numStr = argv[1];
  if (std::strcmp(numStr, "1") != 0 && std::strcmp(numStr, "2") != 0) 
  {
    return 1;
  }
  int num = numStr[0] - '0';
  std::ifstream fin(argv[2]);
  if (!fin) 
  { 
    return 2; 
  }
  long long R, C;
  if (!(fin >> R >> C)) 
  {
    return 2;
  }
  if (R < 0 || C < 0)
  { 
    return 2; 
  }
  if (R > 0 && C > 10000000LL / R)
  {
    return 2;
  }
  long long total = R * C;
  if (num == 1 && total > 10000)
  {
    return 2; 
  }
  long long stackMatrix[10000];    
  bool stackVisited[10000];
  long long* matrix;
  bool* visited;
  if (num == 1) {
      matrix = stackMatrix;
      visited = stackVisited;
  }
  else {
      long long n = (total > 0) ? total : 1;
      matrix = new long long[n];
      visited = new bool[n];
  }
  if (!readMatrix(fin, matrix, total)) {
      if (num == 2) { delete[] matrix; delete[] visited; }
      return 2;
  }
  long long minSum = minAntiDiagonalSum(matrix, R, C);
  spiralProcess(matrix, visited, R, C, total);
  std::ofstream fout(argv[3]);
  if (!fout) {
      if (num == 2) { delete[] matrix; delete[] visited; }
      return 2;
  }
  fout << R << " " << C;
  for (long long i = 0; i < total; i++) 
  {
    fout << " " << matrix[i];
  }
  fout << "\n";
  fout << minSum << "\n";
  if (num == 2) { delete[] matrix; delete[] visited; }
  return 0;
}