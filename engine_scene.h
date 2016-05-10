/**
 *
 * @project Arkanoid
 * @brief EngineScene Header
 * @author Toni Marquez
 *
 **/

#ifndef __ENGINESCENE_H__
#define __ENGINESCENE_H__ 1

#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#define WIN32
#include <ESAT_extra/chipmunk/chipmunk.h>
#include <ESAT_extra/imgui.h>

#include "lua.hpp"
#include "luawrapper.h"
#include "gtmath.h"
#include "text.h"
#include "sprite.h"
#include "gameobject2d.h"

#define SINGLETON GameManager::instance()
#define BAR_TAG 1
#define BALL_TAG 2
#define BRICK_TAG 3
#define WALL_TAG 4
#define LIMIT_TAG 5

static enum GameStatus {
  kGameStatus_None = 0,
  kGameStatus_Start,
  kGameStatus_Playing,
  kGameStatus_Finished
};

class EngineScene {

  public:

    /// constructor
    EngineScene();

    /** settings **/
    void initMap();
    void initTexts();
    void levelDump(unsigned short int level);

    /// init values
    void init();

    /** input functions **/
    void inputBar();

    /** update functions **/
    void updateScene();
    void updateBar();
    void updateBall();
    void updateBricks();
    void checkStatus();

    /** render functions **/
    void renderScenario();
    void renderLifes();

    /** GUI **/
    void HUD();
    void debug();

    /** game flow **/
    void input();
    void update(const double delta_time);
    void render();

    /** setters **/
    void set_levelNum(unsigned short int level);
    void set_scoreAmount(unsigned short int score);

    /** reseters **/
    void resetLevel();
    void resetGame();

    /**
     * @brief teleport an object to a specified position able to put there
              visible or not
     * @param const gtmath::Vec3 position, const bool visible
     * @return void
     **/
    void teleportObject(GameObject2D* object,
                        const gtmath::Vec3 position,
                        const bool visible);

    /**
     * @brief play a sound sample with a specified volume
     * @param const unsigned short int sound_num, const float volume
     * @return void
     **/
    void playAudio(const unsigned short int sound_num, const float volume);

    /// destructor
    ~EngineScene();

    /// public consts
    static const unsigned short int kNumLevels = 3;
    static const unsigned short int kGridCols = 10;
    const float kBarSpeed = 500.0f;

  private:

    /// copy constructor
    EngineScene(const EngineScene& copy);
    EngineScene operator=(const EngineScene& copy);

    /// private vars
    GameStatus game_status_;
    cpSpace* space_;
    GameObject2D* bar_;
    GameObject2D* ball_;
    GameObject2D* wall_[4];
    GameObject2D** bricks_;
    Text* level_;
    Text* score_;
    unsigned short int updating_; // 0 = not update, 1 = score++, 2 = life--
    unsigned short int total_levels_;
    unsigned short int current_level_;
    unsigned short int life_num_;
    unsigned short int score_amount_;
    unsigned short int brick_num_;
    unsigned short int* grid_;
    float ball_speed_;
    bool is_joint_;
};

#endif
