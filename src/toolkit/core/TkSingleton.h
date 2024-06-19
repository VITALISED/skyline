#pragma once

template <typename T>
class cTkSingleton
{
  public:
    void Construct();
    void Destruct();

    static T &GetInstance()
    {
        static T gInstance;

        if (gInstance.mbInitialised == false)
        {
            gInstance               = T();
            gInstance.mbInitialised = true;
        }

        return gInstance;
    }

  protected:
    cTkSingleton()                     = default;
    cTkSingleton(const cTkSingleton &) = delete;

  private:
    bool mbInitialised;
};