#How do I do stuff?

##Installing SFML

###If you have Ubuntu/Debian installed... in terminal type
```
sudo apt-get install libsfml-dev
```

###If you have Mac OSX, open up terminal and install homebrew
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

After that's done:
```
brew update
brew install sfml
```
###If you have Windows
RIP. Visual Studio is a pain. Probably do-able. Look at the tutorials on SFML. And then install CMake and stuff.
Or just get Ubuntu.

##After installing SFML (this is for Ubuntu and Mac OSX)

Clown the git respository. In terminal:
```
git clone https://github.com/RustyBamboo/Programming-project.git
cd Programming-project/client/build
```
Linking/Building/Running (assuming in the build directory):
```
cmake ..
make
./game
```