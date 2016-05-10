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

  cpBody* body;
  cpShape* a = NULL;
  cpShape* b = NULL;
  unsigned short int* updating = (unsigned short int*)data;

  cpArbiterGetShapes(arbiter, &a, &b);

  printf("COLLISION %d %d\n",
         cpShapeGetCollisionType(a),
         cpShapeGetCollisionType(b));

  /*
  if (cpShapeGetCollisionType(a) == BRICK_TAG){
    body = cpShapeGetBody(a);
    cpBodyFree(body);
    *updating = 1;
  }
  if (cpShapeGetCollisionType(b) == BRICK_TAG){
    body = cpShapeGetBody(b);
    cpBodyFree(body);
    *updating = 1;
  }

  if (cpShapeGetCollisionType(a) == LIMIT_TAG){
    body = cpShapeGetBody(a);
    cpBodyFree(body);
    *updating = 2;
  }
  if (cpShapeGetCollisionType(b) == LIMIT_TAG){
    body = cpShapeGetBody(b);
    cpBodyFree(body);
    *updating = 2;
  }
  */

  return cpTrue;
}

/// constructor
EngineScene::EngineScene() {

  game_status_ = kGameStatus_None;
  space_ = cpSpaceNew();
  bar_ = new GameObject2D();
  ball_ = new GameObject2D();
  for (unsigned short int i = 0; i < 4; i++){
    wall_[i] = new GameObject2D();
  }
  bricks_ = nullptr;
  level_ = new Text();
  score_ = new Text();
  updating_ = 0;
  total_levels_ = 0;
  current_level_ = 0;
  life_num_ = 0;
  score_amount_ = 0;
  brick_num_ = 0;
  grid_ = nullptr;
  ball_speed_ = 0.0f;
  is_joint_ = false;
}

/** settings **/
void EngineScene::initMap() {

  LuaWrapper lua;
  lua.init("config.lua");

  // walls (up, down, left, right)
  wall_[0]->init(space_, 1.0f, 1.0f, false);
  wall_[0]->addBodySprite("data/assets/sprites/wall_h.png",
                          { 400.0f, 90.0f, 1.0f },
                          10.0f,
                          0.0f);
  wall_[0]->set_tag(WALL_TAG);

  wall_[1]->init(space_, 1.0f, 1.0f, false);
  wall_[1]->addBodySprite("data/assets/sprites/wall_h.png",
                          { 400.0f, 770.0f, 1.0f },
                          10.0f,
                          0.0f);
  wall_[1]->set_tag(LIMIT_TAG);

  wall_[2]->init(space_, 1.0f, 1.0f, false);
  wall_[2]->addBodySprite("data/assets/sprites/wall_v.png",
                          { 30.0f, 430.0f, 1.0f },
                          10.0f,
                          0.0f);
  wall_[2]->set_tag(WALL_TAG);

  wall_[3]->init(space_, 1.0f, 1.0f, false);
  wall_[3]->addBodySprite("data/assets/sprites/wall_v.png",
                          { 770.0f, 430.0f, 1.0f },
                          10.0f,
                          0.0f);
  wall_[3]->set_tag(WALL_TAG);

  // bar
  bar_->init(space_);
  bar_->addBodySprite("data/assets/sprites/bar.png",
                      { lua.getNumberFromTable("bar_settings", "x"),
                        lua.getNumberFromTable("bar_settings", "y"),
                        1.0f },
                      lua.getNumberFromTable("bar_settings", "mass"),
                      lua.getNumberFromTable("bar_settings", "friction"));
  bar_->set_elasticity(lua.getNumberFromTable("bar_settings", "elasticity"));
  bar_->set_infinity(lua.getBooleanFromTable("bar_settings", "infinity"));
  bar_->set_tag(BAR_TAG);

  // ball
  ball_->init(space_);
  ball_->addBodySprite("data/assets/sprites/ball.png",
                       { lua.getNumberFromTable("ball_settings", "x"),
                         lua.getNumberFromTable("ball_settings", "y"),
                         1.0f },
                       lua.getNumberFromTable("ball_settings", "mass"),
                       lua.getNumberFromTable("ball_settings", "friction"));
  ball_->set_elasticity(lua.getNumberFromTable("ball_settings", "elasticity"));
  ball_->set_infinity(lua.getBooleanFromTable("ball_settings", "infinity"));
  ball_->set_tag(BALL_TAG);

  ball_speed_ = lua.getNumberFromTable("ball_settings", "speed");

  // settings
  total_levels_ = lua.getGlobalNumber("kTotalLevels");
  current_level_ = 1;
  life_num_ = 3;
  is_joint_ = true;
  game_status_ = kGameStatus_Start;
}

