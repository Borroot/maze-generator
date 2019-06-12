#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

#define O 2 // obstacle
#define V 1 // visited
#define U 0 // unvisited

const int height = 25;
const int width = height;

const int H = height*2+1; // height
const int W = width*2+1;  // width

struct Cell {
	int x;
	int y;
};

const int DIR_SIZE = 4;
const Cell directions[DIR_SIZE] = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};

ostream &operator<< (ostream &out, Cell cell){
	cout << "[" << cell.x << "," << cell.y << "]";
	return out;
}

void print(vector<Cell> v){
	cout << "{";
	for(int i = 0; i < v.size(); i++){
		cout << v[i];

		if(i != v.size()-1)
			cout << ", ";
	}
	cout << "}" << endl;
}

void print(int maze[H][W]){
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			if(maze[y][x] == O) {
				if(y % 2 == 0)
					cout << '-';
				else
					cout << '|';
			} else if(maze[y][x] == V) {
				cout << ' ';
			} else { // unvisited
				cout << '.';
			}
			cout << " ";
		}
		cout << endl;
	}
}

void init(int maze[H][W], vector<Cell> &unvisited){
	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			if(y % 2 == 0 || x % 2 == 0){
				maze[y][x] = O;
			}else{
				maze[y][x] = U;
				Cell cell = {x, y};
				unvisited.push_back(cell);
			}
		}
	}
}

int cell_value(int maze[H][W], Cell cell){
	return maze[cell.y][cell.x];
}

bool valid_cell(Cell cell){
	return cell.x >= 0 && cell.x < W && cell.y >= 0 && cell.y < H;
}

vector<Cell> neighbors(int maze[H][W], Cell cell){
	vector<Cell> neighbors;

	for(int i = 0; i < DIR_SIZE; i++){
		int new_x = cell.x + directions[i].x;
		int new_y = cell.y + directions[i].y;
		Cell neighbor = {new_x, new_y};

		if(valid_cell(neighbor)){
			neighbors.push_back(neighbor);
		}
	}

	return neighbors;
}

bool unvisited_neighbors(int maze[H][W], Cell cell){
	vector<Cell> _neighbors = neighbors(maze, cell);

	for(int i = 0; i < _neighbors.size(); i++){
		if(cell_value(maze, _neighbors[i]) == U){
			return true;
		}
	}
	return false;
}

Cell random_unvisited_neighbor(int maze[H][W], Cell cell){
	assert(unvisited_neighbors(maze, cell));

	vector<Cell> _neighbors = neighbors(maze, cell);
	vector<Cell> _unvisited_neighbors;

	for(int i = 0; i < _neighbors.size(); i++){
		if(cell_value(maze, _neighbors[i]) == U){
			_unvisited_neighbors.push_back(_neighbors[i]);
		}
	}

	int index = rand() % _unvisited_neighbors.size();
	return _unvisited_neighbors[index];
}

void remove_wall(int maze[H][W], Cell c1, Cell c2){
	Cell wall = {(c1.x+c2.x)/2, (c1.y+c2.y)/2};
	maze[wall.y][wall.x] = V;
}

void generate(int maze[H][W], vector<Cell> &unvisited, vector<Cell> &visited){
	Cell current = unvisited.back();
	unvisited.pop_back();
	visited.push_back(current);
	maze[current.y][current.y] = V;
	
	while(unvisited.size() != 0){
		if(unvisited_neighbors(maze, current)){
			Cell neighbor = random_unvisited_neighbor(maze, current);
			remove_wall(maze, current, neighbor);

			current = neighbor;
			unvisited.pop_back();
			visited.push_back(current);	
			maze[current.y][current.x] = V;
		}else if(visited.size() != 0){
			current = visited.back();
			visited.pop_back();	
		}
	}
}

int main(){
	srand(time(0));

 	int maze[H][W];
	vector<Cell> unvisited;
	vector<Cell> visited;

	init(maze, unvisited);
	generate(maze, unvisited, visited);
	print(maze);

	return 0;
}
