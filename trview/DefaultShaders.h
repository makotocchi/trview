#pragma once

#include <atlbase.h>
#include <d3d11.h>

namespace trview
{
    namespace graphics
    {
        struct IShaderStorage;
    }

    void load_default_shaders(const CComPtr<ID3D11Device>& device, graphics::IShaderStorage& storage);
}