#include <iostream>
#include <vector>

using namespace std;

#define O 2 // obstacle
#define V 1 // visited
#define U 0 // unvisited

int H = 10; // height
int W = H;  // width

void print(vector<vector<int>> maze){
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			if(maze[y][x] == O)
				cout << 'O';
			else if(maze[y][x] == V)
				cout << 'V';
			else 
				cout << 'U';
		}
		cout << endl;
	}
}

void init(vector<vector<int>> &maze){
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			maze[y][x] = V;
		}
	}
}

int main(){
 	vector<vector<int>> maze(H, vector<int>(W));
	init(maze);
	print(maze);

	return 0;
}
