#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
	////Actor constructor with default values for start direction, size, depth, whether the actor is damageable, physical, or alive. Initializes these values
	//Into the base class of the GraphObject or into the member variables.
	Actor(int imageID, double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1.0, int depth = 0, bool damageable = true, bool physical = true, bool alive = true);
	//Actor pure virtual function doSomething() which is called during each tick of the game.
	virtual void doSomething() = 0;
	//Returns whether the Actor is alive
	bool getStatus();
	//Returns whether the Actor is physical (can block other actors)
	bool getPhysical();
	//Sets the Actor's status to the provided parameter (true or false representing alive or terminated)
	void setStatus(bool status);
	//Virtual function returning whether the Actor is Peach (since peach is so important I have specific function to identify it). Function returns false.
	virtual bool isPeach();
	//Virtual bonk function that returns whether the bonk carried out the relevant activity. In this case returns true.
	virtual bool bonk();
	//Function accepts a pair of coordinates, a pointer to an actor to ignore, as well as whether to search for physical actors, whether to consider peach,
	//and whether to consider if the actor is damageable. This function can be used to check for overlap in derived classes (note that it checks all four corners of sprite,
	//so may be overkill depending on use) and returns a pointer to the overlapping actor.
	Actor* overlaps(int X, int Y, Actor* curr, bool considerPhysical = true, bool peachAllowed = true, bool damageable = false);
	//A lighter weight function than overlaps that confirms whether the current Actor overlaps with Peach, returning true or false.
	bool overlapsPeach(int X, int Y);
	//Returns whether the actor is damageable
	bool isDamageable();
	//Virtual function that damages the actor. In this case damaging the actor does not do anything.
	virtual bool Damage();
	//Function that returns pointer to the world that the Actors live in.
	StudentWorld* getWorld();
private:
	//Pointer to student world that is initalized when actor is instantiated. Should always be pointer to StudentWorld object.
	StudentWorld* m_studentWorld;
	//Boolean variables to indicate the qualities of the actor. By default the actor is physical, damagable, and alive.
	bool m_alive;
	bool m_physical;
	bool m_damageable; 
};

class Block : public Actor
{
public:
	//Constructor for the block class that accepts sprite location, the world, the goodie the block contains (if it contains one), as well as the default start direction, size, and depth.
	//The constructor initializes the block as alive and with the default block image.
	Block(double startX, double startY, StudentWorld* world, char goodie = 'n', int startDirection = 0, double size = 1.0, int depth = 2, int image = IID_BLOCK);
	//Implementation of Actor doSomething virtual function. This checks if there is a goodie and releases it. Otherwise, the function will play the bonk sound effect.
	virtual void doSomething();
	//Returns the goodie the block contains
	char getGoodie();
	//Sets the block's current goodie to the provided parameter
	char setGoodie(char to);
	//Implementation of Actor doSomething virtual function. This checks if there is a goodie and releases it. Otherwise, the function will play the bonk sound effect.
	virtual bool bonk();
private:
	//Goodie that the block contains
	char m_goodie;
};

class Pipe : public Block {
public:
	//Pipe constructor. Since pipe essentially behaves like a block without a goodie and a different texture, constructor passes specific pipe image and lack of goodie
	//to the block constructor, as well as the location, world pointer, start direction, size, and depth.
	Pipe(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1.0, int depth = 2);
private:
};

class Flag : public Actor {
public:
	//Flag class constructor takes starting location, a pointer to the StudentWorld, and the starting direction, size, depth, and the flag image (so that the derived mario class
	//can pass in its specific sprite)
	Flag(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1.0, int depth = 1, int image = IID_FLAG);
	//Implementation of doSomething function that, if the flag is active, confirms peach is touching the flag before increasing the score, killing the flag, and moving to the next level
	virtual void doSomething();
	//Virtual function that, in the case of a flag object, will move to the next level
	virtual void proceed();
private:
};

class Mario : public Flag {
public:
	//Mario class constructor accepting the starting location, a pointer to the StudentWorld, and the starting direction, size, depth. Since Marios mostly have the same behavior as
	//Flags, Mario is derived from Flags.
	Mario(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1.0, int depth = 1);
	//Virtual function that now moves to the end of game message.
	virtual void proceed();
private:
};

