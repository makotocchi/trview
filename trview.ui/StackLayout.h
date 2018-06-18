/// @file StackLayout.h
/// @brief Lays elements out in horizontal or vertical direction.

#pragma once

#include "ILayout.h"

namespace trview
{
    namespace ui
    {
        /// Lays elements out in horizotnal or vertical direction.
        class StackLayout : public ILayout
        {
        public:
            StackLayout();

            /// Destructor for StackLayout.
            virtual ~StackLayout() = default;

            /// Lay out the controls based on the layout scheme of this layout.
            /// @param control The control that will have its layout altered.
            virtual void recalculate(Control& control) override;
        };
    }
}
