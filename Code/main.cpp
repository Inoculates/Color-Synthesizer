#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "WindowManager.h"
#include "ColorManager.h"
#include "CursorManager.h"

//This class handles all mouse events, as well as the drawing of all sprites.
class ColorSynthesizer {
private:
    //Window that draws the sprites.
    sf::RenderWindow &window;
    //These variables are used to ensure that if the color slider must be used by first clicking, then dragging the slider. Similarly, coloring must be inititated by clicking on a pixel.
    bool coloring = false, sliding = false;
    //This integer tells the class which objects to draw
    int state = 0;
public:
    //Handles pixels and their assorted colors.
    WindowManager wManager;
    //Handles the coloration of pixels.
    ColorManager cManager;
    //Handles the size of the cursor.
    CursorManager sManager;
    
    //Gives the window pointer to each of the managers, so that they may reference the render window used.
    ColorSynthesizer(sf::RenderWindow *window) : window(*window), wManager(window), cManager(window), sManager(window) {}
    
    void setState(int state) {
        this->state = state;
    }
    
    //This initiates events based on whether a button contains the mouse location when a click is a registered.
    void detectEvent(float x, float y) {
        if (wManager.back.getGlobalBounds().contains(x, y) && state != 0)
            setState(0);
        else if (wManager.colorButton.getGlobalBounds().contains(x, y) && state == 0)
            setState(1);
        else if (wManager.cursorButton.getGlobalBounds().contains(x, y) && state == 0)
            setState(2);
        else if (state == 0)
            wManager.checkButtonPresssed(x, y);
        else if (state == 2)
            sManager.checkButtonPresssed(x, y);
        
        //Checks if the user has clicked on a pixel.
        coloring = true;
        handlePixelEvents(x, y);
        
        if (state == 1) {
            //Checks if the user has clicked on the color slider, assuming the menu is in the color state.
            sliding = true;
            handleSliderEvents(x, y);
        }
    }
    
    //Checks if the user is holding his or her mouse down on the pixel board or on the slider.
    void handleEvents(float x, float y) {
        handlePixelEvents(x, y);
        handleSliderEvents(x, y);
    }
    
