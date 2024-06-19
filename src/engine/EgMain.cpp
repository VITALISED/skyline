#include <engine/EgMain.h>

void cEgEngine::Construct()
{
    TK_INFO("Engine!");
}

void cEgEngine::Render()
{
    this->mpRenderer->Render();
}

void cEgEngine::Destruct()
{
    delete this->mpRenderer;
}

void cEgEngine::Configure()
{
    this->mpRenderer = new cEgRenderer();
}