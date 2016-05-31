/**
 *
 * @project Arkanoid
 * @brief GameManager Header
 * @author Toni Marquez
 *
 **/

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__ 1

#include "engine_scene.h"

class GameManager {

  public:

    /// singleton
    static GameManager& instance();

    /// init values
    void init(const unsigned short int stage_width,
              const unsigned short int stage_height,
              const double sleep_MS);

    /** getters **/
    const unsigned short int stageWidth();
    const unsigned short int stageHeight();
    const double sleepMS();

    /// public vars
    bool debug_mode_;
    EngineScene* engine_scene_;

  private:

    /// constructor & destructor
    GameManager();
    ~GameManager();

    /// copy constructor
    GameManager(const GameManager& copy);
    GameManager operator=(const GameManager& copy);

    /// private vars
    unsigned short int stage_width_;
    unsigned short int stage_height_;
    double sleep_MS_;
};

#endif
