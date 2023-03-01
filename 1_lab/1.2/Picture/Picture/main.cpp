#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


std::vector<std::unique_ptr<sf::Shape>> InitializeLetters() {
    std::vector<std::unique_ptr<sf::Shape>> figures;

    //пр€моугольна€ фара
    auto rectangularHeadlight = std::make_unique<sf::RectangleShape>();
    rectangularHeadlight->setSize(sf::Vector2f(5, 20));
    rectangularHeadlight->setPosition(950, 330);
    rectangularHeadlight->setFillColor(sf::Color{ 255, 140, 0 });
    rectangularHeadlight->setOutlineColor(sf::Color::Black);
    rectangularHeadlight->setOutlineThickness(5);
    figures.push_back(move(rectangularHeadlight));

    //кругла€ фара
    auto roundHeadlight = std::make_unique<sf::CircleShape>(8);
    roundHeadlight->setPosition(940, 360);
    roundHeadlight->setFillColor(sf::Color{ 255, 140, 0 });
    roundHeadlight->setOutlineColor(sf::Color::Black);
    roundHeadlight->setOutlineThickness(5);
    figures.push_back(move(roundHeadlight));

    //кузов
    auto body = std::make_unique<sf::RectangleShape>();
    body->setSize(sf::Vector2f(900, 200));
    body->setPosition(45, 200);
    body->setFillColor(sf::Color{ 0, 139, 139 });
    body->setOutlineColor(sf::Color::Black);
    body->setOutlineThickness(5);
    figures.push_back(move(body));

    //нижн€€ лини€
    auto bottomLine = std::make_unique<sf::RectangleShape>();
    bottomLine->setSize(sf::Vector2f(900, 5));
    bottomLine->setPosition(45, 360);
    bottomLine->setFillColor(sf::Color::Black);
    figures.push_back(move(bottomLine));

    //верхн€€ лини€
    auto topLine = std::make_unique<sf::RectangleShape>();
    topLine->setSize(sf::Vector2f(900, 5));
    topLine->setPosition(45, 210);
    topLine->setFillColor(sf::Color::Black);
    figures.push_back(move(topLine));

    //лева€ рамка колеса
    auto leftBorderWheel = std::make_unique<sf::CircleShape>(60);
    leftBorderWheel->setPosition(230, 340);
    leftBorderWheel->setFillColor(sf::Color::White);
    leftBorderWheel->setOutlineColor(sf::Color::Black);
    leftBorderWheel->setOutlineThickness(5);
    figures.push_back(move(leftBorderWheel));

    //права€ рамка колеса
    auto rightBorderWheel = std::make_unique<sf::CircleShape>(60);
    rightBorderWheel->setPosition(650, 340);
    rightBorderWheel->setFillColor(sf::Color::White);
    rightBorderWheel->setOutlineColor(sf::Color::Black);
    rightBorderWheel->setOutlineThickness(5);
    figures.push_back(move(rightBorderWheel));

    //левый закрывающий пр€моугольник
    auto leftBlock = std::make_unique<sf::RectangleShape>();
    leftBlock->setSize(sf::Vector2f(140, 80));
    leftBlock->setPosition(225, 405);
    leftBlock->setFillColor(sf::Color::White);
    figures.push_back(move(leftBlock));

    //правый закрывающий пр€моугольник
    auto rightBlock = std::make_unique<sf::RectangleShape>();
    rightBlock->setSize(sf::Vector2f(140, 80));
    rightBlock->setPosition(645, 405);
    rightBlock->setFillColor(sf::Color::White);
    figures.push_back(move(rightBlock));

    //левое колесо
    auto leftWheel = std::make_unique<sf::CircleShape>(40);
    leftWheel->setPosition(250, 355);
    leftWheel->setFillColor(sf::Color{ 128, 128, 128 });
    leftWheel->setOutlineColor(sf::Color::Black);
    leftWheel->setOutlineThickness(10);
    figures.push_back(move(leftWheel));

    //левый диск
    auto leftDisk = std::make_unique<sf::CircleShape>(20);
    leftDisk->setPosition(270, 374);
    leftDisk->setFillColor(sf::Color::Black);
    figures.push_back(move(leftDisk));

    //правое колесо
    auto rightWheel = std::make_unique<sf::CircleShape>(40);
    rightWheel->setPosition(670, 355);
    rightWheel->setFillColor(sf::Color{ 128, 128, 128 });
    rightWheel->setOutlineColor(sf::Color::Black);
    rightWheel->setOutlineThickness(10);
    figures.push_back(move(rightWheel));

    //правый диск
    auto rightDisk = std::make_unique<sf::CircleShape>(20);
    rightDisk->setPosition(690, 374);
    rightDisk->setFillColor(sf::Color::Black);
    figures.push_back(move(rightDisk));

    //заднее окно
    auto rearWindow = std::make_unique<sf::RectangleShape>();
    rearWindow->setSize(sf::Vector2f(50, 100));
    rearWindow->setPosition(45, 225);
    rearWindow->setFillColor(sf::Color{ 0, 191, 255 });
    rearWindow->setOutlineColor(sf::Color::Black);
    rearWindow->setOutlineThickness(5);
    figures.push_back(move(rearWindow));

    //задн€€ лева€ дверь
    auto rearLeftDoor = std::make_unique<sf::RectangleShape>();
    rearLeftDoor->setSize(sf::Vector2f(30, 150));
    rearLeftDoor->setPosition(140, 250);
    rearLeftDoor->setFillColor(sf::Color{ 0, 191, 255 });
    rearLeftDoor->setOutlineColor(sf::Color::Black);
    rearLeftDoor->setOutlineThickness(5);
    figures.push_back(move(rearLeftDoor));

    //задн€€ права€ дверь
    auto rearRightDoor = std::make_unique<sf::RectangleShape>();
    rearRightDoor->setSize(sf::Vector2f(30, 150));
    rearRightDoor->setPosition(170, 250);
    rearRightDoor->setFillColor(sf::Color{ 0, 191, 255 });
    rearRightDoor->setOutlineColor(sf::Color::Black);
    rearRightDoor->setOutlineThickness(5);
    figures.push_back(move(rearRightDoor));

    //среднее левое окно
    auto middleLeftWindow = std::make_unique<sf::RectangleShape>();
    middleLeftWindow->setSize(sf::Vector2f(130, 100));
    middleLeftWindow->setPosition(230, 225);
    middleLeftWindow->setFillColor(sf::Color{ 0, 191, 255 });
    middleLeftWindow->setOutlineColor(sf::Color::Black);
    middleLeftWindow->setOutlineThickness(5);
    figures.push_back(move(middleLeftWindow));

    //среднее правое окно
    auto middleRightWindow = std::make_unique<sf::RectangleShape>();
    middleRightWindow->setSize(sf::Vector2f(130, 100));
    middleRightWindow->setPosition(400, 225);
    middleRightWindow->setFillColor(sf::Color{ 0, 191, 255 });
    middleRightWindow->setOutlineColor(sf::Color::Black);
    middleRightWindow->setOutlineThickness(5);
    figures.push_back(move(middleRightWindow));

    //средн€€ лева€ дверь
    auto middleLeftDoor = std::make_unique<sf::RectangleShape>();
    middleLeftDoor->setSize(sf::Vector2f(30, 150));
    middleLeftDoor->setPosition(560, 250);
    middleLeftDoor->setFillColor(sf::Color{ 0, 191, 255 });
    middleLeftDoor->setOutlineColor(sf::Color::Black);
    middleLeftDoor->setOutlineThickness(5);
    figures.push_back(move(middleLeftDoor));

    //средн€€ права€ дверь
    auto middleRightDoor = std::make_unique<sf::RectangleShape>();
    middleRightDoor->setSize(sf::Vector2f(30, 150));
    middleRightDoor->setPosition(590, 250);
    middleRightDoor->setFillColor(sf::Color{ 0, 191, 255 });
    middleRightDoor->setOutlineColor(sf::Color::Black);
    middleRightDoor->setOutlineThickness(5);
    figures.push_back(move(middleRightDoor));

    //переднее окно
    auto frontWindow = std::make_unique<sf::RectangleShape>();
    frontWindow->setSize(sf::Vector2f(130, 100));
    frontWindow->setPosition(640, 225);
    frontWindow->setFillColor(sf::Color{ 0, 191, 255 });
    frontWindow->setOutlineColor(sf::Color::Black);
    frontWindow->setOutlineThickness(5);
    figures.push_back(move(frontWindow));

    //водительское окно
    auto driverWindow = std::make_unique<sf::RectangleShape>();
    driverWindow->setSize(sf::Vector2f(90, 100));
    driverWindow->setPosition(855, 225);
    driverWindow->setFillColor(sf::Color{ 0, 191, 255 });
    driverWindow->setOutlineColor(sf::Color::Black);
    driverWindow->setOutlineThickness(5);
    figures.push_back(move(driverWindow));

    //держатель штанг
    auto rodHolder = std::make_unique<sf::RectangleShape>();
    rodHolder->setSize(sf::Vector2f(100, 20));
    rodHolder->setPosition(400, 175);
    rodHolder->setFillColor(sf::Color{ 0, 139, 139 });
    rodHolder->setOutlineColor(sf::Color::Black);
    rodHolder->setOutlineThickness(5);
    figures.push_back(move(rodHolder));

    //лева€ штанга
    auto leftRod = std::make_unique<sf::RectangleShape>();
    leftRod->setSize(sf::Vector2f(450, 5));
    leftRod->setPosition(30, 30);
    leftRod->setFillColor(sf::Color::Black);
    leftRod->rotate(18);
    figures.push_back(move(leftRod));

    //права€ штанга
    auto rightRod = std::make_unique<sf::RectangleShape>();
    rightRod->setSize(sf::Vector2f(346, 5));
    rightRod->setPosition(120, 30);
    rightRod->setFillColor(sf::Color::Black);
    rightRod->rotate(24);
    figures.push_back(move(rightRod));

    //провода
    auto wires = std::make_unique<sf::RectangleShape>();
    wires->setSize(sf::Vector2f(1200, 10));
    wires->setPosition(0, 30);
    wires->setFillColor(sf::Color::Black);
    figures.push_back(move(wires));


    return figures;
}

void Render(sf::RenderWindow& window, std::vector<std::unique_ptr<sf::Shape>>& letters) {
    window.clear(sf::Color::White);
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
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Picture");
    window.setVerticalSyncEnabled(true);

    LaunchAWindow(window);

    return 0;
}