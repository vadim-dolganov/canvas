﻿#include "stdafx.h"
#include "AbstractWindow.h"


namespace
{
    const char WINDOW_TITLE[] = "Canvas";

    using SDLWindowPtr = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
    using SDLGLContextPtr = std::unique_ptr<void, void(*)(SDL_GLContext)>;

    class CChronometer
    {
    public:
        CChronometer()
            : m_lastTime(std::chrono::system_clock::now())
        {
        }

        float GrabDeltaTime()
        {
            auto newTime = std::chrono::system_clock::now();
            auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - m_lastTime);
            m_lastTime = newTime;
            return 0.001f * float(timePassed.count());
        }

    private:
        std::chrono::system_clock::time_point m_lastTime;
    };
}

class CAbstractWindow::Impl
{
public:
    Impl()
        : m_pWindow(nullptr, SDL_DestroyWindow)
        , m_pGLContext(nullptr, SDL_GL_DeleteContext)
    {
    }

    void ShowFixedSize(glm::ivec2 const& size)
    {
        m_size = size;
        m_pWindow.reset(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

        m_pGLContext.reset(SDL_GL_CreateContext(m_pWindow.get()));
        if (!m_pGLContext)
        {
            std::cerr << "OpenGL context initialization failed" << std::endl;
            std::abort();
        }
    }

    glm::ivec2 GetWindowSize() const
    {
        return m_size;
    }

    bool IsTerminated() const
    {
        return m_isTerminated;
    }

    void SetBackgroundColor(const glm::vec4 &color)
    {
        m_clearColor = color;
    }

    void Clear()const
    {
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SwapBuffers()
    {
        SDL_GL_SwapWindow(m_pWindow.get());
    }

    bool ConsumeEvent(const SDL_Event &event)
    {
        bool consumed = false;
        if (event.type == SDL_QUIT)
        {
            m_isTerminated = true;
            consumed = true;
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            OnWindowEvent(event.window);
            consumed = true;
        }
        return consumed;
    }

private:
    void OnWindowEvent(const SDL_WindowEvent &event)
    {
        if (event.event == SDL_WINDOWEVENT_RESIZED)
        {
            m_size = { event.data1, event.data2 };
        }
    }


    SDLWindowPtr m_pWindow;
    SDLGLContextPtr m_pGLContext;
    glm::vec4 m_clearColor;
    glm::ivec2 m_size;
    bool m_isTerminated = false;
};

CAbstractWindow::CAbstractWindow()
    : m_pImpl(new Impl)
{
}

CAbstractWindow::~CAbstractWindow()
{
}

void CAbstractWindow::ShowFixedSize(const glm::ivec2 &size)
{
    m_pImpl->ShowFixedSize(size);
}

void CAbstractWindow::DoGameLoop(std::vector<std::shared_ptr<IShape>> const& shapes)
{
    SDL_Event event;
    CChronometer chronometer;
    while (true)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (!m_pImpl->ConsumeEvent(event))
            {
                OnWindowEvent(event);
            }
        }
        if (m_pImpl->IsTerminated())
        {
            break;
        }
        m_pImpl->Clear();
        const float deltaSeconds = chronometer.GrabDeltaTime();
        OnUpdateWindow(deltaSeconds);
        OnDrawWindow(shapes, m_pImpl->GetWindowSize());
        m_pImpl->SwapBuffers();
    }
}

void CAbstractWindow::SetBackgroundColor(const glm::vec4 &color)
{
    m_pImpl->SetBackgroundColor(color);
}