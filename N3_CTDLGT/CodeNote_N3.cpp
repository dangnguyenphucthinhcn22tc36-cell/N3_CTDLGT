#include "CodeNote_N3.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace N3CTDLGT;

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Application::Run(gcnew CodeNote_N3());

    return 0;
}