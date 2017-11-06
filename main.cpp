#include <iostream>
#include "stdlib.h"
#include <SFML/Graphics.hpp>

int rnd(int m)
{
    return float(rand())/RAND_MAX*m;
}

//sf::Rect b1, b2;

//b1 = brick.GetGlobalBounds();
//b2 = ball.GetGlobalBounds();

//if(b1.intersects(b2))

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    sf::Event event;
    sf::Texture l_texture, b_texture[3], bl_texture;
    l_texture.loadFromFile("line.png");
    b_texture[0].loadFromFile("brick-blue.png");
    b_texture[1].loadFromFile("brick-green.png");
    b_texture[2].loadFromFile("brick-orange.png");
    bl_texture.loadFromFile("ball.png");
    sf::Sprite l_sprite, bricks[63], bl_sprite;
    l_sprite.setTexture(l_texture);
    bl_sprite.setTexture(bl_texture);
    int x_pos = 500;
    l_sprite.setPosition(x_pos, 500);
    int b_x_pos = 450;
    int b_y_pos = 300;

    int b_x = -20;
    int b_y = 100;
    int i = 0;
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 21; x++)
        {
            bricks[i].setPosition(b_x, b_y);
            bricks[i].setTexture(b_texture[rnd(3)]);
            b_x += 40;
            i++;
        }
        b_y += 20;
        if(i % 2 == 1) b_x = 0;
        else b_x = -20;
    }

    int x_direction = 0;
    int y_direction = 4;
    while(window.isOpen())
    {
        window.clear();
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return false;
                }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            if(x_pos > 0)
                x_pos -= 4;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            if(x_pos < 700)
                x_pos += 4;
        l_sprite.setPosition(x_pos, 500);
        window.draw(l_sprite);
        for(int i = 0; i < 63; i++) window.draw(bricks[i]);

        if(bl_sprite.getGlobalBounds().intersects(l_sprite.getGlobalBounds()))
        {
            y_direction = -4;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x_direction = -4;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x_direction = 4;
        }
        for(int i = 0; i < 63; i++) if(bl_sprite.getGlobalBounds().intersects(bricks[i].getGlobalBounds())) y_direction = 4;

        if(b_x_pos < 0 || b_x_pos > 780) x_direction -= x_direction * 2;
        b_x_pos += x_direction;
        b_y_pos += y_direction;
        bl_sprite.setPosition(b_x_pos, b_y_pos);
        window.draw(bl_sprite);
        window.display();
    }
}
