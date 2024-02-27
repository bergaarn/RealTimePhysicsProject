//#include <SFML/Graphics.hpp>
#include <SFML/Includes/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <chrono>

// If pi is not defined, define it.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constant Values
const float HEIGHT = 900.0f;                      // height of the window
const float WIDTH = 1600.0f;                      // width of the window
const float windCap = 2.5f;                       // wind capacity for either direction       
const float collisionEnergy = 1.5f;               // Determines how a collision is treated by the surrounding walls/groun
const float RHO = 1.225f;                         // air density (kg/m^3)
const float CD = 0.47f;                           // drag coefficient of a sphere
const float A = 0.25f * M_PI * pow(0.05f, 2.0f);  // cross-sectional area of the ball (m^2)
const float GRAVITY = 9.82f;                      // gravity constant in sweden (m/s^2)

// Helper Functions
void windCalculation(sf::Vector2f &windSpeed, bool &windDirection)
{
    std::cout << "wind: " << windSpeed.x << "\n";
    if (windSpeed.x >= windCap || windSpeed.x <= -windCap)
    {
        if (windDirection)
        {
            windDirection = false;
            windSpeed.x = -(windCap + 0.01);
        }
        else
        {
            windDirection = true;
            windSpeed.x = -(windCap - 0.01);
        }
    }

    if (windDirection)
    {
        windSpeed.x = windSpeed.x + 0.005;
    }
    else
    {
        windSpeed.x = windSpeed.x - 0.005;
    }
}
void resetBall(sf::Vector2f &ballPos, sf::CircleShape &ball, sf::Vector2f &ballVelocity, sf::Vector2f &windSpeed, bool &windDirection)
{
    ballPos.x = (WIDTH / 2.0f);
    ballPos.y = (HEIGHT / 2.0f);
    ball.setPosition(ballPos.x, ballPos.y);
    ballVelocity.y = 0.01f;
    ballVelocity.x = 0.01f;
    windSpeed.x = 1.0f;
    windSpeed.y = 0.0f;
    windDirection = true;
}

