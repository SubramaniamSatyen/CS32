#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//Incomplete Class Declarations
class Actor;
class Peach;

//Student World class definition as defined in spec. Goal of class is to create the world for all of the game's actors to 
//exist. In charge of managing actor interactions, transitioning, playing sounds, etc (as per spec).
class StudentWorld : public GameWorld
{
public:
	//Student World Constructor as provided. Initializes the variables indicating completed level and completed game to false.
	StudentWorld(std::string assetPath);
	//Init function as required by spec. Initializes any variables not initialized by constructor or other functions. 
	//Allocates a Peach object and inserts all other game actors into the game world
	virtual int init();
	//Move function as required by the spec. Function is called for each iteration of the game to update the screen. First prompts all
	//actors to doSomething(). If peach has died, then play the death sound and return that the player has died. If peach has finished the level
	//or won, return the relevant status. Delete any actors that are dead. Then render the game text at the top of the screen. If successful return status.
	virtual int move();
	//CleanUp function as required by the spec. Deletes all the active members to prevent memory leaks.
	virtual void cleanUp();
	//For provided coordinates and a pointer to an actor to ignore, considers whether there is a physical actor at that position
	Actor* getActorAt(int X, int Y, Actor* curr);
	//For given coordinates, an actor to ignore, as well as whether to consider if the actor is physical, is peach,
	//or is damageable, returns a pointer to an actor present at that position or the nullptr if no actor is present.
	Actor* getActorAt(int X, int Y, Actor* curr, bool considerPhysical, bool peachAllowed, bool damageable);
	//Adds parameter actor to the end of the actor list
	bool addActor(Actor* actor);
	//Returns whether the parameter coordinates overlap with Peach
	bool checkPeach(int X, int Y);
	//Returns pointer to the current peach actor.
	Peach* getPeach();
	//Informs the StudentWorld that the level was completed
	bool setNextLevel();
	//Informs the StudentWorld that the game was won
	bool wonGame();
	//Helper function to load the specified level and return whether the loading was successful
	bool loadLevel(std::string s);
	//Student World destructor. Destroys all dynamically allocated actors by calling the cleanUp function.
	~StudentWorld();
private:
	//Updates the status of the text at the top of the screen by looking at the lives of the player, the score of the player, and the status of peach.
	bool updateStatus();
	std::list<Actor*> m_actors;
	Peach* m_peach;
	bool m_levelFinished;
	bool m_won;
};

#endif // STUDENTWORLD_H_
