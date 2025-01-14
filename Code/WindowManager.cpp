//
//  WindowManager.cpp
//  ColorSynthesizer
//
//  Created by Akshay Subramaniam on 14/1/15.
//  Copyright (c) 2015 Incultus. All rights reserved.
//
#include "WindowManager.h"

//Sets the render window of the class to the main class.
WindowManager::WindowManager(sf::RenderWindow *window) : window(*window) {
    initializeValues();
}

//Initializes the text as well as the textures concerning the class.
void WindowManager::initializeValues() {
    // Set the Icon
    icon.loadFromFile(resourcePath() + "icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    buttonFont.loadFromFile(resourcePath() + "CL.ttf");
    
    colorText.setFont(buttonFont);
    fillText.setFont(buttonFont);
    eraseText.setFont(buttonFont);
    cursorText.setFont(buttonFont);
    backText.setFont(buttonFont);
    
    colorText.setString("Choose Color");
    fillText.setString("Fill Pixels");
    eraseText.setString("Erase Pixels");
    cursorText.setString("Cursor Size");
    backText.setString("Back");
    
    colorText.setCharacterSize(24);
    fillText.setCharacterSize(24);
    eraseText.setCharacterSize(24);
    cursorText.setCharacterSize(24);
    backText.setCharacterSize(16);
    
    colorText.setColor(sf::Color::Black);
    fillText.setColor(sf::Color::Black);
    eraseText.setColor(sf::Color::Black);
    cursorText.setColor(sf::Color::Black);
    backText.setColor(sf::Color::Black);
    
    pixelT.loadFromFile(resourcePath() + "pixel.png");
    pixelbT.loadFromFile(resourcePath() + "pixelborder.png");
    mainMenuT.loadFromFile(resourcePath() + "menuidle.png");
    buttonTN.loadFromFile(resourcePath() + "button.png");
    buttonTH.loadFromFile(resourcePath() + "buttonhighlighted.png");
    buttonTP.loadFromFile(resourcePath() + "buttonpressed.png");
    backTN.loadFromFile(resourcePath() + "back.png");
    backTH.loadFromFile(resourcePath() + "backhighlighted.png");
    backTP.loadFromFile(resourcePath() + "backpressed.png");
    
    setSprites();
}

//Creates the sprites.
void WindowManager::setSprites() {
    sf::Sprite mm(mainMenuT);
    sf::Sprite b1(buttonTN), b2(buttonTP), b3(buttonTN), b4(buttonTN), b5(backTN);
    
    mainMenu = mm;
    colorButton = b1;
    fillButton = b2;
    eraseButton = b3;
    cursorButton = b4;
    back = b5;
    
    //Fills the window below the UI bar with pixels, which are uniformly spaced.
    for (int x = 0; x < window.getSize().x; x += pixelT.getSize().x)
        for (int y = 128; y < window.getSize().y; y += pixelT.getSize().y)
        {
            sf::Sprite pixel(pixelT);
            sf::Sprite pixelBorder(pixelbT);
            pixel.setPosition(x, y);
            pixelBorder.setPosition(x, y);
            pixels.push_back(pixel);
            pixelBorders.push_back(pixelBorder);
            colors.push_back(sf::Color(255, 255, 255, 255));
            transparentPixels.push_back(false);
        }
    
    //Sets the position of the buttons on the UI bar.
    mainMenu.setPosition(0, 0);
    colorButton.setPosition(50, 25);
    fillButton.setPosition(325, 68);
    eraseButton.setPosition(325, 10);
    cursorButton.setPosition(600, 25);
    
    //Sets the position of the texts on the UI bar.
    colorText.setPosition(colorButton.getPosition().x + 3, colorButton.getPosition().y + 7.5);
    fillText.setPosition(fillButton.getPosition().x + 32.5, fillButton.getPosition().y + 7.5);
    eraseText.setPosition(eraseButton.getPosition().x + 18, eraseButton.getPosition().y + 7.5);
    cursorText.setPosition(cursorButton.getPosition().x + 20, cursorButton.getPosition().y + 7.5);
    backText.setPosition(back.getPosition().x + 10, backText.getPosition().y + 5);
    
    back.setPosition(2, 2);
}

//Checks if the fill pixels or erase pixels button is pressed.
void WindowManager::checkButtonPresssed(float x, float y) {
    //Creates placeholder sprites to set the button sprites to, such that the buttons change their textures/appearances.
    sf::Sprite bN(buttonTN);
    sf::Sprite bP(buttonTP);
    
    //Sets the placeholder sprites to the same position so that when copied, the buttons will appear in the same place.
    bN.setPosition(fillButton.getPosition());
    bP.setPosition(fillButton.getPosition());
    
    //If the fill pixels button is clicked.
    if (fillButton.getGlobalBounds().contains(x, y) && !filling) {
        //Sets the button the placeholder button, so that the fill button appears selected.
        fillButton = bP;
        //Sets the pixel mode to filling.
        filling = true;
        
        //Sets the erase button to its normal form, so that the erase button appears unselected.
        bN.setPosition(eraseButton.getPosition());
        eraseButton = bN;
    }
    
    //Inverse of the fill button.
    bN.setPosition(eraseButton.getPosition());
    bP.setPosition(eraseButton.getPosition());
    
    if (eraseButton.getGlobalBounds().contains(x, y) && filling) {
        eraseButton = bP;
        filling = false;
        
        bN.setPosition(fillButton.getPosition());
        fillButton = bN;
    }
}


//Checks if any of the buttons are moused over, so that they are highlighted.
void WindowManager::checkButtonHighlighted(float x, float y) {
    //Creates placeholder sprites for the buttons, so that the buttons can change their textures.
    sf::Sprite bN(buttonTN);
    sf::Sprite bH(buttonTH);
    sf::Sprite bP(buttonTP);
    
    sf::Sprite bN2(backTN);
    sf::Sprite bH2(backTH);
    
    bN.setPosition(colorButton.getPosition());
    bH.setPosition(colorButton.getPosition());
    
    //If the color button contains the mouse position, it sets the button to appear highlighted, else normal.
    if (colorButton.getGlobalBounds().contains(x, y))
        colorButton = bH;
    else
        colorButton = bN;
    
    bN.setPosition(fillButton.getPosition());
    bH.setPosition(fillButton.getPosition());
    bP.setPosition(fillButton.getPosition());
    
    //For the fill and erase button, if the buttons are NOT moused over, and the mode is fill or erase respectively, the buttons are set to appear selected.
    if (fillButton.getGlobalBounds().contains(x, y))
        fillButton = bH;
    else if (filling)
        fillButton = bP;
    else
        fillButton = bN;
    
    bN.setPosition(eraseButton.getPosition());
    bH.setPosition(eraseButton.getPosition());
    bP.setPosition(eraseButton.getPosition());
    
    if (eraseButton.getGlobalBounds().contains(x, y))
        eraseButton = bH;
    else if (!filling)
        eraseButton = bP;
    else
        eraseButton = bN;
    
    bN.setPosition(cursorButton.getPosition());
    bH.setPosition(cursorButton.getPosition());
    
    if (cursorButton.getGlobalBounds().contains(x, y))
        cursorButton = bH;
    else
        cursorButton = bN;
    
    bN2.setPosition(back.getPosition());
    bH2.setPosition(back.getPosition());
    
    if (back.getGlobalBounds().contains(x, y))
        back = bH2;
    else
        back = bN2;
}

bool WindowManager::getFilling() {
    return filling;
}