void EngineScene::initTexts() {

  level_->init("LEVEL 1", { 450.0f, 60.0f });
  score_->init("SCORE          0\0", { 588.0f, 60.0f });
}

void EngineScene::levelDump(unsigned short int level) {

  char buffer[128];
  char number[8];
  sprintf(buffer, "level\0");
  sprintf(number, "%d", level);
  strcat(buffer, number);

  LuaWrapper lua;
  lua.init("config.lua");

  brick_num_ = lua.getIntegerFromTableByIndex(buffer, 0);
  bricks_ = (GameObject2D**)malloc(sizeof(GameObject2D) * brick_num_);
  grid_ = (unsigned short int*)malloc(sizeof(unsigned short int) * brick_num_);

  for (unsigned short int i = 0; i < brick_num_; i++){
    grid_[i] = lua.getIntegerFromTableByIndex(buffer, i + 1);
    bricks_[i] = nullptr;
  }

  float x_offset = 170.0f;
  float y_offset = 200.0f;
  for (unsigned short int i = 0; i < brick_num_; i++){
    if (i % kGridCols == 0 && i != 0){
      x_offset = 170.0f;
      y_offset += 30.0f;
    }
    if (grid_[i] != 0){
      bricks_[i] = new GameObject2D();
      bricks_[i]->init(space_, 1.0f, 1.0f, false);
      memset(buffer, 0, 128);
      memset(number, 0, 8);
      sprintf(buffer, "data/assets/sprites/brick");
      sprintf(number, "%d.png", grid_[i]);
      strcat(buffer, number);
      bricks_[i]->addBodySprite(buffer,
                                { x_offset, y_offset, 1.0f },
                                10.0f,
                                0.0f);
      bricks_[i]->set_tag(BRICK_TAG);
    }
    x_offset += 50.0f;
  }
}

/// init values
void EngineScene::init() {

  /// set chipmunk space
  cpSpaceSetGravity(space_, { 0.0f, 0.0f });
  cpSpaceSetDamping(space_, 1.0f);

  /// register collider listener
  cpCollisionHandler* handler = cpSpaceAddCollisionHandler(space_,
                                                           BALL_TAG,
                                                           BRICK_TAG);
  /*
  handler = cpSpaceAddCollisionHandler(space_, BALL_TAG, LIMIT_TAG);
  handler = cpSpaceAddCollisionHandler(space_, BALL_TAG, BAR_TAG);
  */
  handler->beginFunc = Collision;
  handler->userData = &updating_;

  /// generate elements
  initMap();
  initTexts();
  levelDump(1);
}

/** input functions **/
void EngineScene::inputBar() {

  if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Space)){
    gtmath::Vec3 velocity = (gtmath::Vec3Right() -
                             gtmath::Vec3Up()) *
                             ball_speed_;
    ball_->set_velocity(velocity);

    is_joint_ = false;
  }
  else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Left)){
    gtmath::Vec3 velocity = gtmath::Vec3Right() * -kBarSpeed;
    bar_->addForce(velocity);
  }
  else if (ESAT::IsSpecialKeyPressed(ESAT::kSpecialKey_Right)){
    gtmath::Vec3 velocity = gtmath::Vec3Right() * kBarSpeed;
    bar_->addForce(velocity);
  }
}

/** update functions **/
void EngineScene::updateScene() {

  switch (updating_) {
    case 1: {
      brick_num_--;
      score_amount_ += 100;
      set_scoreAmount(score_amount_);
      updating_ = 0;
    } break;
    case 2: {
      life_num_--;
      resetLevel();
      updating_ = 0;
    } break;
  }
}

void EngineScene::updateBar() {

  bar_->set_position({ bar_->position().x, 700.0f, bar_->position().z });
  bar_->update();
}

