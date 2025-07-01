#include <gui/gameboard_screen/GameBoardView.hpp>
#include <touchgfx/Color.hpp>
#include "cmsis_os.h"
#include "stm32f4xx.h"

extern osMessageQueueId_t myQueue01Handle;
extern osMessageQueueId_t myQueue02Handle;
extern int score;
extern int mode;
GameBoardView::GameBoardView()
{
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLS; x++) {
			if ((x == 0 || x == COLS - 1) && (y >= 0 && y <= ROWS - 1)) {
				blockArray[y][x].setPosition(x * 15, y * 15, 15, 15);
				blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(110, 110, 110));
				blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(97, 97, 97));
				blockArray[y][x].setBorderSize(3);
			} else if ((x >= 0 && x <= COLS - 1) && (y == ROWS - 1)){
				blockArray[y][x].setPosition(x * 15, y * 15, 15, 15);
				blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(110, 110, 110));
				blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(97, 97, 97));
				blockArray[y][x].setBorderSize(3);
			} else {
				blockArray[y][x].setPosition(x * 15, y * 15, 15, 15);
				blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
				blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
				blockArray[y][x].setBorderSize(1);
			}
			add(blockArray[y][x]);
		}
	}
	for (int y = 0; y < 5; y++) {
		for (int x = COLS; x < COLS + 5; x++) {
			if (y != 4) {
				blockArray[y][x].setPosition(x * 15, y * 15, 15, 15);
				blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
				blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
				blockArray[y][x].setBorderSize(1);
			} else {
				blockArray[y][x].setPosition(x * 15, y * 15, 15, 15);
				blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(110, 110, 110));
				blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(97, 97, 97));
				blockArray[y][x].setBorderSize(3);
			}
			add(blockArray[y][x]);
		}
	}
	nextPieceType = my_rand() % 7 + 1;
	spawnPiece();
	updateBlocks();
}

void GameBoardView::setupScreen()
{
    GameBoardViewBase::setupScreen();
    spawnPiece();
}

void GameBoardView::tearDownScreen()
{
    GameBoardViewBase::tearDownScreen();
}

uint32_t GameBoardView::my_rand() {
	return HAL_GetTick() ^ SysTick->VAL;
}
void GameBoardView::Ring(uint8_t duration)
{

	while(duration --){
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_RESET);
	}

}

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 8000; i++) {
        __NOP();  // Lệnh không làm gì, chỉ để vòng lặp không bị tối ưu hóa
    }
}

void GameBoardView::gameOver() {
	application().gotoGameOverScreenNoTransition();
}

void GameBoardView::rotate() {
	int rotated[4][4] = {0};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			rotated[j][3 - i] = currentPiece.shape[i][j];
		}
	}

	int backup[4][4] = {0};
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			backup[i][j] = currentPiece.shape[i][j];

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			currentPiece.shape[i][j] = rotated[i][j];

	if (checkCollision(currentPiece.x, currentPiece.y)) {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				currentPiece.shape[i][j] = backup[i][j];
	}
}

bool GameBoardView::checkCollision(int newX, int newY) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece.shape[i][j]) {
                int gx = newX + j;
                int gy = newY + i;
                if (gx < 1 || gx >= COLS - 1|| gy >= ROWS - 1 || grid[gy][gx]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void GameBoardView::spawnPiece() {
    currentPiece.x = 4;
    currentPiece.y = 0;

    currentPieceType = nextPieceType;
    nextPieceType = my_rand() % 7;
    rand_num = currentPieceType;

    if (currentPiece.x >= COLS - 2) {
        currentPiece.x = 0;
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
             currentPiece.shape[i][j] = SHAPES[rand_num][i][j];

    currentPiece.color = rand_num + 1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (SHAPES[nextPieceType][i][j] != 0) {
                int color = nextPieceType + 1;
                if (color > 7) color = 0;
                grid[offsetY + i][offsetX + j] = color;
            } else {
                grid[offsetY + i][offsetX + j] = 0;
            }
        }
    }

    if (checkCollision(currentPiece.x, currentPiece.y)) {
        gameOver();
    }
}


void GameBoardView::autoDrop()
{
    if (!checkCollision(currentPiece.x, currentPiece.y + 1)) {
        currentPiece.y++;
    } else {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (currentPiece.shape[i][j]) {
                    int gx = currentPiece.x + j;
                    int gy = currentPiece.y + i;
                    if (gx >= 0 && gx < COLS && gy >= 0 && gy < ROWS)
                        grid[gy][gx] = currentPiece.color;
                }
            }
        }
        int rowsCleared = clearFullRows();

        score += rowsCleared;

        spawnPiece();
    }
}

