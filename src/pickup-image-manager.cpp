//
// pickup-image-manager.cpp
//
#include "pickup-image-manager.hpp"

#include "check-macros.hpp"
#include "config.hpp"
#include "texture-loader.hpp"

namespace thornberry
{

    PickupImageManager::PickupImageManager()
        : m_textures{}
    {}

    void PickupImageManager::setup(const Config & t_config)
    {
        // careful with this, cannot allow the vector to resize after this
        m_textures.reserve(static_cast<std::size_t>(Pickup::Count));

        for (std::size_t index{ 0 }; index < static_cast<std::size_t>(Pickup::Count); ++index)
        {
            const std::string filename{ pickupToFilename(static_cast<Pickup>(index)) };

            sf::Texture & texture = m_textures.emplace_back();

            util::TextureLoader::load(
                texture, (t_config.media_path / "image" / "animation" / "pickup" / filename), true);
        }
    }

    const sf::Texture & PickupImageManager::get(const Pickup t_pickup) const
    {
        const std::size_t index{ static_cast<std::size_t>(t_pickup) };

        M_CHECK(
            (index < m_textures.size()),
            "Error:  PickupImageManager::get(" << toString(t_pickup) << ") Unknown pickup!");

        return m_textures.at(index);
    }

} // namespace thornberry