#include <97_planet/planet_program.h>

#include <debug_drawer_2d.h>

namespace neko{

void PlanetProgram::LoadSimulation(EntityManager& entityManager, Transform2dManager& transform2DManager,
                                   Body2dManager& body2DManager, BoxCollider2dManager& boxCollider2DManager,
                                   CircleCollider2dManager& circleCollider2DManager,
                                   PolygonCollider2dManager& polygonCollider2DManager)
{
    planets_.resize(nbPlanet);

    for(int i = 0; i < nbPlanet; i++)
    {
        planets_[i] = Planet(
                physics::Vec2(RandomRange(-40, 40), RandomRange(-40, 40)),
                RandomRange(minRadius, maxRadius),
                10,
                physics::Vec2(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f)));
    }
}

void PlanetProgram::Update(seconds dt) {
    for(int i = 0; i < planets_.size(); i++)
    {
        planets_[i].position += planets_[i].velocity * dt.count(); //TODO Lorna

        for(int j = 0; j < planets_.size(); j++){
            if(i == j) continue;

            float dist = (planets_[i].position - planets_[j].position).Magnitude();

            //TODO if contact => planet absorb

            float m = planets_[i].mass * planets_[j].mass;

            float force = 0.00001f * m / dist;

            //TODO update velocity


        }

        physics::DebugDrawer2dLocator::get().DrawCircle(planets_[i].position, planets_[i].radius);
    }

    //Comment supprimer un élément dans un vecteur
    //Tip 1: Nouveau vecteur
    std::vector<Planet> copyPlanet;
    copyPlanet.clear();

    for(int i = 0; i < planets_.size(); i++){
        if(planets_[i].mass <= 0){
            std::cout << "A planet died\n";
        }else{
            //planete vivante
            copyPlanet.push_back(planets_[i]);
        }
    }

    planets_ = copyPlanet;

    //Tip 2: Iterator
    for(auto it = planets_.begin(); it != planets_.end(); it++){
        if(it->mass <= 0){
            std::cout << "A planet died\n";
            it = planets_.erase(it);
        }
    }
}
}
