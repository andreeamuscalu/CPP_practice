#include <iostream> 
#define LINES 20
#define COLUMNS 20 

//celule vi *, celule moarte -

struct Shape {
public:
	char X;
	char Y;
	char lines;
	char columns;
	char** figure;
};

struct Glider : public Shape {
	static const char GLIDER_SIZE = 3;
	Glider(char x, char y);
	~Glider();
};

struct Blinker : public Shape {
	static const char BLINKER_HEIGHT = 1;
	static const char BLINKER_WIDTH = 3;
	Blinker(char x, char y);
	~Blinker();
};

struct Block : public Shape {
	static const char BLOCK_HEIGHT = 2;
	static const char BLOCK_WIDTH = 2;
	Block(char x, char y);
	~Block();
};

struct Boat : public Shape {
	static const char BOAT_SIZE = 3;
	Boat(char x, char y);
	~Boat();
};

struct Beacon : public Shape {
	static const char BEACON_SIZE = 4;
	Beacon(char x, char y);
	~Beacon();
};

class GameOfLife {
public:
	GameOfLife(Shape sh);
	void print();
	void update();
	char getState(char state, char x, char y, bool toggle);
	void iterate(unsigned int iterations);
private:
	char world[LINES][COLUMNS];
	char otherWorld[LINES][COLUMNS];
	bool toggle;
	Shape shape;
};

GameOfLife::GameOfLife(Shape sh) :
	shape(sh),
	toggle(true)
{
	for (char i = 0; i < LINES; i++) {
		for (char j = 0; j < COLUMNS; j++) {
			world[i][j] = '-';
		}
	}
	for (char i = shape.Y; i - shape.Y < shape.lines; i++) {
		for (char j = shape.X; j - shape.X < shape.columns; j++) {
			if (i < LINES && j < COLUMNS) {
				world[i][j] =
					shape.figure[i - shape.Y][j - shape.X];
			}
		}
	}
}

void GameOfLife::print() {
	if (toggle) {
		for (char i = 0; i < LINES; i++) {
			for (char j = 0; j < COLUMNS; j++) {
				std::cout << world[i][j];
			}
			std::cout << std::endl;
		}
	}
	else {
		for (char i = 0; i < LINES; i++) {
			for (char j = 0; j < COLUMNS; j++) {
				std::cout << otherWorld[i][j];
			}
			std::cout << std::endl;
		}
	}
	for (char i = 0; i < COLUMNS; i++) {
		std::cout << '=';
	}
	std::cout << std::endl;
}

void GameOfLife::update() {
	if (toggle) {
		for (char i = 0; i < LINES; i++) {
			for (char j = 0; j < COLUMNS; j++) {
				otherWorld[i][j] =
					GameOfLife::getState(world[i][j], i, j, toggle);
			}
		}
		toggle = !toggle;
	}
	else {
		for (char i = 0; i < LINES; i++) {
			for (char j = 0; j < COLUMNS; j++) {
				world[i][j] =
					GameOfLife::getState(otherWorld[i][j], i, j, toggle);
			}
		}
		toggle = !toggle;
	}
}

char GameOfLife::getState(char state, char y, char x, bool toggle) {
	char neighbors = 0;
	if (toggle) {
		for (char i = y - 1; i <= y + 1; i++) {
			for (char j = x - 1; j <= x + 1; j++) {
				if (i == y && j == x) {
					continue;
				}
				if (i > -1 && i < LINES && j > -1 && j < COLUMNS) {
					if (world[i][j] == '*') {
						neighbors++;
					}
				}
			}
		}
	}
	else {
		for (char i = y - 1; i <= y + 1; i++) {
			for (char j = x - 1; j <= x + 1; j++) {
				if (i == y && j == x) {
					continue;
				}
				if (i > -1 && i < LINES && j > -1 && j < COLUMNS) {
					if (otherWorld[i][j] == '*') {
						neighbors++;
					}
				}
			}
		}
	}
	if (state == '*') {
		return (neighbors > 1 && neighbors < 4) ? '*' : '-';
	}
	else {
		return (neighbors == 3) ? '*' : '-';
	}
}

void GameOfLife::iterate(unsigned int iterations) {
	for (int i = 0; i < iterations; i++) {
		print();
		update();
	}
}

