#pragma once

#include <vector>
#include "Waypoint.h"

namespace trview
{
    namespace route
    {
        class Route
        {
        public:
            void add(Waypoint waypoint);
            const std::vector<Waypoint>& waypoints() const;
        private:
            std::vector<Waypoint> _waypoints;
        };
    }
}
