#pragma once

#include <SimpleMath.h>

namespace trview
{
    namespace route
    {
        class Waypoint
        {
        public:
            Waypoint(const DirectX::SimpleMath::Vector3& position);
            DirectX::SimpleMath::Vector3 position() const;
        private:
            DirectX::SimpleMath::Vector3 _position;
        };
    }
}