void EngineScene::updateBall() {

  if (is_joint_){

    ball_->set_position({ bar_->position().x,
                          ball_->position().y,
                          ball_->position().z });
  }

  ball_->set_angle(0.0f);
  ball_->update();
}

void EngineScene::updateBricks() {

  for (unsigned short int i = 0; i < brick_num_; i++){
    if (bricks_[i] != nullptr){ bricks_[i]->update(); }
  }
}

void EngineScene::checkStatus() {

  if (life_num_ < 1){ game_status_ = kGameStatus_Finished; }

  if (brick_num_ < 1){
    if (current_level_ < total_levels_){

      current_level_++;
      levelDump(current_level_);
      resetLevel();
    }
    else { game_status_ = kGameStatus_Finished; }
  }
}

/** render functions **/
void EngineScene::renderScenario() {

  for(unsigned short int i = 0; i < 4; i++){
    wall_[i]->update();
  }
}

void EngineScene::renderLifes() {

  float posx = 46.0f;

  for (unsigned short int i = 0; i < life_num_; i++){
    Sprite* lifes = new Sprite();
    lifes->init("data/assets/sprites/bar.png",
               { posx, 50.0f, 1.0f });
    lifes->set_scale({ 0.5f, 0.5f, 1.0f });
    lifes->render();
    posx += 70.0f;
  }
}

/* GUI */
void EngineScene::HUD() {

  level_->render();
  score_->render();
}

void EngineScene::debug() {

  if (SINGLETON.debug_mode_){

    LuaWrapper lua;
    lua.init("config.lua");

    // space get values
    gtmath::Point space_gravity = { cpSpaceGetGravity(space_).x,
                                    cpSpaceGetGravity(space_).y };
    float space_damping = cpSpaceGetDamping(space_);

    // bar get values
    gtmath::Vec3 bar_position = bar_->position();
    gtmath::Vec3 bar_velocity = bar_->velocity();
    float bar_angle = bar_->angle();
    float bar_mass = bar_->mass();
    float bar_friction = bar_->friction();
    float bar_elasticity = bar_->elasticity();
    float bar_moment = bar_->moment();
    bool bar_infinity = bar_->infinity();

    // ball get values
    gtmath::Vec3 ball_position = ball_->position();
    gtmath::Vec3 ball_velocity = ball_->velocity();
    float ball_angle = ball_->angle();
    float ball_mass = ball_->mass();
    float ball_friction = ball_->friction();
    float ball_elasticity = ball_->elasticity();
    float ball_moment = ball_->moment();
    bool ball_infinity = ball_->infinity();

    // imgui interface
    ImGui::Begin("Debug Window");
    ImGui::Text("Debugger for Arkanoid");
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Mouse Position: (%g, %g)", io.MousePos.x, io.MousePos.y);
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
      ImGui::SliderFloat("Bar Mass", &bar_mass, 0.1f, 20.0f);
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
    if (ImGui::Button("Reset Scene")){
      // reset space
      cpSpaceSetGravity(space_, { 0.0f, 0.0f });
      cpSpaceSetDamping(space_, 1.0f);

      // reset bar
      bar_position = { lua.getNumberFromTable("bar_settings", "x"),
                       lua.getNumberFromTable("bar_settings", "y"),
                       1.0 };
      bar_velocity = gtmath::Vec3Zero();
      bar_angle = 0.0f;
      bar_mass = lua.getNumberFromTable("bar_settings", "mass");
      bar_friction = lua.getNumberFromTable("bar_settings", "friction");
      bar_elasticity = lua.getNumberFromTable("bar_settings", "elasticity");
      bar_moment = lua.getNumberFromTable("bar_settings", "moment");
      bar_infinity = lua.getBooleanFromTable("bar_settings", "infinity");

      // reset ball
      ball_position = { lua.getNumberFromTable("ball_settings", "x"),
                        lua.getNumberFromTable("ball_settings", "y"),
                        1.0f };
      ball_velocity = gtmath::Vec3Zero();
      ball_angle = 0.0f;
      ball_mass = lua.getNumberFromTable("ball_settings", "mass");
      ball_friction = lua.getNumberFromTable("ball_settings", "friction");
      ball_elasticity = lua.getNumberFromTable("ball_settings", "elasticity");
      ball_moment = lua.getNumberFromTable("ball_settings", "moment");
      ball_infinity = lua.getBooleanFromTable("ball_settings", "infinity");

      // reset control vars
      is_joint_ = true;
      resetGame();
    }
    ImGui::End();
    ImGui::Render();

    // space set values
    cpSpaceSetGravity(space_, { space_gravity.x, space_gravity.y });
    cpSpaceSetDamping(space_, space_damping);

    // bar set values
    bar_->set_position(bar_position);
    bar_->set_velocity(bar_velocity);
    bar_->set_angle(bar_angle);
    bar_->set_mass(bar_mass);
    bar_->set_friction(bar_friction);
    bar_->set_elasticity(bar_elasticity);
    bar_->set_moment(bar_moment);
    bar_->set_infinity(bar_infinity);

    // ball set values
    ball_->set_position(ball_position);
    ball_->set_velocity(ball_velocity);
    ball_->set_angle(ball_angle);
    ball_->set_mass(ball_mass);
    ball_->set_friction(ball_friction);
    ball_->set_elasticity(ball_elasticity);
    ball_->set_moment(ball_moment);
    ball_->set_infinity(ball_infinity);
  }
}

