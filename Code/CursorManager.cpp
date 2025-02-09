//
//  CursorManager.cpp
//  ColorSynthesizer
//
//  Created by Akshay Subramaniam on 15/1/15.
//  Copyright (c) 2015 Incultus. All rights reserved.
//

#include "CursorManager.h"

//Sets the render window of the main class, so that this one may reference it.
CursorManager::CursorManager(sf::RenderWindow *window) : window(*window) {
    initializeValues();
}

void CursorManager::initializeValues() {
    //Creates the textures, and texts.
    buttonFont.loadFromFile(resourcePath() + "CL.ttf");
    sizeText.setFont(buttonFont);
    sizeText.setString("Choose Cursor Size");
    sizeText.setCharacterSize(24);
    sizeText.setColor(sf::Color::Black);
    
    //Each texture variation of the five cursor sizes. Normal, highlighted, and pressed.
    button1PN.loadFromFile(resourcePath() + "onepixelbutton.png");
    button3P1N.loadFromFile(resourcePath() + "threepixelbutton1.png");
    button3P2N.loadFromFile(resourcePath() + "threepixelbutton2.png");
    button5PN.loadFromFile(resourcePath() + "fivepixelbutton.png");
    button9PN.loadFromFile(resourcePath() + "ninepixelbutton.png");
    
    button1PH.loadFromFile(resourcePath() + "onepixelbuttonhighlighted.png");
    button3P1H.loadFromFile(resourcePath() + "threepixelbutton1highlighted.png");
    button3P2H.loadFromFile(resourcePath() + "threepixelbutton2highlighted.png");
    button5PH.loadFromFile(resourcePath() + "fivepixelbuttonhighlighted.png");
    button9PH.loadFromFile(resourcePath() + "ninepixelbuttonhighlighted.png");
    
    button1PP.loadFromFile(resourcePath() + "onepixelbuttonpressed.png");
    button3P1P.loadFromFile(resourcePath() + "threepixelbutton1pressed.png");
    button3P2P.loadFromFile(resourcePath() + "threepixelbutton2pressed.png");
    button5PP.loadFromFile(resourcePath() + "fivepixelbuttonpressed.png");
    button9PP.loadFromFile(resourcePath() + "ninepixelbuttonpressed.png");
    
    setButtons();
}

//Creates the buttons of the cursor sizes.
void CursorManager::setButtons() {
    sf::Sprite b1p(button1PP), b3p1(button3P1N), b3p2(button3P2N), b5p(button5PN), b9p(button9PN);
    
    //Sets all cursor buttons except for the first to their normal appearance. Since the cursor size is initialized as one pixel, the first cursor button starts selected.
    button1P = b1p;
    button3P1 = b3p1;
    button3P2 = b3p2;
    button5P = b5p;
    button9P = b9p;
    
    //Sets the positions of the buttons so that they are spread out.
    button1P.setPosition(200, 50);
    button3P1.setPosition(300, 50);
    button3P2.setPosition(400, 50);
    button5P.setPosition(500, 50);
    button9P.setPosition(600, 50);
    
    sizeText.setPosition(325, 5);
}

