/// @file SpriteSizeStore.h
/// @brief Stores the state of a sprite for the duration of an operation.
/// 
/// Stores the properties of a sprite for the duration of an operation. This way the host size
/// for example can be stored before the operation begins and restored after the operation has
/// finished. This is particularly useful when rendering to a different render target.

#pragma once

#include <cstdint>

namespace trview
{
    namespace graphics
    {
        class Sprite;

        /// Used to set and restore the host size of a sprite - useful when using the DirectXTK
        /// sprite to render to a different render target.
        class SpriteSizeStore final
        {
        public:
            /// Begin a sprite size store operation, setting the sprite to the new size specified
            /// after storing the old host size for later restoration.
            /// sprite: The sprite to operate on.
            /// new_width: The new host width of the sprite.
            /// new_height: The new host height of the sprite.
            explicit SpriteSizeStore(Sprite& sprite, uint32_t new_width, uint32_t new_height);

            /// When this executes it will restore the host size of the sprite to what it was when
            /// the SpriteSizeStore was created.
            ~SpriteSizeStore();
        private:
            Sprite& _sprite;
            uint32_t _width;
            uint32_t _height;
        };
    }
}
