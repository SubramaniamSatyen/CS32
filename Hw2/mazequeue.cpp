#include <iostream>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> cQueue;

    //Push the starting coordinate (sr,sc) onto the coordinate stack
    Coord start = Coord(sr, sc);
    cQueue.push(start);

    //Update maze[sr][sc] to indicate that the algorithm has encountered it (i.e., set maze[sr][sc] to have a value other than '.')
    maze[sr][sc] = 'O';

    //While the stack is not empty,
    while (!cQueue.empty()) {
        //Pop the top coordinate off the stack.
        Coord top = cQueue.front();
        cQueue.pop();
        //If the current (r,c) coordinate is equal to the ending coordinate, then we've solved the maze so return true!
        if (top.c() == ec && top.r() == er) {
            return true;
        }
        //Check each place you can move from the current cell
        if (maze[top.r()][top.c() - 1] == '.') {
            cQueue.push(Coord(top.r(), top.c() - 1));
            maze[top.r()][top.c() - 1] = 'O';
        }
        if (maze[top.r() + 1][top.c()] == '.') {
            cQueue.push(Coord(top.r() + 1, top.c()));
            maze[top.r() + 1][top.c()] = 'O';
        }
        if (maze[top.r()][top.c() + 1] == '.') {
            cQueue.push(Coord(top.r(), top.c() + 1));
            maze[top.r()][top.c() + 1] = 'O';
        }
        if (maze[top.r() - 1][top.c()] == '.') {
            cQueue.push(Coord(top.r() - 1, top.c()));
            maze[top.r() - 1][top.c()] = 'O';
        }
    }
    //There was no solution, so return false    
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X.X..X...X",
        "X....XXX.X",
        "X.XXXX.X.X",
        "X......XXX",
        "X.XX.X...X",
        "X.X..X.X.X",
        "X.X.XXXX.X",
        "X.X...X..X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 4, 6, 1, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}