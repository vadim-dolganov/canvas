#pragma once
#include "AbstractWindow.h"
#include "Canvas.h"

class CWindow : public CAbstractWindow
{
public:
    CWindow();
    ~CWindow();
protected:
    void OnWindowEvent(const SDL_Event &event) override;

    void OnUpdateWindow(float deltaSeconds) override;

    void OnDrawWindow(std::vector<std::shared_ptr<IShape>> const& shapes, const glm::ivec2 & size) override;


private:
    void SetupView(const glm::ivec2 & size);

    CCanvas m_canvas;
    glm::vec2 m_dragOffset;
};