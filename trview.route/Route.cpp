#include "Route.h"

namespace trview
{
    namespace route
    {
        void Route::add(Waypoint waypoint)
        {
            _waypoints.push_back(waypoint);
        }

        const std::vector<Waypoint>& Route::waypoints() const
        {
            return _waypoints;
        }
    }
}
