#include <game/GcMain.h>

void cGcMain::Construct()
{
    cTkString lsApplicationName = "GcGame";
    cTkString lsEngineName      = "skyline";

    cTkAssert::Setup();

    cTkSystem &gSystem                 = cTkSystem::GetInstance();
    cEgEngine &gEngine                 = cEgEngine::GetInstance();
    cGcApplication &gApplication       = cGcApplication::GetInstance();
    cTkConVar<float> gc_engine_version = cTkConVar<float>("gc_engine_version", "test cvar", 1.0, ETkConFlags_None);

    gSystem.Construct();

#ifdef D_DEBUG
    gSystem.mpFilesystem->SetWorkingDirectory(D_WORKING_DIR);
#endif

    gEngine.Configure();
    gApplication.Construct();

    TK_INFO("Constructed Application Components");
}

eProcessExit cGcMain::Main()
{
    cTkSystem &gSystem           = cTkSystem::GetInstance();
    cEgEngine &gEngine           = cEgEngine::GetInstance();
    cGcApplication &gApplication = cGcApplication::GetInstance();

    cGcMain::Construct();

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

    return EProcessExit_Success;
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
#endif // D_DEBUG

    int liResult = cGcMain::Main();

#ifdef D_DEBUG
    FreeConsole();
#endif // D_DEBUG

    return liResult;
}

#else // !D_MSVC

int main(int argc, char *argv[])
{
    return cGcMain::Main();
}

#endif // D_MSVC