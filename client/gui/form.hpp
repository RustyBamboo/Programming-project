#ifndef GUI_FORM_HPP
#define GUI_FORM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "textbox.hpp"
#include "button.hpp"

//Stores all texboxs and a submit button and processes input
namespace gui {
    class Form {
    private:
        std::vector<gui::TextBox*> textboxes;
        gui::Button *button;
    public:
        Form();
        void draw(sf::RenderWindow &window);
        bool update(sf::Event &event);
        void addTextBox(gui::TextBox &textbox);
        void setButton(gui::Button &b);
        void noSelect();
        std::vector<std::string> process();
    };
}

#endif