#include <SFML/Graphics.hpp>
#include "minesweeper_class.hpp"
#include "arma_helper.hpp"
#include <iostream>
#include <string>

// Forward declaration of solve function
void solve(MSBoard& board, int x);

int main() {
    int rows = 14, cols = 18, mines = 40;
    int cellSize = 32;
    int margin = 2;
    int buttonHeight = 50;
    MSBoard board(rows, cols, mines);
    board.open(3, 3); // Initial open

    sf::RenderWindow window(sf::VideoMode({(unsigned int) (cols * cellSize), (unsigned int) (rows * cellSize + buttonHeight)}), "Minesweeper Solver GUI");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Font not found!" << std::endl;
        return 1;
    }

    sf::RectangleShape button(sf::Vector2f(cols * cellSize, buttonHeight));
    button.setFillColor(sf::Color(100, 200, 100));
    button.setPosition(sf::Vector2f(0, rows * cellSize));

    sf::Text buttonText("Solve Layer", font, 24);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(sf::Vector2f(cols * cellSize / 2 - 70, rows * cellSize + 10));

    bool needsRedraw = true;
    bool tryNoRREF = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.y > rows * cellSize) {
                    // Button clicked
                    std::vector<std::vector<int>> before = board.revealedBoard;
                    solve(board, tryNoRREF ? 2 : 0);
                    if (board.revealedBoard == before && !tryNoRREF) {
                        tryNoRREF = true;
                        solve(board, 2); // Try without row reduction
                    } else {
                        tryNoRREF = false;
                    }
                    needsRedraw = true;
                } else {
                    // Board click: open cell
                    int r = mousePos.y / cellSize;
                    int c = mousePos.x / cellSize;
                    if (r >= 0 && r < rows && c >= 0 && c < cols) {
                        board.open(r, c);
                        needsRedraw = true;
                    }
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter) {
                    // Space bar or Enter key pressed
                    std::vector<std::vector<int>> before = board.revealedBoard;
                    solve(board, tryNoRREF ? 2 : 0);
                    if (board.revealedBoard == before && !tryNoRREF) {
                        tryNoRREF = true;
                        solve(board, 2); // Try without row reduction
                    } else {
                        tryNoRREF = false;
                    }
                    needsRedraw = true;
                }
            }
        }
        if (needsRedraw) {
            window.clear(sf::Color::White);
            // Draw board
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    sf::RectangleShape cell(sf::Vector2f(cellSize - margin, cellSize - margin));
                    cell.setPosition(sf::Vector2f(c * cellSize + margin / 2, r * cellSize + margin / 2));
                    int val = board.revealedBoard[r][c];
                    if (val == -1) {
                        cell.setFillColor(sf::Color(180, 180, 180)); // Covered
                    } else if (val == -2) {
                        cell.setFillColor(sf::Color(255, 100, 100)); // Marked as mine
                    } else {
                        cell.setFillColor(sf::Color(220, 220, 220)); // Revealed
                    }
                    window.draw(cell);
                    if (val >= 0) {
                        if (val > 0) {
                            sf::Text num(std::to_string(val), font, 18);
                            num.setFillColor(sf::Color::Blue);
                            num.setPosition(sf::Vector2f(c * cellSize + 10, r * cellSize + 5));
                            window.draw(num);
                        }
                    } else if (val == -2) {
                        sf::Text mine("M", font, 18);
                        mine.setFillColor(sf::Color::Red);
                        mine.setPosition(sf::Vector2f(c * cellSize + 8, r * cellSize + 5));
                        window.draw(mine);
                    }
                }
            }
            // Draw button
            window.draw(button);
            window.draw(buttonText);
            window.display();
            needsRedraw = false;
        }

        if (board.isSolved()) {
            sf::Text solvedText("Board Solved!", font, 36);
            solvedText.setFillColor(sf::Color::Green);
            solvedText.setPosition(sf::Vector2f(cols * cellSize / 2 - 120, rows * cellSize / 2));
            window.clear(sf::Color::White);
            window.draw(solvedText);
            window.display();
            sf::sleep(sf::seconds(5)); // Display for 5 seconds
            window.close();
        }
    }
    return 0;
}