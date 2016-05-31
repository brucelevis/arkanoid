/**
 *
 * @project Arkanoid
 * @brief EngineScene Class
 * @author Toni Marquez
 *
 **/

#include "engine_scene.h"
#include "game_manager.h"
#include "audio_manager.h"

/// collision handler
cpBool Collision(cpArbiter *arbiter, cpSpace *space, void *data) {

  cpShape* a = NULL;
  cpShape* b = NULL;
  GameState* game_state = (GameState*)data;

  cpArbiterGetShapes(arbiter, &a, &b);

  /*
  */
  printf("COLLISION %d %d\n",
         cpShapeGetCollisionType(a),
         cpShapeGetCollisionType(b));

  // brick collision
  for (unsigned short int i = 0; i < game_state->bricks_amount_; i++){
    if (game_state->bricks_[i].handle_->tag() == cpShapeGetCollisionType(a) ||
        game_state->bricks_[i].handle_->tag() == cpShapeGetCollisionType(b)){

      if (game_state->bricks_[i].type_ == 2){
        game_state->bricks_[i].handle_->set_sprite(
            "data/assets/sprites/brick8.png");
      }
      game_state->bricks_[i].type_--;
      if (game_state->bricks_[i].type_ < 1){
        game_state->bricks_[i].must_die_ = true;
      }
      game_state->updating_ = 1;
      return cpTrue;
    }
  }

  // limit collision
  if (cpShapeGetCollisionType(a) == LIMIT_TAG ||
      cpShapeGetCollisionType(b) == LIMIT_TAG){

    if (!game_state->godmode_){ game_state->updating_ = 2; }
    return cpTrue;
  }

  // wall collision && bar center collision
  if (cpShapeGetCollisionType(a) == WALL_TAG ||
      cpShapeGetCollisionType(a) == CBAR_TAG ||
      cpShapeGetCollisionType(b) == WALL_TAG ||
      cpShapeGetCollisionType(b) == CBAR_TAG){

    game_state->updating_ = 3;
    return cpTrue;
  }

  // bar border collision
  if (cpShapeGetCollisionType(a) == LBAR_TAG ||
      cpShapeGetCollisionType(b) == LBAR_TAG){

    game_state->updating_ = 4;
    return cpTrue;
  }
  else if (cpShapeGetCollisionType(a) == RBAR_TAG ||
           cpShapeGetCollisionType(b) == RBAR_TAG){

    game_state->updating_ = 5;
    return cpTrue;
  }

  /*
  // powerup collision
  if (cpShapeGetCollisionType(a) == POWERUP_TAG){ game_state->updating_ = 6; }
  else if (cpShapeGetCollisionType(b) == POWERUP_TAG){
    game_state->updating_ = 6;
  }
  */

  return cpFalse;
}

/// constructor
EngineScene::EngineScene() {

  game_state_.space_ = cpSpaceNew();
  game_state_.cbar_ = new GameObject2D();
  game_state_.lbar_ = new GameObject2D();
  game_state_.rbar_ = new GameObject2D();
  game_state_.ball_ = new GameObject2D();
  for (unsigned short int i = 0; i < 4; i++){
    game_state_.walls_[i] = new GameObject2D();
  }
  game_state_.bricks_amount_ = 0;
  game_state_.updating_ = 0;
  game_state_.godmode_ = false;
  game_state_.freemode_ = false;
  game_state_.drawcolliders_ = false;
  game_status_ = kGameStatus_None;
  gamepad_ = nullptr;
  lua_ = nullptr;
  level_ = new Text();
  score_ = new Text();
  life_ = new Sprite();
  bar_velocity_ = { 0.0f, 0.0f, 0.0f };
  total_levels_ = 0;
  current_level_ = 0;
  lifes_amount_ = 0;
  score_amount_ = 0;
  bar_max_speed_ = 0.0f;
  bar_speed_ = 0.0f;
  bar_friction_ = 0.0f;
  ball_speed_ = 0.0f;
  is_joint_ = false;
}

