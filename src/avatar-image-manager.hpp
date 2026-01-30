#ifndef AVATAR_IMAGE_MANAGER_HPP_INLCUDED
#define AVATAR_IMAGE_MANAGER_HPP_INLCUDED
//
// avatar-image-manager.hpp
//
#include "avatar-image.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <memory>
#include <vector>

namespace thornberry
{
    struct Config;
    struct Context;

    //
    struct AvatarImagePack
    {
        std::size_t ref_count{ 0 };
        sf::Texture texture{};
    };

    // this class needs to be a singleton because it's needed in destructors
    class AvatarImageManager
    {
      public:
        AvatarImageManager();

        static AvatarImageManager & instance();
        void setup(const Config & t_config);
        const sf::Texture & shadowTexture() const { return *m_shadowTextureUPtr; }
        const sf::Texture & acquire(const AvatarImage & t_image);
        void release(const AvatarImage & t_image);
        void teardown();

      private:
        std::filesystem::path m_mediaPath;
        std::unique_ptr<sf::Texture> m_shadowTextureUPtr;
        std::vector<AvatarImagePack> m_imagePacks;
    };

} // namespace thornberry

#endif // AVATAR_IMAGE_MANAGER_HPP_INLCUDED