//Similar to other managers, checks whether a button is moused over. Other managers have a more detailed explanation of this method.
void CursorManager::checkButtonHighlighted(float x, float y) {
    
    sf::Sprite b1N(button1PN);
    sf::Sprite b1H(button1PH);
    sf::Sprite b1P(button1PP);
    
    b1N.setPosition(button1P.getPosition());
    b1H.setPosition(button1P.getPosition());
    b1P.setPosition(button1P.getPosition());
    
    if (button1P.getGlobalBounds().contains(x, y))
        button1P = b1H;
    else if (size == 0)
        button1P = b1P;
    else
        button1P = b1N;
    
    sf::Sprite b3N1(button3P1N);
    sf::Sprite b3H1(button3P1H);
    sf::Sprite b3P1(button3P1P);
    
    b3N1.setPosition(button3P1.getPosition());
    b3H1.setPosition(button3P1.getPosition());
    b3P1.setPosition(button3P1.getPosition());
    
    if (button3P1.getGlobalBounds().contains(x, y))
        button3P1 = b3H1;
    else if (size == 1)
        button3P1 = b3P1;
    else
        button3P1 = b3N1;
    
    sf::Sprite b3N2(button3P2N);
    sf::Sprite b3H2(button3P2H);
    sf::Sprite b3P2(button3P2P);
    
    b3N2.setPosition(button3P2.getPosition());
    b3H2.setPosition(button3P2.getPosition());
    b3P2.setPosition(button3P2.getPosition());
    
    if (button3P2.getGlobalBounds().contains(x, y))
        button3P2 = b3H2;
    else if (size == 2)
        button3P2 = b3P2;
    else
        button3P2 = b3N2;
    
    sf::Sprite b5N(button5PN);
    sf::Sprite b5H(button5PH);
    sf::Sprite b5P(button5PP);
    
    b5N.setPosition(button5P.getPosition());
    b5H.setPosition(button5P.getPosition());
    b5P.setPosition(button5P.getPosition());
    
    if (button5P.getGlobalBounds().contains(x, y))
        button5P = b5H;
    else if (size == 3)
        button5P = b5P;
    else
        button5P = b5N;
    
    sf::Sprite b9N(button9PN);
    sf::Sprite b9H(button9PH);
    sf::Sprite b9P(button9PP);
    
    b9N.setPosition(button9P.getPosition());
    b9H.setPosition(button9P.getPosition());
    b9P.setPosition(button9P.getPosition());
    
    if (button9P.getGlobalBounds().contains(x, y))
        button9P = b9H;
    else if (size == 4)
        button9P = b9P;
    else
        button9P = b9N;
}


//Similar to highlighted method.
void CursorManager::checkButtonPresssed(float x, float y) {
    
    sf::Sprite b1P(button1PP);
    sf::Sprite b3P1(button3P1P);
    sf::Sprite b3P2(button3P2P);
    sf::Sprite b5P(button5PP);
    sf::Sprite b9P(button9PP);
    
    b1P.setPosition(button1P.getPosition());
    b3P1.setPosition(button3P1.getPosition());
    b3P2.setPosition(button3P2.getPosition());
    b5P.setPosition(button5P.getPosition());
    b9P.setPosition(button9P.getPosition());
    
    if (button1P.getGlobalBounds().contains(x, y)) {
        button1P = b1P;
        resetCursors(0);
    }
    
    if (button3P1.getGlobalBounds().contains(x, y)) {
        button3P1 = b3P1;
        resetCursors(1);
    }
    
    if (button3P2.getGlobalBounds().contains(x, y)) {
        button3P2 = b3P2;
        resetCursors(2);
    }
    
    if (button5P.getGlobalBounds().contains(x, y)) {
        button5P = b5P;
        resetCursors(3);
    }
    
    
    if (button9P.getGlobalBounds().contains(x, y)) {
        button9P = b9P;
        resetCursors(4);
    }
}

//Sets the old cursor button to be unselected and adjusts the new size.
void CursorManager::resetCursors(int newSize) {
    //Creates the normal version of the button sprites.
    sf::Sprite b1N(button1PN);
    sf::Sprite b3N1(button3P1N);
    sf::Sprite b3N2(button3P2N);
    sf::Sprite b5N(button5PN);
    sf::Sprite b9N(button9PN);
    
    b1N.setPosition(button1P.getPosition());
    b3N1.setPosition(button3P1.getPosition());
    b3N2.setPosition(button3P2.getPosition());
    b5N.setPosition(button5P.getPosition());
    b9N.setPosition(button9P.getPosition());
    
    //If the same cursor button is selected, the method returns.
    if (size == newSize)
        return;
    
    //Sets the old cursor button to the normal texture, and sets the current cursor size to the new one.
    switch (size) {
        case 0:
            button1P = b1N;
            size = newSize;
            return;
        case 1:
            button3P1 = b3N1;
            size = newSize;
            return;
        case 2:
            button3P2 = b3N2;
            size = newSize;
            return;
        case 3:
            button5P = b5N;
            size = newSize;
            return;
        case 4:
            button9P = b9N;
            size = newSize;
            return;
    }
}

int CursorManager::getSize() {
    return size;
}


