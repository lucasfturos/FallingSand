#include "sand_tetrix.hpp"

void SandTetrix::spawnPieces() {
    currentPieceIndex = nextPieceIndex;
    nextPieceIndex = std::rand() % shapes;
    for (auto i = 0; i < squares; ++i) {
        z[i].x = forms[currentPieceIndex][i] % 2 + cols / 2;
        z[i].y = forms[currentPieceIndex][i] / 2 - 1;
    }
    currentPieceColor = nextPieceColor;
    nextPieceColor = colors[std::rand() % colors.size()];
}

bool SandTetrix::checkCollision() {
    for (const auto &pos : z) {
        if (pos.x < 0 || pos.x >= cols || pos.y >= rows ||
            (pos.y >= 0 && board[pos.x][pos.y])) {
            return true;
        }
    }
    return false;
}

void SandTetrix::resetValues() {
    dirX = 0;
    rotate = false;
    dash = 0.3f;
}

void SandTetrix::setRotate() {
    if (rotate) {
        sf::Vector2i coords = z[1];
        for (auto i = 0; i < squares; ++i) {
            int x = z[i].y - coords.y;
            int y = z[i].x - coords.x;

            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if (checkCollision()) {
            for (auto i = 0; i < squares; ++i) {
                z[i] = k[i];
            }
        }
    }
}

void SandTetrix::move2Down() {
    if (timerCount > dash) {
        for (auto i = 0; i < squares; ++i) {
            k[i] = z[i];
            ++z[i].y;
        }

        if (checkCollision()) {
            for (const auto &pos : k) {
                if (pos.y >= 0) {
                    board[pos.x][pos.y] =
                        std::distance(colors.begin(),
                                      std::find(colors.begin(), colors.end(),
                                                currentPieceColor)) +
                        1;
                }
            }
            spawnPieces();
        }

        timerCount = 0;
    }
}

void SandTetrix::changePosition() {
    for (auto i = 0; i < squares; ++i) {
        k[i] = z[i];
        z[i].x += dirX;
    }

    if (checkCollision()) {
        for (auto i = 0; i < squares; ++i) {
            z[i] = k[i];
        }
    }
}

void SandTetrix::setScore() {
    int linesClearedThisFrame = 0;
    for (int y = rows - 1; y >= 0; --y) {
        bool lineFull = true;
        for (int x = 0; x < cols; ++x) {
            if (board[x][y] == 0) {
                lineFull = false;
                break;
            }
        }

        if (lineFull) {
            ++linesClearedThisFrame;
            for (int newY = y; newY > 0; --newY) {
                for (int x = 0; x < cols; ++x) {
                    board[x][newY] = board[x][newY - 1];
                }
            }
            for (int x = 0; x < cols; ++x) {
                board[x][0] = 0;
            }
            ++y;
        }
    }

    if (linesClearedThisFrame > 0) {
        switch (linesClearedThisFrame) {
        case 1:
            score += 40;
            break;
        case 2:
            score += 100;
            break;
        case 3:
            score += 300;
            break;
        case 4:
            score += 1200;
            break;
        default:
            break;
        }
        linesCleared += linesClearedThisFrame;
    }

    for (int x = 0; x < cols; ++x) {
        if (board[x][0] != 0) {
            gameover = true;
            break;
        }
    }
}
