#include <SFML/Graphics.hpp>
#include<sstream>
#include<fstream>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;

//L24 3023  (Muhammad shehryar waheed)
//L24 3007  (Husnain khan)
//l24 3063  (Muazam Mehmood)

string askname( sf::Font& font, string space) 
{
    char name[100] = "";        //name input
    int namelength = 0;         // name length
    space = " ";

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Asking Name of the player");

    sf::Text question;
    question.setFont(font);
    question.setCharacterSize(70);
    question.setFillColor(sf::Color::Yellow);
    question.setPosition(500,400);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && namelength > 0) 
                { // Backspace
                    namelength--;
                    name[namelength] = '\0';
                }
                else if (event.text.unicode == '\r') 
                { // Enter key
                    for (int i = 0; i < namelength; i++) 
                    {
                        name[i] = toupper(name[i]);
                    }
                    return name;
                }
                else if ((event.text.unicode < 128) && namelength < 99)
                { // Valid input
                    name[namelength] = static_cast<char>(event.text.unicode);
                    namelength++;
                    name[namelength] = '\0';
                }
                // Update the display text with current input
            }
                question.setString("What is your name? " + space + "\nYour Name:   " + name);
        }

        window.clear();
        window.draw(question);
        window.display();
    }

    return 0;
}

void updateLeaderboard(string filename, string newName, int newScore) {
    const int size = 5;
    string names[size];
    int scores[size];

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        inputFile >> names[i] >> scores[i];
    }
    inputFile.close();

    int position = -1;
    for (int i = 0; i < size; i++) {
        if (newScore < scores[i]) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        cout << "Score not high enough to update the leaderboard." << endl;
        return;
    }

    for (int i = size - 1; i > position; i--) {
        names[i] = names[i - 1];
        scores[i] = scores[i - 1];
    }
    names[position] = newName;
    scores[position] = newScore;

    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Error opening file!" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        outputFile << names[i] << " " << scores[i] << endl;
    }
    outputFile.close();

    cout << "Leaderboard updated successfully!" << endl;
}

void leaderboardscore(string filename, string* leader)
{
    const int size = 5;
    string names[size];
    int scores[size];

    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    for (int i = 0; i < size; i++)
    {
        inputFile >> names[i] >> scores[i];
    }
    inputFile.close();

    for (int i = 0;i < size;i++)
    {
        leader[i] = names[i] + "    " + to_string(scores[i]) + "\n";
    }
}

