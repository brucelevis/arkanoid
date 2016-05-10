/**
 *
 * @project Arkanoid
 * @brief GameManager Class
 * @author Toni Marquez
 *
 **/

#include "game_manager.h"

/// singleton
GameManager& GameManager::instance() {

  static GameManager* singleton = new GameManager();
  return *singleton;
}

/// constructor
GameManager::GameManager() {

  stage_width_ = 0;
  stage_height_ = 0;
  sleep_MS_ = 0.0f;
  debug_mode_ = false;
  engine_scene_ = nullptr;
}

/// copy constructor
GameManager::GameManager(const GameManager& copy) {

  stage_width_ = copy.stage_width_;
  stage_height_ = copy.stage_height_;
  sleep_MS_ = copy.sleep_MS_;
  debug_mode_ = copy.debug_mode_;
  engine_scene_ = copy.engine_scene_;
}

/// init values
void GameManager::init(const unsigned short int stage_width,
                       const unsigned short int stage_height,
                       const double sleep_MS) {

  stage_width_ = stage_width;
  stage_height_ = stage_height;
  sleep_MS_ = sleep_MS;
  engine_scene_ = new EngineScene();
}

/** getters **/
const unsigned short int GameManager::stageWidth() {

  return stage_width_;
}

const unsigned short int GameManager::stageHeight() {

  return stage_height_;
}

const double GameManager::sleepMS() {

  return sleep_MS_;
}

/// destructor
GameManager::~GameManager() {

  delete engine_scene_;
  engine_scene_ = nullptr;
}
