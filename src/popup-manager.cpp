//
// popup-manager.cpp
//
#include "popup-manager.hpp"

#include "context.hpp"

namespace thornberry
{

    PopupManager::PopupManager()
        : m_windows{}
    {}

    void PopupManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const TextWindowUPtr_t & windowUPtr : m_windows)
        {
            windowUPtr->draw(t_target, t_states);
        }
    }

    void PopupManager::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (m_windows.empty())
        {
            return;
        }

        // only the most recent window handles events
        if (m_windows.back()->handleEvent(t_context, t_event))
        {
            m_windows.pop_back();
            setFocuses(t_context);
        }
    }

    void PopupManager::add(const Context & t_context, const TextWindowSpec & t_spec)
    {
        TextWindowUPtr_t & windowUPtr{ m_windows.emplace_back(std::make_unique<TextWindow>()) };
        windowUPtr->setup(t_context, t_spec);
        setFocuses(t_context);
    }

    void PopupManager::setFocuses(const Context & t_context)
    {
        if (m_windows.empty())
        {
            return;
        }

        for (TextWindowUPtr_t & windowUPtr : m_windows)
        {
            windowUPtr->setFocusOff(t_context);
        }

        m_windows.back()->setFocusOn(t_context);
    }

} // namespace thornberry