void GameBoardView::goRight() {
	if (!checkCollision(currentPiece.x + 1, currentPiece.y)) {
		currentPiece.x++;
	}
}

void GameBoardView::goLeft() {
	if (!checkCollision(currentPiece.x - 1, currentPiece.y)) {
		currentPiece.x--;
	}
}

void GameBoardView::goDown() {
	if (!checkCollision(currentPiece.x, currentPiece.y + 1)) {
		currentPiece.y++;
	}
}
void GameBoardView::handleRight() {
	goRight();
}

void GameBoardView::handleLeft() {
	goLeft();
}

void GameBoardView::handleDown() {
	goDown();
}
int GameBoardView::clearFullRows() {
	int cleared = 0;
	int y = ROWS - 2;  // bắt đầu từ dòng trên cùng bên dưới

	while (y >= 0) {
	    bool full = true;
	    for (int x = 1; x < COLS - 1; x++) {
	        if (grid[y][x] == 0) {
	            full = false;
	            break;
	        }
	    }
	    if (full) {
	    	Ring(1);
	        for (int row = y; row > 0; row--) {
	            for (int col = 1; col < COLS - 1; col++) {
	                grid[row][col] = grid[row - 1][col];
	            }
	        }


	        for (int col = 1; col < COLS - 1; col++) {
	            grid[0][col] = 0;
	        }

	        cleared++;
	        continue;
	    } else {
	        y--;
	    }
	}

	if (cleared == 4) {
		return 8;
	}
	return cleared;
}
void GameBoardView::updateBlocks()
{
	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", score);
	textArea2.setWildcard(textArea2Buffer);
	textArea2.resizeToCurrentText();
	textArea2.invalidate();
    // Vẽ block cố định
    for (int y = 0; y < ROWS - 1; y++) {
        for (int x = 1; x < COLS - 1; x++) {
			int colorCode = grid[y][x];
			if (colorCode) {
				touchgfx::colortype fillColor;
				touchgfx::colortype borderColor;

				switch (colorCode) {
					case 1: // L
						fillColor = touchgfx::Color::getColorFromRGB(255, 165, 0); // Cam
						borderColor = touchgfx::Color::getColorFromRGB(200, 100, 0);
						break;
					case 2: // I
						fillColor = touchgfx::Color::getColorFromRGB(0, 255, 255); // Cyan
						borderColor = touchgfx::Color::getColorFromRGB(0, 200, 200);
						break;
					case 3: // O
						fillColor = touchgfx::Color::getColorFromRGB(255, 255, 0); // Vàng
						borderColor = touchgfx::Color::getColorFromRGB(200, 200, 0);
						break;
					case 4: // T
						fillColor = touchgfx::Color::getColorFromRGB(128, 0, 128); // Tím
						borderColor = touchgfx::Color::getColorFromRGB(100, 0, 100);
						break;
					case 5: // Z
						fillColor = touchgfx::Color::getColorFromRGB(255, 0, 0); // Đỏ
						borderColor = touchgfx::Color::getColorFromRGB(200, 0, 0);
						break;
					case 6: // S
						fillColor = touchgfx::Color::getColorFromRGB(0, 255, 0); // Xanh lá
						borderColor = touchgfx::Color::getColorFromRGB(0, 200, 0);
						break;
					case 7: // J
						fillColor = touchgfx::Color::getColorFromRGB(0, 0, 255); // Xanh dương
						borderColor = touchgfx::Color::getColorFromRGB(0, 0, 200);
						break;
					default:
						fillColor = touchgfx::Color::getColorFromRGB(110, 110, 110);
						borderColor = touchgfx::Color::getColorFromRGB(97, 97, 97);
						break;
				}

				blockArray[y][x].setColor(fillColor);
				blockArray[y][x].setBorderColor(borderColor);
            } else {
                blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
                blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
            }
            blockArray[y][x].invalidate();
        }
    }
    for (int y = 0; y < 4; y++) {
		for (int x = COLS; x < COLS + 5; x++) {
			int colorCode = grid[y][x];
			if (colorCode) {
				touchgfx::colortype fillColor;
				touchgfx::colortype borderColor;

				switch (colorCode) {
					case 1: // L
						fillColor = touchgfx::Color::getColorFromRGB(255, 165, 0); // Cam
						borderColor = touchgfx::Color::getColorFromRGB(200, 100, 0);
						break;
					case 2: // I
						fillColor = touchgfx::Color::getColorFromRGB(0, 255, 255); // Cyan
						borderColor = touchgfx::Color::getColorFromRGB(0, 200, 200);
						break;
					case 3: // O
						fillColor = touchgfx::Color::getColorFromRGB(255, 255, 0); // Vàng
						borderColor = touchgfx::Color::getColorFromRGB(200, 200, 0);
						break;
					case 4: // T
						fillColor = touchgfx::Color::getColorFromRGB(128, 0, 128); // Tím
						borderColor = touchgfx::Color::getColorFromRGB(100, 0, 100);
						break;
					case 5: // Z
						fillColor = touchgfx::Color::getColorFromRGB(255, 0, 0); // Đỏ
						borderColor = touchgfx::Color::getColorFromRGB(200, 0, 0);
						break;
					case 6: // S
						fillColor = touchgfx::Color::getColorFromRGB(0, 255, 0); // Xanh lá
						borderColor = touchgfx::Color::getColorFromRGB(0, 200, 0);
						break;
					case 7: // J
						fillColor = touchgfx::Color::getColorFromRGB(0, 0, 255); // Xanh dương
						borderColor = touchgfx::Color::getColorFromRGB(0, 0, 200);
						break;
					default:
						fillColor = touchgfx::Color::getColorFromRGB(110, 110, 110);
						borderColor = touchgfx::Color::getColorFromRGB(97, 97, 97);
						break;
				}

				blockArray[y][x].setColor(fillColor);
				blockArray[y][x].setBorderColor(borderColor);
			} else {
				blockArray[y][x].setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
				blockArray[y][x].setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
			}
			blockArray[y][x].invalidate();
		}
	}
    // Thêm màu cho các khối
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (currentPiece.shape[i][j]) {
				int gx = currentPiece.x + j;
				int gy = currentPiece.y + i;
				if (gx >= 0 && gx < COLS && gy >= 0 && gy < ROWS) {
					touchgfx::colortype fillColor;
					touchgfx::colortype borderColor;
					switch (currentPiece.color) {
						case 1:
							fillColor = touchgfx::Color::getColorFromRGB(255, 165, 0);
							borderColor = touchgfx::Color::getColorFromRGB(200, 100, 0);
							break;
						case 2:
							fillColor = touchgfx::Color::getColorFromRGB(0, 255, 255);
							borderColor = touchgfx::Color::getColorFromRGB(0, 200, 200);
							break;
						case 3:
							fillColor = touchgfx::Color::getColorFromRGB(255, 255, 0);
							borderColor = touchgfx::Color::getColorFromRGB(200, 200, 0);
							break;
						case 4:
							fillColor = touchgfx::Color::getColorFromRGB(128, 0, 128);
							borderColor = touchgfx::Color::getColorFromRGB(100, 0, 100);
							break;
						case 5:
							fillColor = touchgfx::Color::getColorFromRGB(255, 0, 0);
							borderColor = touchgfx::Color::getColorFromRGB(200, 0, 0);
							break;
						case 6:
							fillColor = touchgfx::Color::getColorFromRGB(0, 255, 0);
							borderColor = touchgfx::Color::getColorFromRGB(0, 200, 0);
							break;
						case 7:
							fillColor = touchgfx::Color::getColorFromRGB(0, 0, 255);
							borderColor = touchgfx::Color::getColorFromRGB(0, 0, 200);
							break;
						default:
							fillColor = touchgfx::Color::getColorFromRGB(255, 255, 255);
							borderColor = touchgfx::Color::getColorFromRGB(200, 200, 200);
							break;
					}

					blockArray[gy][gx].setColor(fillColor);
					blockArray[gy][gx].setBorderColor(borderColor);
					blockArray[gy][gx].invalidate();
				}
			}
		}
	}
}

void GameBoardView::tickEvent()
{
    tickCount++;
    if ((score + 1) * mode < 20) {
		if (tickCount % ((6 - mode) * 3) == 0) {
			autoDrop();
		}
    } else if ((score + 1) * mode < 60 ) {
    	if (tickCount % ((5 - mode) * 3) == 0) {
			autoDrop();
		}
    } else if ((score + 1) * mode < 90){
    	if (tickCount % ((4 - mode) * 3) == 0) {
			autoDrop();
		}
    } else {
    	if (tickCount % ((3 - mode) * 3) == 0) {
			autoDrop();
    }
    }

    uint8_t res;
    if (osMessageQueueGetCount(myQueue01Handle) > 0) {
    	osMessageQueueGet(myQueue01Handle, &res, NULL, osWaitForever);
    	switch(res){
    	case 1:
    		handleRight();
    		break;
    	case 2:
    		handleLeft();
    		break;
    	case 3:
    		rotate();
    		break;
    	case 4:
    		handleDown();
    		break;
    	default:
    		break;
    	}
    }
    updateBlocks();
}


