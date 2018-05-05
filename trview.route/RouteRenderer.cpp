#include "RouteRenderer.h"
#include <vector>

#include <trview.graphics/IShaderStorage.h>
#include <trview.graphics/MeshVertex.h>
#include <trview.graphics/IShader.h>
#include "Route.h"
#include "Waypoint.h"

namespace trview
{
    namespace route
    {
        RouteRenderer::RouteRenderer(const CComPtr<ID3D11Device>& device, const graphics::IShaderStorage& shader_storage, const Texture& waypoint_texture)
            : _waypoint_texture(waypoint_texture),
            _vertex_shader(shader_storage.get("level_vertex_shader")),
            _pixel_shader(shader_storage.get("level_pixel_shader"))
        {
            create_waypoint_mesh(device);
        }

        void RouteRenderer::create_waypoint_mesh(const CComPtr<ID3D11Device>& device)
        {
            using namespace DirectX::SimpleMath;
            const float W = 0.025f;
            const float D = 0.025f;
            const float H = 0.5f;
            const Vector2 UV{ 0,0 };
            const Color C{ 1,1,1,1 };

            const std::vector<MeshVertex> vertices
            {
                // -y
                { { -W, 0, -D }, UV, C },
                { { W, 0, -D }, UV, C },
                { { -W, 0, D }, UV, C },
                { { W, 0, D }, UV, C },

                // -z
                { { -W, 0, -D }, {0,10}, C },
                { { W, 0, -D }, {1,10}, C },
                { { -W, H, -D }, {0,0}, C },
                { { W, H, -D }, {1,0}, C },

                // +x
                { { W, 0, -D },{ 1,10 }, C },
                { { W, 0, D },{ 0,10 }, C },
                { { W, H, -D },{ 1,0 }, C },
                { { W, H, D },{ 0,0 }, C },

                // +z
                { { -W, 0, D },{ 0,10 }, C },
                { { W, 0, D },{ 1,10 }, C },
                { { -W, H, D },{ 0,0 }, C },
                { { W, H, D },{ 1,0 }, C },

                // -x
                { { -W, 0, D },{ 1,10 }, C },
                { { -W, 0, -D },{ 0,10 }, C },
                { { -W, H, D },{ 1,0 }, C },
                { { -W, H, -D },{ 0,0 }, C },

                // +y
                { { -W, H, -D }, UV, C },
                { { W, H, -D }, UV, C },
                { { -W, H, D }, UV, C },
                { { W, H, D }, UV, C },
            };

            const std::vector<uint32_t> indices
            {
                0, 1, 2,  // -y
                1, 3, 2,
                7, 5, 4,  // -z
                4, 6, 7,
                11, 9, 8,  // +x
                8, 10, 11,
                12, 13, 15,  // +z
                15, 14, 12,
                19, 17, 16, // -x
                16, 18, 19,
                22, 21, 20, // +y
                22, 23, 21
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

            _waypoint_index_count = static_cast<uint32_t>(indices.size());
        }

        void RouteRenderer::render(const CComPtr<ID3D11DeviceContext>& context, const DirectX::SimpleMath::Matrix& view_projection, const Route& route)
        {
            _vertex_shader->apply(context);
            _pixel_shader->apply(context);
            for (const Waypoint& waypoint : route.waypoints())
            {
                render_waypoint(context, view_projection, waypoint);
            }
        }

        void RouteRenderer::render(const CComPtr<ID3D11DeviceContext>& context, const DirectX::SimpleMath::Matrix& view_projection, const Waypoint& waypoint)
        {
            _vertex_shader->apply(context);
            _pixel_shader->apply(context);
            render_waypoint(context, view_projection, waypoint);
        }

        void RouteRenderer::render_waypoint(const CComPtr<ID3D11DeviceContext>& context, const DirectX::SimpleMath::Matrix& view_projection, const Waypoint& waypoint)
        {
            using namespace DirectX::SimpleMath;
            // Render the waypoint mesh at the appropriate position.
            D3D11_MAPPED_SUBRESOURCE mapped_resource;
            memset(&mapped_resource, 0, sizeof(mapped_resource));

            struct Data
            {
                Matrix matrix;
                Color colour;
            };

            auto world_view_projection = Matrix::CreateTranslation(waypoint.position()) * view_projection;
            Data data{ world_view_projection, waypoint.colour() };

            context->Map(_waypoint_matrix_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
            memcpy(mapped_resource.pData, &data, sizeof(data));
            context->Unmap(_waypoint_matrix_buffer, 0);

            UINT stride = sizeof(MeshVertex);
            UINT offset = 0;
            context->IASetVertexBuffers(0, 1, &_waypoint_vertex_buffer.p, &stride, &offset);
            context->VSSetConstantBuffers(0, 1, &_waypoint_matrix_buffer.p);

            context->PSSetShaderResources(0, 1, &_waypoint_texture.view.p);
            context->IASetIndexBuffer(_waypoint_index_buffer, DXGI_FORMAT_R32_UINT, 0);
            context->DrawIndexed(_waypoint_index_count, 0, 0);
        }
    }
}