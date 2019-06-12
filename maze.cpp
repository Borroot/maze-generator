#include <iostream>
#include <vector>

using namespace std;

#define O 2 // obstacle
#define V 1 // visited
#define U 0 // unvisited

int height = 5;
int width = height;
int H = height*2+1; // height
int W = width*2+1;  // width

void print(vector<vector<int>> maze){
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			if(maze[y][x] == O) {
				if(y % 2 == 0)
					cout << '-';
				else
					cout << '|';
			} else if(maze[y][x] == V) {
				cout << '.';
			} else { // unvisited
				cout << ' ';
			}
			cout << " ";
		}
		cout << endl;
	}
}

void init(vector<vector<int>> &maze){
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			if(y % 2 == 0 || x % 2 == 0)
				maze[y][x] = O;
		}
	}
}

int main(){
 	vector<vector<int>> maze(H, vector<int>(W));
	init(maze);
	print(maze);

	return 0;
}
