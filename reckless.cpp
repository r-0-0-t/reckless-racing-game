#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

const int XX = 400, YY = 600,car_number = 7;
unsigned long long score = 0,highscore;
int level = 0;
float speedOfCarIncoming[5][car_number] = {
    7.8, 9.4,  10.6, 10.5, 11.73, 9.55,  9.4,
    8.8, 10.4, 11.6, 11.5, 12.73, 10.55, 10.4,
    9.8, 11.4, 12.6, 12.5, 13.73, 11.55, 11.4,
    10.8, 12.4, 13.6, 13.5, 14.73, 12.55, 12.4,
    11.8, 13.4, 14.6, 15.5, 15.73, 13.55, 13.4,
    };

int main()
{
    srand(time(0));
    FILE * fin , *fout;
    fin = fopen("VERYBAD","r");

    fscanf(fin,"%llu",&highscore);
    fclose(fin);
    fout = fopen("VERYBAD","w");

    sf::RenderWindow window (sf::VideoMode(XX,YY),"Reckless Racer");
    window.setVerticalSyncEnabled(true);

    /*--Texture of THe Road--*/
    sf::Texture RoadTexture;
    RoadTexture.loadFromFile("assets/road.png");
    sf::Sprite Road;
    Road.setTexture(RoadTexture);

    /*-----------Title------------*/
    sf::Font Logofont;
    Logofont.loadFromFile("assets/FreckleFace-Regular.ttf");
    sf::Text Logo("Reckless Racer\n\n\n\n\n\n\n  V  0.1",Logofont,55);
    Logo.setPosition(sf::Vector2f(10,10));
    Logo.setColor(sf::Color(239,65,19));
    Logo.setStyle(sf::Text::Bold);
    //------------*----------------/

    /*Car Construction Part*/
    sf::Texture DriverCarTexture;
    DriverCarTexture.loadFromFile("assets/car.png");
    sf::Sprite DriverCar;
    DriverCar.setTexture(DriverCarTexture);
    DriverCar.setPosition(sf::Vector2f(XX-50,YY-100));
    DriverCar.setColor(sf::Color::Red);
    /*----------------------*/

    /*A Junk Rectangle*/
    sf::RectangleShape RectS;
    RectS.setSize(sf::Vector2f(50.f,90.f));
    RectS.setPosition(sf::Vector2f(335.f,YY-100));

    /*CarIncomings Block**/
    sf::Texture CarIncomingTexture;
    CarIncomingTexture.loadFromFile("assets/car1.png");
    sf::Sprite CarIncoming[car_number];
    float CarIncomingPos[6] ={5.0,70.0,145.0,200.0,275.0,330.0};
    /*---------------*/
    int k = 5; //THis k is used for moving car


    /* The Font */
    sf::Font font;
    font.loadFromFile("assets/PassionOne-Black.ttf");
    sf::Text GameOverText("Press Return to Goto MainMenu\n(c) Copyright 2017 - Ishan & Koushik\n SUST",font,10);
    GameOverText.setPosition(sf::Vector2f(20,470));
    GameOverText.setColor(sf::Color::Black);
    // Score
    char S[100];
    sprintf(S,"%05llu",score);
    sf::Text Score;
    Score.setFont(font);
    Score.setCharacterSize(35);
    Score.setString(S);
    Score.setColor(sf::Color(165,211,111));
    Score.setPosition(200, 0);

    char hS[100];
    sprintf(S,"%llu",highscore);
    sf::Text highScore;
    highScore.setFont(font);
    highScore.setCharacterSize(45);
    highScore.setString(S);
    highScore.setColor(sf::Color::Red);
    highScore.setPosition(85, 250);

    //BG Music;
    sf::Music BgMusic;
    BgMusic.openFromFile("assets/mash up nfs mw.ogg");                           ///This is the Main Menu BackGround Song.   mash uo nfs mw.ogg

MainMenu:
{

    sf::Texture mainmenuTexture;
    mainmenuTexture.loadFromFile("assets/MenuBG.png");
    sf::Sprite mainmenu(mainmenuTexture);
    mainmenu.setPosition(sf::Vector2f(0,0));

    sf::Text menu_text[8];
    std::string str[] = { "New Game", "High Score", "Credits", "Exit" };
    for (int k = 0; k < 4; k++)
    {
    menu_text[k].setFont(font);
    menu_text[k].setCharacterSize(45);
    menu_text[k].setString(str[k]);
    menu_text[k].setColor(sf::Color(165,211,111));
    menu_text[k].setPosition(80, 100 + k * 70);
    }

    int Key = 0,Prev_Key = 0;
    while(window.isOpen())
    {
        if(BgMusic.getStatus() != sf::Music::Playing)
            BgMusic.play();
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                fprintf(fout,"%llu\n",highscore);
                fclose(fout);
                window.close();
                }
            if(event.type == sf::Event::KeyPressed ) {
                if(event.key.code == sf::Keyboard::Down)
                {
                    Prev_Key = Key;
                    if(Key<5)
                    Key++;
                    if(Key >= 4) Key = 0;
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    Prev_Key = Key;
                    if(Key>=0)
                    Key--;
                    if(Key < 0) Key = 3;
                }
                else if(event.key.code == sf::Keyboard::Return)
                {
                    if(Key == 0) goto Levels;
                    else if(Key == 1) goto HighScore;
                    else if(Key == 2) goto Credit;
                    else if(Key == 3) {
                            fprintf(fout,"%llu\n",highscore);
                            fclose(fout);
                            window.close();
                    }
                }
            }


        }
        menu_text[Prev_Key].setColor(sf::Color(165,211,111));
        menu_text[Key].setColor(sf::Color(165,0,0));

        window.draw(mainmenu);
        for (int k = 0; k < 4; k++)
        {
        window.draw(menu_text[k]);
        }
        window.draw(Logo);
        window.display();
    }
}

