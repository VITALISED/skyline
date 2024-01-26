#pragma once

#include <engine/renderer/EgRenderer.h>
#include <toolkit/core/TkCore.h>
#include <toolkit/engine/TkEngineSettings.h>

class cEgEngine : public cTkSingleton<cEgEngine>
{
  public:
    void Construct();
    void Destruct();
    void Configure(cTkEngineSettings &lSettings);

    cEgRenderer *mpRenderer;
    cTkEngineSettings *mpSettings;
};