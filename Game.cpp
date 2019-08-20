//
// Created by Hammad Siddiqui on 12/15/15.
//

#include "Game.h"
#include <iostream>
#include "Collision.h"


/*
 * Constructor creates an empty window object of size 640x480 pixels
 * And then, it calls all the initialization of other elements.
 *
 * */
Game::Game() : mWindow(sf::VideoMode(450,520,32),"Frogger"),
               scoreText("0", font, 11),
               mIsMovingDown(false),
               mIsMovingLeft(false),
               mIsMovingRight(false),
               mIsMovingUp(false)  {

   // welcomeScreen(); Text not showing up, Dont know why
    gameOver = false; //Init gameOver to -1
    frogWin = false; ///Init frogWin to -1

    // Load a music to play
    if (!music.openFromFile("assets/music.ogg"))
        std::cout << "Music Failed to load" << std::endl;

    //Game Speed based on frame rate
    mWindow.setFramerateLimit(10);

    //Initial Score
    score = 0;

    //Load Font
    if(!font.loadFromFile("assets/Abduction.ttf"))
    {
        std::cout << "Failed to load font \"Abduction\"" << std::endl;
    }


    //paint out the entire window with blue color
    sf::Color blueColor(0,0,55);
    mWindow.clear(blueColor);
    //initialize frog to its position

    initWindow();
    initCars();
    initFrog();
    initWood();
    initScorecard();
    music.play();



}


void Game::initWindow() {

    //Draw the background
    sf::Texture path;
    path.loadFromFile("assets/background.png");
    sf::Sprite bg;
    bg.setTexture(path);
    bg.scale(2,2);
    bg.setPosition(1,50);
    mWindow.draw(bg);
    //Cute frog Sprite is also called here as it is not moving
    initCuteFrog();


}


void Game::initCars() {

    /*
     * First the texture is loaded, and then the texture is pasted
     * on an SFML Sprite Object
     * Each asset has its own texture and Sprite
     * */
    sf::Texture truck;
    truck.loadFromFile("assets/truck.png");


    sf::Texture car3;
    car3.loadFromFile("assets/car3.png");

    sf::Texture car1;
    car1.loadFromFile("assets/car1.png");

    sf::Texture car2;
    if(!car2.loadFromFile("assets/car2.png"))
        std::cout << "Failed to load car2 Sprite" << std::endl;

    sf::Texture tractor;
    if(!tractor.loadFromFile("assets/tractor.png"))
        std::cout << "Failed to load tracktor Sprite" << std::endl;





    for (int i = 0; i < 4; ++i) {



        truckSprite[i].setTexture(truck);
        truckSprite[i].scale(2,2);
        truckSprite[i].setPosition(70 + (i*120),ROAD_ROW_1_HEIGHT);
        mWindow.draw(truckSprite[i]);


        car1Sprite[i].setTexture(car1);
        car1Sprite[i].scale(2,2);
        car1Sprite[i].setPosition(50 + (i*140),ROAD_ROW_2_HEIGHT);
        mWindow.draw(car1Sprite[i]);

        car2Sprite[i].setTexture(car2);
        car2Sprite[i].scale(2,2);
        car2Sprite[i].setPosition(70 + (i*120), ROAD_ROW_3_HEIGHT);
        mWindow.draw(car2Sprite[i]);

        tractorSprite[i].setTexture(tractor);
        tractorSprite[i].scale(2,2);
        tractorSprite[i].setPosition(120 + (i*120), ROAD_ROW_4_HEIGHT);
        mWindow.draw(tractorSprite[i]);

        car3Sprite[i].setTexture(car3);
        car3Sprite[i].scale(2,2);
        car3Sprite[i].setPosition(170 + (i*120), ROAD_ROW_5_HEIGHT);
        mWindow.draw(car3Sprite[i]);


    }





}


