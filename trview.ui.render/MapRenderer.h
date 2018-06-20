/// @file MapRenderer.h
/// @brief Manages and renders the minimap that is displayed when a room is selected.

#pragma once

#include <d3d11.h>
#include <wrl/client.h>
#include <SimpleMath.h>

#include <vector> 
#include <memory>

#include <trview.common/Point.h>
#include <trview.common/Size.h>
#include <trview.common/Event.h>
#include <trview.graphics/RenderTarget.h>
#include <trview.graphics/Sprite.h>
#include <trview.graphics/Texture.h>

#include "trview\Types.h"
#include "trview\Room.h"

namespace trview
{
    namespace graphics
    {
        struct IShaderStorage;
    }

    namespace ui
    {
        namespace render
        {
            namespace
            {
                struct Tile
                {
                public:
                    Tile() {}

                    Tile(const std::shared_ptr<Sector>& p_sector, Point p_position, Size p_size, uint32_t x, uint32_t z)
                        : sector(p_sector), position(p_position), size(p_size), x(x), z(z) {}

                    std::shared_ptr<Sector> sector; 
                    Point position; 
                    Size size; 
                    uint32_t x{ 0u };
                    uint32_t z{ 0u };
                };
            }

            /// Manages and renders the minimap that is displayed when a room is selected.
            class MapRenderer
            {
            public:
                /// Create a new MapRenderer.
                /// @param device The device to render with.
                /// @param shader_storage The shader storage instance from which to retrieve shaders.
                /// @param width The width of the window.
                /// @param height The height of the window.
                MapRenderer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const graphics::IShaderStorage& shader_storage, int width, int height);

                /// Renders the map.
                /// @param context The D3D context to use.
                void render(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context);

                /// Changes the room to specified room and reloads the map.
                /// @param room The room to load.
                void load(const trview::Room* const room);

                /// Returns the total area of the room.
                /// @returns The area of the room.
                inline std::uint16_t area() const { return _columns * _rows; }

                /// Returns the sector that the cursor is within, or nullptr if none.
                /// @returns The sector at the cursor position.
                std::shared_ptr<Sector> sector_at_cursor() const;

                /// Returns true if cursor is on the control
                /// @returns True if the cursor is over the control.
                bool cursor_is_over_control() const;

                /// Sets the position of the cursor 
                /// @param cursor The cursor position.
                inline void set_cursor_position(const Point& cursor) { _cursor = cursor - _first; }

                /// Returns whether the map is loaded
                /// @returns True if the map is loaded.
                inline bool loaded() const { return _loaded; }

                /// Set the size of the host window.
                /// @param width The width of the host window.
                /// @param height The height of the host window.
                void set_window_size(int width, int height);

                /// Event raised when a sector is hovered over. 
                /// The x and z index of the sector are passed as parameters.
                Event<uint32_t, uint32_t> on_sector_hover;

                /// Event raised when no sector is being hovered over.
                Event<> on_sector_hover_end;
            private:
                /// Returns the sector under the specified position, or nullptr if none.
                /// @param point The point to test.
                /// @returns The sector under the position.
                std::shared_ptr<Sector> sector_at(const Point& point) const;

                /// Determines the position (on screen) to draw a sector 
                /// @param sector The sector to test.
                /// @returns The position at which to draw the sector.
                Point get_position(const Sector& sector) const; 

                /// Determines the size of a sector 
                /// @returns The size of a sector.
                Size get_size() const;

                /// Draws a square at given position, size with given colour.
                /// @param context The D3D context to use.
                /// @param position The position at which to draw the square.
                /// @param size The of the square.
                /// @param colour The colour of the square.
                void draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context, Point position, Size size, const DirectX::SimpleMath::Color& colour);

                /// Update the stored positions of the corners of the map.
                void update_map_position();

                /// Update the render target that the squares will be rendered to, depending on the size of the room (based on columns and rows).
                void update_map_render_target();

                /// Render the map squares and the background.
                /// @param context The D3D context.
                void render_internal(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& context);

                /// Determines if the minimap needs to be re-drawn.
                /// @returns True if the map needs to be re-drawn.
                bool needs_redraw();

                /// Hover over a tile.
                void hover_tile(const Tile& tile);

                Microsoft::WRL::ComPtr<ID3D11Device>               _device;
                int                                                _window_width, _window_height;
                graphics::Sprite                                   _sprite; 
                graphics::Texture                                  _texture;
                std::vector<Tile>                                  _tiles; 
                std::unique_ptr<graphics::RenderTarget>            _render_target;

                Point                               _first, _last; // top-left corner, bottom-right corner (of control) 
                Point                               _cursor; // Position of the cursor relative to the top left of the control.
                std::uint16_t                       _rows, _columns; 
                bool                                _loaded = false;
                
                bool                                _cursor_was_over = false;
                bool                                _force_redraw = true;

                const float                         _DRAW_MARGIN = 30.0f; 
                const float                         _DRAW_SCALE = 14.0f; 

                std::shared_ptr<Sector> _hovered_sector;
            };
        }
    }
};