/** settings **/
void EngineScene::initMap() {

  // walls (up, down, left, right)
  game_state_.walls_[0]->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.walls_[0]->addBodyBox(
      "data/assets/sprites/wall_h.png",
      { 400.0f, 90.0f, 1.0f },
      lua_->getNumberFromTable("wall_settings", "mass"),
      lua_->getNumberFromTable("wall_settings", "friction"));
  game_state_.walls_[0]->set_elasticity(
      lua_->getNumberFromTable("wall_settings", "elasticity"));
  game_state_.walls_[0]->set_tag(WALL_TAG);

  game_state_.walls_[1]->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.walls_[1]->addBodyBox(
      "data/assets/sprites/wall_h.png",
      { 400.0f, 770.0f, 1.0f },
      lua_->getNumberFromTable("wall_settings", "mass"),
      lua_->getNumberFromTable("wall_settings", "friction"));
  game_state_.walls_[1]->set_elasticity(
      lua_->getNumberFromTable("wall_settings", "elasticity"));
  game_state_.walls_[1]->set_tag(LIMIT_TAG);

  game_state_.walls_[2]->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.walls_[2]->addBodyBox(
      "data/assets/sprites/wall_v.png",
      { 30.0f, 430.0f, 1.0f },
      lua_->getNumberFromTable("wall_settings", "mass"),
      lua_->getNumberFromTable("wall_settings", "friction"));
  game_state_.walls_[2]->set_elasticity(
      lua_->getNumberFromTable("wall_settings", "elasticity"));
  game_state_.walls_[2]->set_tag(WALL_TAG);

  game_state_.walls_[3]->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.walls_[3]->addBodyBox(
      "data/assets/sprites/wall_v.png",
      { 770.0f, 430.0f, 1.0f },
      lua_->getNumberFromTable("wall_settings", "mass"),
      lua_->getNumberFromTable("wall_settings", "friction"));
  game_state_.walls_[3]->set_elasticity(
      lua_->getNumberFromTable("wall_settings", "elasticity"));
  game_state_.walls_[3]->set_tag(WALL_TAG);

  // bar center
  game_state_.cbar_->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.cbar_->addBodyBox(
      "data/assets/sprites/cbar.png",
      { lua_->getNumberFromTable("bar_settings", "cbar_x"),
        lua_->getNumberFromTable("bar_settings", "cbar_y"),
        1.0f },
      lua_->getNumberFromTable("bar_settings", "mass"),
      lua_->getNumberFromTable("bar_settings", "friction"));
  game_state_.cbar_->set_elasticity(
      lua_->getNumberFromTable("bar_settings", "elasticity"));
  game_state_.cbar_->set_infinity(
      lua_->getBooleanFromTable("bar_settings", "infinity"));
  game_state_.cbar_->set_tag(CBAR_TAG);

  // bar border left
  game_state_.lbar_->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.lbar_->addBodyBox(
      "data/assets/sprites/bbar.png",
      { lua_->getNumberFromTable("bar_settings", "lbar_x"),
        lua_->getNumberFromTable("bar_settings", "cbar_y"),
        1.0f },
      lua_->getNumberFromTable("bar_settings", "mass"),
      lua_->getNumberFromTable("bar_settings", "friction"));
  game_state_.lbar_->set_elasticity(
      lua_->getNumberFromTable("bar_settings", "elasticity"));
  game_state_.lbar_->set_infinity(
      lua_->getBooleanFromTable("bar_settings", "infinity"));
  game_state_.lbar_->set_tag(LBAR_TAG);

  // bar border right
  game_state_.rbar_->init(game_state_.space_, 1.0f, 1.0f, kBodyKind_Kinematic);
  game_state_.rbar_->addBodyBox(
      "data/assets/sprites/bbar.png",
      { lua_->getNumberFromTable("bar_settings", "rbar_x"),
        lua_->getNumberFromTable("bar_settings", "cbar_y"),
        1.0f },
      lua_->getNumberFromTable("bar_settings", "mass"),
      lua_->getNumberFromTable("bar_settings", "friction"));
  game_state_.rbar_->set_elasticity(
      lua_->getNumberFromTable("bar_settings", "elasticity"));
  game_state_.rbar_->set_infinity(
      lua_->getBooleanFromTable("bar_settings", "infinity"));
  game_state_.rbar_->set_tag(RBAR_TAG);

  bar_max_speed_ = lua_->getNumberFromTable("bar_settings", "max_speed");
  bar_friction_ = lua_->getNumberFromTable("bar_settings", "air_friction");

  // ball
  game_state_.ball_->init(game_state_.space_);
  #if 1 // instantiate as a box
  game_state_.ball_->addBodyBox(
      "data/assets/sprites/ball.png",
      { lua_->getNumberFromTable("ball_settings", "x"),
        lua_->getNumberFromTable("ball_settings", "y"),
        1.0f },
      lua_->getNumberFromTable("ball_settings", "mass"),
      lua_->getNumberFromTable("ball_settings", "friction"));
  #else // instantiate as a circle
  game_state_.ball_->addBodyCircle(
    "data/assets/sprites/ball.png",
    100,
    10.0f,
    { lua_->getNumberFromTable("ball_settings", "x"),
      lua_->getNumberFromTable("ball_settings", "y"),
      1.0f },
    lua_->getNumberFromTable("ball_settings", "mass"),
    lua_->getNumberFromTable("ball_settings", "friction"));
  #endif
  game_state_.ball_->set_elasticity(
      lua_->getNumberFromTable("ball_settings", "elasticity"));
  game_state_.ball_->set_infinity(
      lua_->getBooleanFromTable("ball_settings", "infinity"));
  game_state_.ball_->set_tag(BALL_TAG);

  ball_speed_ = lua_->getNumberFromTable("ball_settings", "speed");

  // settings
  total_levels_ = lua_->getGlobalNumber("kTotalLevels");
  current_level_ = 1;
  lifes_amount_ = 3;
  is_joint_ = true;
  game_status_ = kGameStatus_Start;
}

