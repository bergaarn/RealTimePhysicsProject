/*

#include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_WIDTH = 50;
const int GRID_HEIGHT = 50;
const float CELL_SIZE = 10.f;
const float DELTA_T = 0.1f;
const float DELTA_X = CELL_SIZE;
const float DELTA_Y = CELL_SIZE;
const float ALPHA = 0.1f;

float u[GRID_WIDTH][GRID_HEIGHT];
float u_new[GRID_WIDTH][GRID_HEIGHT];

void initialize_grid() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (i > 10 && i < 20 && j > 10 && j < 20) {
                u[i][j] = 100.f;
            }
            else {
                u[i][j] = 0.f;
            }
            u_new[i][j] = u[i][j];
        }
    }
}

void update_grid() {
    for (int i = 1; i < GRID_WIDTH - 1; i++) {
        for (int j = 1; j < GRID_HEIGHT - 1; j++) {
            u_new[i][j] = u[i][j] + ALPHA * DELTA_T / (DELTA_X * DELTA_X) *
                (u[i + 1][j] - 2 * u[i][j] + u[i - 1][j]) +
                ALPHA * DELTA_T / (DELTA_Y * DELTA_Y) *
                (u[i][j + 1] - 2 * u[i][j] + u[i][j - 1]);
        }
    }
    for (int i = 1; i < GRID_WIDTH - 1; i++) {
        for (int j = 1; j < GRID_HEIGHT - 1; j++) {
            u[i][j] = u_new[i][j];
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Heat Equation");
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    initialize_grid();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        for (int i = 0; i < GRID_WIDTH; i++) {
            for (int j = 0; j < GRID_HEIGHT; j++) {
                cell.setPosition(sf::Vector2f(i * CELL_SIZE, j * CELL_SIZE));
                cell.setFillColor(sf::Color::White);
                cell.setOutlineThickness(1.f);
                cell.setOutlineColor(sf::Color::Black);
                cell.setFillColor(sf::Color(255 * u[i][j] / 100.f, 255 * u[i][j] / 100.f, 255 * u[i][j] / 100.f));
                window.draw(cell);
            }
        }
        update_grid();
        window.display();
        sf::sleep(sf::seconds(0.01f));
    }
    return 0;
}
*/