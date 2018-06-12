#include "stdafx.h"
#include "SettingsWindow.h"

#include <trview.ui/Control.h>
#include <trview.ui/StackPanel.h>
#include <trview.ui/GroupBox.h>
#include <trview.ui/Checkbox.h>
#include <trview.ui/Label.h>

#include "ITextureStorage.h"

using namespace trview::ui;

namespace trview
{
    SettingsWindow::SettingsWindow(Control& parent, const ITextureStorage& texture_storage)
    {
        const auto background_colour = Colour(1.0f, 0.5f, 0.5f, 0.5f);

        auto window = std::make_unique<StackPanel>(Point(400, 200), Size(400, 300), background_colour, Size(5,0));

        auto group = std::make_unique<GroupBox>(Point(), Size(390, 290), background_colour, Colour(1.0f, 0.0f, 0.0f, 0.0f), L"Settings");
        auto panel = std::make_unique<StackPanel>(Point(12, 20), Size(366, 250), background_colour, Size());

        const auto check_off = texture_storage.lookup("check_off");
        const auto check_on = texture_storage.lookup("check_on");

        auto vsync = std::make_unique<Checkbox>(Point(), Size(16, 16), check_off, check_on, L"Vsync");
        vsync->on_state_changed += on_vsync;
        _vsync = vsync.get();
        panel->add_child(std::move(vsync));

        panel->add_child(std::make_unique<Window>(Point(), Size(1, 5), background_colour));

        auto go_to_lara = std::make_unique<Checkbox>(Point(), Size(16, 16), check_off, check_on, L"Go to Lara");
        go_to_lara->on_state_changed += on_go_to_lara;
        _go_to_lara = go_to_lara.get();
        panel->add_child(std::move(go_to_lara));

        group->add_child(std::move(panel));
        window->add_child(std::move(group));

        parent.add_child(std::move(window));
    }

    void SettingsWindow::set_vsync(bool value)
    {
        _vsync->set_state(value);
    }

    void SettingsWindow::set_go_to_lara(bool value)
    {
        _go_to_lara->set_state(value);
    }
}