void EngineScene::initTexts() {

  level_->init("LEVEL 1\0", { 450.0f, 60.0f });
  score_->init("SCORE 0\0", { 620.0f, 60.0f });
}

void EngineScene::initSprites() {

  life_->init("data/assets/sprites/bar.png");
  life_->set_scale({ 0.5f, 0.5f, 1.0f });
}

void EngineScene::initBrick(unsigned short int index,
                            unsigned short int x,
                            unsigned short int y,
                            unsigned short int kind) {

  game_state_.bricks_[index].handle_ = new GameObject2D();
  game_state_.bricks_[index].handle_->init(game_state_.space_,
                                           1.0f,
                                           1.0f,
                                           kBodyKind_Kinematic);
  std::string buffer;
  buffer = "data/assets/sprites/brick" + std::to_string(kind) + ".png";
  game_state_.bricks_[index].handle_->addBodyBox(
      buffer.c_str(),
      { x, y, 1.0f },
      lua_->getNumberFromTable("brick_settings", "mass"),
      lua_->getNumberFromTable("brick_settings", "friction"));
  game_state_.bricks_[index].handle_->set_elasticity(
      lua_->getNumberFromTable("brick_settings", "elasticity"));
  if (kind == 7){ game_state_.bricks_[index].type_ = 2; }
  else { game_state_.bricks_[index].type_ = 1; }
  game_state_.bricks_[index].is_active_ = true;
  game_state_.bricks_[index].must_die_ = false;
  game_state_.bricks_[index].handle_->set_tag(index + 10);
}

void EngineScene::levelDump(unsigned short int level) {

  std::string buffer;
  buffer = "level" + std::to_string(level);
  set_levelNum(lua_->getIntegerFromTableByIndex(buffer.c_str(), 0));
  game_state_.bricks_amount_ = lua_->getIntegerFromTableByIndex(
      buffer.c_str(), 1);

  std::vector<unsigned short int> grid_;
  game_state_.bricks_.resize(game_state_.bricks_amount_);
  for (unsigned short int i = 0; i < kGridCols * kGridRows; i++){
    grid_.push_back(lua_->getIntegerFromTableByIndex(buffer.c_str(), i + 2));
  }

  short int index = 0;
  float x_offset = 170.0f;
  float y_offset = 200.0f;
  for (unsigned short int i = 0; i < kGridCols * kGridRows; i++){
    if (i % kGridCols == 0 && i != 0){
      x_offset = 170.0f;
      y_offset += 30.0f;
    }
    if (grid_[i] != 0){
      initBrick(index, x_offset, y_offset, grid_[i]);
      index++;
    }
    x_offset += 50.0f;
  }
}

/// init values
void EngineScene::init() {

  // lua init
  lua_ = new LuaWrapper();
  lua_->init("config.lua");

  // set chipmunk space
  cpSpaceSetGravity(game_state_.space_, { 0.0f, 0.0f });
  cpSpaceSetDamping(game_state_.space_, 1.0f);

  // register collider listener
  cpCollisionHandler* handler = cpSpaceAddDefaultCollisionHandler(
      game_state_.space_);
  handler->beginFunc = Collision;
  handler->userData = &game_state_;

  // prepare gamepad
  gamepad_ = new Gamepad(0);
  gamepad_->update();
  if (gamepad_->isConnected()){ printf("gamepad is connected\n"); }
  else { printf("gamepad is not connected\n"); }

  // generate elements
  initMap();
  initTexts();
  initSprites();
  levelDump(1);

  AUDIOMANAGER.playFX(0, 1.0f);
}

