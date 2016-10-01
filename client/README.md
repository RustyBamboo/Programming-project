#How do I do stuff?

##Installing SFML

###If you have Ubuntu/Debian installed... in terminal type
```
sudo apt-get install libsfml-dev
```

###If you have Mac OSX
Make sure XCode is installed.
Open up terminal and install commandline developer tools:
```
xcode-select --install
```

Now install homebrew
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

After that's done:
```
brew update
brew install sfml
```
Install CMake:
```
brew install cmake
```
Install git:
```
brew install git
```
###If you have Windows
RIP. Visual Studio is a pain. Probably do-able. Look at the tutorials on SFML. And then install CMake and stuff.
Or just get Ubuntu.

##After installing SFML (this is for Ubuntu and Mac OSX)
Create a project directory. In terminal:
```
mkdir COP3503
cd COP3503
mkdir build
```

Clone the git respository. In terminal:
```
git clone https://github.com/RustyBamboo/Programming-project.git
```
Linking/Building/Running (assuming in the COP3503 directory):
```
cd build
cmake ../Programming-project
make
./client/game
```
