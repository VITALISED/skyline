#include <game/GcMain.h>

int cGcMain::Main()
{
    cGcApplication &gApplication = cGcApplication::GetInstance();
    cTkSystem &gSystem           = cTkSystem::GetInstance();

    TK_INFO("Starting game");

    while (!gApplication.mbQuit)
    {
        gSystem.PollForEvents();
        gApplication.mpClock->Update();
        while (gApplication.mpClock->IsAccumulatorGreaterThanDT())
        {
            gApplication.Update();
            gApplication.mpClock->SyncAccumulatorUpdate();
        }
    }

    cGcMain::Destruct();

    return eProcessExit_Success;
}

void cGcMain::Destruct()
{
    TK_INFO("Cleaning up..");

    cGcApplication::GetInstance().Destruct();
    cTkSystem::GetInstance().Destruct();
}

#ifdef D_MSVC

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return cGcMain::Main();
}

#endif