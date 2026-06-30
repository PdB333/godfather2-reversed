// FUNC_004bf3f0: EngineBase::releaseChildResource
void __fastcall EngineBase::releaseChildResource(int thisPtr)
{
    // clear some flag at offset +0xC (e.g., bActive, bInitialized)
    *(int*)(thisPtr + 0xC) = 0;

    int* childObj = *(int**)(thisPtr + 0x36C); // pointer to child resource object
    if (childObj != nullptr)
    {
        int* subChild = *(int**)(childObj + 0x14); // nested resource pointer
        if (subChild != nullptr)
        {
            FUN_004cb8a0(subChild); // release the nested resource
        }

        // global singleton (DAT_0122344c) – likely a game engine or factory manager
        if (DAT_0122344c != nullptr)
        {
            // call vtable function 0 (usually Release/AddRef) with argument 1
            (*(void(__thiscall**)(int))DAT_0122344c)(1);
        }

        // clear the child pointer
        *(int*)(thisPtr + 0x36C) = 0;
    }
}