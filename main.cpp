#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
class ball :public sf::CircleShape
{
public:
    sf::Vector2f velocity;
    void step()
    {
        this->move(this->velocity);
        this->rotate(((this->velocity.x > 0) - (this->velocity.x < 0))*sqrt(pow(this->velocity.x,2)+pow(this->velocity.y,2))/8*180/3.14);
    };
    bool spadanie;
};
bool kolizja(sf::Vector2f pierwsze,sf::Vector2f drugie,float odleglosc)
{
            return sqrt(pow(pierwsze.x-drugie.x,2)+pow(pierwsze.y-drugie.y,2))<odleglosc;
}
float dotpro(sf::Vector2f pierwsze,sf::Vector2f drugie){return pierwsze.x*drugie.x+pierwsze.y*drugie.y;}
void zderzenie(ball* pierwsza,ball* druga,float reqdis)
{
    float mod3=sqrt(pow(pierwsza->getPosition().x-druga->getPosition().x,2)+pow(pierwsza->getPosition().y-druga->getPosition().y,2));
    sf::Vector2f odleglosc=sf::Vector2f(pierwsza->getPosition().x-druga->getPosition().x,pierwsza->getPosition().y-druga->getPosition().y);
    sf::Vector2f odlegloscminus=sf::Vector2f(-1*(pierwsza->getPosition().x-druga->getPosition().x),-1*(pierwsza->getPosition().y-druga->getPosition().y));
    float skladowa1=dotpro(pierwsza->velocity,odlegloscminus)/mod3;
    float skladowa2=dotpro(druga->velocity,odleglosc)/mod3;
    pierwsza->velocity.x=pierwsza->velocity.x-skladowa1*odlegloscminus.x/mod3+skladowa2*odleglosc.x/mod3;
    pierwsza->velocity.y=pierwsza->velocity.y-skladowa1*odlegloscminus.y/mod3+skladowa2*odleglosc.y/mod3;
    druga->velocity.x=druga->velocity.x-skladowa2*odleglosc.x/mod3+skladowa1*odlegloscminus.x/mod3;
    druga->velocity.y=druga->velocity.y-skladowa2*odleglosc.y/mod3+skladowa1*odlegloscminus.y/mod3;
    float dif=reqdis-sqrt(pow(odleglosc.x,2)+pow(odleglosc.y,2));
    druga->setPosition(druga->getPosition().x+dif*odlegloscminus.x/mod3,druga->getPosition().y+dif*odlegloscminus.y/mod3);
}
int main()
{
    sf::RenderWindow okno(sf::VideoMode(665, 363), "bilard");
    sf::RectangleShape stol ;
    sf::Vector2f stolsize(665, 363);
    stol.setSize(stolsize);
    sf::Texture texture;
    sf::Texture bigtexture;
    sf::Texture kijtexture;
    sf::Texture gotexture;
    if (!texture.loadFromFile("stol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!bigtexture.loadFromFile("PC Computer - Billiards OpenStep - General Sprites.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!kijtexture.loadFromFile("BILLIA~1.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    if (!gotexture.loadFromFile("Black-Game-Over-PNG.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::RectangleShape GameOver;
    GameOver.setSize(sf::Vector2f(665, 363));
    GameOver.setTexture(&gotexture);
    stol.setTexture(&texture);
    stol.setPosition(0,0);
    vector<ball> pilki;
    int i;
    float j=0;
    float n=0;
    sf::Vector2f base;
    base.x=229;
    base.y=190;
    int limit=16;
    for(i=0;i<limit;i++)
    {
        pilki.push_back(ball());
        pilki.at(i).setTexture(&bigtexture);
        pilki.at(i).setTextureRect(sf::IntRect{352+i*19, 1317, 17, 17});
        pilki.at(i).velocity.x=0;
        pilki.at(i).velocity.y=0;
        pilki.at(i).setRadius(8);
        pilki.at(i).setOrigin(8,8);
        pilki.at(i).spadanie=0;
        if(i!=0)
        {
            pilki.at(i).setPosition(base.x-j*17,base.y-8*j+n*17);
            if(n==j)
            {
                j++;
                n=0;
            }
            else
            {
                n++;
            }
        }
    }
    pilki.at(0).setPosition(439,190);
    sf::RectangleShape kij;
    kij.setSize(sf::Vector2f(195,8));
    kij.setTextureRect(sf::IntRect{50,79,195,8});
    kij.setTexture(&kijtexture);
    kij.setOrigin(195,4);
    okno.setFramerateLimit(60);
    okno.display();
    sf::Event zdarzenie;
    bool rysujkij=0;
    bool kijwruchu=0;
    float prendkosc=0;
    std::vector<ball>::iterator tymczasowy;
    std::vector<ball>::iterator tymczasowy2;
    ball biala=pilki.at(0);
    while(okno.isOpen() && pilki.size()!=0)
    {
        okno.clear();
        okno.draw(stol);
        for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
        {
            okno.draw(*tymczasowy);
        }
        for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
        {
            tymczasowy->step();
        }
        for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
        {
            if(tymczasowy->getPosition().x<40)
            {
                tymczasowy->velocity.x=abs(tymczasowy->velocity.x);
            }
            if(tymczasowy->getPosition().x>626)
            {
                tymczasowy->velocity.x=-1*abs(tymczasowy->velocity.x);
            }
            if(tymczasowy->getPosition().x>340 ||tymczasowy->getPosition().x<324)
            {
                if(tymczasowy->getPosition().y<40)
                {
                    tymczasowy->velocity.y=abs(tymczasowy->velocity.y);
                }
                if(tymczasowy->getPosition().y>326)
                {
                    tymczasowy->velocity.y=-1*abs(tymczasowy->velocity.y);
                }
            }
            //Wykrywanie kolizji z dziurami
            if(kolizja(tymczasowy->getPosition(),sf::Vector2f(33,33),15)||kolizja(tymczasowy->getPosition(),sf::Vector2f(33,332),15)||kolizja(tymczasowy->getPosition(),sf::Vector2f(632,332),15)||kolizja(tymczasowy->getPosition(),sf::Vector2f(632,33),15)||kolizja(tymczasowy->getPosition(),sf::Vector2f(332,342),8)||kolizja(tymczasowy->getPosition(),sf::Vector2f(332,24),8))
            {
                tymczasowy->spadanie=1;tymczasowy->velocity=sf::Vector2f(0,0);
            }
        }
        if(rysujkij)
        {
            okno.draw(kij);
        }
        if(kijwruchu)
        {
            prendkosc=prendkosc+0.1;
            kij.move(sf::Vector2f(sin(kij.getRotation()/180*3.14+3.14/2)*prendkosc,cos(kij.getRotation()/180*3.14+3.14/2)*prendkosc*-1));
            if(kolizja(kij.getPosition(),pilki.at(0).getPosition(),pilki.at(0).getRadius()))
            {
                kijwruchu=0;
                rysujkij=0;
                pilki.at(0).velocity=sf::Vector2f(sin(kij.getRotation()/180*3.14+3.14/2)*prendkosc,cos(kij.getRotation()/180*3.14+3.14/2)*prendkosc*-1);
                prendkosc=0;
            }
            if(!stol.getGlobalBounds().contains(kij.getPosition()))
            {
                prendkosc=0;kijwruchu=0;rysujkij=0;
            }
        }
        for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
        {
            for(tymczasowy2=tymczasowy+1;tymczasowy2<pilki.end();tymczasowy2++)
            {
                if(kolizja(tymczasowy->getPosition(),tymczasowy2->getPosition(),tymczasowy->getRadius()+tymczasowy2->getRadius()))
                {
                    zderzenie(&*tymczasowy,&*tymczasowy2,tymczasowy->getRadius()+tymczasowy2->getRadius());
                }
            }
        }
        for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
        {
            if(sqrt(pow(tymczasowy->velocity.x,2)+pow(tymczasowy->velocity.y,2))>0.01)
            {
                tymczasowy->velocity.x=tymczasowy->velocity.x-0.01*tymczasowy->velocity.x/sqrt(pow(tymczasowy->velocity.x,2)+pow(tymczasowy->velocity.y,2));
                tymczasowy->velocity.y=tymczasowy->velocity.y-0.01*tymczasowy->velocity.y/sqrt(pow(tymczasowy->velocity.x,2)+pow(tymczasowy->velocity.y,2));
            }
            else
            {
                tymczasowy->velocity=sf::Vector2f(0,0);
            };
        }
        for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
        {
            if(tymczasowy->spadanie)
        {
            tymczasowy->setScale(tymczasowy->getScale().x-0.125f,tymczasowy->getScale().y-0.125f);
            if(tymczasowy->getScale().x==0)
            {
                pilki.erase(tymczasowy);
            }
        }
        }
        okno.display();
        while (okno.pollEvent(zdarzenie))
        {
            if(zdarzenie.type==sf::Event::Closed)
            {
                okno.close();
            }
            float sumal=0;
            for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
            {
                sumal=abs(tymczasowy->velocity.x)+abs(tymczasowy->velocity.y)+sumal;
            }
            if(zdarzenie.type==sf::Event::MouseButtonPressed && sumal==0)
            {
                if(zdarzenie.mouseButton.button==sf::Mouse::Left && !kijwruchu && pilki.at(0).getTextureRect().left==352)
                {
                    kij.setPosition(sf::Vector2f(zdarzenie.mouseButton.x,zdarzenie.mouseButton.y));
                    kij.setRotation(atan2(pilki.at(0).getPosition().x-kij.getPosition().x,kij.getPosition().y-pilki.at(0).getPosition().y)*360/6.28-90);
                    rysujkij=1;
                }
                if(zdarzenie.mouseButton.button==sf::Mouse::Right)
                {
                    kijwruchu=1;
                }
                bool postaw=1;
                for(tymczasowy=pilki.begin();tymczasowy<pilki.end();tymczasowy++)
                {
                    if(kolizja(tymczasowy->getPosition(),sf::Vector2f(zdarzenie.mouseButton.x,zdarzenie.mouseButton.y),tymczasowy->getRadius()+tymczasowy2->getRadius()))
                    {
                        postaw=0;
                    }

                }
                //sprawdzamie czy w anym miejscu i momencie można postawić białą bilę.
                if(zdarzenie.mouseButton.button==sf::Mouse::Middle && !rysujkij && postaw &&sf::FloatRect{40,40,588,288}.contains(sf::Vector2f(zdarzenie.mouseButton.x,zdarzenie.mouseButton.y)))
                {
                    if(pilki.at(0).getTextureRect().left!=352)
                    {
                        pilki.emplace(pilki.begin(),biala);
                    }
                    pilki.at(0).setPosition(sf::Vector2f(zdarzenie.mouseButton.x,zdarzenie.mouseButton.y));
                }
            }
        }
    }
    okno.draw(GameOver);
    okno.display();
    while(okno.isOpen()){
    while (okno.pollEvent(zdarzenie)) {
    if(zdarzenie.type==sf::Event::Closed){okno.close();}}}
    return 0;
}