    //Sets the color of a pixel if clicked.
    void handlePixelEvents(float x, float y) {
        //If the user has not clicked on the pixel board before mousing over it, nothing will register.
        if (!coloring)
            return;
        
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixels.begin(); iterator != wManager.pixels.end(); ++iterator) {
            //Obtains the position of the pixel in the vector, which is used in the cursor methods.
            int position = std::distance(wManager.pixels.begin(), iterator);
            sf::Color *pColor = &wManager.colors.at(std::distance(wManager.pixels.begin(), iterator));
            if (iterator->getGlobalBounds().contains(x, y)) {
                //If the mode is set to fill, not erase.
                if (wManager.getFilling()) {
                    int position = std::distance(wManager.pixels.begin(), iterator);
                    //Sets pColor to all the values of the current color selected except the alpha.
                    pColor->r = cManager.pixelColor.r;
                    pColor->g = cManager.pixelColor.g;
                    pColor->b = cManager.pixelColor.b;
                    //Automatically sets the alpha to full, in case the pixel is erased.
                    pColor->a = 255;
                    //Sets the colors of the pixels in the cursor to the current color.
                    setPixelColors(position, pColor);
                }
                //If the mode is set to erase
                else {
                    //Sets the alphas of the pixels in the cursor to zero.
                    pColor->a = 0;
                    setPixelColors(position, pColor);
                }
                //Since a pixel contains the mouse position, coloring is set to true, which allows the user to color pixels by simply moving the mouse over pixels as the left mouse button is held.
                coloring = true;
                return;
            }
        }
        //Since no pixel contains the mouse position, coloring is set to false.
        coloring = false;
    }
    
    //Similar to the pixel events, handles the slider events.
    void handleSliderEvents(float x, float y) {
        //Similarly to the pixel events, determines if the user has first clicked on the slider.
        if (!sliding) return;
        
        //If the red color slider contains the mouse position.
        if (cManager.colorSliderR.getGlobalBounds().contains(x, y) && x > cManager.colorSliderR.getPosition().x) {
            cManager.adjustColor(0, x);
            sliding = true;
            return;
        }
        
        //If the blue slider contains the mouse position.
        if (cManager.colorSliderB.getGlobalBounds().contains(x, y) && x > cManager.colorSliderB.getPosition().x) {
            cManager.adjustColor(1, x);
            sliding = true;
            return;
        }
        
        //If the green slider contains the mouse position.
        if (cManager.colorSliderG.getGlobalBounds().contains(x, y) && x > cManager.colorSliderG.getPosition().x) {
            cManager.adjustColor(2, x);
            sliding = true;
            return;
        }
        sliding = false;
    }
    
    //Depending on the state, checks is a button is being moused over, and highlights it if it is.
    void checkButtons(float x, float y) {
        wManager.checkButtonHighlighted(x, y);
        if (state == 2)
            sManager.checkButtonHighlighted(x, y);
    }
    
    //Draws all the objects pertinent to the program, depending on the state.
    void drawObjects() {
        window.draw(wManager.mainMenu);
        switch (state) {
            case 0:
                window.draw(wManager.colorButton);
                window.draw(wManager.fillButton);
                window.draw(wManager.eraseButton);
                window.draw(wManager.cursorButton);
                
                window.draw(wManager.colorText);
                window.draw(wManager.fillText);
                window.draw(wManager.eraseText);
                window.draw(wManager.cursorText);
                break;
            case 1:
                window.draw(cManager.colorSliderR);
                window.draw(cManager.colorSliderB);
                window.draw(cManager.colorSliderG);
                
                window.draw(cManager.redAmount);
                window.draw(cManager.blueAmount);
                window.draw(cManager.greenAmount);
                
                window.draw(cManager.currentColor);
                window.draw(cManager.currentColorBorder);
                window.draw(wManager.back);
                window.draw(wManager.backText);
                
                for (std::vector<sf::Sprite>::iterator iterator = cManager.slitsR.begin(); iterator != cManager.slitsR.end(); ++iterator)
                    window.draw(*iterator);
                
                for (std::vector<sf::Sprite>::iterator iterator = cManager.slitsB.begin(); iterator != cManager.slitsB.end(); ++iterator)
                    window.draw(*iterator);
                
                for (std::vector<sf::Sprite>::iterator iterator = cManager.slitsG.begin(); iterator != cManager.slitsG.end(); ++iterator)
                    window.draw(*iterator);
                
                window.draw(cManager.colorKnobR);
                window.draw(cManager.colorKnobB);
                window.draw(cManager.colorKnobG);
                break;
            case 2:
                window.draw(wManager.back);
                window.draw(wManager.backText);
                window.draw(sManager.button1P);
                window.draw(sManager.button3P1);
                window.draw(sManager.button3P2);
                window.draw(sManager.button5P);
                window.draw(sManager.button9P);
                window.draw(sManager.sizeText);
                break;
        }
        drawPixels();
        drawPixelBorders();
    }
    
    //Using the vectors that hold all the pixels and pixel borders, the class draws all the pixels.
    void drawPixels() {
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixels.begin(); iterator != wManager.pixels.end(); ++iterator) {
            sf::Color *pColor = &wManager.colors.at(std::distance(wManager.pixels.begin(), iterator));
            //Sets the alpha value of the pixel depending on whether it is erased or not.
            if (wManager.transparentPixels.at(std::distance(wManager.pixels.begin(), iterator)))
                pColor->a = 0;
            else
                pColor->a = 255;
            iterator->setColor(*pColor);
        }
        
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixels.begin(); iterator != wManager.pixels.end(); ++iterator) {
            int position = std::distance(wManager.pixels.begin(), iterator);
            
            if (iterator->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                setPixelAlphas(position);
        }
        
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixels.begin(); iterator != wManager.pixels.end(); ++iterator)
            window.draw(*iterator);
    }
    
    //Same idea as the pixels.
    void drawPixelBorders() {
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixelBorders.begin(); iterator != wManager.pixelBorders.end(); ++iterator) {
            sf::Color *pColor = &wManager.colors.at(std::distance(wManager.pixelBorders.begin(), iterator));
            if (wManager.transparentPixels.at(std::distance(wManager.pixelBorders.begin(), iterator)))
                pColor->a = 0;
            else
                pColor->a = 255;
            iterator->setColor(*pColor);
        }
        
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixelBorders.begin(); iterator != wManager.pixelBorders.end(); ++iterator) {
            int position = std::distance(wManager.pixelBorders.begin(), iterator);
            
            if (iterator->getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                setPixelBorderAlphas(position);
        }
        
        for (std::vector<sf::Sprite>::iterator iterator = wManager.pixelBorders.begin(); iterator != wManager.pixelBorders.end(); ++iterator)
            window.draw(*iterator);
        
    }
    
    //Sets the alpha of the pixels in the area of the cursor. This method is used when the user hovers over pixels on the pixel board.
    void setPixelAlphas(int position) {
        switch (sManager.getSize()) {
            case 0:
                //Sets the alpha of the one selected pixel.
                setAlphaPixel(position);
                break;
            case 1:
                //Sets the alphas of the pixels in a three-pixel row fashion.
                setAlphaPixel(position);
                setAlphaPixel(position + 32);
                setAlphaPixel(position - 32);
                break;
            case 2:
                //Sets the alphas of the pixels in a three-pixel column fashion.
                setAlphaPixel(position);
                setAlphaPixel(position + 1);
                setAlphaPixel(position - 1);
                break;
            case 3:
                //Sets the alphas of the pixels in a five-pixel T fashion.
                setAlphaPixel(position);
                setAlphaPixel(position + 1);
                setAlphaPixel(position - 1);
                setAlphaPixel(position + 32);
                setAlphaPixel(position - 32);
                break;
            case 4:
                //Sets the alphas of the pixels in a nine-pixel square fashion.
                setAlphaPixel(position);
                setAlphaPixel(position + 1);
                setAlphaPixel(position - 1);
                setAlphaPixel(position + 31);
                setAlphaPixel(position - 31);
                setAlphaPixel(position + 32);
                setAlphaPixel(position - 32);
                setAlphaPixel(position + 33);
                setAlphaPixel(position - 33);
                return;
        }
    }
    
    //Largely the same as the pixels.
    void setPixelBorderAlphas(int position) {
        switch (sManager.getSize()) {
            case 0:
                setAlphaPixelBorder(position);
                break;
            case 1:
                setAlphaPixelBorder(position);
                setAlphaPixelBorder(position + 32);
                setAlphaPixelBorder(position - 32);
                break;
            case 2:
                setAlphaPixelBorder(position);
                setAlphaPixelBorder(position + 1);
                setAlphaPixelBorder(position - 1);
                break;
            case 3:
                setAlphaPixelBorder(position);
                setAlphaPixelBorder(position + 1);
                setAlphaPixelBorder(position - 1);
                setAlphaPixelBorder(position + 32);
                setAlphaPixelBorder(position - 32);
                break;
            case 4:
                setAlphaPixelBorder(position);
                setAlphaPixelBorder(position + 1);
                setAlphaPixelBorder(position - 1);
                setAlphaPixelBorder(position + 31);
                setAlphaPixelBorder(position - 31);
                setAlphaPixelBorder(position + 32);
                setAlphaPixelBorder(position - 32);
                setAlphaPixelBorder(position + 33);
                setAlphaPixelBorder(position - 33);
                break;
        }
    }
    
    //Sets the color of the pixels in the area of the cursor. This method is used when the user clicks or holds the mouse button down over pixels on the pixel board.
    void setPixelColors(int position, sf::Color *color) {
        switch (sManager.getSize()) {
            case 0:
                //Sets the color of the one selected pixel.
                setPixelColor(position, color);
                break;
            case 1:
                //Sets the colors of the pixels in a three-pixel row fashion.
                setPixelColor(position, color);
                setPixelColor(position + 32, color);
                setPixelColor(position - 32, color);
                break;
            case 2:
                //Sets the colors of the pixels in a three-pixel column fashion.
                setPixelColor(position, color);
                setPixelColor(position + 1, color);
                setPixelColor(position - 1, color);
                break;
            case 3:
                //Sets the colors of the pixels in a five-pixel T fashion.
                setPixelColor(position, color);
                setPixelColor(position + 1, color);
                setPixelColor(position - 1, color);
                setPixelColor(position + 32, color);
                setPixelColor(position - 32, color);
                break;
            case 4:
                //Sets the colors of the pixels in a nine-pixel square fashion.
                setPixelColor(position, color);
                setPixelColor(position + 1, color);
                setPixelColor(position - 1, color);
                setPixelColor(position + 31, color);
                setPixelColor(position - 31, color);
                setPixelColor(position + 32, color);
                setPixelColor(position - 32, color);
                setPixelColor(position + 33, color);
                setPixelColor(position - 33, color);
                break;
        }
    }
    
    //Using the index of the pixel, sets the alpha of the pixels in the area of the cursor.
    void setAlphaPixel(int position) {
        sf::Color color;
        try {
            color = sf::Color::Black;
            color.a = 127.5f;
            wManager.pixels.at(position).setColor(color);
        }
        catch (...) {
            //Do nothing
        }
    }
    
    //Same as the pixel method.
    void setAlphaPixelBorder(int position) {
        sf::Color color;
        try {
            color = sf::Color::Black;
            color.a = 127.5f;
            wManager.pixelBorders.at(position).setColor(color);
        }
        catch (...) {
            //Do nothing
        }
    }
    
    //Using the index of the pixel, sets the color of the pixels in the area of the cursor.
    void setPixelColor(int position, sf::Color *color) {
        try {
            if (color->a == 255)
                wManager.transparentPixels.at(position) = false;
            else
                wManager.transparentPixels.at(position) = true;
            
            wManager.colors.at(position) = *color;
        }
        catch (...) {
            //Do nothing
        }
    }
};

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 640), "Color Synthesizer", sf::Style::Close);
    ColorSynthesizer synthesizer(window);
    
    // Start the game loop
    while (window->isOpen())
    {
        // Process events
        sf::Event event;
        while (window->pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                synthesizer.detectEvent(event.mouseButton.x, event.mouseButton.y);
            
            if (event.type == sf::Event::MouseMoved)
                synthesizer.checkButtons(event.mouseMove.x, event.mouseMove.y);
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
        }
        
        //Conveys the mouse click to the ColorSynthesizer
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            synthesizer.handleEvents(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
        
        // Clear screen
        window->clear(sf::Color::White);
        
        // Draw the sprites
        synthesizer.drawObjects();
        
        // Update the window
        window->display();
    }
    
    //Deletes the render window memory from the heap and exits the window.
    delete window;
    return EXIT_SUCCESS;
}