//-------------------------------------------------------------------------//
//                                  INPUT                                  //
//-------------------------------------------------------------------------//
void EngineScene::input() {

  const float kSpeedIncrease = 25.0f;
  const float kFreeModeForce = 300.0f;

  switch (game_status_){
    case kGameStatus_Start: {

      // using gamepad
      if (gamepad_->isConnected()){
        if (gamepad_->isButtonPressed(Gamepad::A)){
          gtmath::Vec3 ball_velocity = (gtmath::Vec3Right() - gtmath::Vec3Up()) *
                                       ball_speed_;
          game_state_.ball_->set_velocity(ball_velocity);

          is_joint_ = false;
          game_status_ = kGameStatus_Playing;
        }
        else if (gamepad_->getLStickPosition().x != 0.0f){
          float speed = bar_max_speed_ * gamepad_->getLStickPosition().x;
          bar_velocity_ = gtmath::Vec3Right() * speed;
        }
        else { bar_velocity_ = bar_velocity_ * bar_friction_; }
      }
      // using keyboard
      else {
        if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Space)){
          gtmath::Vec3 ball_velocity = (gtmath::Vec3Right() - gtmath::Vec3Up()) *
                                       ball_speed_;
          game_state_.ball_->set_velocity(ball_velocity);

          is_joint_ = false;
          game_status_ = kGameStatus_Playing;
        }
        else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Left)){
          if (bar_speed_ < bar_max_speed_){ bar_speed_ += kSpeedIncrease; }
          bar_velocity_ = gtmath::Vec3Right() * -bar_speed_;
        }
        else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Right)){
          if (bar_speed_ < bar_max_speed_){ bar_speed_ += kSpeedIncrease; }
          bar_velocity_ = gtmath::Vec3Right() * bar_speed_;
        }
        else {
          bar_velocity_ = bar_velocity_ * bar_friction_;
          if (bar_speed_ > 0.0f){ bar_speed_ -= kSpeedIncrease; }
        }
      }

      game_state_.cbar_->set_velocity(bar_velocity_);

    } break;

    case kGameStatus_Playing: {

      if (game_state_.freemode_){

        if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Left)){
          game_state_.ball_->addForce(gtmath::Vec3Right() * -kFreeModeForce);
        }
        else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Right)){
          game_state_.ball_->addForce(gtmath::Vec3Right() * kFreeModeForce);
        }
        else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Up)){
          game_state_.ball_->addForce(gtmath::Vec3Up() * -kFreeModeForce);
        }
        else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Down)){
          game_state_.ball_->addForce(gtmath::Vec3Up() * kFreeModeForce);
        }
      }
      else {

        // using gamepad
        if (gamepad_->isConnected()){
          if (gamepad_->isButtonPressed(Gamepad::A)){
            //!!! powerup reserved
          }
          else if (gamepad_->getLStickPosition().x != 0.0f){
            float speed = bar_max_speed_ * gamepad_->getLStickPosition().x;
            bar_velocity_ = gtmath::Vec3Right() * speed;
          }
          else { bar_velocity_ = bar_velocity_ * bar_friction_; }
        }
        // using keyboard
        else {
          if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Space)){
            //!!! powerup reserved
          }
          else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Left)){
            if (bar_speed_ < bar_max_speed_){ bar_speed_ += kSpeedIncrease; }
            bar_velocity_ = gtmath::Vec3Right() * -bar_speed_;
          }
          else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Right)){
            if (bar_speed_ < bar_max_speed_){ bar_speed_ += kSpeedIncrease; }
            bar_velocity_ = gtmath::Vec3Right() * bar_speed_;
          }
          else {
            bar_velocity_ = bar_velocity_ * bar_friction_;
            if (bar_speed_ > 0.0f){ bar_speed_ -= kSpeedIncrease; }
          }
        }

        game_state_.cbar_->set_velocity(bar_velocity_);
      }

    } break;

    case kGameStatus_Finished: {

      if (gamepad_->isConnected()){
        if (gamepad_->isButtonPressed(Gamepad::A)){
          resetGame(1);
        }
      }
      else {
        if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Enter)){
          resetGame(1);
        }
      }

    } break;
  }
}

