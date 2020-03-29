#include <iostream>
#include <vector>
#include <cstdint>
#include <tuple>
#include <random>
#include <chrono>
#include <thread>

#include <conio.h>

//maybe need for sparrow.

typedef std::tuple < std::intmax_t, std::intmax_t> Point;//x,y;

typedef std::vector<Point> PType;

PType MakeVector(std::size_t N, std::size_t Re, unsigned int S=0) {
	//std::random_device rd;
	std::minstd_rand mr(S);
	std::uniform_int_distribution<> ui(1, Re);

	PType R;

	for (std::size_t i = 0; i < N; i++) {
		R.push_back({ui(mr)*3,ui(mr)});
	}

	return R;
}

Point Move(const Point& In,const std::size_t Re) {
	PType P = { {0,1},{1,0},{0,-1},{-1,0} };

	std::random_device rd;
	std::uniform_int_distribution<> ui(0, P.size() - 1);
	Point R; 
	do{
		std::size_t I = ui(rd);

		R = Point{ ((std::get<0>(In) + std::get<0>(P[I])) % (Re * 3)),((std::get<1>(In) + std::get<1>(P[I])) % Re) };
	} while (std::get<0>(R) < 0 || std::get<1>(R) < 0);
	return R;
}


bool Locate(std::uintmax_t X, std::uintmax_t Y) {
	std::cout << "\x1b[" << Y << ';' << X << "H";
	return true;
}

bool CLS() {
	std::cout << "\x1b[2J";
	return true;
}

bool Show(const PType& P,char Ch='X') {
	std::size_t X = 0;
	for (auto& o : P) {
		Locate(std::get<0>(o)+1, std::get<1>(o)+1);
		std::cout << X++;
	}
	return true;
}/**/

bool NanoSleep(std::chrono::nanoseconds In) {
	std::this_thread::sleep_for(In);
	return true;
}

int main() {

	std::size_t Re = 19;
	std::size_t N = 64;
	PType D = MakeVector(N, Re);

	std::cout << "Press Key to start.";
	_getch();

	while (_kbhit() == 0) {

		for (auto& o : D) {
			o = Move(o, Re);
		}
		NanoSleep(std::chrono::milliseconds (1000)/20);
		CLS();
		Show(D);


	}

	_getch();

	return 0;
}
/** /
int main() {
	for (std::size_t i = 0; i < 16; i++) {
		Locate(i, 0);
		std::cout << i;
	}

	return 0;
}
/**/