class Object : public Actor {
public:
	//Object class constructor. Pure virtual class with the intent of representing projectiles and powerups. The constructor accepts the object's image, location, world pointer, whether it should be targeting peach,
	//damageable objects, and physical objects, whether the object is physical, damageable, and the starting direction, size, and depth.
	Object(int image, double startX, double startY, StudentWorld* world, bool searchPeach, bool searchDamageable, bool searchPhysical, bool isPhysical = false, bool isDamageable = false, int startDirection = 0, double size = 1, int depth = 1);
	//Implementation of Actor virtual function. Checks if object is overlapping with any actor and does object specific behavior if so. Then checks if there is a physical actor below the object,
	//Causing the actor to fall downwards. Checks if there is a physical actor in front of the object and if not, move the object forward. If there is an actor in front of the object,
	//checks if object can bounce. If object can bounce, switch object direction, if not, delete the object from the student world.
	virtual void doSomething(); 
	//Object specific behavior triggered when the target of the object (the Actor that causes special behavior) is encountered. Declared pure virtual so general object cannot be instantiated.
	virtual bool objectBehavior(Actor* other) = 0;
	//Virtual function that returns whether the object will bounce when hitting a physical actor. By default returns true.
	virtual bool bounce();
	//Virtual function that returns the number of points that the object adds to the student world. Returns zero.
	virtual int getPoints();
private:
	//Private member variables to keep track of the target of the object (qualities of Actor that causes special behavior)
	bool m_searchPhysical;
	bool m_searchPeach;
	bool m_searchDamageable;
};

class Enemy : public Actor {
public:
	//Enemy class constructor. Intended to be abstract class for the various enemies peach can encounter. The constructor accepts the object's image, location, world pointer, the size, and the depth.
	Enemy(int image, double startX, double startY, StudentWorld* world, double size = 1, int depth = 0);
	//Enemy doSomething function. Checks to see if the enemy is overlapping with peach and if so, it will bonk peach. The enemy will then determine the direction it's moving, then check if there is an object
	//in the movement direction below the enemy. If not, turn around. If there is a wall in front of the enemy turn around. Otherwise, continue moving in the current direction.
	virtual void doSomething();
	//Returns the number of points the enemy is worth. By default the enemy is worth 100 points.
	virtual int getPoints();
	//If an enemy is bonked, determine if peach is invincible (Enemies can only be bonked by peach - managed through the damageable, physical, and ispeach qualities).
	//If peach is invincible due to the star, then play the kick sound effect and damage the enemy.
	virtual bool bonk();
	//Implementation of virtual damage function. Increases the world's points by the enemy's points and kills the enemy.
	virtual bool Damage();
private:
	//Turns the enemy around. If they are facing left, they will face right; if they are facing right, they will face left.
	void turnAround();
};

class Koopa : public Enemy {
public:
	//Koopa class constructor. Koopa class is derived from enemy, and constructor accepts starting location, world, size and depth. 
	Koopa(double startX, double startY, StudentWorld* world, double size = 1, int depth = 0);
	//Koopa virtual damage function. Koopas spawn shells when they are damaged, which this implementation accounts for.
	virtual bool Damage();
private:
};

class Goomba : public Enemy {
public:
	//Goomba Class constructor. Goomba class is derived from enemy and has the default enemy behavior. Accepts the location, world, size, and depth.
	Goomba(double startX, double startY, StudentWorld* world, double size = 1, int depth = 0);
private:
};


class Piranha : public Enemy {
public:
	//Piranha Class constructor. Accepts the starting position, world, size, and depth. Piranhas have most of the same enemy behavior, but don't move.
	Piranha(double startX, double startY, StudentWorld* world, double size = 1, int depth = 0);
	//Piranha implementation of the doSomething function. If the Piranha is alive, then animate the Piranha. If it overlaps with peach, bonk peach. If Peach is in range,
	//turn to face her and fire a fireaball (or lower the cooldown).
	virtual void doSomething();
private:
	int m_delay;
};

