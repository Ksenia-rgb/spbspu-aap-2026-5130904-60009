#include <iostream>

int podschet(){
	int a = 1, b = 0, chet = 0, c1 = 0, c2 = 0, chet2 = 0;
	while (a != 0) {
		std::cin >> a;
		if (std::cin.fail()){ 
			return 1;
		}
		b++;
	if (c1 + c2 ==  a){
		chet++;
	} 
	if (c1 != 0) {
	    if (c1 < c2){ 
		chet2++;
	} 
	}
		c1 = c2;
		c2 = a;
	
	}
	if (b <= 3) { 
		return 2;
	}
	std::cout << chet << "\n";
	std::cout << chet2 << "\n";
	return 0;


} 
int main(){
	podschet();
}
