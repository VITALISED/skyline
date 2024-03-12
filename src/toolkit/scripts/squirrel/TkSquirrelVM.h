#pragma once

#include <squirrel.h>

class cTkSquirrelVM
{
  public:
    cTkSquirrelVM() { this->Construct(); };

    void Construct();
    void Destruct();

    HSQUIRRELVM mVM;
};