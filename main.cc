/**
 *
 * @project Arkanoid
 * @brief Main
 * @author Toni Marquez
 * @fixes ! ball movement
 *        ! brick remove on collision
 *        > no more collision handlers than the last
 *        - original sounds
 *
 **/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/time.h>

#include "lua.hpp"
#include "luawrapper.h"
#include "game_manager.h"

#define SINGLETON GameManager::instance()

void LuaConfig(){

  LuaWrapper lua;
  lua.init("config.lua");

  if (!SINGLETON.debug_mode_){

    SINGLETON.init(lua.getGlobalNumber("kNormalWindowWidth"),
                   lua.getGlobalNumber("kNormalWindowHeight"),
                   lua.getGlobalNumber("kSleepTime"));
  }
  else {

    SINGLETON.init(lua.getGlobalNumber("kDebugWindowWidth"),
                   lua.getGlobalNumber("kDebugWindowHeight"),
                   lua.getGlobalNumber("kSleepTime"));
  }
}

int ESAT::main(int argc, char** argv){

  /// check for 'debug mode'
  if (argv[1] != NULL && !strncmp(argv[1], "-debug\0", strlen(argv[1]))){
    SINGLETON.debug_mode_ = true;
    printf("DEBUG MODE ON\n");
  }

  srand(time(NULL));

  /// load init config from lua file
  LuaConfig();

  /// game window
  ESAT::WindowInit(SINGLETON.stageWidth(), SINGLETON.stageHeight());
  ESAT::WindowSetMouseVisibility(true);

  /// init scene
  SINGLETON.engine_scene_->init();

  /// game loop
  while (ESAT::WindowIsOpened() &&
         !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)){

    static double last_time = ESAT::Time();
    double tick = ESAT::Time();
    double delta_time = tick - last_time;

    SINGLETON.engine_scene_->input();
    SINGLETON.engine_scene_->update(delta_time);
    SINGLETON.engine_scene_->render();

    double sleep = SINGLETON.sleepMS() - (ESAT::Time() - tick);
    if (sleep > 0.0f){ ESAT::Sleep(sleep); }
    last_time = tick;
  }

  ESAT::WindowDestroy();

  return 0;
}
