/// @file ResizeLayout.h
/// @brief Resizes the control based on the contents of the control.

#pragma once

#include "ILayout.h"
#include "SizeDimension.h"

namespace trview
{
    namespace ui
    {
        /// Resizes the control based on the contents of the control.
        class ResizeLayout : public ILayout
        {
        public:
            explicit ResizeLayout(SizeDimension size_dimension);

            /// Destructor for ResizeLayout.
            virtual ~ResizeLayout() = default;

            /// Lay out the controls based on the layout scheme of this layout.
            /// @param control The control that will have its layout altered.
            virtual void recalculate(Control& control) override;
        private:
            SizeDimension _size_dimension;
        };
    }
}
