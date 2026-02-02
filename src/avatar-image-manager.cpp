//
// avatar-image-manager.cpp
//
#include "avatar-image-manager.hpp"

#include "alpha-masking.hpp"
#include "check-macros.hpp"
#include "config.hpp"
#include "context.hpp"
#include "texture-loader.hpp"

#include <iostream>

namespace thornberry
{

    AvatarImageManager::AvatarImageManager()
        : m_mediaPath{}
        , m_shadowTextureUPtr{ std::make_unique<sf::Texture>() }
        , m_imagePacks{}
    {}

    AvatarImageManager & AvatarImageManager::instance()
    {
        static AvatarImageManager instance;
        return instance;
    }

    void AvatarImageManager::setup(const Config & t_config)
    {
        m_mediaPath = t_config.media_path;

        AlphaMasking::loadAndApplyMasks(
            *m_shadowTextureUPtr,
            (t_config.media_path / "image" / "avatar" / "avatar-shadow.png").string(),
            t_config.background_mask_color,
            true);

        // prevent this vector from ever resizing
        m_imagePacks.resize(static_cast<std::size_t>(AvatarImage::count));
    }

    const sf::Texture & AvatarImageManager::acquire(const AvatarImage & t_image)
    {
        M_CHECK((t_image != AvatarImage::count), "Given AvatarImage::Count!");

        const std::size_t index{ static_cast<std::size_t>(t_image) };

        M_CHECK(
            (index < m_imagePacks.size()),
            "Given invalid AvatarImage that was an index out of range! AvatarImage="
                << toString(t_image) << ", index=" << index);

        AvatarImagePack & pack{ m_imagePacks.at(index) };

        if (0 == pack.ref_count)
        {
            util::TextureLoader::load(
                pack.texture,
                (m_mediaPath / "image" / "avatar" / avatarImageToFilename(t_image)),
                true);
        }

        ++pack.ref_count;

        return pack.texture;
    }

    void AvatarImageManager::release(const AvatarImage & t_image)
    {
        M_CHECK((t_image != AvatarImage::count), "Given AvatarImage::Count!");

        const std::size_t index{ static_cast<std::size_t>(t_image) };

        M_CHECK(
            (index < m_imagePacks.size()),
            "Given invalid AvatarImage that was an index out of range! AvatarImage="
                << toString(t_image) << ", index=" << index);

        AvatarImagePack & pack{ m_imagePacks.at(index) };

        M_CHECK(
            (pack.ref_count >= 1),
            "AvatarImage=\"" << toString(t_image) << "\" had a ref_count=" << pack.ref_count);

        if (1 == pack.ref_count)
        {
            pack.texture = sf::Texture();
        }

        --pack.ref_count;
    }

    void AvatarImageManager::teardown()
    {
        // report any ref_counts not returned to zero
        for (std::size_t index{ 0 }; index < m_imagePacks.size(); ++index)
        {
            const AvatarImagePack & pack{ m_imagePacks.at(index) };

            if (pack.ref_count != 0)
            {
                std::cout
                    << "~AvatarImageManager() found a ref_count that was not zero!  ref_count="
                    << pack.ref_count
                    << ", AvatarImage=" << toString(static_cast<AvatarImage>(index)) << '\n';
            }
        }

        m_imagePacks = std::vector<AvatarImagePack>();
        m_shadowTextureUPtr.reset();
    }

} // namespace thornberry
