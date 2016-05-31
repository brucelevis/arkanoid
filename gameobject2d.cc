/**
 *
 * @brief GameObject2D Class
 * @author Toni Marquez
 *
 **/

#include "gameobject2d.h"

/// constructor
GameObject2D::GameObject2D() {

  space_ = nullptr;
  body_ = nullptr;
  shape_ = nullptr;
  box_ = nullptr;
  poly_ = nullptr;
  sprite_ = nullptr;
  body_type_ = kBodyType_None;
  body_kind_ = kBodyKind_None;
  pointA_ = gtmath::Vec3Zero();
  pointB_ = gtmath::Vec3Zero();
  tag_ = 0;
  moment_ = 0.0f;
  has_sprite_ = false;
  is_visible_ = false;
  is_infinity_ = false;
}

/// init values
void GameObject2D::init(cpSpace* space,
                        const float mass,
                        const float moment,
                        const BodyKind body_kind) {

  space_ = space;
  body_kind_ = body_kind;
  moment_ = moment;

  switch (body_kind_){
    case kBodyKind_Dynamic: {
      body_ = cpSpaceAddBody(space_, cpBodyNew(mass, moment));
    } break;
    case kBodyKind_Kinematic: {
      body_ = cpSpaceAddBody(space_, cpBodyNewKinematic());
    } break;
    case kBodyKind_Static: {
      body_ = cpSpaceAddBody(space_, cpBodyNewStatic());
    } break;
  }

  is_visible_ = true;
}

/** add bodies **/
/// segment shape
void GameObject2D::addBodySegment(const gtmath::Vec3 pointA,
                                  const gtmath::Vec3 pointB,
                                  const float friction,
                                  const float radius,
                                  const float mass) {

  body_type_ = kBodyType_Segment;

  pointA_ = pointA;
  pointB_ = pointB;

  shape_ = cpSpaceAddShape(space_, cpSegmentShapeNew(body_,
                                                     { pointA_.x, pointA_.y },
                                                     { pointB_.x, pointB_.y },
                                                     radius));
  if (body_kind_ == kBodyKind_Dynamic){ cpShapeSetMass(shape_, mass); }
  cpShapeSetFriction(shape_, friction);
}

/// box shape
void GameObject2D::addBodyBox(const float width,
                              const float height,
                              const gtmath::Vec3 position,
                              const float mass,
                              const float friction,
                              const float radius) {

  body_type_ = kBodyType_Box;

  shape_ = cpSpaceAddShape(space_, cpBoxShapeNew(body_, width, height, radius));
  if (body_kind_ == kBodyKind_Dynamic){ cpShapeSetMass(shape_, mass); }
  cpShapeSetFriction(shape_, friction);
  cpBodySetPosition(body_, { position.x, position.y });

  box_ = new Box();
  box_->init(width, height);
}

void GameObject2D::addBodyBox(const char* path,
                              const gtmath::Vec3 position,
                              const float mass,
                              const float friction,
                              const float radius) {

  body_type_ = kBodyType_Box;
  has_sprite_ = true;

  sprite_ = new Sprite();
  sprite_->init(path, position);

  shape_ = cpSpaceAddShape(space_, cpBoxShapeNew(body_,
                                                 sprite_->width(),
                                                 sprite_->height(),
                                                 radius));
  if (body_kind_ == kBodyKind_Dynamic){ cpShapeSetMass(shape_, mass); }
  cpShapeSetFriction(shape_, friction);
  cpBodySetPosition(body_, { position.x, position.y });

  box_ = new Box();
  box_->init(sprite_->width(), sprite_->height());
}

/// polygon regular shape
void GameObject2D::addBodyCircle(const unsigned short int num_verts,
                                 const float size,
                                 const gtmath::Vec3 position,
                                 const float mass,
                                 const float friction,
                                 const float radius) {

  body_type_ = kBodyType_Polygon;

  cpVect* points = new cpVect[num_verts];

  for (unsigned short int i = 0; i < num_verts; i++){
    points[i].x = size * cos(2 * kPid * i / num_verts);
    points[i].y = size * sin(2 * kPid * i / num_verts);
  }

  shape_ = cpSpaceAddShape(space_, cpPolyShapeNewRaw(body_,
                                                     num_verts,
                                                     points,
                                                     radius));

  delete points;
  points = nullptr;

  if (body_kind_ == kBodyKind_Dynamic){ cpShapeSetMass(shape_, mass); }
  cpShapeSetFriction(shape_, friction);
  cpBodySetPosition(body_, { position.x, position.y });

  poly_ = new Poly();
  poly_->init(num_verts, size);
}

