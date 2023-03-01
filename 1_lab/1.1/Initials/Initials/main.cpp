#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


std::vector<std::unique_ptr<sf::Shape>> InitializeLetters() {
    std::vector<std::unique_ptr<sf::Shape>> figures;

    //П

    //левая сторона буквы П
    auto leftRectangleP = std::make_unique<sf::RectangleShape>();
    leftRectangleP->setSize(sf::Vector2f(50, 400));
    leftRectangleP->setPosition(100, 300);
    leftRectangleP->setFillColor(sf::Color::Cyan);
    figures.push_back(move(leftRectangleP));

    //верхняя сторона буквы П
    auto topRectangleP = std::make_unique<sf::RectangleShape>();
    topRectangleP->setSize(sf::Vector2f(250, 50));
    topRectangleP->setPosition(100, 300);
    topRectangleP->setFillColor(sf::Color::Cyan);
    figures.push_back(move(topRectangleP));

    //правая сторона буквы П
    auto rightRectangleP = std::make_unique<sf::RectangleShape>();
    rightRectangleP->setSize(sf::Vector2f(50, 400));
    rightRectangleP->setPosition(300, 300);
    rightRectangleP->setFillColor(sf::Color::Cyan);
    figures.push_back(move(rightRectangleP));

    //Д

    //левая нога Д
    auto leftFootD = std::make_unique<sf::RectangleShape>();
    leftFootD->setSize(sf::Vector2f(50, 120));
    leftFootD->setPosition(450, 580);
    leftFootD->setFillColor(sf::Color::Magenta);
    figures.push_back(move(leftFootD));

    //основание Д
    auto baseD = std::make_unique<sf::RectangleShape>();
    baseD->setSize(sf::Vector2f(250, 50));
    baseD->setPosition(450, 580);
    baseD->setFillColor(sf::Color::Magenta);
    figures.push_back(move(baseD));

    //правая нога Д
    auto rightFootD = std::make_unique<sf::RectangleShape>();
    rightFootD->setSize(sf::Vector2f(50, 120));
    rightFootD->setPosition(650, 580);
    rightFootD->setFillColor(sf::Color::Magenta);
    figures.push_back(move(rightFootD));

    //левая сторона головы Д
    auto leftSideHeadD = std::make_unique<sf::RectangleShape>();
    leftSideHeadD->setSize(sf::Vector2f(50, 280));
    leftSideHeadD->setPosition(500, 300);
    leftSideHeadD->setFillColor(sf::Color::Magenta);
    figures.push_back(move(leftSideHeadD));

    //верхняя сторона головы Д
    auto topSideHeadD = std::make_unique<sf::RectangleShape>();
    topSideHeadD->setSize(sf::Vector2f(150, 50));
    topSideHeadD->setPosition(500, 300);
    topSideHeadD->setFillColor(sf::Color::Magenta);
    figures.push_back(move(topSideHeadD));

    //правая сторона головы Д
    auto rightSideHeadD = std::make_unique<sf::RectangleShape>();
    rightSideHeadD->setSize(sf::Vector2f(50, 280));
    rightSideHeadD->setPosition(600, 300);
    rightSideHeadD->setFillColor(sf::Color::Magenta);
    figures.push_back(move(rightSideHeadD));

    //И

    //левая сторона буквы И
    auto leftSideI = std::make_unique<sf::RectangleShape>();
    leftSideI->setSize(sf::Vector2f(50, 400));
    leftSideI->setPosition(800, 300);
    leftSideI->setFillColor(sf::Color::Yellow);
    figures.push_back(move(leftSideI));

    //средняя палка И
    auto middleStickI = std::make_unique<sf::RectangleShape>();
    middleStickI->setSize(sf::Vector2f(420, 50));
    middleStickI->setPosition(800, 675);
    middleStickI->rotate(-61);
    middleStickI->setFillColor(sf::Color::Yellow);
    figures.push_back(move(middleStickI));

    //правая сторона буквы И
    auto rightSideI = std::make_unique<sf::RectangleShape>();
    rightSideI->setSize(sf::Vector2f(50, 400));
    rightSideI->setPosition(1000, 300);
    rightSideI->setFillColor(sf::Color::Yellow);
    figures.push_back(move(rightSideI));

    return figures;
}

void Render(sf::RenderWindow& window, std::vector<std::unique_ptr<sf::Shape>>& letters) {
    window.clear();
    for (size_t i = 0; i < letters.size(); i++) {
        window.draw(*letters[i]);
    }
    window.display();
}

void LaunchAWindow(sf::RenderWindow& window) {

    auto letters = InitializeLetters();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        Render(window, letters);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1150, 800), "Initials");
    window.setVerticalSyncEnabled(true);

    LaunchAWindow(window);

    return 0;
}