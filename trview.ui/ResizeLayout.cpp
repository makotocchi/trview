#include "ResizeLayout.h"
#include "Control.h"

namespace trview
{
    namespace ui
    {
        ResizeLayout::ResizeLayout(SizeDimension size_dimension)
            : _size_dimension(size_dimension)
        {
        }

        void ResizeLayout::recalculate(Control& control)
        {
            // Iterate through the controls, figure out the largest points based on the position
            // of the child controls. Then resize the control for that, based on the dimensions
            // that are configured to automatically resize.

            float extent_x = 0;
            float extent_y = 0;

            for (const auto& child : control.child_elements())
            {
                const auto pos = child->position();
                const auto size = child->size();
                extent_x = std::max(extent_x, pos.x + size.width);
                extent_y = std::max(extent_y, pos.y + size.height);
            }

            Size size = control.size();
            if (_size_dimension == SizeDimension::Width || _size_dimension == SizeDimension::All)
            {
                size.width = extent_x;
            }
            else if (_size_dimension == SizeDimension::Height || _size_dimension == SizeDimension::All)
            {
                size.height = extent_y;
            }

            control.set_size(size);
        }
    }
}
