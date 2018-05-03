#include "RouteRenderer.h"
#include <SimpleMath.h>
#include <vector>

#include <trview.graphics/MeshVertex.h>

namespace trview
{
    namespace route
    {
        RouteRenderer::RouteRenderer(const CComPtr<ID3D11Device>& device)
        {

        }

        void RouteRenderer::create_waypoint_mesh(const CComPtr<ID3D11Device>& device)
        {
            using namespace DirectX::SimpleMath;
            const float W = 0.025f;
            const float D = 0.025f;
            const float H = 0.5f;
            const Vector2 UV{ 0,0 };
            const Color C{ 1,1,1,1 };

            std::vector<MeshVertex> vertices
            {
                { { -W, 0, -D }, UV, C },
            { { W, 0, -D }, UV, C },
            { { -W, 0, D }, UV, C },
            { { W, 0, D }, UV, C },
            { { -W, H, -D }, UV, C },
            { { W, H, -D }, UV, C },
            { { -W, H, D }, UV, C },
            { { W, H, D }, UV, C },
            };

            std::vector<uint32_t> indices
            {
                0, 1, 2,  // -y
                1, 3, 2,
                5, 1, 0,  // -z
                0, 4, 5,
                7, 3, 1,  // +x 
                1, 5, 7,
                6, 2, 3,  // +z 
                3, 7, 6,
                4, 0, 2,  // -x
                2, 6, 4,
                7, 5, 4,  // +y
                4, 6, 7,
            };

            D3D11_BUFFER_DESC vertex_desc;
            memset(&vertex_desc, 0, sizeof(vertex_desc));
            vertex_desc.Usage = D3D11_USAGE_DEFAULT;
            vertex_desc.ByteWidth = sizeof(MeshVertex) * static_cast<uint32_t>(vertices.size());
            vertex_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

            D3D11_SUBRESOURCE_DATA vertex_data;
            memset(&vertex_data, 0, sizeof(vertex_data));
            vertex_data.pSysMem = &vertices[0];

            device->CreateBuffer(&vertex_desc, &vertex_data, &_waypoint_vertex_buffer);

            D3D11_BUFFER_DESC index_desc;
            memset(&index_desc, 0, sizeof(index_desc));
            index_desc.Usage = D3D11_USAGE_DEFAULT;
            index_desc.ByteWidth = sizeof(uint32_t) * static_cast<uint32_t>(indices.size());
            index_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

            D3D11_SUBRESOURCE_DATA index_data;
            memset(&index_data, 0, sizeof(index_data));
            index_data.pSysMem = &indices[0];

            device->CreateBuffer(&index_desc, &index_data, &_waypoint_index_buffer);

            D3D11_BUFFER_DESC matrix_desc;
            memset(&matrix_desc, 0, sizeof(matrix_desc));

            matrix_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            matrix_desc.ByteWidth = sizeof(Matrix) + sizeof(Color);
            matrix_desc.Usage = D3D11_USAGE_DYNAMIC;
            matrix_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

            device->CreateBuffer(&matrix_desc, nullptr, &_waypoint_matrix_buffer);

            _waypoint_index_count = indices.size();
        }
    }
}
