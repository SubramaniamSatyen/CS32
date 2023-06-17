#include "Actor.h"
#include "StudentWorld.h"
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//Actor constructor with default values for start direction, size, depth, whether the actor is damageable, physical, or alive. Initializes these values
//Into the base class of the GraphObject or into the member variables.
Actor::Actor(int imageID, double startX, double startY, StudentWorld* world, int startDirection, double size, int depth, bool damageable, bool physical, bool alive) : GraphObject(imageID, startX, startY, startDirection
	, depth, size), m_alive(alive), m_studentWorld(world), m_physical(physical), m_damageable(damageable) {
}

//Returns whether the Actor is alive
bool Actor::getStatus() {
	return m_alive;
}

//Sets the Actor's status to the provided parameter (true or false representing alive or terminated)
void Actor::setStatus(bool status) {
	m_alive = status;
}

//Function that returns pointer to the world that the Actors live in.
StudentWorld* Actor::getWorld() {
	return m_studentWorld;
}

//Returns whether the Actor is physical (can block other actors)
bool Actor::getPhysical() {
	return m_physical;
}

//Returns whether the actor is damageable
bool Actor::isDamageable() {
	return m_damageable;
}

//Virtual function that damages the actor. In this case damaging the actor does not do anything.
bool Actor::Damage() {
	return false;
}

//Virtual function returning whether the Actor is Peach (since peach is so important I have specific function to identify it). Function returns false.
bool Actor::isPeach() {
	return false;
}

//Function accepts a pair of coordinates, a pointer to an actor to ignore, as well as whether to search for physical actors, whether to consider peach,
//and whether to consider if the actor is damageable. This function can be used to check for overlap in derived classes (note that it checks all four corners of sprite,
//so may be overkill depending on use).
Actor* Actor::overlaps(int X, int Y, Actor* curr, bool considerPhysical, bool peachAllowed, bool damageable) {
	//Determines if a different actor is present in the sprite's bottom left corner in the current game world with the provided conditions
	Actor* actorBelowLeft = (getWorld()->getActorAt(X, Y, this, considerPhysical, peachAllowed, damageable));
	//If actor exists, return pointer to that actor
	if (actorBelowLeft != nullptr) {
		return actorBelowLeft;
	}
	//Determines if a different actor is present in the sprite's bottom right corner in the current game world with the provided conditions
	Actor* actorBelowRight = (getWorld()->getActorAt(X + SPRITE_WIDTH - 1, Y, this, considerPhysical, peachAllowed, damageable));
	//If actor exists, return pointer to that actor
	if (actorBelowRight != nullptr) {
		return actorBelowRight;
	}
	//Determines if a different actor is present in the sprite's top left corner in the current game world with the provided conditions
	Actor* actorAboveLeft = (getWorld()->getActorAt(X, (Y + SPRITE_HEIGHT - 1), this, considerPhysical, peachAllowed, damageable));
	//If actor exists, return pointer to that actor
	if (actorAboveLeft != nullptr) {
		return actorAboveLeft;
	}
	//Determines if a different actor is present in the sprite's top right corner in the current game world with the provided conditions
	Actor* actorAboveRight = (getWorld()->getActorAt(X + SPRITE_WIDTH - 1, (Y + SPRITE_HEIGHT - 1), this, considerPhysical, peachAllowed, damageable));
	//If actor exists, return pointer to that actor
	if (actorAboveRight != nullptr) {
		return actorAboveRight;
	}
	//If no pointer return nullptr
	return nullptr;
}

//A lighter weight function than overlaps that confirms whether the current Actor overlaps with Peach, returning true or false.
bool Actor::overlapsPeach(int X, int Y){
	//Returns whether the provided coordinates of a sprite would lie within the Peach actor sprite
	return (getWorld()->checkPeach(X, (Y + SPRITE_HEIGHT - 1))) || (getWorld()->checkPeach(X + SPRITE_WIDTH - 1, (Y + SPRITE_HEIGHT - 1))) ||
	(getWorld()->checkPeach(X, Y)) || (getWorld()->checkPeach(X + SPRITE_WIDTH - 1, Y));
}

//Virtual bonk function that returns whether the bonk carried out the relevant activity. In this case returns true
bool Actor::bonk() {
	return true;
}