Levels:
{
    sf::Texture mainmenuTexture;
    mainmenuTexture.loadFromFile("assets/MenuBG.png");
    sf::Sprite mainmenu(mainmenuTexture);
    mainmenu.setPosition(sf::Vector2f(0,0));


    sf::Text menu_text[8];
    std::string str[] = { "NOOB", "AMATEUR", "PRO", "LEGEND","ULTRA-LEGEND" };
    for (int k = 0; k < 5; k++)
    {
    menu_text[k].setFont(font);
    menu_text[k].setCharacterSize(45);
    menu_text[k].setString(str[k]);
    menu_text[k].setColor(sf::Color(165,211,111));
    menu_text[k].setPosition(80, 100 + k * 70);
    }

    int Key = 0,Prev_Key = 0;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                fprintf(fout,"%llu\n",highscore);
                fclose(fout);
                window.close();
                }
            if(event.type == sf::Event::KeyPressed ) {

                if(event.key.code == sf::Keyboard::Escape)
                {
                    goto MainMenu;
                }

                if(event.key.code == sf::Keyboard::Down)
                {
                    Prev_Key = Key;
                    if(Key<6)
                    Key++;
                    if(Key >= 5) Key = 0;
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    Prev_Key = Key;
                    if(Key>=0)
                    Key--;
                    if(Key < 0) Key = 4;
                }
                else if(event.key.code == sf::Keyboard::Return)
                {
                    if(Key == 0)
                    {
                        RoadTexture.loadFromFile("assets/road.png");
                        level = 0;
                        goto PlayGame;
                    }
                    else if(Key == 1) {
                        RoadTexture.loadFromFile("assets/road.png");
                        level = 1;
                        goto PlayGame;
                    }
                    else if(Key == 2) {
                        RoadTexture.loadFromFile("assets/road.png");
                        level = 2;
                        goto PlayGame;
                    }
                    else if(Key == 3) {
                        RoadTexture.loadFromFile("assets/road.png");
                        level = 3;
                        goto PlayGame;
                    }
                    else if(Key == 4) {
                        RoadTexture.loadFromFile("assets/road.png");
                        level = 4;
                        goto PlayGame;
                    }
                }
            }


        }
        menu_text[Prev_Key].setColor(sf::Color(165,211,111));
        menu_text[Key].setColor(sf::Color(165,0,0));

        window.draw(mainmenu);
        for (int k = 0; k < 6; k++)
        {
        window.draw(menu_text[k]);
        }
        window.display();
    }
}

