#pragma once

#include <SimpleMath.h>

namespace trview
{
    namespace route
    {
        class Waypoint
        {
        public:
            Waypoint(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Color& colour);
            DirectX::SimpleMath::Vector3 position() const;
            DirectX::SimpleMath::Color colour() const;
        private:
            DirectX::SimpleMath::Vector3 _position;
            DirectX::SimpleMath::Color _colour;
        };
    }
}