int main()
{                                          
    
    //-----------------------------------Initialize Variables--------------------------------------//
    // Create a window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Real Time Physics Project Joel Berg");
    window.setFramerateLimit(60);

    // Font Creation
    sf::Font font;
    if (!(font.loadFromFile("QuicksandFont/Quicksand-Bold.otf")))
    {
        std::cout << "File not loaded.\n";
    }

    sf::Text velocityText;
    velocityText.setFont(font);
    velocityText.setCharacterSize(48);
    velocityText.setPosition(WIDTH / 2 - 75, HEIGHT / 8);
    velocityText.setOutlineColor(sf::Color::Black);
    velocityText.setOutlineThickness(1.5f);

    sf::Text windText;
    windText.setFont(font);
    windText.setCharacterSize(48);
    windText.setPosition(WIDTH / 2 - 40, HEIGHT / 5);
    windText.setOutlineColor(sf::Color::Black);
    windText.setOutlineThickness(1.5f);
    windText.setFillColor(sf::Color::White);

    // Create the floor
    sf::RectangleShape groundShape(sf::Vector2f(WIDTH, 25));
    groundShape.setFillColor(sf::Color::Green);
    groundShape.setPosition(sf::Vector2f(0, (HEIGHT - 25)));

    // Create the left wall
    sf::RectangleShape leftWall(sf::Vector2f(30.0f, HEIGHT * 0.3));
    leftWall.setFillColor(sf::Color::Black);
    leftWall.setPosition(sf::Vector2f(200, HEIGHT * 0.7 - 25));
    
    // Create the right wall
    sf::RectangleShape rightWall(sf::Vector2f(30.0f, HEIGHT * 0.3));
    rightWall.setFillColor(sf::Color::Black);
    rightWall.setPosition(sf::Vector2f(WIDTH - 250, HEIGHT * 0.7 - 25));
    
    // Create ball 
    sf::CircleShape ball(25.0f);
    ball.setFillColor(sf::Color::Magenta);
    ball.setOutlineThickness(1.0f);
    ball.setOutlineColor(sf::Color::White);
    ball.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);

    // Initialize ball's velocity and position
    sf::Vector2f ballVelocity(0.01f, GRAVITY);
    sf::Vector2f ballPos(WIDTH / 2.0f, HEIGHT / 2.0f);

    // Time variables
    float t = 0.0f;
    unsigned int frameCount = 0;
    float frameTime = 0.0f;
    float deltaTime = 0.0f;
    int fps = 0;
    std::chrono::duration<float> timer;

    // Wind velocity
    sf::Vector2f windVelocity(0.1, 0.0f);
    bool rightWind = true;
    //--------------------------------------------------------------------------------------------//

    //-----------------------------------------Main Loop------------------------------------------//
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto start = std::chrono::steady_clock::now();

        // Reset Ball
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && window.hasFocus())
        {
            resetBall(ballPos, ball, ballVelocity, windVelocity, rightWind);
        }

        // Determine windspeed
        windCalculation(windVelocity, rightWind);

        // Calculate the length/magnitude of ballVelocity
        float ballVelocityMagnitude = sqrt(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
        
        // Calculate the unit vector of ballVelocity
        sf::Vector2f ballVelocityUnitVector = ballVelocity / ballVelocityMagnitude;

        float dragForceMagnitude = 0.5f * RHO * ballVelocityMagnitude * ballVelocityMagnitude * CD * A;
        sf::Vector2f dragForce = -dragForceMagnitude * ballVelocityUnitVector;
        sf::Vector2f gravityForce(0.0f, GRAVITY);
        sf::Vector2f finalForce = dragForce + gravityForce;
        sf::Vector2f acceleration = finalForce / 0.05f;
        ballVelocity = ballVelocity + (acceleration - (0.05f * windVelocity)) * deltaTime;
        ballPos = ballPos + ballVelocity * deltaTime;
   
        // Apply wind resistance
        sf::Vector2f windForce = dragForceMagnitude * windVelocity;
        finalForce += windForce;
        acceleration = finalForce / 0.05f;
        ballVelocity = ballVelocity + acceleration * deltaTime;
        ballPos = ballPos + ballVelocity * deltaTime;
      
        // Left Wall Collision
        if (ballPos.x <= 230)
        {
            ballPos.x = 230;
            ballVelocity.x = -ballVelocity.x * collisionEnergy;
        }

        // Right Wall Collision
        if (ballPos.x > ((WIDTH - 250) - (2 * ball.getRadius())))
        {
            ballPos.x = (WIDTH - 250) - (2 * ball.getRadius());
            ballVelocity.x = -ballVelocity.x * collisionEnergy;
        }

        // Ground Collision
        if (ballPos.y > (groundShape.getPosition().y - (ball.getRadius() * 2)))
        {
            ballPos.y = groundShape.getPosition().y - (ball.getRadius() * 2);

            ballVelocity.y = -ballVelocity.y * collisionEnergy * 1.25f;
        }
    
        // Wind Velocity Text
        std::string shortWind = std::to_string(abs(windVelocity.x)).substr(0, 5);
        velocityText.setString(shortWind);   
        
        velocityText.setFillColor(sf::Color::Green);
        if (windVelocity.x > 1.0f || windVelocity.x < -1.0f)
        {
            velocityText.setFillColor(sf::Color::Yellow);
        }
        if (windVelocity.x > 2.0f || windVelocity.x < -2.0f)
        {
            velocityText.setFillColor(sf::Color::Red);
        }
        
        if (windVelocity.x > 0.0f)
        {
            windText.setString("-->");
        }
        else 
        {
            windText.setString("<--");
        }
        
        // Update, Clear Screen and Draw Objects
        ball.setPosition(ballPos.x, ballPos.y);
        window.clear(sf::Color::Cyan);
        window.draw(groundShape);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(ball);
        window.draw(velocityText);
        window.draw(windText);
     
        // Display Scene
        window.display();

        // Update deltaTime and fps
        auto end = std::chrono::steady_clock::now();
        timer = end - start;
        deltaTime = timer.count();
        frameTime += deltaTime;
        frameCount++;
        fps = frameCount / frameTime;

        std::cout << "framecount: " << frameCount << "\n";
        std::cout << "t: " << frameTime << "\n";
        std::cout << "fps: " << fps << "\n";
       
        window.setTitle("RealTimePhysics Project Joel Berg > Session: " + std::to_string(frameTime) + " s | " + "fps: " + std::to_string(fps));
        
        // Debug
        std::cout << "ball velocity: (" << ballVelocity.x << ", " << ballVelocity.y << ")\n";
        std::cout << "ball position: (" << ball.getPosition().x << ", " << ball.getPosition().y << ")\n\n";   
    }

    return 0;
}