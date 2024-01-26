#include <engine/EgMain.h>

void cEgEngine::Construct()
{
    TK_INFO("Engine!");
}

void cEgEngine::Destruct()
{
    delete this->mpRenderer;
    delete this->mpSettings;
    delete this;
}

void cEgEngine::Configure(cTkEngineSettings &lSettings)
{
    this->mpSettings = new cTkEngineSettings(lSettings);
    this->mpRenderer = new cEgRenderer(lSettings);
}