#include "Waypoint.h"

namespace trview
{
    namespace route
    {
        Waypoint::Waypoint(const DirectX::SimpleMath::Vector3& position)
            : _position(position)
        {
        }

        DirectX::SimpleMath::Vector3 Waypoint::position() const
        {
            return _position;
        }
    }
}
