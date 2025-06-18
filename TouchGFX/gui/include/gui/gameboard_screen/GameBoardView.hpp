#ifndef GAMEBOARDVIEW_HPP
#define GAMEBOARDVIEW_HPP

#include <gui_generated/gameboard_screen/GameBoardViewBase.hpp>
#include <gui/gameboard_screen/GameBoardPresenter.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>

#define ROWS 21
#define COLS 12


const int SHAPES[7][4][4] = {
    // L
    {
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // I
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    },
    // O
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // T
    {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // Z
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // S
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    // J
    {
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    }
};


class GameBoardView : public GameBoardViewBase
{
public:
    GameBoardView();
    virtual ~GameBoardView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void tickEvent();

	struct Tetromino {
		int shape[4][4];
		int x = 4;
		int y = 0;
		int color;
	};
protected:
	uint32_t tickCount = 0;

	BoxWithBorder blockArray[ROWS + 10][COLS + 10];
	Tetromino currentPiece;
	int grid[ROWS + 10][COLS + 10] = {0};
	int rand_num = 1;
	int offsetX = COLS + 1;
	int offsetY = 0;

	// Rand value
	uint32_t my_rand();
	int currentPieceType;
	int nextPieceType;

	void spawnPiece();
	void autoDrop();
	void updateBlocks();
	bool checkCollision(int x, int y);
	void rotate();
	void gameOver();
	int clearFullRows();
	void Ring(uint8_t duration);
	// Move Tetromino
	/* virtual button */
	void goRight();
	void goLeft();
	void goDown();

	void handleRight();
	void handleLeft();
	void handleDown();
};

#endif // GAMEBOARDVIEW_HPP
