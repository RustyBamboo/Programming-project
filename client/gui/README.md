#Using GUI

##Declare a TextBox
```
#include "gui/textbox.hpp" //the path
...
gui::TextBox mytextbox(sf::Vector2f(postionx,postiony), sf::Vector2f(width, height), maxstringlength);

gui::TextBox mytextbox2(sf::Vector2f(postionx,postiony), sf::Vector2f(width, height), maxstringlength);
```

##Define a button
```
#include "gui/button.hpp"
...
gui::Button mybutton(sf::Vector2f(postionx,postiony), sf::Vector2f(width, height), "My Amazing Button");
```

##Define a form
```
#include "gui/form.hpp"
...
gui::Form myform;
myform.addTextBox(mytextbox);
myform.addTextBox(mytextbox2);
myform.setButton(mybutton); //There can only be one button in a form
```

##Now update the form in the Event loop
```
...
while (window.pollEvent(event)) {
...
if(form.update(event)) { //If button was clicked...
    std::vector<std::string> allTheFields = myform.process(); //0 = mytextbox, 1 = mytextbox2
}
...
```

##Make sure to draw
```
...
window.clear();
...
myform.draw(window);
...
window.display();
...
```
