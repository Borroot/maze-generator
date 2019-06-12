#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

#define O 2 // obstacle
#define V 1 // visited
#define U 0 // unvisited


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

void print(vector<vector<int>> &maze){
	for(int y = 0; y < maze.size(); y++){
		for(int x = 0; x < maze[y].size(); x++){
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

void init(vector<vector<int>> &maze, vector<Cell> &unvisited, const int W){
	for(int y = 0; y < maze.size(); y++){
		for(int x = 0; x < W; x++){
			if(y % 2 == 0 || x % 2 == 0){
				maze[y].push_back(O);
			}else{
				maze[y].push_back(U);
				Cell cell = {x, y};
				unvisited.push_back(cell);
			}
		}
	}
}

int cell_value(vector<vector<int>> &maze, Cell cell){
	return maze[cell.y][cell.x];
}

bool valid_cell(vector<vector<int>> &maze, Cell cell){
	return cell.x >= 0 && cell.x < maze[0].size() && cell.y >= 0 && cell.y < maze.size();
}

vector<Cell> neighbors(vector<vector<int>> &maze, Cell cell){
	vector<Cell> neighbors;

	for(int i = 0; i < DIR_SIZE; i++){
		int new_x = cell.x + directions[i].x;
		int new_y = cell.y + directions[i].y;
		Cell neighbor = {new_x, new_y};

		if(valid_cell(maze, neighbor)){
			neighbors.push_back(neighbor);
		}
	}

	return neighbors;
}

bool unvisited_neighbors(vector<vector<int>> &maze, Cell cell){
	vector<Cell> _neighbors = neighbors(maze, cell);

	for(int i = 0; i < _neighbors.size(); i++){
		if(cell_value(maze, _neighbors[i]) == U){
			return true;
		}
	}
	return false;
}

Cell random_unvisited_neighbor(vector<vector<int>> &maze, Cell cell){
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

void remove_wall(vector<vector<int>> &maze, Cell c1, Cell c2){
	Cell wall = {(c1.x+c2.x)/2, (c1.y+c2.y)/2};
	maze[wall.y][wall.x] = V;
}

void generate(vector<vector<int>> &maze, vector<Cell> &unvisited, vector<Cell> &visited){
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

int main(int argc, char* argv[]){
	srand(time(0));

	int height = 25;
	int width = height;

	if(argc > 1){
		height = atoi(argv[1]);
		width = height;
	}
	if(argc > 2){
		width = atoi(argv[2]);
	}
	
	const int H = height*2+1; // array height
	const int W = width*2+1;  // array width

 	vector<vector<int>> maze(H);
	vector<Cell> unvisited;
	vector<Cell> visited;

	init(maze, unvisited, W);
	generate(maze, unvisited, visited);
	print(maze);

	return 0;
}