void Game::initWood() {

    /*
       * First the texture is loaded, and then the texture is pasted
       * on an SFML Sprite Object
       * Each asset has its own texture and Sprite
       * */

    //Init woods and place them on their positions.
    sf::Texture wood1;
    if(!wood1.loadFromFile("assets/wood.png"))
        std::cout << "Failed to load wood Sprite" << std::endl;


    for (int i = 0; i < 4; ++i) {


        wood1Sprite[i].setTexture(wood1);
        wood1Sprite[i].setPosition(70 + (i * 170), WOOD_ROW_1);
        mWindow.draw(wood1Sprite[i]);
        if(i%2 == 0) {
            wood1Sprite[i].setScale(2.5,2.5);
        }
        else {
            wood1Sprite[i].setScale(2.0,2.0);
        }


        wood2Sprite[i].setTexture(wood1);
        wood2Sprite[i].setPosition(70 + (i * 170), WOOD_ROW_2);
        mWindow.draw(wood2Sprite[i]);
        if(i%2 == 0) {
            wood2Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood2Sprite[i].setScale(2.0,2.0);
        }

        wood3Sprite[i].setTexture(wood1);
        wood3Sprite[i].setPosition(70 + (i * 170), WOOD_ROW_3);
        mWindow.draw(wood3Sprite[i]);
        if(i%2 == 0) {
            wood3Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood3Sprite[i].setScale(2.0,2.0);
        }


        wood4Sprite[i].setTexture(wood1);
        wood4Sprite[i].setPosition(10 + (i * 570), WOOD_ROW_4);
        mWindow.draw(wood4Sprite[i]);
        if(i%2 == 0) {
            wood4Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood4Sprite[i].setScale(2.0,2.0);
        }

        wood5Sprite[i].setTexture(wood1);
        wood5Sprite[i].setPosition(0 + (i * 120), WOOD_ROW_5);
        mWindow.draw(wood5Sprite[i]);
        if(i%2 == 0) {
            wood5Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood5Sprite[i].setScale(2.0,2.0);
        }

        wood6Sprite[i].setTexture(wood1);
        wood6Sprite[i].setPosition(45 + (i * 320), WOOD_ROW_6);
        mWindow.draw(wood6Sprite[i]);
        if(i%2 == 0) {
            wood6Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood6Sprite[i].setScale(2.0,2.0);
        }

    }
}


void Game::initFrog() {
    /*
   * First the texture is loaded, and then the texture is pasted
   * on an SFML Sprite Object
   * Each asset has its own texture and Sprite
   * */

    sf::Texture frog;

    if (!frog.loadFromFile("assets/frog.png"))
        std::cout << "Failed to load frog Sprite" << std::endl;

    frogSprite.setTexture(frog);
    frogSprite.setScale(2.0,2.0);
    frogSprite.setPosition(mWindow.getSize().x/2  - frogSprite.getGlobalBounds().width/2 ,mWindow.getSize().y -70); //Initial position of the frog
    mWindow.draw(frogSprite);
}


void Game::initCuteFrog() {
    sf::Texture cuteFrog;
    if(!cuteFrog.loadFromFile("assets/cuteFrog.png")){
        std::cout << "Failed to load cute frog Sprite" << std::endl;
    }

    cuteFrogSprite.setTexture(cuteFrog);
    cuteFrogSprite.setScale(2.0,2.0);
    cuteFrogSprite.setPosition((mWindow.getSize().x/2  - frogSprite.getGlobalBounds().width/2) - 2 , 63); //Initial position of the frog
    mWindow.draw(cuteFrogSprite);
}

void Game::renderCars() {


    //Init truck
    sf::Texture truck;
    truck.loadFromFile("assets/truck.png");

    sf::Texture car3;
    car3.loadFromFile("assets/car3.png");

    sf::Texture car2;
    car2.loadFromFile("assets/car2.png");

    sf::Texture car1;
    car1.loadFromFile("assets/car1.png");

    //Tractor
    sf::Texture tractor;
    if(!tractor.loadFromFile("assets/tractor.png"))
        std::cout << "Failed to load tracktor Sprite" << std::endl;



    for (int i = 0; i < 4; ++i) {
        tractorSprite[i].setTexture(tractor);
        mWindow.draw(tractorSprite[i]);


        truckSprite[i].setTexture(truck);
        mWindow.draw(truckSprite[i]);

        car3Sprite[i].setTexture(car3);
        mWindow.draw(car3Sprite[i]);

        car2Sprite[i].setTexture(car2);

        mWindow.draw(car2Sprite[i]);

        car1Sprite[i].setTexture(car1);

        mWindow.draw(car1Sprite[i]);


    }

}



