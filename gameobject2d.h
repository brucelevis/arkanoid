/**
 *
 * @brief GameObject2D Header
 * @author Toni Marquez
 * @fixes - joints & constrains
 *
 **/

#ifndef __GAMEOBJECT2D_H__
#define __GAMEOBJECT2D_H__ 1
#include <stdio.h>
#include <stdlib.h>

#define WIN32
#include <ESAT_extra/chipmunk/chipmunk.h>

#include "gtmath.h"
#include "box.h"
#include "polygon.h"
#include "sprite.h"

static enum BodyType {
  kBodyType_None = 0,
  kBodyType_Segment,
  kBodyType_Box,
  kBodyType_Polygon,
  kBodyType_Circle,
  kBodyType_Sprite
};

static enum BodyKind {
  kBodyKind_None = 0,
  kBodyKind_Dynamic,
  kBodyKind_Kinematic,
  kBodyKind_Static
};

class GameObject2D {

  public:

    /// constructor
    GameObject2D();

    /// destructor
    ~GameObject2D();

    /// init values
    void init(cpSpace* space,
              const float mass = 1.0f,
              const float moment = 1.0f,
              const BodyKind body_kind = kBodyKind_Dynamic);

    /*
    // use this to create a world space
    cpSpace* space = cpSpaceNew();
    cpSpaceSetGravity(space, { 0.0f, 9.8f });
    cpSpaceSetDamping(space_, 0.5f); // set air friction

    // use this to update objects position
    cpSpaceStep(space, delta / 100.0f);

    // use this for free memory
    cpSpaceFree(space);
    */

    /*
    // use this to add a collision handler
    cpBool Collision(cpArbiter *arbiter, cpSpace *space, void *data) {
      cpShape* a = NULL;
      cpShape* b = NULL;
      cpArbiterGetShapes(arbiter, &a, &b);
      //printf("COLLISION %d %d\n", cpShapeGetCollisionType(a), cpShapeGetCollisionType(b));
      bool* collision = (bool*)data;
      *collision = true;
      return cpTrue;
    }

    cpCollisionHandler* handler = cpSpaceAddCollisionHandler(space_, 1, 2);
    handler->beginFunc = Collision;
    handler->userData = &collision_;
    */

    /** add bodies **/
    /// segment body
    void addBodySegment(const gtmath::Vec3 pointA = { 0.0f, 0.0f, 1.0f },
                        const gtmath::Vec3 pointB = { 0.0f, 0.0f, 1.0f },
                        const float friction = 0.5f,
                        const float radius = 1.0f,
                        const float mass = 10.0f);
    /// box body
    void addBodyBox(const float width = 50.0f,
                    const float height = 50.0f,
                    const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
                    const float mass = 10.0f,
                    const float friction = 0.5f,
                    const float radius = 1.0f);
    /// polygon regular body
    void addBodyPoly(const unsigned short int num_verts = 10,
                     const float size = 50.0f,
                     const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
                     const float mass = 10.0f,
                     const float friction = 0.5f,
                     const float radius = 1.0f);
    /// polygon free body
    void addBodyPolyFree(const unsigned short int num_verts,
                         const gtmath::Vec3* verts,
                         const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
                         const float mass = 10.0f,
                         const float friction = 0.5f,
                         const float radius = 1.0f);
    /// sprite body
    void addBodySprite(const char* path,
                       const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
                       const float mass = 10.0f,
                       const float friction = 0.5f,
                       const float radius = 1.0f);
    /// sprite body multiple shapes
    /*
    void addBodySpriteJoint(const char* path,
                            const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
                            const float mass = 10.0f,
                            const float friction = 0.5f,
                            const float radius = 1.0f);
                            */

    /**
     * @brief update object position and render it
     * @param none
     * @return void
     **/
    void update();

    /// add a force to a specified point of the object
    void addForce(const gtmath::Vec3 force);

    /** setters **/
    void set_position(const gtmath::Vec3 position);
    void set_velocity(const gtmath::Vec3 velocity);
    void set_angle(const float radians);
    void set_mass(const float mass);
    void set_friction(const float friction);
    void set_elasticity(const float elasticity);
    void set_moment(const bool inertia);
    void set_infinity(const bool infinity);
    void set_visible(const bool visible);
    void set_sprite(const char* path);
    void set_tag(const unsigned short int tag);

    /** getters **/
    const gtmath::Vec3 position();
    const gtmath::Vec3 velocity();
    const float angle();
    const float mass();
    const float friction();
    const float elasticity();
    const float moment();
    const bool infinity();
    const float width();
    const float height();
    const unsigned short int numVerts();
    const gtmath::Vec3 vert(unsigned short int index);
    const unsigned short int tag();

    /// delete body from space
    void removeBody();

  private:

    /// copy constructor
    GameObject2D(const GameObject2D& copy);
    GameObject2D operator=(const GameObject2D& copy);

    /// private vars
    cpSpace* space_;
    cpBody* body_;
    cpShape* shape_;
    Box* box_;
    Polygon* poly_;
    Sprite* sprite_;
    BodyType body_type_;
    BodyKind body_kind_;
    gtmath::Vec3 pointA_;
    gtmath::Vec3 pointB_;
    unsigned short int tag_;
    float moment_;
    bool is_visible_;
    bool is_infinity_;
};

#endif
