#ifndef POPUP_MANAGER_HPP_INCLUDED
#define POPUP_MANAGER_HPP_INCLUDED
//
// popup-manager.hpp
//
#include "text-window.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <vector>

namespace thornberry
{
    struct Context;

    using TextWindowUPtr_t = std::unique_ptr<TextWindow>;

    //
    class PopupManager
    {
      public:
        PopupManager();

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void handleEvent(const Context & t_context, const sf::Event & t_event);
        void add(const Context & t_context, const TextWindowSpec & t_spec);
        [[nodiscard]] bool isThereAPopup() const noexcept { return !m_windows.empty(); }
      
    private:
        void setFocuses(const Context & t_context);

      private:
        std::vector<TextWindowUPtr_t> m_windows;
    };

} // namespace thornberry

#endif // POPUP_MANAGER_HPP_INCLUDED
