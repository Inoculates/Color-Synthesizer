//
//  ColorManager.cpp
//  ColorSynthesizer
//
//  Created by Akshay Subramaniam on 14/1/15.
//  Copyright (c) 2015 Incultus. All rights reserved.
//

#include "ColorManager.h"

//Acquires the renderwindow of the main class.
ColorManager::ColorManager(sf::RenderWindow *window) : window(*window) {
    createUI();
    createText();
}

//Creates the sprites and textures concerning the color UI.
void ColorManager::createUI() {
    //Creates the textures for the sprites.
    colorSliderT.loadFromFile(resourcePath() + "colorslider.png");
    currentColorT.loadFromFile(resourcePath() + "currentcolor.png");
    currentColorB.loadFromFile(resourcePath() + "currentcolorborder.png");
    pixelSlitT.loadFromFile(resourcePath() + "pixelslit.png");
    colorKnobT.loadFromFile(resourcePath() + "knob.png");
    
    //Creates the temporary sprites, which are used to set the sprites displayed.
    sf::Sprite cSlider(colorSliderT);
    sf::Sprite cKnob(colorKnobT);
    sf::Sprite cColor(currentColorT);
    sf::Sprite cColorB(currentColorB);
    
    colorSliderR = cSlider;
    colorSliderB = cSlider;
    colorSliderG = cSlider;
    
    colorKnobR = cKnob;
    colorKnobB = cKnob;
    colorKnobG = cKnob;
    
    currentColor = cColor;
    currentColorBorder = cColorB;
    
    //Sets the positions of the slider borders.
    colorSliderR.setPosition(290, 25);
    colorSliderB.setPosition(290, 50);
    colorSliderG.setPosition(290, 75);
    
    //Sets the position of the current color indicator.
    currentColor.setPosition(198, 25);
    currentColorBorder.setPosition(198, 25);
    
    //Creates the color slits that comprise the slider, from zero to 255.
    for (int i = 0; i < 255; i ++) {
        sf::Sprite slit(pixelSlitT);
        slit.setPosition(colorSliderR.getPosition().x + i + 1, colorSliderR.getPosition().y + 1);
        slit.setColor(sf::Color(i, 0, 0, 255));
        slitsR.push_back(slit);
    }
    
    for (int i = 0; i < 255; i ++) {
        sf::Sprite slit(pixelSlitT);
        slit.setPosition(colorSliderB.getPosition().x + i + 1, colorSliderB.getPosition().y + 1);
        slit.setColor(sf::Color(0, 0, i, 255));
        slitsB.push_back(slit);
    }
    
    for (int i = 0; i < 255; i ++) {
        sf::Sprite slit(pixelSlitT);
        slit.setPosition(colorSliderG.getPosition().x + i + 1, colorSliderG.getPosition().y + 1);
        slit.setColor(sf::Color(0, i, 0, 255));
        slitsG.push_back(slit);
    }
    
    //Sets the position of the knobs of the sliders. Note each color is subtracted by one to prevent the vector from trying to access position 255, which is above the maximum length.
    colorKnobR.setPosition(slitsR.at(red - 1).getPosition().x - 2, colorSliderR.getPosition().y + 1);
    colorKnobB.setPosition(slitsB.at(blue - 1).getPosition().x - 2, colorSliderB.getPosition().y + 1);
    colorKnobG.setPosition(slitsG.at(green - 1).getPosition().x - 2, colorSliderG.getPosition().y + 1);
}

//Creates the text by setting the font, string, color, and size of each font.
void ColorManager::createText() {
    colorFont.loadFromFile(resourcePath() + "CL.ttf");
    
    redAmount.setFont(colorFont);
    blueAmount.setFont(colorFont);
    greenAmount.setFont(colorFont);
    
    redAmount.setString(std::to_string(red));
    blueAmount.setString(std::to_string(blue));
    greenAmount.setString(std::to_string(green));
    
    redAmount.setCharacterSize(20);
    blueAmount.setCharacterSize(20);
    greenAmount.setCharacterSize(20);
    
    redAmount.setColor(sf::Color::Black);
    blueAmount.setColor(sf::Color::Black);
    greenAmount.setColor(sf::Color::Black);
    
    redAmount.setPosition(colorSliderR.getPosition().x + 265, colorSliderR.getPosition().y - 7);
    blueAmount.setPosition(colorSliderB.getPosition().x + 265, colorSliderB.getPosition().y - 7);
    greenAmount.setPosition(colorSliderG.getPosition().x + 265, colorSliderG.getPosition().y - 7);
}

//Sets the current color depending on the distance between the slider end and the mouse position.
void ColorManager::adjustColor(int color, float position) {
    switch (color) {
        case 0:
            red = 255 - (colorSliderR.getPosition().x + 256 - position);
            redAmount.setString(std::to_string(red));
            break;
        case 1:
            blue = 255 - (colorSliderB.getPosition().x + 256 - position);
            blueAmount.setString(std::to_string(blue));
            break;
        case 2:
            green = 255 - (colorSliderG.getPosition().x + 256 - position);
            greenAmount.setString(std::to_string(green));
            break;
    }
    pixelColor = sf::Color(red, green, blue);
    currentColor.setColor(pixelColor);
    
    //The use of redF, blueF, and greenF ensures that the value does not go out of bounds, by preventing the values from going above 254 or below zero.
    float redF, blueF, greenF;
    
    if (red > 0)
        redF = red - 1;
    else redF = 0;
    
    if (blue > 0)
        blueF = blue - 1;
    else blueF = 0;
    
    if (green > 0)
        greenF = green - 1;
    else greenF = 0;
    
    colorKnobR.setPosition(slitsR.at(redF).getPosition().x - 2, colorSliderR.getPosition().y + 1);
    colorKnobB.setPosition(slitsB.at(blueF).getPosition().x - 2, colorSliderB.getPosition().y + 1);
    colorKnobG.setPosition(slitsG.at(greenF).getPosition().x - 2, colorSliderG.getPosition().y + 1);
}