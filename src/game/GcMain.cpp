#include <game/GcMain.h>

int cGcMain::Main()
{
    TK_INFO("Starting Game Process!");

    TkSTD::String lsApplicationName = "GcGame";
    TkSTD::String lsEngineName      = "skyline";

    cTkSystem &gSystem           = cTkSystem::GetInstance();
    cEgEngine &gEngine           = cEgEngine::GetInstance();
    cGcApplication &gApplication = cGcApplication::GetInstance();

    cTkEngineSettings lSettings = cTkEngineSettings(
        lsApplicationName, VK_MAKE_API_VERSION(0, 1, 0, 0), lsEngineName, VK_MAKE_API_VERSION(0, 1, 0, 0));
    gSystem.Construct();
    gEngine.Configure(lSettings);
    gApplication.Construct();

    TK_INFO("Created Application Components");

    while (!gApplication.mbQuit)
    {
        gSystem.PollForEvents();
        gApplication.mpClock->Update();
        while (gApplication.mpClock->IsAccumulatorGreaterThanDT())
        {
            float lfTimestep = gApplication.mpClock->GetTimestep();
            gApplication.Update(lfTimestep);
            gApplication.mpClock->SyncAccumulatorUpdate();
        }

        gEngine.Render();
    }

    TK_INFO("Exited Application Loop");

    cGcMain::Destruct();

    return eProcessExit_Success;
}

void cGcMain::Destruct()
{
    TK_INFO("Cleaning up");

    cEgEngine::GetInstance().Destruct();
    cGcApplication::GetInstance().Destruct();
    cTkSystem::GetInstance().Destruct();
}

#ifdef D_MSVC

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef D_DEBUG
    AllocConsole();
    SetConsoleTitle("GcGame");
    freopen("CONOUT$", "wt", stdout);
#endif

    int liResult = cGcMain::Main();

#ifdef D_DEBUG
    FreeConsole();
#endif

    return liResult;
}

#else

int main(int argc, char *argv[])
{
    return cGcMain::Main();
}

#endif