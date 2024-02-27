/*
#include <SFML/Graphics.hpp>
const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;
const float BALL_RADIUS = 10.0f;
const float PADDLE_WIDTH = 10.0f;
const float PADDLE_HEIGHT = 100.0f;
const float BALL_VELOCITY = 300.0f;

void resetGame(sf::CircleShape& ball, sf::RectangleShape& leftPaddle, sf::RectangleShape& rightPaddle, sf::Vector2f& ballVelocity)
{
    // Reset the ball position
    ball.setPosition(WIDTH / 2, HEIGHT / 2);

    // Reset the ball velocity
    ballVelocity = { BALL_VELOCITY, BALL_VELOCITY };

    // Reset the paddle positions
    leftPaddle.setPosition(PADDLE_WIDTH / 2, HEIGHT / 2);
    rightPaddle.setPosition(WIDTH - PADDLE_WIDTH / 2, HEIGHT / 2);
}

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong");
    window.setFramerateLimit(60);

    // Create the ball
    sf::CircleShape ball(BALL_RADIUS);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(BALL_RADIUS, BALL_RADIUS);
    ball.setPosition(WIDTH / 2, HEIGHT / 2);

    // Create the paddles
    sf::RectangleShape leftPaddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setOrigin(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);
    leftPaddle.setPosition(PADDLE_WIDTH / 2, HEIGHT / 2);

    sf::RectangleShape rightPaddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setOrigin(PADDLE_WIDTH / 2, PADDLE_HEIGHT / 2);
    rightPaddle.setPosition(WIDTH - PADDLE_WIDTH / 2, HEIGHT / 2);

    // Set the ball's initial velocity
    sf::Vector2f ballVelocity(BALL_VELOCITY, BALL_VELOCITY);

    sf::Clock clock;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Update the ball's position based on its velocity
        float dt = clock.restart().asSeconds();
        ball.move(ballVelocity * dt);

        // Check for collision with the top or bottom of the window
        if (ball.getPosition().y < BALL_RADIUS ||
            ball.getPosition().y > HEIGHT - BALL_RADIUS)
        {
            ballVelocity.y *= -1;
        }

        // Check for collision with the left or right paddles
        if (ball.getPosition().x < PADDLE_WIDTH + BALL_RADIUS &&
            ball.getPosition().y >= leftPaddle.getPosition().y - PADDLE_HEIGHT / 2 &&
            ball.getPosition().y <= leftPaddle.getPosition().y + PADDLE_HEIGHT / 2)
        {
            ballVelocity.x = -1;
        }

        if (ball.getPosition().x > WIDTH - PADDLE_WIDTH - BALL_RADIUS &&
            ball.getPosition().y >= rightPaddle.getPosition().y - PADDLE_HEIGHT / 2 &&
            ball.getPosition().y <= rightPaddle.getPosition().y + PADDLE_HEIGHT / 2)
        {
            ballVelocity.x = -1;
        }

        // Move the paddles based on user input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            leftPaddle.move(0, -300 * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            leftPaddle.move(0, 300 * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            rightPaddle.move(0, -300 * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            rightPaddle.move(0, 300 * dt);
        }

        // Keep the paddles within the window
        if (leftPaddle.getPosition().y - PADDLE_HEIGHT / 2 < 0)
        {
            leftPaddle.setPosition(leftPaddle.getPosition().x, PADDLE_HEIGHT / 2);
        }

        if (leftPaddle.getPosition().y + PADDLE_HEIGHT / 2 > HEIGHT)
        {
            leftPaddle.setPosition(leftPaddle.getPosition().x, HEIGHT - PADDLE_HEIGHT / 2);
        }

        if (rightPaddle.getPosition().y - PADDLE_HEIGHT / 2 < 0)
        {
            rightPaddle.setPosition(rightPaddle.getPosition().x, PADDLE_HEIGHT / 2);
        }

        if (rightPaddle.getPosition().y + PADDLE_HEIGHT / 2 > HEIGHT)
        {
            rightPaddle.setPosition(rightPaddle.getPosition().x, HEIGHT - PADDLE_HEIGHT / 2);
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the ball and paddles
        window.draw(ball);
        window.draw(leftPaddle);
        window.draw(rightPaddle);

        // Display the window
        window.display();
    }

    return 0;
}
*/