//-------------------------------------------------------------------------//
//                                 UPDATE                                  //
//-------------------------------------------------------------------------//
void EngineScene::updateScene() {

  switch (game_state_.updating_) {
    // score
    case 1: {
      unsigned short int sample = (rand() % 3) + 4;
      AUDIOMANAGER.playFX(sample, 1.0f);
      for (unsigned short int i = 0; i < game_state_.bricks_.size(); i++){
        if (game_state_.bricks_[i].must_die_){
          game_state_.bricks_[i].must_die_ = false;
          game_state_.bricks_[i].is_active_ = false;
          game_state_.bricks_[i].handle_->set_position(
              { game_state_.bricks_[i].handle_->position().x - 1000.0f,
                game_state_.bricks_[i].handle_->position().y,
                1.0f });
          score_amount_ += 100;
        }
      }
      set_scoreAmount(score_amount_);
      game_state_.updating_ = 0;
    } break;
    // die
    case 2: {
      AUDIOMANAGER.playFX(3, 1.0f);
      lifes_amount_--;
      resetLevel();
      game_state_.updating_ = 0;
    } break;
    // bounce
    case 3: {
      AUDIOMANAGER.playFX(1, 1.0f);
      game_state_.updating_ = 0;
    } break;
    case 4: {
      AUDIOMANAGER.playFX(1, 1.0f);
      game_state_.ball_->set_velocity({ -ball_speed_,
                                        game_state_.ball_->velocity().y,
                                        0.0f });
      game_state_.updating_ = 0;
    } break;
    case 5: {
      AUDIOMANAGER.playFX(1, 1.0f);
      game_state_.ball_->set_velocity({ ball_speed_,
                                        game_state_.ball_->velocity().y,
                                        0.0f });
      game_state_.updating_ = 0;
    } break;
    // powerup
    case 6: {
      AUDIOMANAGER.playFX(2, 1.0f);
      game_state_.updating_ = 0;
    } break;
  }
}

void EngineScene::updateBar() {

  const float kLeftLimit = 75.0f;
  const float kRightLimit = 725.0f;

  // bar limits
  if (game_state_.cbar_->position().x < kLeftLimit){

    bar_velocity_.x *= -1;
    game_state_.cbar_->set_position({ kLeftLimit + 5,
                                     game_state_.cbar_->position().y,
                                     1.0f });
  }
  else if (game_state_.cbar_->position().x > kRightLimit){

    bar_velocity_.x *= -1;
    game_state_.cbar_->set_position({ kRightLimit - 5,
                                     game_state_.cbar_->position().y,
                                     1.0f });
  }

  // border bar position
  game_state_.lbar_->set_position({ game_state_.cbar_->position().x - 30.0f,
                                    game_state_.cbar_->position().y,
                                    1.0f });
  game_state_.rbar_->set_position({ game_state_.cbar_->position().x + 30.0f,
                                    game_state_.cbar_->position().y,
                                    1.0f });

  // update
  if (game_state_.cbar_ != nullptr){ game_state_.cbar_->update(); }
  if (game_state_.lbar_ != nullptr){ game_state_.lbar_->update(); }
  if (game_state_.rbar_ != nullptr){ game_state_.rbar_->update(); }
}

void EngineScene::updateBall() {

  if (is_joint_){
    game_state_.ball_->set_position({ game_state_.cbar_->position().x,
                                      game_state_.ball_->position().y,
                                      1.0f });
  }

  if (game_state_.ball_ != nullptr){ game_state_.ball_->update(); }
}

void EngineScene::updateBricks() {

  for (unsigned short int i = 0; i < game_state_.bricks_amount_; i++){
    if (game_state_.bricks_[i].handle_ != nullptr){
      game_state_.bricks_[i].handle_->update();
    }
  }
}

void EngineScene::update(const double delta_time) {

  // update gamepad
  gamepad_->update();

  // update elements
  updateScene();
  updateBar();
  updateBall();
  updateBricks();
  checkStatus();
  showInfo();

  // update chipmunk space
  cpSpaceStep(game_state_.space_, delta_time / 1000.0f);
}

//-------------------------------------------------------------------------//
//                                 RENDER                                  //
//-------------------------------------------------------------------------//
void EngineScene::renderScenario() {

  for(unsigned short int i = 0; i < 4; i++){
    if (game_state_.walls_[i] != nullptr){ game_state_.walls_[i]->update(); }
  }
}

void EngineScene::renderLifes() {

  float x_offest = 46.0f;

  for (unsigned short int i = 0; i < lifes_amount_; i++){
    life_->set_position({ x_offest, 50.0f, 1.0f });
    life_->render();
    x_offest += 70.0f;
  }
}

void EngineScene::render() {

  ESAT::DrawBegin();
  ESAT::DrawClear(0, 0, 0);

  renderScenario();
  renderLifes();
  HUD();
  debug();

  ESAT::DrawEnd();
  ESAT::WindowFrame();
}

/** GUI **/
void EngineScene::HUD() {

  level_->render();
  score_->render();
}

