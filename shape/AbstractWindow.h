#pragma once
#include "IShape.h"
class CAbstractWindow : private boost::noncopyable
{
public:
    CAbstractWindow();
    virtual ~CAbstractWindow();

    void ShowFixedSize(glm::ivec2 const& size);
    void DoGameLoop(std::vector<std::shared_ptr<IShape>> const& shapes);

protected:
    void SetBackgroundColor(glm::vec4 const& color);

    virtual void OnWindowEvent(const SDL_Event &event) = 0;
    virtual void OnUpdateWindow(float deltaSeconds) = 0;
    virtual void OnDrawWindow(std::vector<std::shared_ptr<IShape>> const& shapes, const glm::ivec2 & size) = 0;

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};