#include <SFML/Graphics.hpp>
#include <iostream>
#include "ParticleBoard.h"
using namespace std;

int main()
{
    std::cout << "1: Enter Constants Manually\nAny other key: Use Defaults" << endl;
    int input;
    int height, width;
    float coul, grav;
    cin >> input;
    if (input == 1)
    {
        cout << "Board Height: " << endl;
        cin >> height;
        cout << "Board Width: " << endl;
        cin >> width;
        cout << "Coulomb Constant: " << endl;
        cin >> coul;
        cout << "Gravitational Constant: " << endl;
        cin >> grav;
    }
    else
    {
        height = 600; width = 800; coul = 300; grav = 0.25;
    }
    ParticleBoard board(height, width, coul, grav);
    sf::RenderWindow window(sf::VideoMode(board.Width(), board.Height()), "Sim");

    window.setFramerateLimit(100);

    //Sets up two default particles in a binary orbit (not necessary)
    board.particles.push_back(ParticleBoard::Particle(1, 1, sf::Vector2f(400, 300)));
    board.particles.push_back(ParticleBoard::Particle(1, -1, sf::Vector2f(200, 300)));
    board.particles.at(0).velocity = sf::Vector2f(0, 1);
    board.particles.at(1).velocity = sf::Vector2f(0, -1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                board.LeftClick(sf::Mouse::getPosition(window), window);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                board.RightClick(sf::Mouse::getPosition(window), window);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::X)
                {
                    board.particles.clear();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    board.TogglePause();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    board.ResetVelocities();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    ParticleBoard::ToggleLockedCharge();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Z)
                {
                    board.particles.pop_back();
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::G)
                {
                    ParticleBoard::ToggleGravity();
                }
            }
        }
        if (!board.IsPaused())
        {
            board.CalcNetForces();
            board.MoveParticles();
        }
        window.clear();
        board.Draw(window);
        window.display();
    }

    return 0;
}
