/// @file Sprite.h
/// @brief Used to render a texture to a render target.
/// 
/// Renders 2D textures to a render target. This can be to the screen or to a render target texture.

#pragma once

#include <wrl/client.h>
#include <d3d11.h>
#include <cstdint>

#include <SimpleMath.h>

namespace trview
{
    namespace graphics
    {
        struct IShader;
        struct IShaderStorage;
        class Texture;

        /// Renders 2D textures to a render target.This can be to the screen or to a render target texture.
        class Sprite
        {
        public:
            /// Create a new sprite.
            /// @param device The D3D device to use to create resources.
            /// @param shader_storage The interface to use to retrieve shaders.
            /// @param host_width The width of the render target.
            /// @param host_height The height of the render target.
            Sprite(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const graphics::IShaderStorage& shader_storage, uint32_t host_width, uint32_t host_height);

            /// Render a texture to the current render target.
            /// @param context The D3D context to use to render.
            /// @param texture The texture to render.
            /// @param x The x coordinate at which to render the texture.
            /// @param y The y coordinate at which to render the texture.
            /// @param width The width to which to scale the renderered texture.
            /// @param height The height to which to scale the renderered texture.
            /// @param colour Optional colour to apply to the texture when it is rendered.
            void render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context, const Texture& texture, float x, float y, float width, float height, DirectX::SimpleMath::Color colour = { 1,1,1,1 });

            /// Get the width that the sprite considers the current render target to be.
            /// @returns The current host width.
            uint32_t host_width() const;

            /// Get the height that the sprite considers the current render target to be.
            /// @returns The current host height.
            uint32_t host_height() const;

            /// Set the host size - the size of the render target that is being rendered to.
            /// @param width The width of the render target.
            /// @param height The height of the render target.
            void set_host_size(uint32_t width, uint32_t height);

            Sprite(const Sprite&) = delete;
            Sprite& operator=(const Sprite&) = delete;
        private:
            /// Create the buffer used to pass parameters to the shader.
            /// @param device The D3D device to use to create the buffer.
            void create_matrix(const Microsoft::WRL::ComPtr<ID3D11Device>& device);

            /// Update the buffer used to pass parameters to the shader.
            /// @param context The D3D device context to use to update the buffer.
            /// @param x The x position at which to render the texture.
            /// @param y The y position at which to render the texture.
            /// @param width The width to which to scale the renderered texture.
            /// @param height The height to which to scale the renderered texture.
            /// @param colour Optional colour to apply to the texture when it is rendered.
            void update_matrix(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context, float x, float y, float width, float height, const DirectX::SimpleMath::Color& colour);

            Microsoft::WRL::ComPtr<ID3D11Buffer>       _vertex_buffer;
            Microsoft::WRL::ComPtr<ID3D11Buffer>       _index_buffer;
            Microsoft::WRL::ComPtr<ID3D11SamplerState> _sampler_state;
            Microsoft::WRL::ComPtr<ID3D11Buffer>       _matrix_buffer;
            graphics::IShader*          _vertex_shader;
            graphics::IShader*          _pixel_shader;
            uint32_t                    _host_width;
            uint32_t                    _host_height;
        };
    }
}
