#include <04_restitution/restitution_program.h>

namespace neko{

void neko::RestitutionProgram::LoadSimulation(EntityManager& entityManager, Transform2dManager& transform2DManager,
                                              Body2dManager& body2DManager, BoxCollider2dManager& boxCollider2DManager,
                                              CircleCollider2dManager& circleCollider2DManager,
                                              PolygonCollider2dManager& polygonCollider2DManager)
{
    for(int i = 0; i < nbBall; i++){
        //Create an entity
        auto entity = entityManager.CreateEntity();

        //Add transform, body and circleCollider
        transform2DManager.AddComponent(entity);
        body2DManager.AddComponent(entity);
        circleCollider2DManager.AddComponent(entity);

        //Set position at the center of the screen
        if(nbBall % 2 == 0)
        {
            transform2DManager.SetPosition(entity, Vec2f((i - nbBall / 2) * horizontalSpaceBetweenBall + horizontalSpaceBetweenBall * 0.5f, 40.0f));
        }else{
            transform2DManager.SetPosition(entity, Vec2f((i - nbBall / 2) * horizontalSpaceBetweenBall, 40.0f));
        }

        //Set the body type to dynamic
        auto body = body2DManager.GetComponent(entity);
        body.bodyType = BodyType::DYNAMIC;
        body.gravityScale = 1;
        body2DManager.SetComponent(entity, body);

        //Set circle collider
        auto collider = circleCollider2DManager.GetComponent(entity);
        collider.restitution = ((i) / (nbBall - 1.0f));
        collider.friction = 0;
        collider.radius = 0.5f;
        collider.centroid = Vec2f(0,0);
        collider.isTrigger = false;
        circleCollider2DManager.SetComponent(entity, collider);
    }

    //Add ground to bounce of
    auto boxEntity = entityManager.CreateEntity();

    transform2DManager.AddComponent(boxEntity);
    body2DManager.AddComponent(boxEntity);
    boxCollider2DManager.AddComponent(boxEntity);

    transform2DManager.SetPosition(boxEntity, Vec2f(0, -20));

    auto boxBody = body2DManager.GetComponent(boxEntity);
    boxBody.bodyType = BodyType::STATIC;
    boxBody.gravityScale = 0;
    body2DManager.SetComponent(boxEntity, boxBody);

    auto boxCollider = boxCollider2DManager.GetComponent(boxEntity);
    boxCollider.extent = Vec2f(200, 10);
    boxCollider.restitution = 1;
    boxCollider.friction = 0;
    boxCollider.isTrigger = false;
    boxCollider2DManager.SetComponent(boxEntity, boxCollider);
}
} //namespace neko