/** game flow **/
//-------------------------------------------------------------------------//
//                                  INPUT                                  //
//-------------------------------------------------------------------------//
void EngineScene::input() {

  switch (game_status_){
    case kGameStatus_Start:
    case kGameStatus_Playing: { inputBar(); } break;
    case kGameStatus_Finished: {
      if (ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Enter)){ resetGame(); }
    } break;
  }
}

//-------------------------------------------------------------------------//
//                                 UPDATE                                  //
//-------------------------------------------------------------------------//
void EngineScene::update(const double delta_time) {

  updateBar();
  updateBall();
  updateBricks();

  if (game_status_ == kGameStatus_Finished){

    // !!! game over text
  }

  /// update chipmunk space
  cpSpaceStep(space_, delta_time / 1000.0f);
}

//-------------------------------------------------------------------------//
//                                 RENDER                                  //
//-------------------------------------------------------------------------//
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

/** setters **/
void EngineScene::set_levelNum(unsigned short int level) {

  char buffer[128];
  char number[8];

  sprintf(buffer, "LEVEL \0");
  sprintf(number, "%d", level);
  strcat(buffer, number);

  level_->set_text(buffer);
}

void EngineScene::set_scoreAmount(unsigned short int score) {

  char buffer[128];
  char number[8];

  sprintf(buffer, "SCORE          \0");
  sprintf(number, "%d", score);
  strcat(buffer, number);

  score_->set_text(buffer);
}

/** reseters **/
void EngineScene::resetLevel() {

  LuaWrapper lua;
  lua.init("config.lua");

  bar_->set_position({ lua.getNumberFromTable("bar_settings", "x"),
                       lua.getNumberFromTable("bar_settings", "y"),
                       1.0f });
  ball_->set_position({ lua.getNumberFromTable("ball_settings", "x"),
                        lua.getNumberFromTable("ball_settings", "y"),
                        1.0f });
  is_joint_ = true;
}

void EngineScene::resetGame() {

  current_level_ = 1;
  life_num_ = 3;

  set_levelNum(current_level_);
  set_scoreAmount(0);

  levelDump(current_level_);
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
  object->set_velocity({ 0.0f, 0.0f, 0.0f });
  object->set_angle(0.0f);
  object->set_visible(visible);
}

/**
 * @brief play a sound sample with a specified volume
 * @param const unsigned short int sound_num, const float volume
 * @return void
 **/
void EngineScene::playAudio(const unsigned short int sound_num,
                            const float volume) {

  int sample = AudioManager::instance().soloud_.play(
                   AudioManager::instance().fx_[sound_num]);
  AudioManager::instance().soloud_.setVolume(sample, volume);
}

/// destructor
EngineScene::~EngineScene() {

  cpSpaceFree(space_);
  delete bar_;
  delete ball_;
  delete bricks_;
  delete level_;
  delete score_;
  delete grid_;
  bar_ = nullptr;
  ball_ = nullptr;
  bricks_ = nullptr;
  level_ = nullptr;
  score_ = nullptr;
  grid_ = nullptr;
  for (unsigned short int i = 0; i < 4; i++){
    delete wall_[i];
    wall_[i] = nullptr;
  }
}