void Game::renderWoods() {
    sf::Texture wood1;
    if(!wood1.loadFromFile("assets/wood.png"))
        std::cout << "Failed to load wood Sprite" << std::endl;
    for (int i = 0; i < 3; ++i) {
        wood1Sprite[i].setTexture(wood1);
        mWindow.draw(wood1Sprite[i]);
        if(i%2 == 0) {
            wood1Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood1Sprite[i].setScale(2.0,2.0);
        }

        wood2Sprite[i].setTexture(wood1);
        mWindow.draw(wood2Sprite[i]);
        if(i%2 == 0) {
            wood2Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood2Sprite[i].setScale(2.0,2.0);
        }

        wood3Sprite[i].setTexture(wood1);
        mWindow.draw(wood3Sprite[i]);
        if(i%2 == 0) {
            wood3Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood3Sprite[i].setScale(2.0,2.0);
        }

        wood4Sprite[i].setTexture(wood1);
        mWindow.draw(wood4Sprite[i]);
        if(i%2 == 0) {
            wood4Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood4Sprite[i].setScale(2.0,2.0);
        }

        wood5Sprite[i].setTexture(wood1);
        mWindow.draw(wood5Sprite[i]);
        if(i%2 == 0) {
            wood5Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood5Sprite[i].setScale(2.0,2.0);
        }

        wood6Sprite[i].setTexture(wood1);
        mWindow.draw(wood6Sprite[i]);
        if(i%2 == 0) {
            wood6Sprite[i].setScale(2.5,2.0);
        }
        else {
            wood6Sprite[i].setScale(2.0,2.0);
        }
    }
}


void Game::renderScoreCard() {

        if(score < 0) {
            score = 0;
        }
        scoreText.setString(std::to_string(score));
};




void Game::renderFrog() {
    sf::Texture frog;
    if(mIsMovingUp || mIsMovingDown){
        if (!frog.loadFromFile("assets/frogJump.png"))
            std::cout << "Failed to load frog Jump Sprite" << std::endl;
    }

    else {

        if (!frog.loadFromFile("assets/frog.png"))
            std::cout << "Failed to load frog Sprite" << std::endl;

    }
    frogSprite.setTexture(frog);
    frogSprite.setScale(2.0,2.0);
    mWindow.draw(frogSprite);
}



void Game::initScorecard() {

    scoreText.setCharacterSize(20);
    scoreText.setPosition(mWindow.getSize().x/2 - scoreText.getGlobalBounds().width/2, 10);
    mWindow.draw(scoreText);
}


void Game::run() {
   // welcomeScreen();

    while(mWindow.isOpen()) {




        //Respond to Events in the Event Queue
        processEvents();
        //Update the Game according to the events
        update();
        //Render the update screen in the window.
        render();
    }
}

void Game::processEvents() {
    /*
       * This method catches all the events happening inside the window
       * and adds all these events to the event queue.
       * The queue is the used to program logic according to the type of event
       * */

    while(mWindow.pollEvent(event)) {

        switch (event.type) {
            case sf::Event::KeyPressed :
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased :
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

            default:
                continue;
        }



    }
}


void Game::render() {

    /*
     * After the positions of the vechicle and wood logs are updated un the "update()" method
     * All these updates needs to be rendered on the window.
     * This method also renders the screens for game over and game win.
     * */

    //If the frog is able to successfully collide with cute Frog, it wins and this is rendered
    if(frogWin){
        mWindow.clear(sf::Color::Black);
        sf::Text win("You Win", font, 32);
        win.setPosition(mWindow.getSize().x/2 - frogSprite.getGlobalBounds().width/2,
                        mWindow.getSize().y/2 - frogSprite.getGlobalBounds().height/2);
        mWindow.draw(win);
        mWindow.display();
        sf::Time t1 = sf::seconds(1.0f);
        sf::sleep(t1);
        mWindow.close();
    }
    else if (gameOver) {
        mWindow.clear(sf::Color::Black);
        sf::Text lose("Game Over " + std::to_string(score), font, 22);
        lose.setPosition((mWindow.getSize().x/2 - frogSprite.getGlobalBounds().width/2) -50,
                        mWindow.getSize().y/2 - frogSprite.getGlobalBounds().height/2);
        mWindow.draw(lose);
        mWindow.display();
        sf::Time t1 = sf::seconds(7.0f);
        sf::sleep(t1);
        mWindow.close();
    }
    else{
        mWindow.clear(sf::Color::Transparent);
        initWindow();
        renderWoods();
        renderFrog();
        renderCars();
        renderScoreCard();
        mWindow.draw(scoreText);
        mWindow.display();

    }


}


