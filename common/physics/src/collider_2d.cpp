#include "../include/collider_2d.h"

namespace neko::physics
{

Collider2d::Collider2d() :
        isTrigger_(true),
        restitution_(0),
        friction_(0),
        offset_(),
        centroid_() {}

Collider2d::Collider2d(bool isTrigger, float restitution, float friction, Vec2 offset) :
        isTrigger_(isTrigger),
        restitution_(restitution),
        friction_(friction),
        offset_(offset),
        centroid_() {}
} //namespace neko::physics