void EngineScene::debug() {

  if (GAMEMANAGER.debug_mode_){

    // game state get values
    int level = current_level_;
    int lifes = lifes_amount_;
    int bricks = game_state_.bricks_amount_;

    // space get values
    gtmath::Point space_gravity = { cpSpaceGetGravity(game_state_.space_).x,
                                    cpSpaceGetGravity(game_state_.space_).y };
    float space_damping = cpSpaceGetDamping(game_state_.space_);

    // bar get values
    gtmath::Vec3 bar_position = game_state_.cbar_->position();
    gtmath::Vec3 bar_velocity = game_state_.cbar_->velocity();
    float bar_angle = game_state_.cbar_->angle();
    float bar_friction = game_state_.cbar_->friction();
    float bar_elasticity = game_state_.cbar_->elasticity();
    float bar_moment = game_state_.cbar_->moment();
    bool bar_infinity = game_state_.cbar_->infinity();

    // ball get values
    gtmath::Vec3 ball_position = game_state_.ball_->position();
    gtmath::Vec3 ball_velocity = game_state_.ball_->velocity();
    float ball_angle = game_state_.ball_->angle();
    float ball_mass = game_state_.ball_->mass();
    float ball_friction = game_state_.ball_->friction();
    float ball_elasticity = game_state_.ball_->elasticity();
    float ball_moment = game_state_.ball_->moment();
    bool ball_infinity = game_state_.ball_->infinity();

    // imgui interface
    ImGui::Begin("Debug Window");
    ImGui::Text("Debugger for Arkanoid");
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Mouse Position: (%g, %g)", io.MousePos.x, io.MousePos.y);
    // game info
    if (ImGui::CollapsingHeader("Game State")){
      bool godmode = game_state_.godmode_;
      ImGui::Checkbox("God Mode", &godmode);
      game_state_.godmode_ = godmode;
      ImGui::SameLine();
      bool freemode = game_state_.freemode_;
      ImGui::Checkbox("Free Mode", &freemode);
      game_state_.freemode_ = freemode;
      ImGui::SameLine();
      bool colliders = game_state_.drawcolliders_;
      ImGui::Checkbox("Draw Colliders", &colliders);
      game_state_.drawcolliders_ = colliders;
      ImGui::InputInt("Lifes", &lifes);
    }
    // space info
    if (ImGui::CollapsingHeader("Space Settings")){
      ImGui::DragFloat2("Space Gravity", &space_gravity.x);
      ImGui::SliderFloat("Space Damping", &space_damping, 0.0f, 1.0f);
    }
    // bar settings
    if (ImGui::CollapsingHeader("Bar Settings")){
      ImGui::DragFloat2("Bar Position", &bar_position.x);
      ImGui::DragFloat2("Bar Velocity", &bar_velocity.x);
      ImGui::SliderFloat("Bar Angle", &bar_angle, -(kPid / 2), (kPid / 2));
      ImGui::SliderFloat("Bar Friction", &bar_friction, 0.0f, 1.0f);
      ImGui::SliderFloat("Bar Elasticity", &bar_elasticity, 0.0f, 1.0f);
      ImGui::Checkbox("Bar Infinity", &bar_infinity);
      if (!bar_infinity){
        ImGui::SliderFloat("Bar Moment", &bar_moment, 0.0f, 1.0f);
      }
    }
    // ball settings
    if (ImGui::CollapsingHeader("Ball Settings")){
      ImGui::DragFloat2("Ball Position", &ball_position.x);
      ImGui::DragFloat2("Ball Velocity", &ball_velocity.x);
      ImGui::SliderFloat("Ball Angle", &ball_angle, -(kPid / 2), (kPid / 2));
      ImGui::SliderFloat("Ball Mass", &ball_mass, 0.1f, 20.0f);
      ImGui::SliderFloat("Ball Friction", &ball_friction, 0.0f, 1.0f);
      ImGui::SliderFloat("Ball Elasticity", &ball_elasticity, 0.0f, 1.0f);
      ImGui::Checkbox("Ball Infinity", &ball_infinity);
      if (!ball_infinity){
        ImGui::SliderFloat("Ball Moment", &ball_moment, 0.0f, 1.0f);
      }
    }
    // bricks settings
    if (ImGui::CollapsingHeader("Bricks Settings")){
      for (unsigned short int i = 0; i < game_state_.bricks_amount_; i++){
        if (game_state_.bricks_[i].is_active_){
          gtmath::Vec3 brick_position = game_state_.bricks_[i].handle_->position();
          gtmath::Vec3 brick_velocity = game_state_.bricks_[i].handle_->velocity();
          float brick_angle = game_state_.bricks_[i].handle_->angle();
          float brick_friction = game_state_.bricks_[i].handle_->friction();
          float brick_elasticity = game_state_.bricks_[i].handle_->elasticity();

          std::string name;
          name = "Brick" + std::to_string(i + 1);
          if (ImGui::TreeNode(name.c_str())){
            name = "Brick" + std::to_string(i + 1) + " Position";
            ImGui::DragFloat2(name.c_str(), &brick_position.x);
            name = "Brick" + std::to_string(i + 1) + " Velocity";
            ImGui::DragFloat2(name.c_str(), &brick_velocity.x);
            name = "Brick" + std::to_string(i + 1) + " Angle";
            ImGui::SliderFloat(name.c_str(), &brick_angle, -(kPid / 2), (kPid / 2));
            name = "Brick" + std::to_string(i + 1) + " Friction";
            ImGui::SliderFloat(name.c_str(), &brick_friction, 0.0f, 1.0f);
            name = "Brick" + std::to_string(i + 1) + " Elasticity";
            ImGui::SliderFloat(name.c_str(), &brick_elasticity, 0.0f, 1.0f);
            ImGui::TreePop();
          }

          game_state_.bricks_[i].handle_->set_position(brick_position);
          game_state_.bricks_[i].handle_->set_velocity(brick_velocity);
          game_state_.bricks_[i].handle_->set_angle(brick_angle);
          game_state_.bricks_[i].handle_->set_friction(brick_friction);
          game_state_.bricks_[i].handle_->set_elasticity(brick_elasticity);
        }
      }
    }
    if (ImGui::Button("Reset Level")){
      // reset space
      cpSpaceSetGravity(game_state_.space_, { 0.0f, 0.0f });
      cpSpaceSetDamping(game_state_.space_, 1.0f);

      // reset bar
      bar_position = { lua_->getNumberFromTable("bar_settings", "cbar_x"),
                       lua_->getNumberFromTable("bar_settings", "cbar_y"),
                       1.0 };
      bar_velocity = gtmath::Vec3Zero();
      bar_angle = 0.0f;
      bar_friction = lua_->getNumberFromTable("bar_settings", "friction");
      bar_elasticity = lua_->getNumberFromTable("bar_settings", "elasticity");
      bar_moment = lua_->getNumberFromTable("bar_settings", "moment");
      bar_infinity = lua_->getBooleanFromTable("bar_settings", "infinity");

      // reset ball
      ball_position = { lua_->getNumberFromTable("ball_settings", "x"),
                        lua_->getNumberFromTable("ball_settings", "y"),
                        1.0f };
      ball_velocity = gtmath::Vec3Zero();
      ball_angle = 0.0f;
      ball_mass = lua_->getNumberFromTable("ball_settings", "mass");
      ball_friction = lua_->getNumberFromTable("ball_settings", "friction");
      ball_elasticity = lua_->getNumberFromTable("ball_settings", "elasticity");
      ball_moment = lua_->getNumberFromTable("ball_settings", "moment");
      ball_infinity = lua_->getBooleanFromTable("ball_settings", "infinity");

      // reset control vars
      resetGame(level);
    }
    ImGui::SameLine();
    if (ImGui::Button("Next Level")){
      if (current_level_ < total_levels_){ nextLevel(); }
      else {
        current_level_ = 1;
        resetGame(current_level_);
      }
    }
    ImGui::End();
    ImGui::Render();

    // game state set values
    lifes_amount_ = lifes;
    if (game_state_.drawcolliders_){
      game_state_.cbar_->drawCollider(true);
      game_state_.lbar_->drawCollider(true);
      game_state_.rbar_->drawCollider(true);
      game_state_.ball_->drawCollider(true);
      for (unsigned short int i = 0; i < 4; i++){
        game_state_.walls_[i]->drawCollider(true);
      }
      for (unsigned short int i = 0; i < game_state_.bricks_.size(); i++){
        game_state_.bricks_[i].handle_->drawCollider(true);
      }
    }
    else {
      game_state_.cbar_->drawCollider(false);
      game_state_.lbar_->drawCollider(false);
      game_state_.rbar_->drawCollider(false);
      game_state_.ball_->drawCollider(false);
      for (unsigned short int i = 0; i < 4; i++){
        game_state_.walls_[i]->drawCollider(false);
      }
      for (unsigned short int i = 0; i < game_state_.bricks_.size(); i++){
        game_state_.bricks_[i].handle_->drawCollider(false);
      }
    }

    // space set values
    cpSpaceSetGravity(game_state_.space_, { space_gravity.x, space_gravity.y });
    cpSpaceSetDamping(game_state_.space_, space_damping);

    // bar set values
    game_state_.cbar_->set_position(bar_position);
    game_state_.cbar_->set_velocity(bar_velocity);
    game_state_.cbar_->set_angle(bar_angle);
    game_state_.cbar_->set_friction(bar_friction);
    game_state_.cbar_->set_elasticity(bar_elasticity);
    game_state_.cbar_->set_moment(bar_moment);
    game_state_.cbar_->set_infinity(bar_infinity);

    // ball set values
    game_state_.ball_->set_position(ball_position);
    game_state_.ball_->set_velocity(ball_velocity);
    game_state_.ball_->set_angle(ball_angle);
    game_state_.ball_->set_mass(ball_mass);
    game_state_.ball_->set_friction(ball_friction);
    game_state_.ball_->set_elasticity(ball_elasticity);
    game_state_.ball_->set_moment(ball_moment);
    game_state_.ball_->set_infinity(ball_infinity);
  }
}

