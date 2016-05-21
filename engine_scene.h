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
#include "box.h"
#include "sprite.h"
#include "gameobject2d.h"

#define GAMEMANAGER GameManager::instance()
#define AUDIOMANAGER AudioManager::instance()
#define BAR_TAG 1
#define BALL_TAG 2
#define BRICK_TAG 3
#define WALL_TAG 4
#define LIMIT_TAG 5
#define POWERUP_TAG 6

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

    /** update functions **/
    void updateScene();
    void updateBar();
    void updateBall();
    void updateBricks();

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

    /** checkers **/
    void checkStatus();
    void showInfo();

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
    static const unsigned short int kGridRows = 7;

    /// public struct
    static struct GameState {

    };

    GameState game_state_;

  private:

    /// copy constructor
    EngineScene(const EngineScene& copy);
    EngineScene operator=(const EngineScene& copy);

    /// private vars
    GameStatus game_status_;
    cpSpace* space_;
    GameObject2D* bar_;
    GameObject2D* ball_;
    GameObject2D* walls_[4];
    GameObject2D* bricks_[kGridCols * kGridRows];
    Text* level_;
    Text* score_;
    gtmath::Vec3 bar_velocity_;
    // 0 = not update, 1 = score, 2 = die, 3 = bounce, 4 = powerup
    unsigned short int updating_;
    unsigned short int total_levels_;
    unsigned short int current_level_;
    unsigned short int lifes_amount_;
    unsigned short int score_amount_;
    unsigned short int bricks_amount_;
    float bar_max_speed_;
    float bar_speed_;
    float bar_friction_;
    float ball_speed_;
    bool is_joint_;
};

#endif