void GameObject2D::addBodyCircle(const char* path,
                                 const unsigned short int num_verts,
                                 const float size,
                                 const gtmath::Vec3 position,
                                 const float mass,
                                 const float friction,
                                 const float radius) {

  body_type_ = kBodyType_Polygon;
  has_sprite_ = true;

  sprite_ = new Sprite();
  sprite_->init(path, position);

  cpVect* points = new cpVect[num_verts];

  for (unsigned short int i = 0; i < num_verts; i++){
    points[i].x = size * cos(2 * kPid * i / num_verts);
    points[i].y = size * sin(2 * kPid * i / num_verts);
  }

  shape_ = cpSpaceAddShape(space_, cpPolyShapeNewRaw(body_,
                                                     num_verts,
                                                     points,
                                                     radius));

  delete points;
  points = nullptr;

  if (body_kind_ == kBodyKind_Dynamic){ cpShapeSetMass(shape_, mass); }
  cpShapeSetFriction(shape_, friction);
  cpBodySetPosition(body_, { position.x, position.y });

  poly_ = new Poly();
  poly_->init(num_verts, size);
}

/// polygon free shape
void GameObject2D::addBodyPoly(const unsigned short int num_verts,
                               const gtmath::Vec3* verts,
                               const gtmath::Vec3 position,
                               const float mass,
                               const float friction,
                               const float radius) {

  body_type_ = kBodyType_Polygon;

  cpVect* points = new cpVect[num_verts];

  for (unsigned short int i = 0; i < num_verts; i++){
    points[i].x = verts[i].x;
    points[i].y = verts[i].y;
  }

  shape_ = cpSpaceAddShape(space_, cpPolyShapeNewRaw(body_,
                                                     num_verts,
                                                     points,
                                                     radius));

  delete points;
  points = nullptr;

  if (body_kind_ == kBodyKind_Dynamic){ cpShapeSetMass(shape_, mass); }
  cpShapeSetFriction(shape_, friction);
  cpBodySetPosition(body_, { position.x, position.y });

  poly_ = new Poly();
  poly_->init(num_verts, verts);
}

/**
 * @brief update object position and render it
 * @param none
 * @return void
 **/
void GameObject2D::update() {

  if (body_ != nullptr){
    switch (body_type_){
      case kBodyType_Segment: {
        if (is_visible_){
          ESAT::DrawSetStrokeColor(255, 255, 255, 255);
          ESAT::DrawLine(pointA_.x, pointA_.y, pointB_.x, pointB_.y);
        }
      } break;
      case kBodyType_Box: {
        box_->set_position({ cpBodyGetPosition(body_).x,
                             cpBodyGetPosition(body_).y,
                             1.0f });
        box_->set_rotation(cpBodyGetAngle(body_));
        if (is_visible_){ box_->render(); }
      } break;
      case kBodyType_Circle:
      case kBodyType_Polygon: {
        poly_->set_position({ cpBodyGetPosition(body_).x,
                              cpBodyGetPosition(body_).y,
                              1.0f });
        poly_->set_rotation(cpBodyGetAngle(body_));
        if (is_visible_){ poly_->render(); }
      } break;
    }

    if (has_sprite_){
      sprite_->set_position({ cpBodyGetPosition(body_).x,
                              cpBodyGetPosition(body_).y,
                              1.0f });
      sprite_->set_rotation(cpBodyGetAngle(body_));
      sprite_->render();
    }
  }
}

/// add a force to a specified point of the object
void GameObject2D::addForce(const gtmath::Vec3 force) {

  cpBodySetForce(body_, { force.x, force.y });
}

/** setters **/
void GameObject2D::set_position(const gtmath::Vec3 position) {

  cpBodySetPosition(body_, { position.x, position.y });

  switch (body_type_){
    case kBodyType_Box: {
      box_->set_position({ position.x, position.y, 1.0f });
    } break;
    case kBodyType_Circle:
    case kBodyType_Polygon: {
      poly_->set_position({ position.x, position.y, 1.0f });
    } break;
  }
}

void GameObject2D::set_velocity(const gtmath::Vec3 velocity) {

  cpBodySetVelocity(body_, { velocity.x, velocity.y });
}

