#pragma once

#include <engine/renderer/EgRenderer.h>
#include <toolkit/core/TkCore.h>

class cEgEngine : public cTkSingleton<cEgEngine>
{
  public:
    void Construct();
    void Destruct();
    void Configure();
    void Render();

    cEgRenderer *mpRenderer;
};