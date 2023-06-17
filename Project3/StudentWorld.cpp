#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <iostream>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

//Student World Constructor as provided. Initializes the variables indicating completed level and completed game to false.
StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_levelFinished(false), m_won(false), m_peach(nullptr)
{
}
//For given coordinates, an actor to ignore, as well as whether to consider if the actor is physical, is peach,
//or is damageable, returns a pointer to an actor present at that position or the nullptr if no actor is present.
Actor* StudentWorld::getActorAt(int X, int Y, Actor* curr, bool considerPhysical, bool peachAllowed, bool damageable) {
    list<Actor*>::iterator iter = m_actors.begin();
    while (iter != m_actors.end()) {
        if ((*iter)->getX() <= X && (*iter)->getY() <= Y && (*iter)->getX() + SPRITE_WIDTH - 1 >= X && (*iter)->getY() + SPRITE_HEIGHT - 1 >= Y && (*iter) != curr) {
            if (peachAllowed) {
                if (damageable) {
                    if ((*iter)->isDamageable()) {
                        if ((*iter)->getPhysical() || !considerPhysical) {
                            return (*iter);
                        }
                    }
                }
                else {
                    if ((*iter)->getPhysical() || !considerPhysical) {
                        return (*iter);
                    }
                }
            }
            else {
                if (!(*iter)->isPeach()) {
                    if (damageable) {
                        if ((*iter)->isDamageable()) {
                            if ((*iter)->getPhysical() || !considerPhysical) {
                                return (*iter);
                            }
                        }
                    }
                    else {
                        if ((*iter)->getPhysical() || !considerPhysical) {
                            return (*iter);
                        }
                    }
                }
            }
        }
        iter++;
    }
    return nullptr;
}

Actor* StudentWorld::getActorAt(int X, int Y, Actor* curr) {
    return getActorAt(X, Y, curr, true, true, false);
}

//Returns whether the parameter coordinates overlap with Peach
bool StudentWorld::checkPeach(int X, int Y) {
    return (m_peach->getX() <= X && m_peach->getY() <= Y && m_peach->getX() + SPRITE_WIDTH - 1 >= X && m_peach->getY() + SPRITE_HEIGHT - 1 >= Y);
}

//Adds parameter actor to the end of the actor list
bool StudentWorld::addActor(Actor* actor) {
    m_actors.push_back(actor);
    return true;
}