Glider::Glider(char x, char y) {
	X = x;
	Y = y;
	lines = GLIDER_SIZE;
	columns = GLIDER_SIZE;
	figure = new char* [GLIDER_SIZE];
	for (char i = 0; i < GLIDER_SIZE; i++) {
		figure[i] = new char[GLIDER_SIZE];
	}
	for (char i = 0; i < GLIDER_SIZE; i++) {
		for (char j = 0; j < GLIDER_SIZE; j++) {
			figure[i][j] = '-';
		}
	}
	figure[0][1] = '*';
	figure[1][2] = '*';
	figure[2][0] = '*';
	figure[2][1] = '*';
	figure[2][2] = '*';
}

Glider::~Glider() {
	for (char i = 0; i < GLIDER_SIZE; i++) {
		delete[] figure[i];
	}
	delete[] figure;
}

Blinker::Blinker(char x, char y) {
	X = x;
	Y = y;
	lines = BLINKER_HEIGHT;
	columns = BLINKER_WIDTH;
	figure = new char* [BLINKER_HEIGHT];
	for (char i = 0; i < BLINKER_HEIGHT; i++) {
		figure[i] = new char[BLINKER_WIDTH];
	}
	for (char i = 0; i < BLINKER_HEIGHT; i++) {
		for (char j = 0; j < BLINKER_WIDTH; j++) {
			figure[i][j] = '*';
		}
	}
}

Blinker::~Blinker() {
	for (char i = 0; i < BLINKER_HEIGHT; i++) {
		delete[] figure[i];
	}
	delete[] figure;
}

Block::Block(char x, char y) {
	X = x;
	Y = y;
	lines = BLOCK_HEIGHT;
	columns = BLOCK_WIDTH;
	figure = new char* [BLOCK_HEIGHT];
	for (char i = 0; i < BLOCK_HEIGHT; i++) {
		figure[i] = new char[BLOCK_WIDTH];
	}
	for (char i = 0; i < BLOCK_HEIGHT; i++) {
		for (char j = 0; j < BLOCK_WIDTH; j++) {
			figure[i][j] = '*';
		}
	}
}

Block::~Block() {
	for (char i = 0; i < BLOCK_HEIGHT; i++) {
		delete[] figure[i];
	}
	delete[] figure;
}

Boat::Boat(char x, char y) {
	X = x;
	Y = y;
	lines = BOAT_SIZE;
	columns = BOAT_SIZE;
	figure = new char* [BOAT_SIZE];
	for (char i = 0; i < BOAT_SIZE; i++) {
		figure[i] = new char[BOAT_SIZE];
	}
	for (char i = 0; i < BOAT_SIZE; i++) {
		for (char j = 0; j < BOAT_SIZE; j++) {
			figure[i][j] = '-';
		}
	}
	figure[0][0] = '*';
	figure[0][1] = '*';
	figure[1][0] = '*';
	figure[1][2] = '*';
	figure[2][1] = '*';
}

Boat::~Boat() {
	for (char i = 0; i < BOAT_SIZE; i++) {
		delete[] figure[i];
	}
	delete[] figure;
}

Beacon::Beacon(char x, char y) {
	X = x;
	Y = y;
	lines = BEACON_SIZE;
	columns = BEACON_SIZE;
	figure = new char* [BEACON_SIZE];
	for (char i = 0; i < BEACON_SIZE; i++) {
		figure[i] = new char[BEACON_SIZE];
	}
	for (char i = 0; i < BEACON_SIZE; i++) {
		for (char j = 0; j < BEACON_SIZE; j++) {
			figure[i][j] = '-';
		}
	}
	figure[0][0] = '*';
	figure[0][1] = '*';
	figure[1][0] = '*';
	figure[2][3] = '*';
	figure[3][2] = '*';
	figure[3][3] = '*';
}

Beacon::~Beacon() {
	for (char i = 0; i < BEACON_SIZE; i++) {
		delete[] figure[i];
	}
	delete[] figure;
}

int main() {
	int ticks;
	std::cout << "Set number of ticks: ";
	std::cin >> ticks;
	std::cout << "================================================" << std::endl;

	std::cout << "GLIDER PATERN\n";
	Glider glider(10, 10);
	GameOfLife gol(glider);
	gol.iterate(ticks);

	std::cout << "BLINKER PATERN\n";
	Blinker blinker(10, 10);
	GameOfLife gol2(blinker);
	gol2.iterate(ticks);

	std::cout << "BLOCK PATERN\n";
	Block block(10, 10);
	GameOfLife gol3(block);
	gol3.iterate(ticks);

	std::cout << "BOAT PATERN\n";
	Boat boat(10, 10);
	GameOfLife gol4(boat);
	gol4.iterate(ticks);

	std::cout << "BEACON PATERN\n";
	Beacon beacon(10, 10);
	GameOfLife gol5(beacon);
	gol5.iterate(ticks);
}
