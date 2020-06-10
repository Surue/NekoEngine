#include <rigidbody.h>

namespace neko::physics
{

RigidBody::RigidBody(
        Vec2 position,
        float angle,
        float gravityScale,
        Vec2 linearVelocity,
        float angularVelocity,
        Vec2 force,
        float torque,
        float mass,
        float invMass,
        BodyType bodyType) :
        position_(position),
        angle_(angle),
        gravityScale_(gravityScale),
        linearVelocity(linearVelocity),
        angularVelocity(angularVelocity),
        force_(force),
        torque_(torque),
        mass_(mass),
        invMass_(invMass),
        bodyType_(bodyType) {}
} //namespace neko::physics