HighScore:
{
    window.clear();


    BgMusic.stop();
    sf::Music CreditMusic;
    CreditMusic.openFromFile("assets/feed the addiction nfs mw.ogg");                  ///This is the High Score Music      feed the addiction.ogg

    sf::Font inst;
    inst.loadFromFile("assets/PassionOne-Black.ttf");
    sf::Text instruction("Press ESc For\n MainMenu",inst,25);
    instruction.setPosition(sf::Vector2f(200,540));
    instruction.setColor(sf::Color(184,172,159));

    sf::Texture ScoreBack;
    ScoreBack.loadFromFile("assets/highscoreback.png");
    sf::Sprite Score;
    Score.setTexture(ScoreBack);
    while(window.isOpen())
    {
        if(CreditMusic.getStatus() != sf::Music::Playing)
            CreditMusic.play();

        sprintf(hS,"High Score \n        %llu",highscore);
        highScore.setString(hS);
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                fprintf(fout,"%llu\n",highscore);
                            fclose(fout);
                window.close();
                }
            if(event.type == sf::Event::KeyPressed )
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    goto MainMenu;
                }
            }


        }

        window.draw(Score);
        window.draw(instruction);
        window.draw(highScore);
        window.display();
    }


}

Credit:
{
    BgMusic.stop();
    sf::Music CreditMusic;
    CreditMusic.openFromFile("assets/da ya thang nfs mw.ogg");                             ///This is the Credit Song       da ya thang nfs mw.ogg

    window.clear();
    sf::Texture CreditTexture;
    CreditTexture.loadFromFile("assets/MenuBG.png");
    sf::Sprite Credit(CreditTexture);
    Credit.setPosition(sf::Vector2f(0,0));

    sf::Font inst2;
    inst2.loadFromFile("assets/PassionOne-Black.ttf");
    sf::Text instruction2("             Game Project-2\n\nProject By:\nIshan & Koushik.\nDeveloped with:\nSFML & C++\n\nSubmitted to:\nMr.Asif Samir\nAssistant Professor\nSWE,SUST",inst2,25);
    instruction2.setPosition(sf::Vector2f(55,100));
    //instruction2.setStyle(sf::Text::Bold);
    instruction2.setColor(sf::Color::Green);

    sf::RectangleShape RectS;
    RectS.setSize(sf::Vector2f(300.f,350.f));
    RectS.setPosition(sf::Vector2f(50.f,YY-500));
    RectS.setFillColor(sf::Color::Black);

    sf::Font inst1;
    inst1.loadFromFile("assets/PassionOne-Black.ttf");
    sf::Text instruction1("Press ESc For\n MainMenu",inst1,25);
    instruction1.setPosition(sf::Vector2f(200,540));
    instruction1.setColor(sf::Color(184,172,159));


    while(window.isOpen())
    {
        if(CreditMusic.getStatus() != sf::Music::Playing)
            CreditMusic.play();
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                fprintf(fout,"%llu\n",highscore);
                fclose(fout);
                window.close();
                }
            if(event.type == sf::Event::KeyPressed )
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    CreditMusic.stop();
                    goto MainMenu;
                }
            }


        }
        window.draw(Credit);
        window.draw(RectS);
        window.draw(instruction2);
        window.draw(instruction1);
        window.display();
    }
}


