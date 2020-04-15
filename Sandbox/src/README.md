# README for Road Rash!

## Structure

The basic structure is as follows:
 * Sandbox.cpp is the entry point to the application.
 * It has a GameLayer which is in-charge of keeping track of the game status and UI. GameLayer has a GameLevel object in it which is the actual game logic.
 * The GameLevel class has all the game objects (classes derived from GameObject) and uses them to decide how each game object is to be updated.
 * The GameObject implementations also have their own OnUpdate which allows them to update their parameters over time. This can be considered as the free state behavior when no other objects interact with it.
 * Every object also has an OnRender which determines how the object should be displayed onto the screen.

## Conventions

The game is to be implemented using Ancora's capabilities in the background. There are a few comments placed in files in Sandbox folder and they follow a convention. Apart from the regular comments which explain the piece of code, a comment starting with:
 * (#) indicates the following piece of code has to be implemented by you guys and contributes to core game logic.
 * ($) gives a slight direction in which the code should proceed.
 * (*) indicates the following piece of code should be implemented by me and is an extension of engine side of the code.
 * (^) indicates the functionality of the following piece of code can be changed in the future, after discussion.

Some naming conventions:
 * Member variables of classes start with ```m_``` followed by the name in CamelCase. Example: ```m_SomeName```
 * Static variables start with ```s_``` followed by the name in CamelCase. Example: ```s_SomeName```
 * Local variables are in camelCase. Example: ```someName```
 * Functions, classes, structs, and variables in structs are in CamelCase. Example: ```SomeName```

Please try to follow the above conventions for comments and naming.

## Compiling

The application, in its present state, will not compile successfully. The list of things to be added in the engine for the game to compile successfully is given below:
 * Renderer3D
     - Single Shader Rendering

_* This file will be updated every time a feature is implemented in the engine._