/** checkers **/
void EngineScene::checkStatus() {

  if (lifes_amount_ < 1){

    teleportObject(game_state_.cbar_, { -100.0f, -100.0f, 1.0f }, false);
    teleportObject(game_state_.ball_, { -100.0f, -100.0f, 1.0f }, false);
    game_status_ = kGameStatus_Finished;
  }

  if (isLevelFinished()){
    if (current_level_ < total_levels_){
      nextLevel();
      game_status_ = kGameStatus_Start;
    }
    else {
      teleportObject(game_state_.cbar_, { -100.0f, -100.0f, 1.0f }, false);
      teleportObject(game_state_.ball_, { -200.0f, -200.0f, 1.0f }, false);
      game_status_ = kGameStatus_Finished;
    }
  }
}

const bool EngineScene::isLevelFinished() {

  for (unsigned short int i = 0; i < game_state_.bricks_amount_; i++){
    if (game_state_.bricks_[i].is_active_ == true){
      return false;
    }
  }

  return true;
}

void EngineScene::showInfo() {

  if (game_status_ == kGameStatus_Finished){

    Text game_over;
    Text total_score;

    std::string buffer;
    buffer = "TOTAL SCORE " + std::to_string(score_amount_);

    game_over.init("GAME OVER\0", { 268.0f, 420.0f }, 50);
    total_score.init(buffer.c_str(), { 296.0f, 460.0f });

    game_over.render();
    total_score.render();
  }
}

