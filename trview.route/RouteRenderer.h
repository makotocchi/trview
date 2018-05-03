#pragma once

#include <atlbase.h>
#include <d3d11.h>
#include <cstdint>

namespace trview
{
    namespace route
    {
        class RouteRenderer
        {
        public:
            explicit RouteRenderer(const CComPtr<ID3D11Device>& device);
        private:
            void create_waypoint_mesh(const CComPtr<ID3D11Device>& device);

            CComPtr<ID3D11Buffer> _waypoint_vertex_buffer;
            CComPtr<ID3D11Buffer> _waypoint_index_buffer;
            CComPtr<ID3D11Buffer> _waypoint_matrix_buffer;
            uint32_t              _waypoint_index_count;
        };
    }
}