int main() 
{
    bool isjumping = false;
    bool jumpside = true;
    bool menu = true;
    bool ondabba = false;
    bool istime = false;
    bool coin1 = true;
    bool coin2 = true;
    bool coin3 = true;
    bool coin4 = true;
    bool coin5 = true;
    bool isalive = false;
    bool isdead = false;
    bool pipecol = false;
    bool onpipe = true;
    bool showtext = false;
    bool win = false;                                               //game ending
    bool setpos = true;
    bool timetogo = false;
    bool gamekatime = true;
    bool isname = true;
    bool leader = false;
    const float gravity = 0.002f;
    const float jumpSpeed = -0.9f;
    const float moveSpeed = 0.7f;
    float zonearea1 = 1550.0f;
    float zonearea2 = 1000.0f;
    float level = 840.0f;                                           //player movement ground
    float enemyspeed1 = 0.07f;
    float enemyspeed2 = 0.07f;
    float enemyspeed3 = 0.07f;
    float velocityY = 1.0f;
    float velocityE1 = 1.0f;
    float velocityE2 = 1.0f;
    float velocityE3 = 1.0f;
    float velocityE4 = 1.0f;
    float winspeed = 0.3f;
    int screen = 0;
    int score = 0;
    int life = 3;
    int enemycount = 0;
    int final = 0;
    string nameofplayer;
    string leadernames[5];

    sf::Clock deathtimer;
    sf::Clock timer;
    sf::Clock pipetimer;
    sf::Clock lifeminustimer;
    sf::Clock gametime;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mario Game");

    //menu loads----------------------------------------------------------------------------------------------------------------------------------
    sf::Texture menuscreen;
    if (!menuscreen.loadFromFile("image\\menuscreen.png"))
    {
        return -1;
    }
    sf::Sprite menupage;                                                                                    //menu
    menupage.setTexture(menuscreen);

    menupage.setScale(
        window.getSize().x / menupage.getGlobalBounds().width,
        window.getSize().y / menupage.getGlobalBounds().height
    );

    //skyblocks------------------------------------------------------------------------------------------------------------------------------------
    sf::Texture skyb;
    if (!skyb.loadFromFile("image\\skyblock.png"))
    {
        return -1;
    }
    sf::Sprite skyblock1(skyb);                                                                       //skyblock1
    skyblock1.setPosition(799, level - 219);
    skyblock1.setScale(0.87, 0.9);

    sf::Texture skyb2;
    if (!skyb2.loadFromFile("image\\skyblock3.png"))
    {
        return -1;
    }
    sf::Sprite skyblock2(skyb2);                                                                       //skyblock2
    skyblock2.setPosition(1220, level - 600);
    skyblock2.setScale(0.87, 0.9);

    sf::Texture skyb3;
    if (!skyb3.loadFromFile("image\\skyblock2.png"))
    {
        return -1;
    }
    sf::Sprite skyblock3(skyb3);                                                                       //skyblock3
    skyblock3.setPosition(850, level - 200);
    skyblock3.setScale(0.87, 0.9);

    sf::Sprite skyblock4(skyb3);                                                                       //skyblock4
    skyblock4.setPosition(850, level - 150);
    skyblock4.setScale(0.87, 0.9);

    sf::Texture ques;
    if (!ques.loadFromFile("image\\questionmark.png"))
    {
        return -1;
    }
    sf::Sprite question1(ques);
    question1.setScale(1.207, 1.207);
    question1.setPosition(500, level - 200);                                                        //question mark
    sf::Sprite question2(ques);
    question2.setScale(1.38, 1.38);
    question2.setPosition(890, level - 212.5);
    sf::Sprite question3(ques);
    question3.setScale(1.38, 1.38);
    question3.setPosition(1069, level - 212.5);
    sf::Sprite question4(ques);
    question4.setScale(1.38, 1.38);
    question4.setPosition(825, level - 212.5);
    sf::Sprite question5(ques);
    question5.setScale(1.38, 1.38);
    question5.setPosition(1580, level - 370);

    //coin load-----------------------------------------------------------------------------------------------------------------------------------
    sf::Texture cointex;
    if (!cointex.loadFromFile("image\\coin.png"))
    {
        return -1;                                                                                         //coin
    }
    sf::Sprite coin(cointex);
    coin.setPosition(-100, -100);

    //zone load------------------------------------------------------------------------------------------------------------------------------------
    sf::Texture zone;
    if (!zone.loadFromFile("image\\deathzone.png"))
    {
        return -1;
    }
    sf::Sprite deathzone1(zone);                                                                                   //zone 1
    deathzone1.setPosition(zonearea1, 930);
    deathzone1.setScale(0.6, 3);

    sf::Sprite deathzone2(zone);                                                                                   //zone 2
    deathzone2.setPosition(zonearea2, 930);
    deathzone2.setScale(0.6, 3);

    //enemy load===================================================================================================================================
    sf::Texture enemytax;
    if (!enemytax.loadFromFile("image\\enemy1.png"))
    {
        return -1;                                                                                         //enemy 1
    }
    sf::Sprite enemy1(enemytax);
    enemy1.setScale(1.3, 1.3);
    enemy1.setPosition(1200.0, level + 21);
    sf::Sprite enemy2(enemytax);                                                                            //enemy 2
    enemy2.setScale(1.3, 1.3);
    enemy2.setPosition(500.0, level + 21);
    sf::Sprite enemy3(enemytax);                                                                            //enemy 3
    enemy3.setScale(1.3, 1.3);
    enemy3.setPosition(700.0, level + 21);
    sf::Sprite enemy4(enemytax);                                                                            //enemy 4
    enemy4.setScale(1.3, 1.3);
    enemy4.setPosition(920.0, level - 870);
    sf::Sprite enemy5(enemytax);                                                                            //enemy 5
    enemy5.setScale(1.3, 1.3);
    enemy5.setPosition(1000.0, level - 220);
    sf::Sprite enemy6(enemytax);                                                                            //enemy 6
    enemy6.setScale(1.3, 1.3);
    enemy6.setPosition(1520.0, level - 830);


    //pipe load====================================================================================================================================
    sf::Texture pipetax;
    if (!pipetax.loadFromFile("image\\pipe.png"))
    {
        return -1;                                                                                         //pipe
    }
    sf::Sprite pipe1(pipetax);
    pipe1.setScale(2.5, 2);
    sf::Sprite pipe2(pipetax);
    pipe2.setScale(2.5, 2);


    //mario sprites*******************************************************************************************************************************
    sf::Texture leftTexture;
    if (!leftTexture.loadFromFile("image\\leftjump.png"))
    {
        return -1;                                                                                         //leftrun
    }

    sf::Texture leftidle;
    if (!leftidle.loadFromFile("image\\leftidle.png"))
    {
        return -1;                                                                                        //leftidle
    }

    sf::Texture rightidle;
    if (!rightidle.loadFromFile("image\\rightidle.png"))
    {
        return -1;                                                                                        //leftidle
    }

    sf::Texture rightTexture;
    if (!rightTexture.loadFromFile("image\\rightjump.png"))
    {
        return -1;                                                                                        //rightrun
    }
    sf::Sprite player(rightidle);

    player.setPosition(100, 500);
    player.setScale(1.5f, 1.5f);

    //background loads//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    sf::Texture transdeath;
    if (!transdeath.loadFromFile("image\\deathscreentransparent.png"))
    {
        return -1;                                                                                        //transparent death screen
    }
    sf::Sprite transscreen;
    transscreen.setTexture(transdeath);
    transscreen.setScale(window.getSize().x / transscreen.getGlobalBounds().width, window.getSize().y / transscreen.getGlobalBounds().height);

    sf::Texture death;
    if (!death.loadFromFile("image\\deathscreen.png"))
    {
        return -1;                                                                                        //death screen
    }
    sf::Sprite deathscreen;
    deathscreen.setTexture(death);

    deathscreen.setScale(window.getSize().x / deathscreen.getGlobalBounds().width, window.getSize().y / deathscreen.getGlobalBounds().height);

    //*************************************************************************************************************************************************************************************

    sf::Texture titlebackgroundTexture;
    if (!titlebackgroundTexture.loadFromFile("image\\Titlescreen.png"))
    {
        return -1;                                                                                        //title screen
    }
    sf::Sprite background(titlebackgroundTexture);


    background.setScale(window.getSize().x / background.getGlobalBounds().width, window.getSize().y / background.getGlobalBounds().height);


    sf::Texture leadertex;
    if (!leadertex.loadFromFile("image\\leaderboard.png"))
    {
        return -1;                                                                                        //leader board screen
    }       
    sf::Sprite leaderboard(leadertex);


    leaderboard.setScale(window.getSize().x / leaderboard.getGlobalBounds().width, window.getSize().y / leaderboard.getGlobalBounds().height);

    sf::Texture simple;
    if (!simple.loadFromFile("image\\simplescreen.png"))
    {
        return -1;                                                                                        //through out common screen
    }
    sf::Sprite simplescreen(simple);
    simplescreen.setScale(window.getSize().x / simplescreen.getGlobalBounds().width, window.getSize().y / simplescreen.getGlobalBounds().height);

    //*******************************************************************************************************************************************************************************************
    sf::Texture wintex;
    if (!wintex.loadFromFile("image\\winscreen.png"))
    {
        return -1;                                                                                        //winning screen
    }
    sf::Sprite winback(wintex);
    winback.setScale(window.getSize().x / winback.getGlobalBounds().width, window.getSize().y / winback.getGlobalBounds().height);

    sf::Texture wintrans;
    if (!wintrans.loadFromFile("image\\winscreentrans.png"))
    {
        return -1;                                                                                        //winning screen transparent
    }
    sf::Sprite winbacktrans(wintrans);
    winbacktrans.setScale(window.getSize().x / winbacktrans.getGlobalBounds().width, window.getSize().y / winbacktrans.getGlobalBounds().height);


    //*******************************************************************************************************************************************************************************************
    sf::Texture cast;
    if (!cast.loadFromFile("image\\castle.png"))
    {
        return -1;                                                                                      //CASTLE
    }
    sf::Sprite castle(cast);
    castle.setScale(0.9, 0.9);
    castle.setPosition(1450, level - 369);

    //*******************************************************************************************************************************************************************************************
    sf::Texture fla1;
    if (!fla1.loadFromFile("image\\flag1.png"))
    {
        return -1;                                                                                      //flag 1st part
    }
    sf::Sprite flag1(fla1);
    flag1.setPosition(1100, level - 420);

    sf::Texture fla2;
    if (!fla2.loadFromFile("image\\flag2.png"))
    {
        return -1;                                                                                      //flag 2nd part
    }
    sf::Sprite flag2(fla2);
    flag2.setPosition(1117, level - 398);
    flag2.setScale(0.2, 0.2);

    //*******************************************************************************************************************************************************************************************
    sf::Texture star;
    if (!star.loadFromFile("image\\stairs.png"))
    {
        return -1;                                                                                      //Stairs
    }
    sf::Sprite stairs(star);
    stairs.setScale(0.9, 0.9);
    stairs.setPosition(300, level - 314.25);

    sf::Texture ek;
    if (!ek.loadFromFile("image\\ekdabba.png"))
    {
        return -1;
    }
    sf::Sprite dabba1(ek);                                                                                      //dabba 1
    dabba1.setScale(1.5, 1.5);
    dabba1.setPosition(300, level + 45);
    sf::Sprite dabba2(ek);                                                                                      //dabba 2
    dabba2.setScale(1.5, 1.5);
    dabba2.setPosition(352, level - 7);
    sf::Sprite dabba3(ek);                                                                                      //dabba 3
    dabba3.setScale(1.5, 1.5);
    dabba3.setPosition(402, level - 60);
    sf::Sprite dabba4(ek);                                                                                      //dabba 4
    dabba4.setScale(1.5, 1.5);
    dabba4.setPosition(452, level - 111);
    sf::Sprite dabba5(ek);                                                                                      //dabba 5
    dabba5.setScale(1.5, 1.5);
    dabba5.setPosition(504, level - 163);
    sf::Sprite dabba6(ek);                                                                                      //dabba 6
    dabba6.setScale(1.5, 1.5);
    dabba6.setPosition(556, level - 213);
    sf::Sprite dabba7(ek);                                                                                      //dabba 7
    dabba7.setScale(1.5, 1.5);
    dabba7.setPosition(606, level - 265);
    sf::Sprite dabba8(ek);                                                                                      //dabba 8
    dabba8.setScale(1.5, 1.5);
    dabba8.setPosition(659, level - 314);
    sf::Sprite dabba9(ek);                                                                                      //dabba 9
    dabba9.setScale(1.5, 1.5);
    dabba9.setPosition(712, level - 314);
    sf::Sprite dabba10(ek);                                                                                      //dabba 10
    dabba10.setScale(1.5, 1.5);
    dabba10.setPosition(1093, level + 45);

    //fonts load/////////////////////////////////////////////////////////-------------------------------------///////////////////////////////////////
    sf::Font font;
    if (!font.loadFromFile("font\\PixeloidSans.ttf"))
    {
        return -1;                                                                                          //score
    }

    sf::Text totalscore;
    totalscore.setFont(font);
    totalscore.setFillColor(sf::Color::White);
    totalscore.setCharacterSize(30);
    totalscore.setPosition(32, 27);

    sf::Text noliveleft;
    noliveleft.setFont(font);                                                                               //no live text
    noliveleft.setString("DEAD");
    noliveleft.setFillColor(sf::Color::White);
    noliveleft.setCharacterSize(30);
    noliveleft.setPosition(925, 27);

    sf::Text lifeminustext1;
    lifeminustext1.setFont(font);                                                                            //life - 1 counter text
    lifeminustext1.setString("1 life lost");
    lifeminustext1.setFillColor(sf::Color::Red);
    lifeminustext1.setCharacterSize(30);
    lifeminustext1.setPosition(1565, level + 100);

    sf::Text lifeminustext2;
    lifeminustext2.setFont(font);                                                                            //life - 1 counter text
    lifeminustext2.setString("1 life lost");
    lifeminustext2.setFillColor(sf::Color::Red);
    lifeminustext2.setCharacterSize(30);
    lifeminustext2.setPosition(zonearea2 + 25, level + 100);

    sf::Text maintime;
    maintime.setFont(font);
    maintime.setFillColor(sf::Color::White);                                                               //final time on winscreen
    maintime.setCharacterSize(70);
    maintime.setPosition(730, 330);

    sf::Text welldone;
    welldone.setFont(font);
    welldone.setFillColor(sf::Color::Yellow);                                                               //thanks on winscreen
    welldone.setCharacterSize(70);
    welldone.setPosition(570, 330);
    welldone.setString("\n\nTHANKS FOR PLAYING");

    sf::Text enter;
    enter.setFont(font);
    enter.setFillColor(sf::Color::White);                                                               //enter saying on winscreen
    enter.setCharacterSize(30);
    enter.setPosition(720, 630);
    enter.setString("\n\nPress ENTER to continue!!!");

    sf::Text gametimer;
    gametimer.setFont(font);
    gametimer.setFillColor(sf::Color::White);                                                           //game ka time
    gametimer.setPosition(1715, 30);
    gametimer.setCharacterSize(30);

    sf::Text leadert1;
    leadert1.setFont(font);
    leadert1.setFillColor(sf::Color::Yellow);                                                           //leader board ke liye
    leadert1.setPosition(850, 350);
    leadert1.setCharacterSize(30);

    sf::Text leadert2;
    leadert2.setFont(font);
    leadert2.setFillColor(sf::Color::Cyan);                                                           //leader board ke liye
    leadert2.setPosition(850, 430);
    leadert2.setCharacterSize(30);

    sf::Text leadert3;
    leadert3.setFont(font);
    leadert3.setFillColor(sf::Color::Blue);                                                           //leader board ke liye
    leadert3.setPosition(850, 510);
    leadert3.setCharacterSize(30);

    sf::Text leadert4;
    leadert4.setFont(font);
    leadert4.setFillColor(sf::Color::White);                                                           //leader board ke liye
    leadert4.setPosition(850, 590);
    leadert4.setCharacterSize(30);

    sf::Text leadert5;
    leadert5.setFont(font);
    leadert5.setFillColor(sf::Color::White);                                                           //leader board ke liye
    leadert5.setPosition(850, 670);
    leadert5.setCharacterSize(30);

    //***********************************************************************   back box load   *****************************************************************
    sf::Texture back;
    if (!back.loadFromFile("image\\backbox.png"))
    {
        return -1;                                                                                          //back box 1
    }
    sf::Sprite backbox1(back);
    backbox1.setPosition(20, 20);
    backbox1.setScale(0.25, 0.5);

    sf::Sprite backbox2(back);                                                                              //back box 2
    backbox2.setPosition(870, 20);
    backbox2.setScale(0.25, 0.5);

    sf::Sprite backbox3(back);                                                                              //back box 3
    backbox3.setPosition(1700, 20);
    backbox3.setScale(0.25, 0.5);

    //heart load************************************************************************************************************************************
    sf::Texture heart;
    if (!heart.loadFromFile("image\\heart.png"))
    {
        return -1;                                                                                          //heart
    }
    sf::Sprite heartbox1(heart);
    heartbox1.setScale(0.31, 0.31);
    heartbox1.setPosition(886, 27);
    sf::Sprite heartbox2(heart);
    heartbox2.setScale(0.31, 0.31);
    heartbox2.setPosition(945, 27);
    sf::Sprite heartbox3(heart);
    heartbox3.setScale(0.31, 0.31);
    heartbox3.setPosition(1003, 27);
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++   MUSIC TIME BABY   +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    sf::Music backmusic;
    if (!backmusic.openFromFile("sound\\background.ogg"))                       //background music
    {
        return -1;
    }
    backmusic.setLoop(true);
    backmusic.setVolume(100);
    backmusic.play();

    sf::Music jump;
    if (!jump.openFromFile("sound\\jump.ogg"))                       //jump music
    {
        return -1;
    }
    jump.setVolume(5);

    sf::Music coinm;
    if (!coinm.openFromFile("sound\\coin.ogg"))                       //coin music
    {
        return -1;
    }
    coinm.setVolume(50);

    sf::Music diem;
    if (!diem.openFromFile("sound\\die.ogg"))                       //die music
    {
        return -1;
    }
    diem.setVolume(0);
    diem.setLoop(true);
    diem.play();


    sf::Music winm;
    if (!winm.openFromFile("sound\\win.ogg"))                       //win music
    {
        return -1;
    }
    winm.setVolume(50);

    sf::Music smash;
    if (!smash.openFromFile("sound\\smash.ogg"))                       //enemy smash music
    {
        return -1;
    }
    smash.setVolume(30);

    sf::Music hit;
    if (!hit.openFromFile("sound\\hit.ogg"))                       //enemy hit music
    {
        return -1;
    }
    hit.setVolume(50);

    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$    CODING AREA    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                menu = !menu;
            }
        }

        //time of the game
          sf::Time elapsed = gametime.getElapsedTime();

          int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
          int seconds = static_cast<int>(elapsed.asSeconds()) % 60;

          std::ostringstream timeStream;
          timeStream << "Time: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
          gametimer.setString(timeStream.str());
        
        if (menu) 
        {
            backmusic.setVolume(100);
            diem.setVolume(0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                menu = false;
                leader = false;
                player.setPosition(100, level - 400);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                player.setPosition(100, level);
                life = 3;
                isjumping = false;
                jumpside = true;
                ondabba = false;
                istime = false;
                coin1 = true;
                coin2 = true;
                coin3 = true;
                coin4 = true;
                coin5 = true;
                isalive = false;
                isdead = false;
                pipecol = false;
                onpipe = true;
                showtext = false;
                win = false;                                               //game ending
                setpos = true;
                timetogo = false;
                gamekatime = true;
                zonearea1 = 1550.0f;
                zonearea2 = 1000.0f;
                level = 840.0f;                                           //player movement ground
                enemyspeed1 = 0.07f;
                enemyspeed2 = 0.07f;
                enemyspeed3 = 0.07f;
                velocityY = 1.0f;
                velocityE1 = 1.0f;
                velocityE2 = 1.0f;
                velocityE3 = 1.0f;
                velocityE4 = 1.0f;
                winspeed = 0.3f;
                screen = 0;
                score = 0;
                life = 3;
                enemycount = 0;
                heartbox1.setPosition(886, 27);
                heartbox2.setPosition(945, 27);
                heartbox3.setPosition(1003, 27);
                enemy1.setPosition(1200.0, level + 21);
                enemy2.setPosition(500.0, level + 21);
                enemy3.setPosition(700.0, level + 21);
                enemy4.setPosition(1020.0, level - 870);
                enemy5.setPosition(1000.0, level - 220);
                menu = false;
                continue;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                leader = true;
                menu = false;
            }

            //**************************************************     Basic logic     ******************************************************************
            if (true)
            {
                if (!isjumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                {
                    jump.play();
                    isjumping = true;
                    velocityY = jumpSpeed;
                    if (jumpside)
                    {
                        player.setTexture(rightTexture);
                    }
                    else
                    {
                        player.setTexture(leftTexture);
                    }
                }

                if (isjumping)
                {
                    velocityY += gravity;
                }

                player.move(0, velocityY);

                if (player.getPosition().y >= level)
                {
                    player.setPosition(player.getPosition().x, level);
                    isjumping = false;
                }

                if (!isjumping)
                {
                    if (jumpside)
                        player.setTexture(rightidle);
                    else
                        player.setTexture(leftidle);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    jumpside = false;
                    if (player.getPosition().x > 0)
                    {
                        player.move(-moveSpeed, 0);
                        player.setTexture(leftTexture);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    jumpside = true;
                    if (player.getPosition().x + player.getGlobalBounds().width < window.getSize().x)
                    {
                        player.move(moveSpeed, 0);
                        player.setTexture(rightTexture);
                    }
                }
            }
        }
        else if (leader)
        {
           leaderboardscore("score.txt",leadernames);
           leadert1.setString(leadernames[0]);
           leadert2.setString(leadernames[1]);
           leadert3.setString(leadernames[2]);
           leadert4.setString(leadernames[3]);
           leadert5.setString(leadernames[4]);
           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
           {
               leader = false;
               menu = true;
           }
        }
        else if (win)
        {
            if(gamekatime)
            {
                maintime.setString(timeStream.str());
                final = seconds + (minutes * 60);
                updateLeaderboard("score.txt", nameofplayer, final);
                gamekatime = false;
            }
            if (player.getPosition().x > 0)
            {
                player.setTexture(rightidle);
                if (setpos)
                {
                    player.setPosition(1000, level);
                    setpos = false;
                }

                if (player.getPosition().x == 1000 && flag2.getPosition().y <= level - 30)
                {
                    flag2.setPosition(flag2.getPosition().x, flag2.getPosition().y + winspeed);
                }

                if (flag2.getPosition().y >= level - 45 && player.getPosition().x < 1600)
                {
                    player.setTexture(rightTexture);
                    player.move(winspeed - 0.1, 0);
                    timer.restart();
                }
                if (player.getPosition().x >= 1600 && timer.getElapsedTime().asSeconds() > 1.5)
                {
                    win = false;
                    timetogo = true;
                    player.setPosition(-100, -100);
                }
            }
        }
        else if (isdead)
        {
            backmusic.setVolume(0);
            diem.setVolume(50);
        }
        else if (screen == 0)
        {
            if (screen == 0 && enemycount == 0 && isname)
            {
                nameofplayer = askname(font, " ");
                isname = false;
            }

            if (gamekatime)
            {
                gametime.restart();
                gamekatime = false;
            }

            if ((player.getPosition().x >= 1820 && screen == 0) && (enemycount >= 1 && score >= 40))                        //screen shift to 1
            {
                player.setPosition(100, level);
                screen = 1;
                continue;
            }

            //pipe
            if (true)
            {
                pipe1.setPosition(1400, level - 37);

                if (player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    if (!pipecol)
                    {

                        if (player.getGlobalBounds().top + player.getGlobalBounds().height <= pipe1.getGlobalBounds().top + 1)
                        {
                            player.setPosition(player.getPosition().x, pipe1.getGlobalBounds().top - player.getGlobalBounds().height);
                            velocityY = 0;
                            isjumping = false;
                        }

                        pipecol = true;
                        pipetimer.restart();
                    }

                    if (player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                    {
                        if (player.getGlobalBounds().left < pipe1.getGlobalBounds().left - 25) // Left collision
                        {
                            player.setPosition(pipe1.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                        }
                        else if (player.getGlobalBounds().left + player.getGlobalBounds().width > pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width + 30) // Right collision
                        {
                            player.setPosition(pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width, player.getPosition().y);
                        }
                    }
                    onpipe = true;
                }

                if (!player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    onpipe = false;
                }

                if (pipecol && pipetimer.getElapsedTime().asSeconds() > 0.2)
                {
                    pipecol = false;
                }
            }

            //score calculator
            totalscore.setString("Score: " + to_string(score));

            //enemy1 section
            if (true)
            {
                if (enemy1.getPosition().x <= 0 || enemy1.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    enemyspeed1 = -enemyspeed1;                                                 //swap enemy direction
                }

                enemy1.setPosition(enemy1.getPosition().x + enemyspeed1, level + 21);//move enemy

                if (player.getGlobalBounds().intersects(enemy1.getGlobalBounds()))
                {
                    if ((player.getPosition().y + player.getGlobalBounds().height <= enemy1.getPosition().y + 5) && (isjumping))
                    {
                        smash.play();
                        score += 10;
                        enemy1.setPosition(-100, -100);                                              //enemy collsion detection
                        enemycount++;
                    }
                    else if (!isalive)
                    {
                        hit.play();
                        life--;
                        player.setPosition(100, level - 200);
                        deathtimer.restart();
                        isalive = true;
                    }
                }

                if (isalive && deathtimer.getElapsedTime().asSeconds() > 1)
                {
                    isalive = false;
                }
            }

            //coins section
            if (true)
            {
                if (player.getGlobalBounds().intersects(question1.getGlobalBounds()))               //question1 block detection
                {
                    if (player.getPosition().y > question1.getPosition().y + question1.getGlobalBounds().height - 5)
                    {
                        player.setPosition(player.getPosition().x, question1.getPosition().y + question1.getGlobalBounds().height);
                        if (coin1)
                        {
                            coinm.play();
                            coin1 = false;
                            istime = true;
                            timer.restart();
                            coin.setPosition(510, level - 270);
                            score += 10;
                        }
                    }
                }

                if (istime && timer.getElapsedTime().asSeconds() > 1)
                {
                    coin.setPosition(-100, -100);                                   // coin1 spawning
                    istime = false;
                }

                if (player.getGlobalBounds().intersects(question2.getGlobalBounds()))  //question2 block detection
                {
                    if (player.getPosition().y > question2.getPosition().y + question2.getGlobalBounds().height - 5)
                    {
                        player.setPosition(player.getPosition().x, question2.getPosition().y + question2.getGlobalBounds().height);
                        if (coin2)
                        {
                            coinm.play();
                            coin2 = false;
                            istime = true;
                            timer.restart();
                            coin.setPosition(904, level - 283);
                            score += 10;
                        }
                    }
                }

                if (istime && timer.getElapsedTime().asSeconds() > 1)
                {
                    coin.setPosition(-100, -100);                                   // coin2 spawning
                    istime = false;
                }

                if (player.getGlobalBounds().intersects(question3.getGlobalBounds()))  //question3 block detection
                {
                    if (player.getPosition().y > question3.getPosition().y + question3.getGlobalBounds().height - 5)
                    {
                        player.setPosition(player.getPosition().x, question3.getPosition().y + question3.getGlobalBounds().height);
                        if (coin3)
                        {
                            coinm.play();
                            coin3 = false;
                            istime = true;
                            timer.restart();
                            coin.setPosition(1084, level - 283);
                            score += 10;
                        }
                    }
                }

                if (istime && timer.getElapsedTime().asSeconds() > 1)
                {
                    coin.setPosition(-100, -100);                                   // coin3 spawning
                    cout << coin3;
                    istime = false;
                }

                if (player.getGlobalBounds().intersects(skyblock1.getGlobalBounds()))
                {
                    // top collision
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= skyblock1.getGlobalBounds().top + 5 &&
                        player.getGlobalBounds().top + player.getGlobalBounds().height > skyblock1.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, skyblock1.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                    //bottom collision
                    else if (player.getGlobalBounds().top >= skyblock1.getGlobalBounds().top + skyblock1.getGlobalBounds().height - 5 &&
                        player.getGlobalBounds().top < skyblock1.getGlobalBounds().top + skyblock1.getGlobalBounds().height + 20)
                    {
                        player.setPosition(player.getPosition().x, skyblock1.getGlobalBounds().top + skyblock1.getGlobalBounds().height);
                    }
                    // left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= skyblock1.getGlobalBounds().left + 25 &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > skyblock1.getGlobalBounds().left)
                    {
                        player.setPosition(skyblock1.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // right collision
                    else if (player.getGlobalBounds().left >= skyblock1.getGlobalBounds().left + skyblock1.getGlobalBounds().width - 25 &&
                        player.getGlobalBounds().left < skyblock1.getGlobalBounds().left + skyblock1.getGlobalBounds().width)
                    {
                        player.setPosition(skyblock1.getGlobalBounds().left + skyblock1.getGlobalBounds().width, player.getPosition().y);
                    }
                }
            }

            //basic logics
            if (true)
            {
                if (!isjumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                {
                    jump.play();
                    isjumping = true;
                    velocityY = jumpSpeed;

                    if (jumpside)
                    {
                        player.setTexture(rightTexture);
                    }
                    else
                    {
                        player.setTexture(leftTexture);
                    }
                }


                if (isjumping || !onpipe)
                {
                    velocityY += gravity;                                           // add gravity
                }

                if (!isjumping)
                {
                    if (jumpside)
                    {
                        player.setTexture(rightidle);
                    }
                    else
                    {
                        player.setTexture(leftidle);
                    }
                }

                player.move(0, velocityY);

                if (player.getPosition().y >= level)
                {
                    player.setPosition(player.getPosition().x, level);
                    isjumping = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    jumpside = false;
                    if (player.getPosition().x >= 0)                                        //left walk limit
                    {
                        player.move(-moveSpeed, 0);
                        player.setTexture(leftTexture);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    jumpside = true;
                    if (player.getPosition().x + player.getGlobalBounds().width <= window.getSize().x)                  //right walk limit
                    {
                        player.move(moveSpeed, 0);
                        player.setTexture(rightTexture);
                    }
                }
            }

            //hearts logic
            if (true)
            {
                if (life == 2)
                {
                    heartbox3.setPosition(-100, -100);
                }
                else if (life == 1)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                }
                else if (life == 0)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                    heartbox1.setPosition(-100, -100);
                    isdead = true;
                }
            }
        }
        else if (screen == 1)
        {
            gamekatime = true;
            if ((player.getPosition().x >= 1820 && screen == 1) && (enemycount >= 3 && score >= 70))
            {
                player.setPosition(50, level);
                screen = 2;
                continue;
            }

            //zone area 1
            deathzone1.setPosition(zonearea1, 930);

            //score calculator
            totalscore.setString("Score: " + std::to_string(score));

            //coin4
            if (true)
            {
                if (player.getGlobalBounds().intersects(question4.getGlobalBounds())) // question4 block detection
                {
                    // Bottom collision
                    if (player.getPosition().y > question4.getGlobalBounds().top + question4.getGlobalBounds().height - 5)
                    {
                        player.setPosition(player.getPosition().x, question4.getGlobalBounds().top + question4.getGlobalBounds().height);
                    }
                    // Top collision
                    else if (player.getGlobalBounds().top + player.getGlobalBounds().height <= question4.getGlobalBounds().top + 5)
                    {
                        player.setPosition(player.getPosition().x, question4.getGlobalBounds().top - player.getGlobalBounds().height);
                    }
                    // Right collision
                    else if (player.getGlobalBounds().left < question4.getGlobalBounds().left && player.getGlobalBounds().left + player.getGlobalBounds().width > question4.getGlobalBounds().left)
                    {
                        player.setPosition(question4.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // Left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width > question4.getGlobalBounds().left + question4.getGlobalBounds().width &&
                        player.getGlobalBounds().left < question4.getGlobalBounds().left + question4.getGlobalBounds().width)
                    {
                        player.setPosition(question4.getGlobalBounds().left + question4.getGlobalBounds().width, player.getPosition().y);
                    }

                    // Coin interaction logic
                    if (coin4)
                    {
                        coinm.play();
                        coin4 = false;
                        istime = true;
                        timer.restart();
                        coin.setPosition(839, level - 283); // Adjust position as required
                        score += 10;
                    }
                }

                // Timer logic for the coin
                if (istime && timer.getElapsedTime().asSeconds() > 1)
                {
                    istime = false;
                    coin.setPosition(-100, -100);
                }
            }

            //pipe 1
            if (true)
            {
                pipe1.setPosition(300, level - 37);

                if (player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    // top collision
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= pipe1.getGlobalBounds().top + 5 &&
                        player.getGlobalBounds().top + player.getGlobalBounds().height > pipe1.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, pipe1.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                    // left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= pipe1.getGlobalBounds().left + 25 &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > pipe1.getGlobalBounds().left)
                    {
                        player.setPosition(pipe1.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // right collision
                    else if (player.getGlobalBounds().left >= pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width - 25 &&
                        player.getGlobalBounds().left < pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width)
                    {
                        player.setPosition(pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width, player.getPosition().y);
                    }
                    onpipe = false;
                }
            }

            //pipe 2
            if (true)
            {
                pipe2.setPosition(1200, level - 37);

                if (player.getGlobalBounds().intersects(pipe2.getGlobalBounds()))
                {
                    // top collision
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= pipe2.getGlobalBounds().top + 5 &&
                        player.getGlobalBounds().top + player.getGlobalBounds().height > pipe2.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, pipe2.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                    // left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= pipe2.getGlobalBounds().left + 25 &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > pipe2.getGlobalBounds().left)
                    {
                        player.setPosition(pipe2.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // right collision
                    else if (player.getGlobalBounds().left >= pipe2.getGlobalBounds().left + pipe2.getGlobalBounds().width - 25 &&
                        player.getGlobalBounds().left < pipe2.getGlobalBounds().left + pipe2.getGlobalBounds().width)
                    {
                        player.setPosition(pipe2.getGlobalBounds().left + pipe2.getGlobalBounds().width, player.getPosition().y);
                    }
                    onpipe = false;
                }
            }

            //enemy2 section
            if (true)
            {
                if (enemy2.getGlobalBounds().intersects(pipe1.getGlobalBounds()) || enemy2.getGlobalBounds().intersects(pipe2.getGlobalBounds()))
                {
                    enemyspeed1 = -enemyspeed1;                                                 //swap enemy direction
                }

                enemy2.setPosition(enemy2.getPosition().x + enemyspeed1, level + 21);//move enemy

                if (player.getGlobalBounds().intersects(enemy2.getGlobalBounds()))
                {
                    if ((player.getPosition().y + player.getGlobalBounds().height <= enemy2.getPosition().y + 5) && (isjumping))
                    {
                        smash.play();
                        enemy2.setPosition(-100, -100);                                              //enemy collsion detection
                        enemyspeed1 = 0;
                        enemycount++;
                        score += 10;
                    }
                    else if (!isalive) 
                    {
                        hit.play();
                        life--;
                        player.setPosition(100, level - 200);
                        isalive = true;
                        deathtimer.restart();
                    }
                }
                if (isalive && deathtimer.getElapsedTime().asSeconds() > 1) {
                    isalive = false;
                }
            }

            //enemy3 section
            if (true)
            {
                if (enemy3.getGlobalBounds().intersects(pipe1.getGlobalBounds()) || enemy3.getGlobalBounds().intersects(pipe2.getGlobalBounds()))
                {
                    enemyspeed2 = -enemyspeed2;                                                 //swap enemy direction
                }

                enemy3.setPosition(enemy3.getPosition().x + enemyspeed2, level + 21);//move enemy

                if (player.getGlobalBounds().intersects(enemy3.getGlobalBounds()))
                {
                    if ((player.getPosition().y + player.getGlobalBounds().height <= enemy3.getPosition().y + 5) && (isjumping))
                    {
                        smash.play();
                        enemy3.setPosition(-100, -100);                                              //enemy collsion detection
                        enemyspeed2 = 0;
                        enemycount++;
                        score += 10;
                    }
                    else if (!isalive)
                    {
                        hit.play();
                        life--;
                        player.setPosition(100, level - 200);
                        isalive = false;
                        deathtimer.restart();
                    }
                }

                if (!isalive && deathtimer.getElapsedTime().asSeconds() > 1) {
                    isalive = false;
                }
            }

            //basic movements
            if (true)
            {
                if (!isjumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                {
                    jump.play();
                    isjumping = true;
                    velocityY = jumpSpeed;

                    if (jumpside)
                    {
                        player.setTexture(rightTexture);
                    }
                    else
                    {
                        player.setTexture(leftTexture);
                    }
                }


                if (isjumping || !onpipe)
                {
                    velocityY += gravity;
                }

                player.move(0, velocityY);

                if (player.getPosition().y >= level && !(player.getPosition().x >= zonearea1 && player.getPosition().x <= zonearea1 + 150))
                {
                    player.setPosition(player.getPosition().x, level);
                    isjumping = false;
                }
                else
                {
                    if (player.getPosition().y > level + 100)
                    {
                        player.setPosition(100, level - 200);
                        life--;
                        showtext = true;
                        lifeminustimer.restart();
                    }
                }

                if (showtext && lifeminustimer.getElapsedTime().asSeconds() > 1.5)
                {
                    showtext = false;
                }

                if (!isjumping)
                {
                    if (jumpside)
                    {
                        player.setTexture(rightidle);
                    }
                    else
                    {
                        player.setTexture(leftidle);
                    }
                }


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    jumpside = false;
                    if (player.getPosition().x >= 0)
                    {
                        player.move(-moveSpeed, 0);
                        player.setTexture(leftTexture);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    jumpside = true;
                    if (player.getPosition().x + player.getGlobalBounds().width <= window.getSize().x)
                    {
                        player.move(moveSpeed, 0);
                        player.setTexture(rightTexture);
                    }
                }
            }

            //hearts logic
            if (true)
            {
                if (life == 2)
                {
                    heartbox3.setPosition(-100, -100);
                }
                else if (life == 1)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                }
                else if (life == 0)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                    heartbox1.setPosition(-100, -100);
                    isdead = true;
                }
            }
        }
        else if (screen == 2)
        {
            if ((player.getPosition().x >= 1820 && screen == 2) && (enemycount >= 4 && score >= 80))
            {
                player.setPosition(100, level);
                screen = 3;
                continue;
            }

            //zone area 2
            deathzone2.setPosition(zonearea2, 930);
            //score calculator
            totalscore.setString("Score: " + std::to_string(score));

            //enemy4 section
            if (true)
            {
                if (enemy4.getPosition().x > 0) // check for enemy is active
                {
                    if (enemy4.getPosition().x <= 0 || enemy4.getGlobalBounds().left + enemy4.getGlobalBounds().width >= window.getSize().x)
                    {
                        
                        enemyspeed1 = -enemyspeed1; // swap direction
                    }

                    float enemyxpos = enemy4.getPosition().x + enemyspeed1;
                    float enemyypos = enemy4.getPosition().y + velocityE1;

                    // Collision with skyblocks
                    if (enemy4.getGlobalBounds().intersects(skyblock2.getGlobalBounds()))
                    {
                        if (enemy4.getGlobalBounds().top + enemy4.getGlobalBounds().height <= skyblock2.getGlobalBounds().top + 5 && velocityE1 > 0)
                        {
                            enemyypos = skyblock2.getGlobalBounds().top - 75;
                            velocityE1 = 0;
                        }
                    }
                    else if (enemy4.getGlobalBounds().intersects(skyblock3.getGlobalBounds()))
                    {
                        if (enemy4.getGlobalBounds().top + enemy4.getGlobalBounds().height <= skyblock3.getGlobalBounds().top + 5 && velocityE1 > 0)
                        {
                            enemyypos = skyblock3.getGlobalBounds().top - 75;
                            velocityE1 = 0;
                        }
                    }

                    if (enemy4.getPosition().y >= level + 18)
                    {
                        velocityE1 = 0;
                    }

                    if (!enemy4.getGlobalBounds().intersects(skyblock2.getGlobalBounds()) &&
                        !enemy4.getGlobalBounds().intersects(skyblock3.getGlobalBounds()) &&
                        !(enemy4.getPosition().y >= level + 18))
                    {
                        velocityE1 += gravity;
                    }

                    enemy4.setPosition(enemyxpos, enemyypos); // Update position

                    if (player.getGlobalBounds().intersects(enemy4.getGlobalBounds()))
                    {
                        if (player.getGlobalBounds().top + player.getGlobalBounds().height <= enemy4.getGlobalBounds().top + 5 && isjumping)
                        {
                            smash.play();
                            score += 10;
                            enemy4.setPosition(-100, -100);
                            enemycount++;
                        }
                        else if (!isalive)
                        {
                            hit.play();
                            life--;
                            player.setPosition(100, level - 200);
                            isalive = true;
                            deathtimer.restart();
                        }
                    }
                }
                if (isalive && deathtimer.getElapsedTime().asSeconds() > 1)
                {
                    isalive = false;
                }
            }

            //coin5
            if (true)
            {
                if (player.getGlobalBounds().intersects(question5.getGlobalBounds()))               //question 5 block detection
                {
                    if (player.getPosition().y > question5.getPosition().y + question5.getGlobalBounds().height - 5)
                    {
                        player.setPosition(player.getPosition().x, question5.getPosition().y + question5.getGlobalBounds().height);
                        if (coin5)
                        {
                            coinm.play();
                            coin5 = false;
                            istime = true;
                            timer.restart();
                            coin.setPosition(1595, level - 450);
                            score += 10;
                        }
                    }
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= question5.getGlobalBounds().left &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > question5.getGlobalBounds().left)
                    {
                        player.setPosition(question5.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                }

                if (istime && timer.getElapsedTime().asSeconds() > 1)
                {
                    istime = false;
                    coin.setPosition(-100, -100);
                }
            }

            //pipe
            pipe2.setPosition(1550, level - 37);
            if (true)
            {
                if (player.getGlobalBounds().intersects(pipe2.getGlobalBounds()))
                {
                    // top collision
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= pipe2.getGlobalBounds().top + 5 &&
                        player.getGlobalBounds().top + player.getGlobalBounds().height > pipe2.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, pipe2.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                    // left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= pipe2.getGlobalBounds().left + 25 &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > pipe2.getGlobalBounds().left)
                    {
                        player.setPosition(pipe2.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // right collision
                    else if (player.getGlobalBounds().left >= pipe2.getGlobalBounds().left + pipe2.getGlobalBounds().width - 25 &&
                        player.getGlobalBounds().left < pipe2.getGlobalBounds().left + pipe2.getGlobalBounds().width)
                    {
                        player.setPosition(pipe2.getGlobalBounds().left + pipe2.getGlobalBounds().width, player.getPosition().y);
                    }
                    onpipe = false;
                }
            }

            //movement on skyblock by player
            if (true)
            {
                if (player.getGlobalBounds().intersects(skyblock3.getGlobalBounds()))
                {
                    //top collision
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height < skyblock3.getGlobalBounds().top + 5 &&
                        player.getGlobalBounds().top + player.getGlobalBounds().height >= skyblock3.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x,skyblock3.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                    //bottom collision
                    if (player.getGlobalBounds().top >= skyblock3.getGlobalBounds().top + skyblock3.getGlobalBounds().height - 5 &&
                        player.getGlobalBounds().top < skyblock3.getGlobalBounds().top + skyblock3.getGlobalBounds().height + 20)
                    {
                        player.setPosition(player.getPosition().x, skyblock3.getGlobalBounds().top + skyblock3.getGlobalBounds().height);
                    }
                    // left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= skyblock3.getGlobalBounds().left + 25 &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > skyblock3.getGlobalBounds().left)
                    {
                        player.setPosition(skyblock3.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // right collision
                    else if (player.getGlobalBounds().left >= skyblock3.getGlobalBounds().left + skyblock3.getGlobalBounds().width - 25 &&
                        player.getGlobalBounds().left < skyblock3.getGlobalBounds().left + skyblock3.getGlobalBounds().width)
                    {
                        player.setPosition(skyblock3.getGlobalBounds().left + skyblock3.getGlobalBounds().width, player.getPosition().y);
                    }
                }
            }

            //player basic movements
            if (true)
            {
                zonearea1 = 1000.0f;
                deathzone1.setPosition(zonearea1, 930);

                if (!isjumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                {
                    jump.play();
                    isjumping = true;
                    velocityY = jumpSpeed;

                    if (jumpside)
                    {
                        player.setTexture(rightTexture);
                    }
                    else
                    {
                        player.setTexture(leftTexture);
                    }
                }


                if (isjumping || !onpipe)
                {
                    velocityY += gravity;                                           // add gravity
                }

                if (!isjumping)
                {
                    if (jumpside)
                    {
                        player.setTexture(rightidle);
                    }
                    else
                    {
                        player.setTexture(leftidle);
                    }
                }

                player.move(0, velocityY);

                if (player.getPosition().y >= level && !(player.getPosition().x > zonearea2 && player.getPosition().x <= zonearea2 + 150))
                {
                    player.setPosition(player.getPosition().x, level);
                    isjumping = false;
                }
                else
                {
                    if (player.getPosition().y > level + 100)
                    {
                        player.setPosition(100, level - 200);
                        life--;
                        showtext = true;
                        lifeminustimer.restart();
                    }
                }

                if (showtext && lifeminustimer.getElapsedTime().asSeconds() > 1.5)
                {
                    showtext = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    jumpside = false;
                    if (player.getPosition().x >= 0)                                        //left walk limit
                    {
                        player.move(-moveSpeed, 0);
                        player.setTexture(leftTexture);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    jumpside = true;
                    if (player.getPosition().x + player.getGlobalBounds().width <= window.getSize().x)                  //right walk limit
                    {
                        player.move(moveSpeed, 0);
                        player.setTexture(rightTexture);
                    }
                }
            }

            //hearts logic
            if (true)
            {
                if (life == 2)
                {
                    heartbox3.setPosition(-100, -100);
                }
                else if (life == 1)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                }
                else if (life == 0)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                    heartbox1.setPosition(-100, -100);
                    isdead = true;
                }
            }

        }
        else if (screen == 3)
        {
            if ((player.getPosition().x >= 1820 && screen == 3) && (enemycount >= 5 && score >= 90))
            {
                player.setPosition(100, level);
                screen = 4;
                continue;
            }

            //skyblock logic
            if (true)
            {
                if (player.getGlobalBounds().intersects(skyblock4.getGlobalBounds()))
                {
                    //top collision
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height < skyblock4.getGlobalBounds().top + 5 &&
                        player.getGlobalBounds().top + player.getGlobalBounds().height >= skyblock4.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, skyblock4.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                    //bottom collision
                    if (player.getGlobalBounds().top >= skyblock4.getGlobalBounds().top + skyblock4.getGlobalBounds().height - 5 &&
                        player.getGlobalBounds().top < skyblock4.getGlobalBounds().top + skyblock4.getGlobalBounds().height + 20)
                    {
                        player.setPosition(player.getPosition().x, skyblock4.getGlobalBounds().top + skyblock4.getGlobalBounds().height);
                    }
                    // left collision
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width <= skyblock4.getGlobalBounds().left + 25 &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > skyblock4.getGlobalBounds().left)
                    {
                        player.setPosition(skyblock4.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    // right collision
                    else if (player.getGlobalBounds().left >= skyblock4.getGlobalBounds().left + skyblock4.getGlobalBounds().width - 25 &&
                        player.getGlobalBounds().left < skyblock4.getGlobalBounds().left + skyblock4.getGlobalBounds().width)
                    {
                        player.setPosition(skyblock4.getGlobalBounds().left + skyblock4.getGlobalBounds().width, player.getPosition().y);
                    }
                }
            }

            //pipe
            if (true)
            {
                pipe1.setPosition(300, level - 37);

                if (player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= pipe1.getGlobalBounds().top + 1)
                    {
                        player.setPosition(player.getPosition().x, pipe1.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }

                    pipetimer.restart();
                }

                if (player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    if (player.getGlobalBounds().left < pipe1.getGlobalBounds().left - 25) // Left collision
                    {
                        player.setPosition(pipe1.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }
                    else if (player.getGlobalBounds().left + player.getGlobalBounds().width > pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width + 30) // Right collision
                    {
                        player.setPosition(pipe1.getGlobalBounds().left + pipe1.getGlobalBounds().width, player.getPosition().y);
                    }
                }
                onpipe = true;

                if (!player.getGlobalBounds().intersects(pipe1.getGlobalBounds()))
                {
                    onpipe = false;
                }

            }

            //enemy section
            if (true)
            {
                if (player.getGlobalBounds().intersects(enemy5.getGlobalBounds()))
                {
                    if ((player.getPosition().y + player.getGlobalBounds().height <= enemy5.getPosition().y + 5) && (isjumping))
                    {
                        smash.play();
                        score += 10;
                        enemy5.setPosition(-100, -100);                                              //enemy collsion detection
                        enemycount++;
                    }
                    else if (!isalive)
                    {
                        hit.play();
                        life--;
                        player.setPosition(100, level - 200);
                        deathtimer.restart();
                        isalive = true;
                    }
                }

                if (isalive && deathtimer.getElapsedTime().asSeconds() > 1)
                {
                    isalive = false;
                }
            }

            //score calculator
            totalscore.setString("Score: " + std::to_string(score));

            //basic movement logics
            if (true)
            {
                if (!isjumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                {
                    jump.play();
                    isjumping = true;
                    velocityY = jumpSpeed;

                    if (jumpside)
                    {
                        player.setTexture(rightTexture);
                    }
                    else
                    {
                        player.setTexture(leftTexture);
                    }
                }


                if (isjumping || !onpipe)
                {
                    velocityY += gravity;                                           // add gravity
                }

                if (!isjumping)
                {
                    if (jumpside)
                    {
                        player.setTexture(rightidle);
                    }
                    else
                    {
                        player.setTexture(leftidle);
                    }
                }

                player.move(0, velocityY);

                if (player.getPosition().y >= level)
                {
                    player.setPosition(player.getPosition().x, level);
                    isjumping = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    jumpside = false;
                    if (player.getPosition().x >= 0)                                        //left walk limit
                    {
                        player.move(-moveSpeed, 0);
                        player.setTexture(leftTexture);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    jumpside = true;
                    if (player.getPosition().x + player.getGlobalBounds().width <= window.getSize().x)                  //right walk limit
                    {
                        player.move(moveSpeed, 0);
                        player.setTexture(rightTexture);
                    }
                }
            }

            //hearts logic
            if (true)
            {
                if (life == 2)
                {
                    heartbox3.setPosition(-100, -100);
                }
                else if (life == 1)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                }
                else if (life == 0)
                {
                    heartbox3.setPosition(-100, -100);
                    heartbox2.setPosition(-100, -100);
                    heartbox1.setPosition(-100, -100);
                    isdead = true;
                }
            }
        }
        else if (screen == 4)
        {
            //score calculator
            totalscore.setString("Score: " + std::to_string(score));

            //stairs logic
            if (true)
            {
                if (player.getGlobalBounds().intersects(dabba1.getGlobalBounds()))          //dabba 1
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba1.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba1.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba1.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba1.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba1.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba1.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba1.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba2.getGlobalBounds()))          //dabba 2
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba2.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba2.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba2.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba2.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba2.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba2.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba2.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba3.getGlobalBounds()))          //dabba 3
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba3.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba3.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba3.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba3.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba3.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba3.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba3.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba4.getGlobalBounds()))          //dabba 4
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba4.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba4.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba4.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba4.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba4.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba4.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba4.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba5.getGlobalBounds()))          //dabba 5
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba5.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba5.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba5.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba5.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba5.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba5.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba5.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba6.getGlobalBounds()))          //dabba 6
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba6.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba6.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba6.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba6.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba6.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba6.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba6.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba7.getGlobalBounds()))          //dabba 7
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba7.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba7.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba7.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba7.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba7.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba7.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba7.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba8.getGlobalBounds()))          //dabba 8
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba8.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba8.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba8.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba8.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba8.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba8.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba8.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba9.getGlobalBounds()))          //dabba 9
                {
                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba9.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba9.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba9.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(dabba10.getGlobalBounds()))          //dabba 10
                {
                    if (player.getGlobalBounds().left + player.getGlobalBounds().width >= dabba10.getGlobalBounds().left
                        && player.getGlobalBounds().left < dabba10.getGlobalBounds().left + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba10.getGlobalBounds().top + 5)
                    {
                        player.setPosition(dabba10.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                    }

                    if (player.getGlobalBounds().top + player.getGlobalBounds().height <= dabba10.getGlobalBounds().top + 5
                        && player.getGlobalBounds().top + player.getGlobalBounds().height > dabba10.getGlobalBounds().top)
                    {
                        player.setPosition(player.getPosition().x, dabba10.getGlobalBounds().top - player.getGlobalBounds().height);
                        velocityY = 0;
                        isjumping = false;
                    }
                }

                if (player.getGlobalBounds().intersects(stairs.getGlobalBounds()))              //stairs logic from right side
                {
                    if (player.getGlobalBounds().left < stairs.getGlobalBounds().left + stairs.getGlobalBounds().width &&
                        player.getGlobalBounds().left + player.getGlobalBounds().width > stairs.getGlobalBounds().left + stairs.getGlobalBounds().width)
                    {
                        player.setPosition(stairs.getGlobalBounds().left + stairs.getGlobalBounds().width, player.getPosition().y);
                    }
                }
            }

            //flag part
            if (true)
            {
                if (player.getGlobalBounds().left + player.getGlobalBounds().width >= flag1.getGlobalBounds().left + 10)
                {
                    player.setPosition(1300, level);
                    win = true;
                    backmusic.setVolume(30);
                    winm.play();
                }
            }

            //basic logics
            if (true)
            {
                if (!isjumping && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
                {
                    jump.play();
                    isjumping = true;
                    velocityY = jumpSpeed;

                    if (jumpside)
                    {
                        player.setTexture(rightTexture);
                    }
                    else
                    {
                        player.setTexture(leftTexture);
                    }
                }


                if (isjumping || !ondabba)
                {
                    velocityY += gravity;                                           // add gravity
                }

                if (!isjumping)
                {
                    if (jumpside)
                    {
                        player.setTexture(rightidle);
                    }
                    else
                    {
                        player.setTexture(leftidle);
                    }
                }

                player.move(0, velocityY);

                if (player.getPosition().y >= level)
                {
                    player.setPosition(player.getPosition().x, level);
                    isjumping = false;
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    jumpside = false;
                    if (player.getPosition().x >= 0)                                        //left walk limit
                    {
                        player.move(-moveSpeed, 0);
                        player.setTexture(leftTexture);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    jumpside = true;
                    if (player.getPosition().x + player.getGlobalBounds().width <= window.getSize().x)                  //right walk limit
                    {
                        player.move(moveSpeed, 0);
                        player.setTexture(rightTexture);
                    }
                }
            }
        }

        //***********************************************     OUTPUT SECTION     ***********************************************************************************
        window.clear();
        if (menu)
        {
            window.draw(menupage);
            window.draw(player);
        }
        else if (leader)
        {
            window.draw(leaderboard);
            window.draw(leadert1);
            window.draw(leadert2);
            window.draw(leadert3);
            window.draw(leadert4);
            window.draw(leadert5);
        }
        else if (win)
        {
            window.draw(winback);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            window.draw(castle);
            window.draw(dabba1);
            window.draw(dabba2);
            window.draw(dabba3);
            window.draw(dabba4);
            window.draw(dabba5);
            window.draw(dabba6);
            window.draw(dabba7);
            window.draw(dabba8);
            window.draw(dabba9);
            window.draw(stairs);
            window.draw(flag1);
            window.draw(flag2);
            window.draw(dabba10);
            window.draw(player);
        }
        else if (timetogo)
        {
            window.draw(winback);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            window.draw(castle);
            window.draw(dabba1);
            window.draw(dabba2);
            window.draw(dabba3);
            window.draw(dabba4);
            window.draw(dabba5);
            window.draw(dabba6);
            window.draw(dabba7);
            window.draw(dabba8);
            window.draw(dabba9);
            window.draw(stairs);
            window.draw(flag1);
            window.draw(flag2);
            window.draw(dabba10);
            window.draw(winbacktrans);
            window.draw(maintime);
            window.draw(welldone);
            window.draw(enter);

            //reset everything 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                win = false;
                menu = true;
                timetogo = false;
                player.setPosition(100, level);
                life = 3;
                timer.restart();
                isjumping = false;
                jumpside = true;
                ondabba = false;
                istime = false;
                coin1 = true;
                coin2 = true;
                coin3 = true;
                coin4 = true;
                coin5 = true;
                isname = true;
                isalive = false;
                isdead = false;
                pipecol = false;
                onpipe = true;
                showtext = false;
                win = false;                                               //game ending
                setpos = true;
                timetogo = false;
                gamekatime = true;
                zonearea1 = 1550.0f;
                zonearea2 = 1000.0f;
                level = 840.0f;                                           //player movement ground
                enemyspeed1 = 0.07f;
                enemyspeed2 = 0.07f;
                enemyspeed3 = 0.07f;
                velocityY = 1.0f;
                velocityE1 = 1.0f;
                velocityE2 = 1.0f;
                velocityE3 = 1.0f;
                velocityE4 = 1.0f;
                winspeed = 0.3f;
                screen = 0;
                score = 0;
                life = 3;
                enemycount = 0;
                heartbox1.setPosition(886, 27);
                heartbox2.setPosition(945, 27);
                heartbox3.setPosition(1003, 27);
                enemy1.setPosition(1200.0, level + 21);
                enemy2.setPosition(500.0, level + 21);
                enemy3.setPosition(700.0, level + 21);
                enemy4.setPosition(1020.0, level - 870);
                enemy5.setPosition(1000.0, level - 220);
                flag2.setPosition(1117, level - 398);
            }
        }
        else if (isdead)
        {
            window.draw(deathscreen);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                win = false;
                menu = true;
                timetogo = false;
                player.setPosition(100, level);
                life = 3;
                timer.restart();
                isjumping = false;
                jumpside = true;
                ondabba = false;
                istime = false;
                coin1 = true;
                coin2 = true;
                coin3 = true;
                coin4 = true;
                coin5 = true;
                isalive = false;
                isdead = false;
                pipecol = false;
                onpipe = true;
                showtext = false;
                win = false;                                               //game ending
                setpos = true;
                timetogo = false;
                gamekatime = true;
                zonearea1 = 1550.0f;
                zonearea2 = 1000.0f;
                level = 840.0f;                                           //player movement ground
                enemyspeed1 = 0.07f;
                enemyspeed2 = 0.07f;
                enemyspeed3 = 0.07f;
                velocityY = 1.0f;
                velocityE1 = 1.0f;
                velocityE2 = 1.0f;
                velocityE3 = 1.0f;
                velocityE4 = 1.0f;
                winspeed = 0.3f;
                screen = 0;
                score = 0;
                life = 3;
                enemycount = 0;
                heartbox1.setPosition(886, 27);
                heartbox2.setPosition(945, 27);
                heartbox3.setPosition(1003, 27);
                enemy1.setPosition(1200.0, level + 21);
                enemy2.setPosition(500.0, level + 21);
                enemy3.setPosition(700.0, level + 21);
                enemy4.setPosition(1020.0, level - 870);
                enemy5.setPosition(1000.0, level - 220);
                flag2.setPosition(1117, level - 398);
            }
        }
        else if (screen == 0)
        {
            window.draw(background);
            window.draw(pipe1);
            window.draw(enemy1);
            window.draw(skyblock1);
            window.draw(question1);
            window.draw(question2);
            window.draw(question3);
            window.draw(backbox3);
            window.draw(gametimer);
            if (istime)
                window.draw(coin);
            window.draw(player);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
        }
        else if (screen == 1)
        {
            window.draw(simplescreen);
            window.draw(deathzone1);
            window.draw(pipe1);
            window.draw(pipe2);
            window.draw(player);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            window.draw(backbox3);
            window.draw(gametimer);
            if (showtext)
            {
                window.draw(lifeminustext1);
            }
            window.draw(enemy2);
            window.draw(enemy3);
            window.draw(question4);
            window.draw(coin);
        }
        else if (screen == 2)
        {
            window.draw(simplescreen);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            window.draw(skyblock2);
            window.draw(skyblock3);
            window.draw(enemy4);
            window.draw(deathzone2);
            window.draw(player);
            window.draw(pipe2);
            window.draw(question5);
            window.draw(backbox3);
            window.draw(gametimer);
            window.draw(coin);
            if (showtext)
                window.draw(lifeminustext2);
        }
        else if (screen == 3)
        {
            window.draw(simplescreen);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            window.draw(backbox3);
            window.draw(gametimer);
            window.draw(skyblock4);
            window.draw(enemy5);
            window.draw(pipe1);
            window.draw(player);
        }
        else if (screen == 4)
        {
            window.draw(simplescreen);
            window.draw(backbox1);
            window.draw(totalscore);
            window.draw(backbox2);
            window.draw(heartbox1);
            window.draw(heartbox2);
            window.draw(heartbox3);
            window.draw(backbox3);
            window.draw(gametimer);
            window.draw(castle);
            window.draw(dabba1);
            window.draw(dabba2);
            window.draw(dabba3);
            window.draw(dabba4);
            window.draw(dabba5);
            window.draw(dabba6);
            window.draw(dabba7);
            window.draw(dabba8);
            window.draw(dabba9);
            window.draw(stairs);
            window.draw(flag1);
            window.draw(flag2);
            window.draw(dabba10);
            window.draw(player);
        }

        window.display();
    }
    return 0;
}