class PowerUp : public Object {
public:
	//PowerUp Class constructor. Accepts the image, starting position, world, starting direction, size, and depth. Intended to represent the three powerups in the game.
	PowerUp(int image, double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
	//Virtual function that returns if the current powerup is a Flower. Returns false.
	virtual bool isFlower();
	//Virtual function that returns if the current powerup is a Mushroom. Returns false.
	virtual bool isMushroom();
	//Virtual function that returns if the current powerup is a Star. Returns false.
	virtual bool isStar();
	virtual bool objectBehavior(Actor* other);
	//Virtual function for any extra behavior a powerup may require when it is acquired. By default does nothing, but is implemented.
	virtual bool extraBehavior();
private:
};

class Mushroom : public PowerUp {
public:
	//Mushroom constructor, takes the mushroom's location, the world, the start direction, size, and depth.
	Mushroom(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
	//Virtual function that internally confirms which powerup this class represents. Returns true.
	virtual bool isMushroom();
	//Virtual function implementation that returns the number of points the mushroom provides, 75 points.
	virtual int getPoints();
private:
};

class Flower : public PowerUp {
public:
	//Flower constructor, takes location, world, starting direction, size and depth.
	Flower(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
	//Virtual function that internally confirms which powerup this class represents. Returns true.
	virtual bool isFlower();
	//Virtual function implementation that returns the number of points the flower provides, 50 points.
	virtual int getPoints();
private:
};

class Star : public PowerUp {
public:
	//Star constructor, takes location, world, starting direciton, size, and depth.
	Star(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
	//Virtual function that internally confirms which powerup this class represents. Returns true.
	virtual bool isStar();
	//Virtual function implementation that returns the number of points the flower provides, 100 points.
	virtual int getPoints();
	//Virtual function implementation that carries out star specific behavior, specifically setting the star cooldown.
	virtual bool extraBehavior();
private:
};

class Projectile : public Object {
public:
	//Projectile constructor. Derived from Object class, accepts image, location, world, start direction, size, depth, and whether the projectile attacks peach.
	Projectile(int image, double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1, bool attackPeach = false);
	//Object specific behavior to carry out when the projectile encounters its target (either peach, or something damageable). Implemented in Projectile class, and target clarified in derived classes.
	virtual bool objectBehavior(Actor* other);
	//Returns whether the projectile can bounce. By default returns false (most projectiles cannot bounce).
	virtual bool bounce();
private:
};

class PiranhaFireball : public Projectile {
public:
	//PiranhaFireball constructor. Derived from the Projectile class, accepting the location, world, start direction, size, and depth. 
	PiranhaFireball(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
	//Implementation of object behavior when it encounters its target. PiranhaFireballs confirm they are attacking peach, then damage peach and kill the projectile.
	virtual bool objectBehavior(Actor* other);
private:
};

class Fireball : public Projectile {
public:
	//Fireball constructor. Derived from the Projectile class accepts the location, world, startDirection, size, and depth. The constructor 
	//indicates it should not look for damageable actors other than peach
	Fireball(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
private:
};

class Shell : public Projectile {
public:
	//Shell constructor. Derived from the Projectile class, accepting the location, world, start direction, size, and depth. The constructor indicates the projectile class should not search 
	//for peach (instead search for enemies). 
	Shell(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1, int depth = 1);
private:
};


class Peach : public Actor
{
public:
	//Peach constructor. Accepts the starting location of peach, the world, the starting direction, size, and depth. Initializes the peach actor as having one health, not being invincible
	//not having any powerups, not jumping, and not having any cooldowns (invincibility or shoot power). 
	Peach(double startX, double startY, StudentWorld* world, int startDirection = 0, double size = 1.0, int depth = 0);
	//Implementation of bonk function. If peach is invincible, don't do anything. Otherwise, decrease peach's health, increase the temporary invinciblity ticks. Indicate that it is invincible.
	//Remove all powerups. If the health is greater 0, play the hurt sound effect. Otherwise, decrease the player's lives and set peach's status equal to false.

	virtual void doSomething();
	//Implementation of bonk function. If peach is invincible, don't do anything. Otherwise, decrease peach's health, increase the temporary invinciblity ticks. Indicate that it is invincible.
	//Remove all powerups. If the health is greater 0, play the hurt sound effect. Otherwise, decrease the player's lives and set peach's status equal to false.
	virtual bool bonk();
	//Returns whether peach has the invincible ability. Peach specific ability, so implemented here.
	bool getInvincible();
	//Returns whether peach has the shoot ability. Peach specific ability, so implemented here.
	bool getShoot();
	//Returns whether peach has the jump ability. Peach specific ability, so implemented here.
	bool getJump();
	//Sets peach's hit points to the provided parameter. Peach specific ability, so implemented here.
	int setHealth(int h);
	//Decrement peach's hit points by one. Peach specific ability, so implemented here.
	int decHealth();
	//Function to set peach's internal attributes based off of what power peach has encountered. Returns whether internals were changed.
	bool gainPower(bool flower, bool mushroom, bool star);
	//Damaging Peach effectively bonks peach.
	virtual bool Damage();
	//Sets all of peach's powers to false. Peach specific ability, so implemented here.
	bool losePower();
	//Sets the peach invincibility ticks to the provided parameter. Peach specific ability, so implemented here.
	bool setTicks(int ticks);
	//Virtual implementation that returns true, since the actor is peach.
	virtual bool isPeach();
private:
	int m_health;

	int m_invTicks;
	bool m_invincible;

	bool m_tempInv;
	int m_tempInvTicks;

	bool m_shoot;
	int m_shootTicks;

	bool m_jump;
	int remaining_jump_distance;
};

#endif // ACTOR_H_