PlayGame:
{
    BgMusic.stop();
    window.clear();
    sf::Music BgMusic;
    BgMusic.openFromFile("assets/audi.ogg");                                                  ///This the Car Sound           audi.ogg
    sf::Sprite CarIncoming[car_number];


    // The loop here will initialise the CarIncoming array with some randome position.
    // This will be the starting positions of the incoming  cars.
    // So if the Game is over and Player starts it again it will initialise the Array Of the positions

    for(int i = 0;i < car_number;++i)
        {
            CarIncoming[i].setTexture(CarIncomingTexture);
            CarIncoming[i].setColor(sf::Color(rand()%255,rand()%255,rand()%255));
            CarIncoming[i].setPosition(sf::Vector2f(CarIncomingPos[rand()%6],rand()%500-YY));
        }

    //SFML Game Loop
    while(window.isOpen())
    {
        if(BgMusic.getStatus() != sf::Music::Playing)
            BgMusic.play();
        sprintf(S,"Score : %04llu",score);
        Score.setString(S);
        //Randomly Generate Position for incoming Cars;
        // They are stored in CarIncoming array.
        // They will not be changed in the array until any car moves beyond the limit.
        for(int i = 0;i < car_number;++i)
        {
            // They will not be changed in the array until any car moves beyond the limit.
            if(CarIncoming[i].getPosition().y > 600)
            {

                CarIncoming[i].setColor(sf::Color(rand()%255,rand()%255,rand()%255));
                CarIncoming[i].setTexture(CarIncomingTexture);
                CarIncoming[i].setPosition(sf::Vector2f(CarIncomingPos[rand()%6],rand()%500-YY));
                score++;
            }
        }
        for(int i = 0;i < car_number;++i)
        {
            for(int j = 0;j < car_number;++j)
                {
                    if(CarIncoming[i].getGlobalBounds().intersects(CarIncoming[j].getGlobalBounds()))
                {
                    CarIncoming[i].move(0,-2);
                }
                if(CarIncoming[j].getGlobalBounds().intersects(CarIncoming[i].getGlobalBounds()))
                {
                    CarIncoming[j].move(0,-2);
                }
                }
        }

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                fprintf(fout,"%llu\n",highscore);
                fclose(fout);
                window.close();
                }
        }
        if(event.type == sf::Event::KeyPressed ) {
                if(event.key.code == sf::Keyboard::Right)
                {
                    // Here k variable contains 0-5 values.
                    // It will help to move the Driver's Car position.
                    // CarIncomingPos doesnt contain only the X position of incoming cars but also driver Car.
                    if(k<5)
                    k++;
                    DriverCar.setPosition(sf::Vector2f(CarIncomingPos[k],YY-100));
                }
                else if(event.key.code == sf::Keyboard::Left)
                {
                    if(k>0)
                    k--;
                    DriverCar.setPosition(sf::Vector2f(CarIncomingPos[k],YY-100));
                }

            }
        for(int i = 0;i < car_number;++i)
        {
            CarIncoming[i].move(0,speedOfCarIncoming[level][i]);
            if(CarIncoming[i].getGlobalBounds().intersects(DriverCar.getGlobalBounds()))
                {
                    window.clear();
                    goto gameOver;
                }
        }

        window.draw(Road);
        for(int i = 0;i < car_number;++i)
        {
            window.draw(CarIncoming[i]);
        }
        window.draw(DriverCar);
        window.draw(Score);
        window.display();
    }
}

/*The Game Over Part*/
gameOver:
{
    if(score > highscore)
    {
        highscore = score;
    }

    BgMusic.stop();
    window.clear();
    sf::Music BgMusic;
    BgMusic.openFromFile("assets/sound effect.ogg");                ///This is Car Crash Sound Effect    sound effect.ogg

//
    sf::Text GameOverText;
    GameOverText.setFont(font);
    if(highscore > score){
    sprintf(S,"Your Score: \n%15llu",score);
    GameOverText.setCharacterSize(60);
    }
    else
    {
        sprintf(S,"  Congratulations!!!\n    New HighScore: \n%15llu",score);
        GameOverText.setCharacterSize(40);
    }
    GameOverText.setString(S);
    GameOverText.setPosition(40,200);
    GameOverText.setColor(sf::Color(239,237,217));

    sf::Font wracked;
    wracked.loadFromFile("assets/Mostwasted.ttf");
    sf::Text Wrecked;
    Wrecked.setFont(wracked);
    Wrecked.setCharacterSize(80);
    Wrecked.setString("WRECKED");
    Wrecked.setPosition(60,90);
    Wrecked.setColor(sf::Color::White);


    sf::Texture theEndTexture;
    theEndTexture.loadFromFile("assets/Busted.png");
    sf::Sprite theEnd(theEndTexture);
    theEnd.setPosition(sf::Vector2f(0,0));

    if(BgMusic.getStatus() != sf::Music::Playing)
        BgMusic.play();

    while(window.isOpen())
    {

        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                {
                fprintf(fout,"%llu\n",highscore);
                fclose(fout);
                window.close();
                }
            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Return)
                    {
                        score = 0;
                        goto MainMenu;
                    }

        }
        window.draw(theEnd);
        window.draw(Wrecked);
        window.draw(GameOverText);
        window.display();
    }
}
/*-----------------------*/
}
