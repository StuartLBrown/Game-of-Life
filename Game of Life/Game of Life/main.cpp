#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
using namespace sf;
using namespace std;
Vector2f operator-(const Vector2f& v1, const Vector2f& v2);
bool checkSpot(bool state, int numNeighbors);
int getNumNeighbors(int x, int y,bool tiles[100][100]);
int checkX(int x, int maxSize);
int main()
{
    RenderWindow window(VideoMode(1000, 1000), "Conway's Game of Life");
    window.setFramerateLimit(10);
    bool tiles[100][100] = { false };
    RectangleShape background((Vector2f)window.getSize());
    bool steps = false;
    background.setFillColor(Color::White);
    RectangleShape grid(Vector2f(10, 10));
    grid.setOutlineColor(Color::Color(135, 135, 135));
    grid.setOutlineThickness(1);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Mouse::isButtonPressed(Mouse::Button::Left)) {
            Vector2i pos = Mouse::getPosition(window);
            Vector2f newPos(pos.x / 10, pos.y / 10);
            if ((newPos.x < 100 && newPos.y < 100) && (newPos.x >= 0 && newPos.y >= 0)) {
                cout << newPos.x << " " << newPos.y << endl;
                tiles[(int)newPos.x][(int)newPos.y] = true;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Space))
            steps = !steps;
        if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 100; j++)
                    tiles[i][j] = false;
            }
        }
        window.clear();
        window.draw(background);
        
        for (int i = 0; i < window.getSize().x / 10; i++) {
            for (int j = 0; j < window.getSize().y / 10; j++) {
                if (tiles[i][j]) {
                    RectangleShape temp(Vector2f(10, 10));
                    temp.setPosition(i * 10, j * 10);
                    temp.setFillColor(Color::Black);
                    window.draw(temp);
                }
                else {
                    window.draw(grid);
                    grid.setPosition(i * 10, j * 10);
                }
            }
        }
        if (!steps) {
            bool temp[100][100] = { false };
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 100; j++) {
                    temp[i][j] = checkSpot(tiles[i][j], getNumNeighbors(i, j, tiles));
                }
            }
            for (int i = 0; i < 100; i++) {
                memcpy(tiles[i], temp[i], 100 * sizeof(bool));
            }
            window.setTitle("Conway's Game of Life");
        }
        else
            window.setTitle("Paused");
        window.display();
    }

    return 0;
}
Vector2f operator-(const Vector2f& v1, const Vector2f& v2) {
    return Vector2f(v1.x - v2.x, v1.y - v2.y);
}
bool checkSpot(bool state, int numNeighbors) {
    if (state) {
        if (numNeighbors < 2 || numNeighbors>3)
            state = false;
    }
    else {
        if (numNeighbors == 3)
            state = true;
    }
    return state;
}
int getNumNeighbors(int x, int y, bool tiles[100][100]) {   
    int num = 0;
    num += tiles[checkX(x-1,100)][checkX(y - 1, 100)] ? 1 : 0;
    num += tiles[x][checkX(y - 1, 100)] ? 1 : 0;
    num += tiles[checkX(x + 1, 100)][checkX(y - 1, 100)] ? 1 : 0;
    num += tiles[checkX(x - 1, 100)][y] ? 1 : 0;
    num += tiles[checkX(x + 1, 100)][y] ? 1 : 0;
    num += tiles[checkX(x - 1, 100)][checkX(y + 1, 100)] ? 1 : 0;
    num += tiles[x][checkX(y + 1, 100)] ? 1 : 0;
    num += tiles[checkX(x + 1, 100)][checkX(y + 1, 100)] ? 1 : 0;
    return num;
}
int checkX(int x, int maxSize) {
    if (x >= maxSize)
        x = 0;
    else if (x < 0)
        x = maxSize - 1;
    return x;
}