//
//  CursorManager.h
//  ColorSynthesizer
//
//  Created by Akshay Subramaniam on 15/1/15.
//  Copyright (c) 2015 Incultus. All rights reserved.
//

#ifndef __ColorSynthesizer__CursorManager__
#define __ColorSynthesizer__CursorManager__

#include <SFML/Audio.hpp>
#include <SFMl/Graphics.hpp>
#include "ResourcePath.hpp"

class CursorManager {
private:
    //The integer that determines the cursor size.
    int size = 0;
    sf::RenderWindow &window;
    sf::Texture button1PN, button3P1N, button3P2N, button5PN, button9PN;
    sf::Texture button1PH, button3P1H, button3P2H, button5PH, button9PH;
    sf::Texture button1PP, button3P1P, button3P2P, button5PP, button9PP;
    sf::Font buttonFont;
    
    void resetCursors(int newSize);
public:
    //The sprites of the cursor buttons.
    sf::Sprite button1P, button3P1, button3P2, button5P, button9P;
    //The only text in the cursor UI.
    sf::Text sizeText;
    
    CursorManager(sf::RenderWindow *window);
    void initializeValues();
    void setButtons();
    void checkButtonPresssed(float x, float y);
    void checkButtonHighlighted(float x, float y);
    int getSize();
};

#endif /* defined(__ColorSynthesizer__CursorManager__) */