//Constructor for the block class that accepts sprite location, the world, the goodie the block contains (if it contains one), as well as the default start direction, size, and depth.
//The constructor initializes the block as alive and with the default block image.
Block::Block(double startX, double startY, StudentWorld* world, char goodie, int startDirection, double size, int depth, int image) : Actor(image, startX, startY, world, startDirection, size, depth, false, true, true), m_goodie(goodie) {
}

//Implementation of Actor doSomething virtual function. This checks if there is a goodie and releases it. Otherwise, the function will play the bonk sound effect.
bool Block::bonk() {
	//If there is a goodie
	if (getGoodie() != 'n') {
		//Play the power up sound 
		getWorld()->playSound(SOUND_POWERUP_APPEARS);
		//Create goodie in space above the block
		PowerUp* p;
		if (m_goodie == 'm') {
			p = new Mushroom(getX(), getY() + SPRITE_HEIGHT, getWorld());
		}
		else if (m_goodie == 'f') {
			p = new Flower(getX(), getY() + SPRITE_HEIGHT, getWorld());
		}
		else if (m_goodie == 's') {
			p = new Star(getX(), getY() + SPRITE_HEIGHT, getWorld());
		}
		//Add the goodie to the world
		getWorld()->addActor(p);
		//Set the block so that it doesn't have any goodie
		setGoodie('n');
	}
	else {
		//Plays bonk sound
		getWorld()->playSound(SOUND_PLAYER_BONK);
	}
	return true;
}

//Implementation of Actor doSomething virtual function. This checks if there is a goodie and releases it. Otherwise, the function will play the bonk sound effect.
void Block::doSomething() {
}

//Returns the goodie the block contains
char Block::getGoodie() {
	return (m_goodie);
}

//Sets the block's current goodie to the provided parameter
char Block::setGoodie(char to) {
	m_goodie = to;
	return to;
}