void GameObject2D::set_angle(const float radians) {

  cpBodySetAngle(body_, radians);
}

void GameObject2D::set_mass(const float mass) {

  cpBodySetMass(body_, mass);
  cpShapeSetMass(shape_, mass);
}

void GameObject2D::set_friction(const float friction) {

  cpShapeSetFriction(shape_, friction);
}

void GameObject2D::set_elasticity(const float elasticity) {

  cpShapeSetElasticity(shape_, elasticity);
}

void GameObject2D::set_moment(const bool inertia) {

  cpBodySetMoment(body_, inertia);
}

void GameObject2D::set_infinity(const bool infinity) {

  is_infinity_ = infinity;

  if (is_infinity_){ cpBodySetMoment(body_, INFINITY); }
  else { cpBodySetMoment(body_, moment_); }
}

void GameObject2D::set_visible(const bool visible) {

  is_visible_ = visible;
}

void GameObject2D::set_sprite(const char* path) {

  sprite_->set_sprite(path);
}

void GameObject2D::set_tag(const unsigned short int tag) {

  tag_ = tag;
  cpShapeSetCollisionType(shape_, tag_);
}

/** getters **/
const gtmath::Vec3 GameObject2D::position() {

  gtmath::Vec3 position = { cpBodyGetPosition(body_).x,
                            cpBodyGetPosition(body_).y,
                            1.0f };

  return position;
}

const gtmath::Vec3 GameObject2D::velocity() {

  gtmath::Vec3 velocity = { cpBodyGetVelocity(body_).x,
                            cpBodyGetVelocity(body_).y,
                            0.0f };

  return velocity;
}

const float GameObject2D::angle() {

  return cpBodyGetAngle(body_);
}

const float GameObject2D::mass() {

  return cpBodyGetMass(body_);
}

const float GameObject2D::friction() {

  return cpShapeGetFriction(shape_);
}

const float GameObject2D::elasticity() {

  return cpShapeGetElasticity(shape_);
}

const float GameObject2D::moment() {

  return cpBodyGetMoment(body_);
}

const bool GameObject2D::infinity() {

  return is_infinity_;
}

const float GameObject2D::width() {

  if (body_type_ == kBodyType_Box){ return box_->width(); }
  else { return 0.0f; }
}

const float GameObject2D::height() {

  if (body_type_ == kBodyType_Box){ return box_->height(); }
  else { return 0.0f; }
}

const unsigned short int GameObject2D::numVerts() {

  return cpPolyShapeGetCount(shape_);
}

const gtmath::Vec3 GameObject2D::vert(unsigned short int vert) {

  gtmath::Vec3 vertex = { cpPolyShapeGetVert(shape_, vert).x,
                          cpPolyShapeGetVert(shape_, vert).y };

  return vertex;
}

const unsigned short int GameObject2D::tag() {

  return cpShapeGetCollisionType(shape_);
}

/// draw collider
void GameObject2D::drawCollider(const bool enabled) {

  switch (body_type_){
    case kBodyType_Box: {
      if (enabled){ box_->drawLines(true); }
      else { box_->drawLines(false); }
    } break;
    case kBodyType_Circle:
    case kBodyType_Polygon: {
      if (enabled){ poly_->drawLines(true); }
      else { poly_->drawLines(false); }
    } break;
  }
}

/// delete body from space
void GameObject2D::removeBody() {

  if (shape_ != nullptr){
    cpSpaceRemoveShape(space_, shape_);
    cpShapeDestroy(shape_);
    cpShapeFree(shape_);
    shape_ = nullptr;
  }

  if (body_ != nullptr){
    cpSpaceRemoveBody(space_, body_);
    cpBodyDestroy(body_);
    cpBodyFree(body_);
    body_ = nullptr;
  }
}

/// destructor
GameObject2D::~GameObject2D() {

  cpSpaceFree(space_);
  if (shape_ != nullptr){
    cpSpaceRemoveShape(space_, shape_);
    cpShapeDestroy(shape_);
    cpShapeFree(shape_);
    shape_ = nullptr;
  }
  if (body_ != nullptr){
    cpSpaceRemoveBody(space_, body_);
    cpBodyDestroy(body_);
    cpBodyFree(body_);
    body_ = nullptr;
  }
  delete box_;
  delete poly_;
  delete sprite_;
  space_ = nullptr;
  box_ = nullptr;
  poly_ = nullptr;
  sprite_ = nullptr;
}
