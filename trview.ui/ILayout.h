/// @file ILayout.h
/// @brief Interface for a method of laying out controls inside a control.

#pragma once

namespace trview
{
    namespace ui
    {
        class Control;

        /// Interface for a method of laying out controls inside a control.
        struct ILayout
        {
            /// Destructor for ILayout.
            virtual ~ILayout() = 0;

            /// Lay out the controls based on the layout scheme of this layout.
            /// @param control The control that will have its layout altered.
            virtual void recalculate(Control& control) = 0;
        };
    }
}