/** setters **/
void EngineScene::set_levelNum(unsigned short int level) {

  std::string buffer;
  buffer = "LEVEL " + std::to_string(level);

  level_->set_text(buffer.c_str());
}

void EngineScene::set_scoreAmount(unsigned short int score) {

  std::string buffer;
  buffer = "SCORE " + std::to_string(score);

  score_->set_text(buffer.c_str());
}

/** reseters **/
void EngineScene::resetBricks() {

  for (unsigned short int i = 0; i < game_state_.bricks_.size(); i++){
    game_state_.bricks_[i].handle_->set_position(
        { game_state_.bricks_[i].handle_->position().x - 1000.0f,
          game_state_.bricks_[i].handle_->position().y,
          1.0f });
    game_state_.bricks_[i].handle_->removeBody();
  }

  game_state_.bricks_.clear();
}

void EngineScene::resetLevel() {

  teleportObject(game_state_.cbar_,
                 { lua_->getNumberFromTable("bar_settings", "cbar_x"),
                   lua_->getNumberFromTable("bar_settings", "cbar_y"),
                   1.0f },
                 true);

  teleportObject(game_state_.ball_,
                 { lua_->getNumberFromTable("ball_settings", "x"),
                   lua_->getNumberFromTable("ball_settings", "y"),
                   1.0f },
                 true);

  AUDIOMANAGER.playFX(0, 1.0f);
  is_joint_ = true;
  game_status_ = kGameStatus_Start;
}

void EngineScene::nextLevel() {

  resetBricks();
  resetLevel();
  current_level_++;
  levelDump(current_level_);
}

void EngineScene::resetGame(unsigned short int level) {

  resetBricks();
  lifes_amount_ = 3;
  score_amount_ = 0;
  set_scoreAmount(0);
  levelDump(level);
  resetLevel();
}

/**
 * @brief teleport the ship to a specified position able to put there
          visible or not
 * @param const gtmath::Vec3 position, const bool visible
 * @return void
 **/
void EngineScene::teleportObject(GameObject2D* object,
                                 const gtmath::Vec3 position,
                                 const bool visible) {

  object->set_position(position);
  object->set_velocity(gtmath::Vec3Zero());
  object->set_angle(0.0f);
  object->set_visible(visible);
}

/// destructor
EngineScene::~EngineScene() {

  // delete global struct
  cpSpaceFree(game_state_.space_);
  delete game_state_.cbar_;
  delete game_state_.ball_;
  game_state_.cbar_ = nullptr;
  game_state_.ball_ = nullptr;
  for (unsigned short int i = 0; i < 4; i++){
    delete game_state_.walls_[i];
    game_state_.walls_[i] = nullptr;
  }

  // delete private vars
  delete lua_;
  delete level_;
  delete score_;
  delete life_;
  lua_ = nullptr;
  level_ = nullptr;
  score_ = nullptr;
  life_ = nullptr;
}
