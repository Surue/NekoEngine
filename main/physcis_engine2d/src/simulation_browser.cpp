#include <simulation_browser.h>

#include <imgui.h>

namespace neko
{
SimulationBrowser::SimulationBrowser(
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager,
        BoxCollider2dManager& boxCollider2DManager,
        CircleCollider2dManager& circleCollider2DManager,
        PolygonCollider2dManager& polygonCollider2DManager) :
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager),
        boxCollider2DManager_(boxCollider2DManager),
        circleCollider2DManager_(circleCollider2DManager),
        polygonCollider2DManager_(polygonCollider2DManager) {}

void SimulationBrowser::RegisterSimulation(
        std::string simulationName,
        std::unique_ptr<PhysicsSimulationProgramInterface> program)
{
    simulationsNames_.push_back(simulationName);
    simulations_.push_back(std::move(program));
}

void SimulationBrowser::DrawImGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Simulation Browser");
    if (ImGui::BeginCombo("Current simulation",
                          simulationsNames_[currentSimulationIndex_].c_str())) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < simulationsNames_.size(); n++)
        {
            const bool is_selected = (currentSimulationIndex_ == n);
            if (ImGui::Selectable(simulationsNames_[n].c_str(), is_selected))
            {
                SwitchToSimulation(n);
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
            }
        }
        ImGui::EndCombo();
    }
    ImGui::End();
}

void SimulationBrowser::SwitchToSimulation(size_t newSimulationIndex)
{
    const auto previousIndex = currentSimulationIndex_;
    currentSimulationIndex_ = newSimulationIndex;

    //Clear entities
    const Entity lastEntity = entityManager_.GetLastEntity();
    for (Entity e = 0; e < lastEntity; e++)
    {
        entityManager_.DestroyEntity(e);
    }

    //Load new simulation
    simulations_[currentSimulationIndex_]->LoadSimulation(
            entityManager_,
            transform2DManager_,
            body2DManager_,
            boxCollider2DManager_,
            circleCollider2DManager_,
            polygonCollider2DManager_
    );
}

void SimulationBrowser::Init()
{
    simulations_[currentSimulationIndex_]->LoadSimulation(entityManager_,
                                                          transform2DManager_,
                                                          body2DManager_,
                                                          boxCollider2DManager_,
                                                          circleCollider2DManager_,
                                                          polygonCollider2DManager_);
}

void SimulationBrowser::Update(seconds dt)
{

}

void SimulationBrowser::Destroy()
{

}
} //namespace neko