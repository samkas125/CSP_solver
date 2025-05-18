#include <vector>

class MSBoard {
    public:
        std::vector<std::vector<int>> revealedBoard;
        int rows;
        int cols;
        int mines;
        MSBoard(int numRows, int numCols, int numMines);
        void open(int row, int col);
        void markMine(int row, int col);
        std::vector<std::vector<int>> board;
        bool started = false;
        bool isSolved ();
    private:
        void placeMines(int row, int col);
        bool isAdjacent(int r, int c, int initialRow, int initialCol);
};