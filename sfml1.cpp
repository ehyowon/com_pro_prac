#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;
using namespace sf;

class MyCircle {
public:
    double x, y, radius;

    MyCircle(double x, double y, double radius) : x(x), y(y), radius(radius) {}

    // 충돌 테스트 함수
    bool collisionTest(const MyCircle& obj) const {
        float distance = sqrt(pow(x - obj.x, 2) + pow(y - obj.y, 2));
        float sumRadii = radius + obj.radius;

        return distance <= sumRadii;
    }
};

int main(){
    int nX = 300;
    int nY = 300;

    RenderWindow window(VideoMode(nX, nY), "Moving Ball");

    window.setFramerateLimit(100);

    MyCircle circle1(50, 50, 10);
    MyCircle circle2(100, 100, 20);

    CircleShape Circle1(circle1.radius);
    Circle1.setPosition(circle1.x, circle1.y);
    Circle1.setFillColor(Color(255, 0, 0));
    Circle1.setPointCount(50);

    CircleShape Circle2(circle2.radius);
    Circle2.setPosition(circle2.x, circle2.y);
    Circle2.setFillColor(Color(255, 255, 255));

    Text text;
    Font font;
    int t = 0;
    
    if (!font.loadFromFile("/Users/ehyowon/Desktop/2023-2/컴프실/project/arial.ttf")) {
        return 42; // Robust error handling!
    }

    text.setFont(font);
    text.setString(to_string(t) + " sec");
    text.setCharacterSize(20);
    text.setFillColor(Color::Blue);
    text.setPosition(0, 0);

    clock_t time = clock();

    // 여기서부터 게임 루프
    while (window.isOpen()){
        // 이벤트 검사 및 처리
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            circle1.y -= 2;
        }else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            circle1.y += 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            circle1.x -= 2;
        }else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            circle1.x += 2;
        }

        Circle1.setPosition(circle1.x, circle1.y);
        
        if (circle1.collisionTest(circle2)) {
            cout << "True: Circles are colliding!" << endl;
        } else {
            cout << "False: Circles are not colliding." << endl;
        }       
        
        time = clock();
        time = time / CLOCKS_PER_SEC;
        text.setString(to_string(time) + " sec");

        // 화면을 지운다. 
        window.clear();

        // 화면에 원을 그린다.
        window.draw(Circle1);
        window.draw(Circle2);
        window.draw(text);

        // 화면을 표시한다. 
        window.display();
    }

    return 0;
}