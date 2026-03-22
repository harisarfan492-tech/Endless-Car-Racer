//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//class Player {
//private:
//    sf::Texture texture;
//    sf::Sprite  sprite;
//
//public:
//    Player() : sprite(texture) {
//        if (!texture.loadFromFile("Sprite 90.jpg")) {
//            std::cout << "Error: Could not load player car texture.\n";
//        }
//
//        sprite.setTexture(texture, true);
//
//        auto size = texture.getSize();
//        sprite.setOrigin({ size.x / 2.f, size.y / 2.f });
//        sprite.setScale({ 0.1f, 0.1f });
//        sprite.setPosition({ 656.f, 700.f });
//    }
//
//    void handleInput(float dt) {
//        float moveSpeed = 300.f;
//        sprite.setRotation(sf::degrees(90.f));
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
//            sprite.move({ -moveSpeed * dt, 0.f });
//            sprite.setRotation(sf::degrees(75.f));
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
//            sprite.move({ moveSpeed * dt, 0.f });
//            sprite.setRotation(sf::degrees(105.f));
//        }
//
//        sf::Vector2f pos = sprite.getPosition();
//        if (pos.x < 50.f)    sprite.setPosition({ 50.f,    pos.y });
//        if (pos.x > 1262.f)  sprite.setPosition({ 1262.f,  pos.y });
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(sprite);
//    }
//
//    sf::FloatRect getBounds() const {
//        return sprite.getGlobalBounds();
//    }
//};
//
//class Enemy {
//private:
//    sf::Texture texture;
//    sf::Texture buggyTexture;
//    sf::Sprite  sprite;
//    sf::Sprite  buggy;
//    float lanes[7] = { 112.f, 325.f, 430.f, 532.f, 656.f, 882.f, 929.f };
//
//public:
//    Enemy() : sprite(texture), buggy(buggyTexture) {
//        if (!texture.loadFromFile("enemycar2.png")) {
//            std::cout << "Error: Could not load enemy car texture.\n";
//        }
//        if (!buggyTexture.loadFromFile("buggy.png")) {
//            std::cout << "Error: Could not load buggy texture.\n";
//        }
//
//        sprite.setTexture(texture, true);
//        buggy.setTexture(buggyTexture, true);
//
//        auto size = texture.getSize();
//        sprite.setOrigin({ size.x / 2.f, size.y / 2.f });
//        sprite.setScale({ 0.05f, 0.05f });
//
//        auto bsize = buggyTexture.getSize();
//        buggy.setOrigin({ bsize.x / 2.f, bsize.y / 2.f });
//        buggy.setScale({ 1.25f, 1.25f });
//
//        resetPosition();
//    }
//
//    void resetPosition() {
//        sprite.setPosition({ lanes[std::rand() % 7], -100.f });
//        buggy.setPosition({ lanes[std::rand() % 7], -300.f }); 
//    }
//
//    void update(float dt, bool isBoosting, float difficulty) {
//        float fallSpeed = (isBoosting ? 400.f : 200.f) * difficulty;
//        sprite.move({ 0.f, fallSpeed * dt });
//        buggy.move({ 0.f, fallSpeed * dt });
//
//        if (sprite.getPosition().y > 900.f) resetPosition();
//        if (buggy.getPosition().y > 900.f) resetPosition();
//    }
//
//    void draw(sf::RenderWindow& window) {   
//        window.draw(sprite);
//        window.draw(buggy);
//    }
//
//    sf::FloatRect getBounds() const {
//        return sprite.getGlobalBounds();
//    }
//};
//
//class Road {
//private:
//    sf::Texture texture;
//    sf::Sprite  road1;
//    sf::Sprite  road2;
//
//public:
//    Road() : road1(texture), road2(texture) {
//        if (!texture.loadFromFile("Highway.png")) {
//            std::cout << "Error: Could not load road texture.\n";
//        }
//
//        road1.setTexture(texture, true);
//        road2.setTexture(texture, true);
//
//        float height = static_cast<float>(texture.getSize().y);
//        road1.setPosition({ 0.f, 0.f });
//        road2.setPosition({ 0.f, -height });
//    }
//
//    void update(float dt, bool isBoosting, float difficulty) {
//        float scrollSpeed = (isBoosting ? 500.f : 100.f) * difficulty;
//        road1.move({ 0.f, scrollSpeed * dt });
//        road2.move({ 0.f, scrollSpeed * dt });
//
//        float height = static_cast<float>(texture.getSize().y);
//
//        if (road1.getPosition().y >= height)
//            road1.setPosition({ 0.f, road2.getPosition().y - height });
//        if (road2.getPosition().y >= height)
//            road2.setPosition({ 0.f, road1.getPosition().y - height });
//    }
//
//    void draw(sf::RenderWindow& window) {
//        window.draw(road1);
//        window.draw(road2);
//    }
//};
//
//class Game {
//private:
//    sf::RenderWindow window;
//    Player player;
//    Enemy  enemy;
//    Road   road;
//
//    int score = 0;
//    float diffculty = 1.0f;
//    sf::Font font;
//    sf::Text scoreText;
//    sf::Clock scoreClock;
//    sf::Clock deltaClock;
//
//public:
//    Game() : window(sf::VideoMode({ 1312, 816 }), "Endless Runner"),
//        scoreText(font) {
//        std::srand(static_cast<unsigned>(std::time(nullptr)));
//        window.setFramerateLimit(60);
//
//        if (!font.openFromFile("arial.ttf")) {
//            std::cout << "Error: Could not load font.\n";
//        }
//
//        scoreText.setString("Score: 0");
//        scoreText.setCharacterSize(30);
//        scoreText.setFillColor(sf::Color::White);
//        scoreText.setPosition({ 20.f, 20.f });
//    }
//
//    void run() {
//        while (window.isOpen()) {
//            processEvents();
//            update();
//            render();
//        }
//    }
//
//private:
//    void processEvents() {
//        while (const std::optional event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>()) {
//                window.close();
//            }
//        }
//    }
//
//    void update() {
//        float dt = deltaClock.restart().asSeconds();
//        bool  isBoosting = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);
//
//        road.update(dt, isBoosting, diffculty);
//        player.handleInput(dt);
//        enemy.update(dt, isBoosting, diffculty);
//		diffculty += dt * 0.05f;
//        if (scoreClock.getElapsedTime().asSeconds() >= 0.1f) {
//            score += isBoosting ? 2 : 1;
//            scoreText.setString("Score: " + std::to_string(score));
//            scoreClock.restart();
//        }
//
//        if (player.getBounds().findIntersection(enemy.getBounds())) {
//            std::cout << "BOOM! CRASH!\n";
//            std::cout << "Final Score: " << score << "\n";
//            window.close();
//        }
//    }
//
//    void render() {
//        window.clear(sf::Color::Black);
//        road.draw(window);
//        enemy.draw(window);
//        player.draw(window);
//        window.draw(scoreText);
//        window.display();
//    }
//};
//
//int main() {
//    Game game;
//    game.run();
//    return 0;
//}