void Game::detectCollision() {
    /*
    * While frog is in the road range:
    *      detect collision on all cars of the row;
    *      if any true, Game over!
    *      y range 290p - 430
    *      p
    **/

    if(frogSprite.getPosition().y > 290 && frogSprite.getPosition().y < 450) {
        //Detect Collision on road
        for (int i = 0; i < 4; ++i) {
            if( Collision::BoundingBoxTest(frogSprite, truckSprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, tractorSprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, car1Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, car2Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, car3Sprite[i]) )
            {
                gameOver = true;
                std::cout << "GAME OVER" << std::endl;
            }

        }
    }

    /*
     * Collision Dectection for road ends here!
     * */


    /*
 * While frog is on the river range:
 *      detect collision on all cars of the row;
 *      if any true, Game over!
 *      y range 290p - 430
 *      p
 **/

    if(frogSprite.getPosition().y > 73 && frogSprite.getPosition().y < 250) {
        //Detect Collision on road
        for (int i = 0; i < 4; ++i) {
            if( Collision::BoundingBoxTest(frogSprite, wood1Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, wood2Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, wood3Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, wood4Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, wood5Sprite[i]) ||
                Collision::BoundingBoxTest(frogSprite, wood6Sprite[i]) )
            {
                frogOnWood = true;
                gameOver = false;

            }
            else {
                gameOver = true;
                frogOnWood = false;

            }
        }
    }

    /*
     * Collision Dectection for river ends here!
     * */


    if(Collision::BoundingBoxTest(frogSprite, cuteFrogSprite)) {
        frogWin = true;
    }
}


void Game::moveFrog() {

    /*
   * This method is a helper method called in update() method to calculate the new positions of
   * the frog.
   * */

    sf::Vector2f movement(0, 0); //frog Movement

    if (mIsMovingUp)
        movement.y -= 20;
    else if (mIsMovingDown)
        movement.y += 20;
    else if (mIsMovingLeft)
        movement.x -= 15;
    else if (mIsMovingRight)
        movement.x += 15;



    if(frogSprite.getPosition().x > 420){
        frogSprite.setPosition(420, frogSprite.getPosition().y);
        movement.x = 0;
        movement.y = 0;
    }
    else if (frogSprite.getPosition().y > 450) {

        frogSprite.setPosition(frogSprite.getPosition().x, 450);
        movement.x = 0;
        movement.y = 0;

    }
    else if(frogSprite.getPosition().x < 0){
        frogSprite.setPosition(0, frogSprite.getPosition().y);
        movement.x = 0;
        movement.y = 0;
    }

    else if(frogSprite.getPosition().y < 73){
        frogSprite.setPosition(frogSprite.getPosition().x, 73);
        movement.x = 0;
        movement.y = 0;
    }

    frogSprite.move(movement);
}


