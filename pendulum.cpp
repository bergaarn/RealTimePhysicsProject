/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float L = 200.f;
const float G = 9.81f;
const float DT = 0.01f;

class Pendulum {
public:
    Pendulum(float length, float angle, float angular_velocity, float mass, float damping) :
        m_length(length), m_angle(angle), m_angular_velocity(angular_velocity),
        m_mass(mass), m_damping(damping) {
        m_ball.setRadius(10.f);
        m_ball.setFillColor(sf::Color::Red);
        m_string.setFillColor(sf::Color::Black);
        m_string.setSize(sf::Vector2f(5.f, length));
        m_string.setOrigin(2.5f, 0.f);
        m_string.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
        update_ball_position();
    }

    void update(float force) {
        float angular_acceleration = -G / m_length * sin(m_angle) - m_damping / m_mass * m_angular_velocity + force / m_mass;
        m_angular_velocity += angular_acceleration * DT;
        m_angle += m_angular_velocity * DT;
        update_ball_position();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_string);
        window.draw(m_ball);
    }

private:
    void update_ball_position() {
        float x = WINDOW_WIDTH / 2.f + m_length * sin(m_angle);
        float y = WINDOW_HEIGHT / 2.f + m_length * cos(m_angle);
        m_ball.setPosition(x, y);
        m_string.setRotation(180.f / M_PI * (M_PI / 2.f - m_angle));
        m_string.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
    }

    float m_length;
    float m_angle;
    float m_angular_velocity;
    float m_mass;
    float m_damping;
    sf::CircleShape m_ball;
    sf::RectangleShape m_string;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pendulum Simulation");
    Pendulum pendulum(L, M_PI / 4.f, 0.f, 1.f, 0.1f);
    float force = 0.f;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    force += 0.1f;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    force -= 0.1f;
                }
            }
        }
        window.clear(sf::Color::White);
        pendulum.update(force);
        pendulum.draw(window);
        window.display();
        sf::sleep(sf::seconds(DT));
    }
    return 0;
}
*/