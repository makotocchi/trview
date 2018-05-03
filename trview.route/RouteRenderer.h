#pragma once

#include <atlbase.h>
#include <d3d11.h>
#include <cstdint>
#include <SimpleMath.h>

#include <trview.common/Texture.h>

namespace trview
{
    namespace route
    {
        class Route;
        class Waypoint;

        class RouteRenderer
        {
        public:
            explicit RouteRenderer(const CComPtr<ID3D11Device>& device, const Texture& waypoint_texture);

            void render(
                const CComPtr<ID3D11DeviceContext>& context, 
                const DirectX::SimpleMath::Matrix& view_projection,
                const Route& route);
        private:
            void create_waypoint_mesh(const CComPtr<ID3D11Device>& device);
            void render_waypoint(const CComPtr<ID3D11DeviceContext>& context, const DirectX::SimpleMath::Matrix& view_projection, const Waypoint& waypoint);

            Texture               _waypoint_texture;
            CComPtr<ID3D11Buffer> _waypoint_vertex_buffer;
            CComPtr<ID3D11Buffer> _waypoint_index_buffer;
            CComPtr<ID3D11Buffer> _waypoint_matrix_buffer;
            uint32_t              _waypoint_index_count;
        };
    }
}