//Helper function to load the specified level and return whether the loading was successful
bool StudentWorld::loadLevel(string s) {
    //Attempts to load the specific level file with provided function
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(s);
    //Determines whether loading was successful
    if (result == Level::load_fail_file_not_found) {
        return false;
    }
    else if (result == Level::load_fail_bad_format) {
        return false;
    }
    //If successful loading, add actors to the world
    else if (result == Level::load_success) {
        Level::GridEntry ge;
        //Iterate through rows and columns of game world
        for (int row = 0; row < 32; row++) {
            for (int col = 0; col < 32; col++) {
                //Get value at each location, determine if it is an actor and add it to the world if it is.
                ge = lev.getContentsOf(col, row);
                if (ge == Level::peach) {
                    Peach* p = new Peach(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_peach = p;
                    m_actors.push_front(p);
                }
                if (ge == Level::block) {
                    Block* b = new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(b);
                }
                if (ge == Level::pipe) {
                    Pipe* p = new Pipe(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(p);
                }
                if (ge == Level::flag) {
                    Flag* f = new Flag(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(f);
                }
                if (ge == Level::mushroom_goodie_block) {
                    Block* b = new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this, 'm');
                    m_actors.push_back(b);
                }
                if (ge == Level::flower_goodie_block) {
                    Block* b = new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this, 'f');
                    m_actors.push_back(b);
                }
                if (ge == Level::star_goodie_block) {
                    Block* b = new Block(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this, 's');
                    m_actors.push_back(b);
                }
                if (ge == Level::koopa) {
                    Koopa* k = new Koopa(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(k);
                }
                if (ge == Level::goomba) {
                    Goomba* g = new Goomba(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(g);
                }
                if (ge == Level::piranha) {
                    Piranha* p = new Piranha(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(p);
                }
                if (ge == Level::mario) {
                    Mario* m = new Mario(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, this);
                    m_actors.push_back(m);
                }
            }
        }

    }
    return true;
}

//Init function as required by spec. Initializes any variables not initialized by constructor or other functions. 
//Allocates a Peach object and inserts all other game actors into the game world
int StudentWorld::init()
{
    //Generating string to load level
    ostringstream s;
    s << "level" << setw(2);
    s.fill('0');
    s << getLevel() << ".txt";
    //Loading level with the generated level string
    if (loadLevel(s.str())) {
        //If successful return continue
        return GWSTATUS_CONTINUE_GAME;
    }
    //If level loading error return level error
    return GWSTATUS_LEVEL_ERROR;
}

//Informs the StudentWorld that the level was completed
bool StudentWorld::setNextLevel() {
    m_levelFinished = true;
    return m_levelFinished;
}

//Informs the StudentWorld that the game was won
bool StudentWorld::wonGame() {
    m_won = true;
    return m_won;
}

//Move function as required by the spec. Function is called for each iteration of the game to update the screen. First prompts all
//actors to doSomething(). If peach has died, then play the death sound and return that the player has died. If peach has finished the level
//or won, return the relevant status. Delete any actors that are dead. Then render the game text at the top of the screen. If successful return status.
int StudentWorld::move()
{
    //Iterates through all actors and prompts them to doSomething.
    list<Actor*>::iterator iter = m_actors.begin();
    while (iter != m_actors.end()) {
        (*iter)->doSomething();
        iter++;
    }
    //If peach has died after game action, play sound and return death status.
    if (!m_peach->getStatus()) {
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    //If peach has reached the flag, play sound and return finished status
    if (m_levelFinished) {
        playSound(SOUND_FINISHED_LEVEL);
        m_levelFinished = false;
        return GWSTATUS_FINISHED_LEVEL;
    }
    //If peach has reached the mario, play sound and return win status
    if (m_won) {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    //Iterate through all actors to check if they are now dead. If so, deallocate the actor and remove them from the list of actors.
    iter = m_actors.begin();
    while (iter != m_actors.end()) {
        if (!(*iter)->getStatus()) {
            delete* iter;
            iter = m_actors.erase(iter);
        }
        else {
            iter++;
        }
    }
    //Update the text on the top of the screen
    updateStatus();
    //Return the successful continue message
    return GWSTATUS_CONTINUE_GAME;
}

//Updates the status of the text at the top of the screen by looking at the lives of the player, the score of the player, and the status of peach.
bool StudentWorld::updateStatus() {
    ostringstream s;
    //Sets the lives of the player, fills the level of the player in, fills the points of the player.
    s << "Lives: " << getLives() << "  Level: " << setw(2);
    s.fill('0');
    s << getLevel() << "  Points: " << setw(6);
    s.fill('0');
    s << getScore();
    //Includes peach's powerups in the specified order
    if (m_peach->getInvincible()) {
        s << " StarPower!";
    }
    if (m_peach->getShoot()) {
        s << " ShootPower!";
    }
    if (m_peach->getJump()) {
        s << " JumpPower!";
    }
    //Renders the gametext with the gameworld provided function
    setGameStatText(s.str());
    return true;
}

//CleanUp function as required by the spec. Deletes all the active members to prevent memory leaks.
void StudentWorld::cleanUp()
{
    //Iterates through actors deleting them and erasing them from the list
    list<Actor*>::iterator iter = m_actors.begin();
    while (iter != m_actors.end()) {
        delete *iter;
        iter = m_actors.erase(iter);
    }
}

//Returns pointer to the current peach actor.
Peach* StudentWorld::getPeach() {
    return m_peach;
}

//Student World destructor. Destroys all dynamically allocated actors by calling the cleanUp function.
StudentWorld::~StudentWorld() {
    cleanUp();
}