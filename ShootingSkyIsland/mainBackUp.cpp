#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <vector>

using namespace std;
using namespace sf;


class Bullet {
    public :
        CircleShape bullet;
        Vector2f cVelocity;
        float maxSpeed;

        Bullet(float radius = 5.0f) : 
            cVelocity(0.0f, 0.0f), maxSpeed(10.0f) 
        {
            this->bullet.setRadius(radius);
            this->bullet.setFillColor(Color::Red);
        }
};






int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shooting Sky Island!", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape player(sf::Vector2f(150.0f, 150.0f));

    sf::Texture charactorPlayer;
    charactorPlayer.loadFromFile("res/pic/C2.png");
    player.setTexture(&charactorPlayer);

    CircleShape PosBullet;
    PosBullet.setFillColor(Color::Green);

    Bullet b1;
    vector<Bullet> bullets;
    bullets.push_back(Bullet(b1));

    /// ENEMY
    struct enemy1 {
        float lifePoint;
        bool state = 1;
        Vector2f enemyPos;
    };

    CircleShape En1(20.0f);
    En1.setFillColor(Color::Blue);

    enemy1 e1[20];

    Vector2f playerCenter;
    Vector2f mousePosWindow;
    Vector2f aimDirection;
    Vector2f aimDirectionNormal;

    sf::RectangleShape gun(sf::Vector2f(80.0f, 50.0f));
    sf::Texture Gun;
    Gun.loadFromFile("res/pic/gun.png");
    gun.setTexture(&Gun);

/*
    sf::RectangleShape bullet(sf::Vector2f(80.0f, 50.0f));
    sf::Texture Bullet;
    Bullet.loadFromFile("res/pic/bull.png");
    bullet.setTexture(&Bullet);
    */

    sf::Clock clock, clockTest;
    float deltaTime = 0.0f;
    int currentX = 0, currentY = 0;
    int posX = 0;
    int switchAnimationState = 0;
    //int BulletState = 0;
    float testtime = 0;

    sf::Vector2u Tsize = charactorPlayer.getSize();
    Tsize.x /= 3;
    Tsize.y /= 3;

    Vector2u Gunsize = Gun.getSize();
    //Vector2u Bulletsize = Bullet.getSize();

    player.setTextureRect(sf::IntRect(Tsize.x * currentX, Tsize.y * currentY, Tsize.x, Tsize.y));
    gun.setTextureRect(sf::IntRect(0, 0, Gunsize.x, Gunsize.y));
    //bullet.setTextureRect(IntRect(0, 0, Bulletsize.x, Bulletsize.y));

    player.setPosition(200, 300);
    gun.setPosition(250, 380);
    PosBullet.setPosition(250, 380);


    En1.setPosition(100.0f, 100.0f);
    


    while (window.isOpen()) {
        
        window.clear();
        sf::Event EVNT;
        while (window.pollEvent(EVNT)) {


            switch (EVNT.type) {
            case sf::Event::Closed: window.close(); break;

            case sf::Event::Resized: std::cout << EVNT.size.width << "     " << EVNT.size.height << std::endl;
            }
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            if (player.getPosition().y > 0.0f) {
                player.move(0.0f, -0.1f);
                gun.move(0.0f, -0.1f);
                PosBullet.move(0.0f, -0.1f);
            }
            currentY = 0;
            switchAnimationState = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            if (player.getPosition().y < 860) {
                player.move(0.0f, 0.1f);
                gun.move(0.0f, 0.1f);
                PosBullet.move(0.0f, 0.1f);
            }
            currentY = 0;
            switchAnimationState = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            if (player.getPosition().x > 0.0f) {
                player.move(-0.1f, 0.0f);
                gun.move(-0.1f, 0.0f);
                PosBullet.move(-0.1f, 0.0f);
            }
            currentY = 1;
            switchAnimationState = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            if (player.getPosition().x < 1780.0f) {
                player.move(0.1f, 0.0f);
                gun.move(0.1f, 0.0f);
                PosBullet.move(0.1f, 0.0f);
            }
            currentY = 2;
            switchAnimationState = 1;
        }

        //SHOOT
        if (Mouse::isButtonPressed(Mouse::Left)) {
            b1.bullet.setPosition(playerCenter);
            b1.cVelocity = aimDirectionNormal * b1.maxSpeed;

            bullets.push_back(Bullet(b1));

            
        }



        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].bullet.move(bullets[i].cVelocity);
        }

        //Update
        playerCenter = Vector2f(PosBullet.getPosition().x + PosBullet.getRadius(), PosBullet.getPosition().y + PosBullet.getRadius());
        mousePosWindow = Vector2f(Mouse::getPosition(window));
        aimDirection = mousePosWindow - playerCenter;
        aimDirectionNormal = aimDirection / (float)(sqrt(pow(aimDirection.x, 2)) + sqrt(pow(aimDirection.y, 2)));

        if (testtime > 1.0) {
            
            if (En1.getPosition().x > player.getPosition().x) {
                En1.move(-0.1f, 0.0f);
            }
            else {
                En1.move(0.1f, 0.0f);
            }
            if (En1.getPosition().y > player.getPosition().y) {
                En1.move(0.0f, -0.1f);
            }
            else {
                En1.move(0.0f, 0.1f);
            }
                
            
            testtime = clockTest.restart().asSeconds();
        }
        testtime = clockTest.getElapsedTime().asSeconds();
        

        if (switchAnimationState == 1) {
            if (deltaTime >= 0.25) {
                deltaTime = clock.restart().asSeconds();
                //player.setTextureRect(sf::IntRect(Tsize.x * currentX, 0, Tsize.x , Tsize.y));
                player.setTextureRect(sf::IntRect(Tsize.x * currentX, Tsize.y * currentY, Tsize.x, Tsize.y));
                //printf("%f", deltaTime);

                if (currentX >= 2) {
                    posX = 1;
                }
                if (currentX <= 0) {
                    posX = 0;
                }
                if (posX == 0) {
                    currentX++;
                }
                else {
                    currentX--;
                }

            }
            deltaTime = clock.getElapsedTime().asSeconds();
        }


        if (switchAnimationState == 0) {
            currentY = 0;
            player.setTextureRect(sf::IntRect(Tsize.x * currentX, Tsize.y * currentY, Tsize.x, Tsize.y));
        }
        switchAnimationState = 0;

        for (size_t i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i].bullet);

            if ((bullets[i].bullet.getPosition().x < 0.0f || bullets[i].bullet.getPosition().x > window.getSize().x) 
                || (bullets[i].bullet.getPosition().y < 0.0f || bullets[i].bullet.getPosition().y > window.getSize().y)) {
                bullets.erase(bullets.begin() + i);
            }
        }

        window.draw(player);
        window.draw(gun);
        window.draw(En1);
        window.display();



    }
    return 0;
}
