/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float BALL_RADIUS = 20.f;
const float DT = 0.01f;
const float GRAVITY = 9.81f;
const float AIR_DENSITY = 1.2f;
const float BALL_MASS = 0.2f;
const float SPIN_RATE = 10.f;
const float SPIN_FACTOR = 0.5f;
const float MAX_SPEED = 50.f;

class Ball {
public:
    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius, float spin, float drag) :
        m_position(position), m_velocity(velocity), m_radius(radius), m_spin(spin), m_drag(drag) {
        m_circle.setRadius(m_radius);
        m_circle.setFillColor(sf::Color::Red);
        m_circle.setOrigin(m_radius, m_radius);
        m_circle.setPosition(m_position);
    }

    void update(float force) {
        float lift = 0.5f * AIR_DENSITY * M_PI * pow(m_radius, 2) * m_spin * m_velocity.y;
        float drag = 0.5f * AIR_DENSITY * M_PI * pow(m_radius, 2) * m_drag * pow(m_velocity.x, 2);
        sf::Vector2f acceleration(-drag / BALL_MASS, GRAVITY + lift / BALL_MASS);
        m_velocity += (acceleration + sf::Vector2f(0.f, force / BALL_MASS)) * DT;
        m_velocity.x = std::min(std::max(m_velocity.x, -MAX_SPEED), MAX_SPEED);
        m_velocity.y = std::min(std::max(m_velocity.y, -MAX_SPEED), MAX_SPEED);
        m_position += m_velocity * DT;
        m_circle.setPosition(m_position);
        m_circle.rotate(-m_spin * SPIN_FACTOR * DT);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_circle);
    }

    sf::Vector2f get_position() const {
        return m_position;
    }

    float get_radius() const {
        return m_radius;
    }

private:
    sf::CircleShape m_circle;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_radius;
    float m_spin;
    float m_drag;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Magnus Effect Simulation");
    Ball ball(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f), sf::Vector2f(20.f, 0.f), BALL_RADIUS, SPIN_RATE, 0.47f);
    float force = 0.f;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    force += 5.f;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    force -= 5.f;
                }
            }
        }
        window.clear(sf::Color::White);
        ball.update(force);
        ball.draw(window);
        window.display();
        sf::sleep(sf::seconds(DT));
    }
    return 0;
}
*/