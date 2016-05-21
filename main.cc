/**
 *
 * @project Arkanoid
 * @brief Main
 * @author Toni Marquez
 * @fixes ! ball bounce with bar
 *        ! invisible bricks
 *        > bricks appear at 0,0
 *        > struct instead of bool for handler (+ check bricks remaining)
 *        / joints
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

#define GAMEMANAGER GameManager::instance()

void LuaConfig(){

  LuaWrapper lua;
  lua.init("config.lua");

  if (!GAMEMANAGER.debug_mode_){

    GAMEMANAGER.init(lua.getGlobalNumber("kNormalWindowWidth"),
                   lua.getGlobalNumber("kNormalWindowHeight"),
                   lua.getGlobalNumber("kSleepTime"));
  }
  else {

    GAMEMANAGER.init(lua.getGlobalNumber("kDebugWindowWidth"),
                   lua.getGlobalNumber("kDebugWindowHeight"),
                   lua.getGlobalNumber("kSleepTime"));
  }
}

int ESAT::main(int argc, char** argv){

  /// check for 'debug mode'
  if (argv[1] != NULL && !strncmp(argv[1], "-debug\0", strlen(argv[1]))){
    GAMEMANAGER.debug_mode_ = true;
    printf("DEBUG MODE ON\n");
  }

  srand(time(NULL));

  /// load init config from lua file
  LuaConfig();

  /// game window
  ESAT::WindowInit(GAMEMANAGER.stageWidth(), GAMEMANAGER.stageHeight());
  ESAT::WindowSetMouseVisibility(true);

  /// init scene
  GAMEMANAGER.engine_scene_->init();

  /// game loop
  while (ESAT::WindowIsOpened() &&
         !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)){

    static double last_time = ESAT::Time();
    double tick = ESAT::Time();
    double delta_time = tick - last_time;

    GAMEMANAGER.engine_scene_->input();
    GAMEMANAGER.engine_scene_->update(delta_time);
    GAMEMANAGER.engine_scene_->render();

    double sleep = GAMEMANAGER.sleepMS() - (ESAT::Time() - tick);
    if (sleep > 0.0f){ ESAT::Sleep(sleep); }
    last_time = tick;
  }

  ESAT::WindowDestroy();

  return 0;
}
