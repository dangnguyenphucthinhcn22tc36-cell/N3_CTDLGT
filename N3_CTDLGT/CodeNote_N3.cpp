#include "CodeNote_N3.h"

// Them thu vien de fix chu mo nhat tren man hinh 150% DPI
#pragma comment(lib, "user32.lib")
#include <ShellScalingAPI.h>
#pragma comment(lib, "Shcore.lib")

using namespace System;
using namespace System::Windows::Forms;
using namespace N3CTDLGT;

[STAThread]
int main(array<String^>^ args)
{
    // Fix chu bi mo nhat tren man hinh co Scaling 125% / 150%
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Application::Run(gcnew CodeNote_N3());

    return 0;
}
