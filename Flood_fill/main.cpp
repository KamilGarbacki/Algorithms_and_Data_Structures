#include <iostream>
#include<vector>
#include <queue>

class Cell{

    int y;
    int x;
public:
    int val;
    bool acc_top;
    bool acc_down;
    bool acc_right;
    bool acc_left;

    Cell()= default;
    Cell(int a, int b): y(a), x(b), val(-1), acc_top(true), acc_down(true), acc_right(true), acc_left(true){}
    Cell(int a, int b, int x): y(a), x(b), val(x), acc_top(true), acc_down(true), acc_right(true), acc_left(true){}

    int get_x() const{return x;}
    int get_y() const{return y;}
};

typedef std::vector<std::vector<Cell>> matrix;

void flood_fill(matrix &maze, std::queue<Cell> q, int size_y, int size_x) {
    while(!q.empty()){
        Cell c = q.front();
        q.pop();
        int val = c.val;
        //down
        if(c.get_y()+1 < size_y && maze[c.get_y() + 1][c.get_x()].val == -1 && maze[c.get_y() + 1][c.get_x()].acc_top){
            maze[c.get_y() + 1][c.get_x()].val = val + 1;
            q.push(maze[c.get_y() + 1][c.get_x()]);
        }
        //up
        if(c.get_y()-1 >= 0 && maze[c.get_y() - 1][c.get_x()].val == -1 && maze[c.get_y() - 1][c.get_x()].acc_down){
            maze[c.get_y() - 1][c.get_x()].val = val + 1;
            q.push(maze[c.get_y() - 1][c.get_x()]);
        }
        //right
        if(c.get_x()+1 < size_x && maze[c.get_y()][c.get_x() + 1].val == -1 && maze[c.get_y()][c.get_x() + 1].acc_left){
            maze[c.get_y()][c.get_x() + 1].val = val + 1;
            q.push(maze[c.get_y()][c.get_x() + 1]);
        }
        //left
        if(c.get_x()-1 >= 0 && maze[c.get_y()][c.get_x() - 1].val == -1 && maze[c.get_y()][c.get_x() - 1].acc_right) {
            maze[c.get_y()][c.get_x() - 1].val = val + 1;
            q.push(maze[c.get_y()][c.get_x() - 1]);
        }

    }
}

void travel(matrix &maze, int size_y, int size_x, Cell curr){
    std::vector<std::pair<Cell, int>> available;
    std::pair<Cell, int> poss_move;

    std::cout << "Current cell: y:" << curr.get_y() << " x: " << curr.get_x() << std::endl;

    if(maze[curr.get_y()][curr.get_x()].val == 0){
        std::cout << "end" << std::endl;
        return;
    }

    //down 0
    if(curr.get_y()+1 < size_y && maze[curr.get_y() + 1][curr.get_x()].acc_top){
        poss_move.first = maze[curr.get_y() + 1][curr.get_x()];
        poss_move.second = 0;
        available.push_back(poss_move);
    }
    //up 1
    if(curr.get_y()-1 >= 0 && maze[curr.get_y() - 1][curr.get_x()].acc_down){
        poss_move.first = maze[curr.get_y() - 1][curr.get_x()];
        poss_move.second = 1;
        available.push_back(poss_move);
    }
    //right 2
    if(curr.get_x()+1 < size_x && maze[curr.get_y()][curr.get_x() + 1].acc_left){
        poss_move.first = maze[curr.get_y()][curr.get_x() + 1];
        poss_move.second = 2;
        available.push_back(poss_move);
    }
    //left 3
    if(curr.get_x()-1 >= 0 && maze[curr.get_y()][curr.get_x() - 1].acc_right){
        poss_move.first = maze[curr.get_y()][curr.get_x() - 1];
        poss_move.second = 0;
        available.push_back(poss_move);
    }

    Cell next_move = available[0].first;
    int direction = available[0].second;

    for (auto & i : available) {
        if(i.first.val < next_move.val){
            direction = i.second;
            next_move = i.first;


        }
    }

    switch(direction){
        case 0:
            std::cout<<"Moving down ";
            break;
        case 1:
            std::cout << "Moving up ";
            break;
        case 2:
            std::cout << "Moving right ";
            break;
        case 3:
            std::cout << "Moving left ";
            break;
        default:
            break;
    }
    travel(maze, size_y, size_x, next_move);
}

void set_wall(matrix &maze, Cell c1, int direction, int size_y, int size_x){
    switch(direction) {
        case 0:
            if (c1.get_y() + 1 < size_y) {
                maze[c1.get_y() + 1][c1.get_x()].acc_top = false;
                maze[c1.get_y()][c1.get_x()].acc_down = false;
            }
            break;
        case 1:
            if (c1.get_y() - 1 >= 0) {
                maze[c1.get_y() - 1][c1.get_x()].acc_down = false;
                maze[c1.get_y()][c1.get_x()].acc_top = false;
            }
            break;
        case 2:
            if (c1.get_x() + 1 < size_x) {
                maze[c1.get_y()][c1.get_x() + 1].acc_left = false;
                maze[c1.get_y()][c1.get_x()].acc_right = false;
            }
            break;
        case 3:
            if (c1.get_x() - 1 >= 0) {
                maze[c1.get_y()][c1.get_x() - 1].acc_right = false;
                maze[c1.get_y()][c1.get_x()].acc_left = false;
            }
            break;
        default:
            break;
    }
}

void reset_maze(matrix &maze, int size_y, int size_x, Cell goal){
    for (int i = 0; i < size_y; i++){
        for (int j = 0; j < size_x; j++) {
            maze[i][j].val = -1;
        }
    }
    maze[goal.get_y()][goal.get_x()].val = 0;
}

int main() {
    matrix maze;

    for (int i = 0; i < 4; i++) {
        std::vector<Cell> temp;
        for (int j = 0; j < 6; j++) {
            temp.push_back(Cell(i,j,-1));
        }
        maze.push_back(temp);
    }

    std::queue<Cell> q;
    Cell goal(2, 4, 0);

    maze[goal.get_y()][goal.get_x()].val = 0;

    q.push(goal);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << maze[i][j].val << " ";
        }
        std::cout << std::endl;
    }

    flood_fill(maze, q, 4, 6);
    std::cout << "------------"<< std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << maze[i][j].val << " ";
        }
        std::cout << std::endl;
    }

    Cell start(3,0);

    travel(maze,4,6,start);
    reset_maze(maze, 4, 6, goal);

    set_wall(maze, maze[3][0], 2, 4, 6);
    set_wall(maze, maze[1][0], 2, 4, 6);
    set_wall(maze, maze[0][0], 2, 4, 6);
    set_wall(maze, maze[1][1], 2, 4, 6);
    set_wall(maze, maze[2][1], 2, 4, 6);
    set_wall(maze, maze[0][2], 0, 4, 6);
    set_wall(maze, maze[0][3], 0, 4, 6);
    set_wall(maze, maze[0][4], 0, 4, 6);
    set_wall(maze, maze[2][3], 2, 4, 6);
    set_wall(maze, maze[2][5], 3, 4, 6);
    set_wall(maze, maze[3][4], 1, 4, 6);
    set_wall(maze, maze[2][3], 1, 4, 6);
    set_wall(maze, maze[2][3], 3, 4, 6);

    q.push(goal);
    flood_fill(maze, q, 4, 6);
    std::cout << "------------"<< std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << maze[i][j].val << " ";
        }
        std::cout << std::endl;
    }
    travel(maze,4,6,start);

    return 0;
}
