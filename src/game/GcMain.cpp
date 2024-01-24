#include <game/GcMain.h>

int cGcMain::Main()
{
    gApplication = new cGcApplication();

    TK_INFO("Starting game");

    while (!gApplication->mbQuit)
    {
        gApplication->mpClock->Update();
        while (gApplication->mpClock->IsAccumulatorGreaterThanDT())
        {
            gApplication->Update();
            TK_INFO("Update call");
            gApplication->mpClock->SyncAccumulatorUpdate();
        }
    }

    delete gApplication;

    return eProcessExit_Success;
}

#ifdef D_MSVC

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return cGcMain::Main();
}

#endif