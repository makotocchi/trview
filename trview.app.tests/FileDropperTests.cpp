#include <trview.app/Menus/FileDropper.h>

using namespace trview;
using namespace trview::tests;

// Tests that sending a dropfile message to the dropper raises the event.
TEST(FileDropper, DropFile)
{
    FileDropper dropper(create_test_window(L"TRViewFileDropperTests"));

    uint32_t times_called = 0;
    std::string file_opened;
    auto token = dropper.on_file_dropped += [&](const auto& file)
    {
        ++times_called;
        file_opened = file;
    };

    std::string filename("test_filename");
    // +2 for the double null terminated list of names.
    HGLOBAL global = GlobalAlloc(GHND, sizeof(DROPFILES) + filename.size() + 2);
    DROPFILES* dropfiles = static_cast<DROPFILES*>(GlobalLock(global));
    dropfiles->pFiles = sizeof(DROPFILES);
    strcpy_s(reinterpret_cast<char*>(dropfiles + 1), filename.size() + 1, filename.c_str());
    GlobalUnlock(global);

    dropper.process_message(WM_DROPFILES, (WPARAM)global, 0);

    GlobalFree(global);

    ASSERT_EQ(1u, times_called);
    ASSERT_EQ(std::string("test_filename"), file_opened);
}

// Tests that the class enables drag and drop
TEST(FileDropper, EnableDragDrop)
{
    Window window = create_test_window(L"TRViewFileDropperTests");
    FileDropper dropper(window);
    LONG_PTR style = GetWindowLongPtr(window, GWL_EXSTYLE);
    ASSERT_EQ(WS_EX_ACCEPTFILES, style & WS_EX_ACCEPTFILES);
}