void Game::moveVehicleAndWoods() {
    /*
     * This method is a helper method called in update() method to calculate the new positions of
     * the vehicles and wood logs.
     * */
    //Vehicle Sprite Movement
    sf::Vector2f leftMovement(-3, 0); //Speed = 3 pixel/computation-time to the left
    sf::Vector2f rightMovement(3, 0); // Speed = 3 to the right


    for (int i = 0; i < 4; ++i) {

        if(truckSprite[i].getPosition().x < -55) {
            truckSprite[i].setPosition(450, ROAD_ROW_1_HEIGHT);
        }
        truckSprite[i].move(leftMovement);

        car2Sprite[i].move(leftMovement);

        if(car2Sprite[i].getPosition().x < -55) {
            car2Sprite[i].setPosition(450, ROAD_ROW_3_HEIGHT);
        }

        car3Sprite[i].move(leftMovement);

        if(car3Sprite[i].getPosition().x < -55) {
            car3Sprite[i].setPosition(450, ROAD_ROW_5_HEIGHT);
        }

        tractorSprite[i].move(rightMovement);

        if(tractorSprite[i].getPosition().x > 450) {
            tractorSprite[i].setPosition(-10, ROAD_ROW_4_HEIGHT);
        }

        car1Sprite[i].move(rightMovement);

        if(car1Sprite[i].getPosition().x > 450) {
            car1Sprite[i].setPosition(-10, ROAD_ROW_2_HEIGHT);
        }

        wood1Sprite[i].move(rightMovement);

        if(wood1Sprite[i].getPosition().x > 450) {
            wood1Sprite[i].setPosition(-100, WOOD_ROW_1);
        }

        wood2Sprite[i].move(leftMovement);

        if(wood2Sprite[i].getPosition().x < -150) {
            wood2Sprite[i].setPosition(450, WOOD_ROW_2);
        }

        wood3Sprite[i].move(rightMovement);

        if(wood3Sprite[i].getPosition().x > 450) {
            wood3Sprite[i].setPosition(-100, WOOD_ROW_3);
        }

        wood4Sprite[i].move(rightMovement);

        if(wood4Sprite[i].getPosition().x > 450) {
            wood4Sprite[i].setPosition(-100, WOOD_ROW_4);
        }

        wood5Sprite[i].move(leftMovement);

        if(wood5Sprite[i].getPosition().x < -150) {
            wood5Sprite[i].setPosition(450, WOOD_ROW_5);
        }

        wood6Sprite[i].move(rightMovement);

        if(wood6Sprite[i].getPosition().x > 450) {
            wood6Sprite[i].setPosition(-100, WOOD_ROW_6);
        }
    }

    if(frogOnWood) {
        if(frogSprite.getPosition().y >= 230 && frogSprite.getPosition().y <= 240){
            frogSprite.move(rightMovement);
        }
        else if(frogSprite.getPosition().y >= 200 && frogSprite.getPosition().y < 230){
            frogSprite.move(leftMovement);
        }
        else if(frogSprite.getPosition().y >= 175 && frogSprite.getPosition().y < 200){
            frogSprite.move(rightMovement);
        }
        else if(frogSprite.getPosition().y >= 150 && frogSprite.getPosition().y < 175){
            frogSprite.move(rightMovement);
        }
        else if(frogSprite.getPosition().y >= 120 && frogSprite.getPosition().y < 150){
            frogSprite.move(leftMovement);
        }
        else if(frogSprite.getPosition().y >= 90 && frogSprite.getPosition().y < 120){
            frogSprite.move(rightMovement);
        }
    }
}

void Game::update() {

    //All logic goes in here
    //Get current position of frog
    //While frogger is within the road range: {
    //If position of frogger == position of any vehicle; Frog Dies (return True) else false and game continues }
    //While frogger is within the river range {
    //If position of frogger
    //Get new positions of all the vehicles which will be passed to render }



    detectCollision();
    moveFrog();
    moveVehicleAndWoods();

}



void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    /*
   * This method is a helper method called in processEvents() method to
   * look for the type of keyboard key pressed.
   * */

    if(key == sf::Keyboard::Up){
        mIsMovingUp = isPressed;
       score++;
    }
    else if (key == sf::Keyboard::Down) {
        mIsMovingDown = isPressed;
        score--;

    }
    else if (key == sf::Keyboard::Left) {
        mIsMovingLeft = isPressed;

    }
    else if (key == sf::Keyboard::Right) {
        mIsMovingRight = isPressed;

    }

    }


/*

void Game::welcomeScreen() {
   // sf::Color blueColor(0,0,55);
    mWindow.clear(sf::Color::Black);

    sf::Text text("Frogger",font,32);
    text.setColor(sf::Color::White);
    text.setPosition(300,300);
    mWindow.draw(text);
    mWindow.display();
    sf::Time t1 = sf::seconds(3.0f);
    sf::sleep(t1);
}

 */

