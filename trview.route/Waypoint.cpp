#include "Waypoint.h"

namespace trview
{
    namespace route
    {
        Waypoint::Waypoint(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Color& colour)
            : _position(position), _colour(colour)
        {
        }

        DirectX::SimpleMath::Vector3 Waypoint::position() const
        {
            return _position;
        }

        DirectX::SimpleMath::Color Waypoint::colour() const
        {
            return _colour;
        }
    }
}