//Pipe constructor. Since pipe essentially behaves like a block without a goodie and a different texture, constructor passes specific pipe image and lack of goodie
//to the block constructor, as well as the location, world pointer, start direction, size, and depth.
Pipe::Pipe(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Block(startX, startY, world,'n',startDirection, size, depth, IID_PIPE) {
}

//Flag class constructor takes starting location, a pointer to the StudentWorld, and the starting direction, size, depth, and the flag image (so that the derived mario class
//can pass in its specific sprite)
Flag::Flag(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth, int image) : Actor(image, startX, startY, world, startDirection, size, depth, false, false, true) {
}

//Implementation of doSomething function that, if the flag is active, confirms peach is touching the flag before increasing the score, killing the flag, and moving to the next level
void Flag::doSomething() {
	//If active and overlapping with peach, increase score, set flag to inactive, and bump the game status to the next state.
	if (getStatus()) {
		if (overlapsPeach(getX(), getY())) {
			getWorld()->increaseScore(1000);
			setStatus(false);
			proceed();
		}
	}
}

//Virtual function that, in the case of a flag object, will move to the next level
void Flag::proceed() {
	getWorld()->setNextLevel();
}

//Mario class constructor accepting the starting location, a pointer to the StudentWorld, and the starting direction, size, depth. Since Marios mostly have the same behavior as
//Flags, Mario is derived from Flags.
Mario::Mario(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Flag(startX, startY, world, startDirection, size, depth, IID_MARIO) {
}

//Virtual function that now moves to the end of game message.
void Mario::proceed() {
	getWorld()->wonGame();
}

//Object class constructor. Pure virtual class with the intent of representing projectiles and powerups. The constructor accepts the object's image, location, world pointer, whether it should be targeting peach,
//damageable objects, and physical objects, whether the object is physical, damageable, and the starting direction, size, and depth.
Object::Object(int image, double startX, double startY, StudentWorld* world, bool searchPeach, bool searchDamageable, bool isPhysical, bool isDamageable, bool searchPhysical, int startDirection, double size, int depth) : Actor(image, startX, startY, world, startDirection, size, depth, isPhysical, isDamageable, true), m_searchDamageable(searchDamageable), m_searchPeach(searchPeach), m_searchPhysical(searchPhysical){
}

//Virtual function that returns whether the object will bounce when hitting a physical actor. By default returns true.
bool Object::bounce() {
	return true;
}

//Virtual function that returns the number of points that the object adds to the student world. Returns zero.
int Object::getPoints() {
	return 0;
}

//Implementation of Actor virtual function. Checks if object is overlapping with any actor and does object specific behavior if so. Then checks if there is a physical actor below the object,
//Causing the actor to fall downwards. Checks if there is a physical actor in front of the object and if not, move the object forward. If there is an actor in front of the object,
//checks if object can bounce. If object can bounce, switch object direction, if not, delete the object from the student world.
void Object::doSomething() {
	//If an actor of the target qualities exists at the same location as the object and the object's behavior was completed, return
	Actor* actorCurr = overlaps(getX(), getY(), this, m_searchPhysical, m_searchPeach, m_searchDamageable);
	if (actorCurr != nullptr && objectBehavior(actorCurr)){
		return;
	}
	else {
		//If there is no physical actor below the object, move the object so it falls downwards
		Actor* actorBelow = (getWorld()->getActorAt(getX(), getY() - 2, this));
		if (actorBelow == nullptr) {
			actorBelow = (getWorld()->getActorAt(getX() + SPRITE_WIDTH - 1, getY() - 2, this));
		}
		if (actorBelow == nullptr) {
			moveTo(getX(), getY() - 2);
		}
		
		//Determines the direction the object is moving and stores it for later
		int dir;
		if (getDirection() == 0) {
			dir = SPRITE_WIDTH + 1;
		}
		else {
			dir = -2;
		}
		//Determines if there is a physical actor blocking the object's movement
		Actor* actorBlocking = (getWorld()->getActorAt(getX() + dir, getY(), this));
		if (actorBlocking == nullptr) {
			actorBlocking = (getWorld()->getActorAt(getX() + dir, getY() + SPRITE_HEIGHT - 1, this));
		}
		//If there is an actor blocking movement, carry out object specific behavior
		if (actorBlocking != nullptr) {
			//If object cannot bounce, terminate the object
			if (!bounce()) {
				setStatus(false);
				return;
			}
			//If the object can bounce, change the direction of the object's movement
			if (getDirection() == 0) {
				setDirection(180);
			}
			else {
				setDirection(0);
			}
		}
		//If there is no object blocking movement, continue moving in the same direction. 
		else {
			if (getDirection() == 0) {
				moveTo(getX() + 2, getY());
			}
			else {
				moveTo(getX() - 2, getY());
			}
		}
	}
}

//Enemy class constructor. Intended to be abstract class for the various enemies peach can encounter. The constructor accepts the object's image, location, world pointer, the size, and the depth.
Enemy::Enemy(int image, double startX, double startY, StudentWorld* world, double size, int depth) : Actor(image, startX, startY, world, randInt(0, 1) * 180, size, depth, true, false, true) {
}

//Enemy doSomething function. Checks to see if the enemy is overlapping with peach and if so, it will bonk peach. The enemy will then determine the direction it's moving, then check if there is an object
//in the movement direction below the enemy. If not, turn around. If there is a wall in front of the enemy turn around. Otherwise, continue moving in the current direction.
void Enemy::doSomething() {
	//If Enemy is alive, proceed with behavior
	if (getStatus()) {
		//If enemy is overlapping with peach, bonk peach
		if (overlapsPeach(getX(), getY())) {
			getWorld()->getPeach()->bonk();
			return;
		}
		//Determine the direction the enemy is moving
		int dir;
		if (getDirection() == 0) {
			dir = SPRITE_WIDTH;
		}
		else {
			dir = -1;
		}
		//If there is an actor in front of the enemy, turn around
		Actor* actorBesideCorner = (getWorld()->getActorAt(getX() + dir, getY(), this));
		if (actorBesideCorner != nullptr) {
			turnAround();
		}
		else {
			//If there is no ground for the enemy to stand on in front of the enemy, turn around
			Actor* actorBesideBelow = (getWorld()->getActorAt(getX() + dir, getY() - 1, this));
			if (actorBesideBelow == nullptr) {
				turnAround();
			}
		}
		//If no issues, move forwards.
		if (getDirection() == 0) {
			moveTo(getX() + 1, getY());
		}
		else {
			moveTo(getX() - 1, getY());
		}
	}
}

//Turns the enemy around. If they are facing left, they will face right; if they are facing right, they will face left.
void Enemy::turnAround() {
	if (getDirection() == 0) {
		setDirection(180);
	}
	else {
		setDirection(0);
	}
}

//If an enemy is bonked, determine if peach is invincible (Enemies can only be bonked by peach - managed through the damageable, physical, and ispeach qualities).
//If peach is invincible due to the star, then play the kick sound effect and damage the enemy.
bool Enemy::bonk() {
	//If peach is invincible from star play kick sound and kill enemy
	if (getWorld()->getPeach()->getInvincible()) {
		getWorld()->playSound(SOUND_PLAYER_KICK);
		Damage();
	}
	return true;
}

//Returns the number of points the enemy is worth. By default the enemy is worth 100 points.
int Enemy::getPoints() {
	return 100;
}

//Implementation of virtual damage function. Increases the world's points by the enemy's points and kills the enemy.
bool Enemy::Damage() {
	//Increases the score by the enemy's points.
	getWorld()->increaseScore(getPoints());
	//Kills the enemy
	setStatus(false);
	return true;
}

//Koopa class constructor. Koopa class is derived from enemy, and constructor accepts starting location, world, size and depth. 
Koopa::Koopa(double startX, double startY, StudentWorld* world, double size, int depth) : Enemy(IID_KOOPA, startX, startY, world, size, depth) {
}

//Koopa virtual damage function. Koopas spawn shells when they are damaged, which this implementation accounts for.
bool Koopa::Damage() {
	//Increase score
	getWorld()->increaseScore(getPoints());
	//Kill the current Koopa
	setStatus(false);
	//Spawn Shell with current direction
	Actor* shell = new Shell(getX(), getY(), getWorld(), getDirection());
	//Add the shell to the world
	getWorld()->addActor(shell);
	return true;
}

//Goomba Class constructor. Goomba class is derived from enemy and has the default enemy behavior. Accepts the location, world, size and depth.
Goomba::Goomba(double startX, double startY, StudentWorld* world, double size, int depth) : Enemy(IID_GOOMBA, startX, startY, world, size, depth) {
}

//Piranha Class constructor. Accepts the starting position, world, size, and depth. Piranhas have most of the same enemy behavior, but don't move.
Piranha::Piranha(double startX, double startY, StudentWorld* world, double size, int depth) : Enemy(IID_PIRANHA, startX, startY, world, size, depth), m_delay(0) {
}

//Piranha implementation of the doSomething function. If the Piranha is alive, then animate the Piranha. If it overlaps with peach, bonk peach. If Peach is in range,
//turn to face her and fire a fireaball (or lower the cooldown).
void Piranha::doSomething() {
	//If still alive, do behavior
	if (getStatus()) {
		//Animate the enemy
		increaseAnimationNumber();
		//If peach overlaps the piranha, bonk peach
		if (overlapsPeach(getX(), getY())) {
			getWorld()->getPeach()->bonk();
			return;
		}
		//If peach is out of range, move on
		if (!(abs(getWorld()->getPeach()->getY() - getY()) <= 1.5 * SPRITE_HEIGHT)) {
			return;
		}
		else {
			//If peach is to the left, turn to face her. Otherwise turn right to face peach.
			if (getX() - getWorld()->getPeach()->getX() >= 0) {
				setDirection(180);
			}
			else {
				setDirection(0);
			}
		}
		//If there is still a cooldown to fire the next shot, cut the decrement the delay and move on.
		if (m_delay > 0) {
			m_delay--;
			return;
		}
		//If there is no delay
		else {
			//If peach is within the trigger range
			if (abs(getWorld()->getPeach()->getX() - getX()) < 8 * SPRITE_WIDTH) {
				//Create a new fireball at the location of the plant
				PiranhaFireball* p = new PiranhaFireball(getX(), getY(), getWorld(), getDirection());
				//Add the fireball to the world
				getWorld()->addActor(p);
				//Play the fireball sound effect
				getWorld()->playSound(SOUND_PIRANHA_FIRE);
				//Reset the fireball cooldown
				m_delay = 40;
			}
		}

	}
}

//PowerUp Class constructor. Accepts the image, starting position, world, starting direction, size, and depth. Intended to represent the three powerups in the game.
PowerUp::PowerUp(int image, double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Object(image, startX, startY, world, true, false, false, false, false, startDirection, size, depth) {
}

//Powerup main behavior that is triggered when it overlaps with peach (as per the base class Object's doSomething function).
bool PowerUp::objectBehavior(Actor* other) {
	//If the other object is somehow not peach (should never happen, but check was encouraged in spec), return false.
	if (!other->isPeach()) {
		return false;
	}
	//If PowerUp has encountered peach
	else {
		//Increase the score by the PowerUp's points
		getWorld()->increaseScore(getPoints());
		//Inform peach which PowerUp she has gained
		getWorld()->getPeach()->gainPower(isFlower(), isMushroom(), isStar());
		//Carry out any PowerUp specific behavior
		extraBehavior();
		//If the PowerUp is not star, set the player's hit points to 2. 
		if (!isStar()) {
			getWorld()->getPeach()->setHealth(2);
		}
		//Kill the PowerUp
		setStatus(false);
		//Play the PowerUp sound.
		getWorld()->playSound(SOUND_PLAYER_POWERUP);
		return true;
	}
}

//Virtual function that returns if the current powerup is a Flower. Returns false.
bool PowerUp::isFlower() {
	return false;
}

//Virtual function that returns if the current powerup is a Mushroom. Returns false.
bool PowerUp::isMushroom() {
	return false;
}

//Virtual function that returns if the current powerup is a Star. Returns false.
bool PowerUp::isStar() {
	return false;
}

//Virtual function for any extra behavior a powerup may require when it is acquired. By default does nothing, but is implemented.
bool PowerUp::extraBehavior() {
	return true;
}

//Mushroom constructor, takes the mushroom's location, the world, the start direction, size, and depth.
Mushroom::Mushroom(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : PowerUp(IID_MUSHROOM, startX, startY, world, startDirection, size, depth)  {
}

//Virtual function that internally confirms which powerup this class represents. Returns true.
bool Mushroom::isMushroom() {
	return true;
}

//Virtual function implementation that returns the number of points the mushroom provides, 75 points.
int Mushroom::getPoints() {
	return 75;
}

//Flower constructor, takes location, world, starting direction, size and depth.
Flower::Flower(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : PowerUp(IID_FLOWER, startX, startY, world, startDirection, size, depth) {
}

//Virtual function that internally confirms which powerup this class represents. Returns true.
bool Flower::isFlower() {
	return true;
}

//Virtual function implementation that returns the number of points the flower provides, 50 points.
int Flower::getPoints() {
	return 50;
}

//Star constructor, takes location, world, starting direciton, size, and depth.
Star::Star(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : PowerUp(IID_STAR, startX, startY, world, startDirection, size, depth) {
}

//Virtual function that internally confirms which powerup this class represents. Returns true.
bool Star::isStar() {
	return true;
}

//Virtual function implementation that returns the number of points the flower provides, 100 points.
int Star::getPoints() {
	return 100;
}

//Virtual function implementation that carries out star specific behavior, specifically setting the star cooldown.
bool Star::extraBehavior() {
	getWorld()->getPeach()->setTicks(150);
	return true;
}

//Projectile constructor. Derived from Object class, accepts image, location, world, start direction, size, depth, and whether the projectile attacks peach.
Projectile::Projectile(int image, double startX, double startY, StudentWorld* world, int startDirection, double size, int depth, bool attackPeach) : Object(image, startX, startY, world, attackPeach, true, false, false, false, startDirection, size, depth) {
}

//Object specific behavior to carry out when the projectile encounters its target (either peach, or something damageable). Implemented in Projectile class, and target clarified in derived classes.
bool Projectile::objectBehavior(Actor* other) {
	//If projectile is active
	if (other->getStatus()) {
		//Damage the other actor
		other->Damage();
		//Kill the projectile
		setStatus(false);
		return true;
	}
	return false;
}

//Returns whether the projectile can bounce. By default returns false (most projectiles cannot bounce).
bool Projectile::bounce() {
	return false;
}

//Shell constructor. Derived from the Projectile class, accepting the location, world, start direction, size, and depth. The constructor indicates the projectile class should not search 
//for peach (instead search for enemies). 
Shell::Shell(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Projectile(IID_SHELL, startX, startY, world, startDirection, size, depth, false) {
}

//PiranhaFireball constructor. Derived from the Projectile class, accepting the location, world, start direction, size, and depth. The constructor indicates the projectile class should search for peach. 
PiranhaFireball::PiranhaFireball(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Projectile(IID_PIRANHA_FIRE, startX, startY, world, startDirection, size, depth, true) {
}

//Implementation of object behavior when it encounters its target. PiranhaFireballs confirm they are attacking peach, then damage peach and kill the projectile.
bool PiranhaFireball::objectBehavior(Actor* other) {
	//If the actor encountered is in fact peach, and the projectile is alive
	if (other->isPeach()) {
		if (other->getStatus()) {
			//Damage peach
			other->Damage();
			//Kill the projectile
			setStatus(false);
			return true;
		}
	}
	return false;
}

//Fireball constructor. Derived from the Projectile class accepts the location, world, startDirection, size, and depth. The constructor 
//indicates it should not look for damageable actors other than peach
Fireball::Fireball(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Projectile(IID_PEACH_FIRE, startX, startY, world, startDirection, size, depth, false) {
}

//Peach constructor. Accepts the starting location of peach, the world, the starting direction, size, and depth. Initializes the peach actor as having one health, not being invincible
//not having any powerups, not jumping, and not having any cooldowns (invincibility or shoot power). 
Peach::Peach(double startX, double startY, StudentWorld* world, int startDirection, double size, int depth) : Actor(IID_PEACH, startX, startY, world, startDirection, size, depth, true, false, true), m_health(1), m_invincible(false), m_jump(false),
m_shoot(false), remaining_jump_distance(0), m_invTicks(0), m_tempInv(false), m_tempInvTicks(0), m_shootTicks(0){

}

//Implementation of bonk function. If peach is invincible, don't do anything. Otherwise, decrease peach's health, increase the temporary invinciblity ticks. Indicate that it is invincible.
//Remove all powerups. If the health is greater 0, play the hurt sound effect. Otherwise, decrease the player's lives and set peach's status equal to false.
bool Peach::bonk() {
	//If peach is invincible, end bonk
	if (m_invincible || m_tempInv) {
		return true;
	}
	//If peach is not invincible
	else {
		//Decrease peach's hit points
		m_health--;
		//Set temporary invincibility ticks to 10
		m_tempInvTicks = 10;
		m_tempInv = true;
		//Remove all powerups
		m_jump = false;
		m_shoot = false;
		//If player still has hit points, play the hurt sound effect
		if (m_health > 0) {
			getWorld()->playSound(SOUND_PLAYER_HURT);
		}
		//If player doesn't have any hit points
		else {
			//Decreases the player's lives
			getWorld()->decLives();
			//Kills peach
			setStatus(false);
		}
		return true;
	}
}

//Sets the peach invincibility ticks to the provided parameter. Peach specific ability, so implemented here.
bool Peach::setTicks(int ticks) {
	m_invTicks = ticks;
	return true;
}

//Returns whether peach has the invincible ability. Peach specific ability, so implemented here.
bool Peach::getInvincible() {
	return m_invincible;
}

//Returns whether peach has the shoot ability. Peach specific ability, so implemented here.
bool Peach::getShoot() {
	return m_shoot;
}

//Returns whether peach has the jump ability. Peach specific ability, so implemented here.
bool Peach::getJump() {
	return m_jump;
}

//Sets peach's hit points to the provided parameter. Peach specific ability, so implemented here.
int Peach::setHealth(int h) {
	m_health = h;
	return m_health;
}

//Decrement peach's hit points by one. Peach specific ability, so implemented here. Peach specific ability, so implemented here.
int Peach::decHealth() {
	m_health--;
	return m_health;
}

//Virtual implementation that returns true, since the actor is peach.
bool Peach::isPeach() {
	return true;
}

//Function to set peach's internal attributes based off of what power peach has encountered. Returns whether internals were changed.
bool Peach::gainPower(bool flower, bool mushroom, bool star) {
	//If mushroom powerup, activate jump power
	if (mushroom) {
		m_jump = true;
		return true;
	}
	//If star powerup, activate invincibility power
	else if (star) {
		m_invincible = true;
		return true;
	}
	//If flower powerup, activate shoot power
	else if (flower) {
		m_shoot = true;
		return true;
	}
	//If none of the above power ups, nothing changed, return false.
	return false;
}

//Sets all of peach's powers to false. Peach specific ability, so implemented here.
bool Peach::losePower() {
	m_jump = false;
	m_invincible = false;
	m_shoot = false;
	return true;
}

//Peach doSomething implementation. 
void Peach::doSomething()
{
	int ch;
	//If peach is not alive
	if (getStatus()) {
		//If invincible, decrease invincibility cooldown
		if (m_invincible) {
			m_invTicks--;
			//If the invinciblity has cooled down, set invincibility to false
			if (m_invTicks <= 0) {
				m_invTicks = 0;
				m_invincible = false;
			}
		}
		//If temporarily invincible, decrease temporary invinciblity cooldown
		if (m_tempInv) {
			m_tempInvTicks--;
			//If the temporary invincibility has cooled down, set temporary invincibility to false
			if (m_tempInvTicks <= 0) {
				m_tempInvTicks = 0;
				m_tempInv = false;
			}
		}
		//If shooting cooldown is active, decrease the cooldown.
		if (m_shootTicks > 0) {
			m_shootTicks--;
		}

		//Confirm that nobody else is at this point and bonk the other actor if it is present
		Actor* otherActor = overlaps(getX(), getY(), this, false, false, false);
		if (otherActor != nullptr) {
			otherActor->bonk();
		}

		//If peach is jumping
		if (remaining_jump_distance > 0) {
			//Confirm no actor would prevent peach for moving upwards. If there is a physical actor above, bonk it and stop jumping.
			Actor* actorAbove = overlaps(getX(), (getY() + 4), this);
			if (actorAbove != nullptr) {
				actorAbove->bonk();
				remaining_jump_distance = 0;
			}
			//Otherwise, move the actor upwards and decrease the jump distance left
			else {
				moveTo(getX(), getY() + 4);
				remaining_jump_distance--;
			}
		}
		//If actor is not jumping
		else {
			//Confirm that there is no actor below peach (between 0 and three pixels inclusive as per the spec). 
			Actor* actorBelowLeft;
			Actor* actorBelowRight;
			bool ground = false;
			for (int i = 1; i <= 4; i++) {
				//Check if there is an actor to the left or right below peach. If so then indicate there is ground below.
				actorBelowLeft = (getWorld()->getActorAt(getX(), getY() - i, this));
				actorBelowRight = (getWorld()->getActorAt(getX() + SPRITE_WIDTH - 1, getY() - i, this));
				if (actorBelowLeft != nullptr || actorBelowRight != nullptr) {
					ground = true;
					break;
				}
			}
			//If there is no ground, peach should fall downwards.
			if (!ground) {
				moveTo(getX(), getY() - 4);
			}
		}
		//If the user has pressed a key
		if (getWorld()->getKey(ch))
		{
			//If the user pressed the left key (either < or a)
			if (ch == KEY_PRESS_LEFT) {
				//Turn peach to face left
				setDirection(180);
				//Check whether there is an actor that would prevent peach from moving left. If so, bonk it.
				Actor* actorLeft = overlaps(getX() - 4, getY(), this);
				if (actorLeft != nullptr) {
					actorLeft->bonk();
				}
				//Otherwise, move peach left.
				else {
					moveTo(getX() - 4, getY());
				}
			}
			//If the user pressed the right key (either > or d)
			else if (ch == KEY_PRESS_RIGHT) {
				//Turn peach to face right
				setDirection(0);
				//If there is an acgtor that would prevent peach from moving right, bonk it.
				Actor* actorRight = overlaps(getX() + 4, getY(), this);
				if (actorRight != nullptr) {
					actorRight->bonk();
				}
				//Otherwise move peach to the right.
				else {
					moveTo(getX() + 4, getY());
				}
			}
			//If the user pressed the up key (either w or ^)
			else if (ch == KEY_PRESS_UP) {
				//If there is ground below peach
				Actor* actorBelow = overlaps(getX(), getY() - 1, this);
				if (actorBelow != nullptr) {
					//If peach has the jump power, set jump height to 12
					if (m_jump) {
						remaining_jump_distance = 12;
					}
					//Otherwise set jump height to 8
					else {
						remaining_jump_distance = 8;
					}
					//Play the jumping sound effect
					getWorld()->playSound(SOUND_PLAYER_JUMP);
				}
			}
			//If the user pressed the space key
			else if (ch == KEY_PRESS_SPACE) {
				//If peach has the shoot powerup
 				if (m_shoot) {
					//If fireball is not on cooldown
					if (m_shootTicks <= 0) {
						//Play the fireball sound effect
						getWorld()->playSound(SOUND_PLAYER_FIRE);
						//Set the shoot cooldown to 8 ticks
						m_shootTicks = 8;
						//Determine which direction the fireball should appear (based off of the direction peach is facing)
						int location;
						if (getDirection() == 0) {
							location = 4;
						}
						else {
							location = -4;
						}
						//Create a fireball with the determined direction
						Actor* fireball = new Fireball(getX() + location, getY(), getWorld(), getDirection());
						//Add the fireball to the world
						getWorld()->addActor(fireball);
					}
				}
			}
		}
	}
}

//Damaging Peach effectively bonks peach. 
bool Peach::Damage() {
	bonk();
	return true;
}