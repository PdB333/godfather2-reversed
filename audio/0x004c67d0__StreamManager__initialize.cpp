// FUNC_NAME: StreamManager::initialize
void __thiscall StreamManager::initialize(StreamManager *this)
{
    // +0x10: first stream handle (e.g., render manager reference)
    *(int *)((char *)this + 0x10) = getMainStreamHandle();           // FUN_0060a380
    // +0x14: second stream handle (e.g., bank stream manager reference)
    *(int *)((char *)this + 0x14) = getStreamManagerHandle(PTR_DAT_0110a36c); // FUN_0060a2e0
    initStreamSystem();                                                // FUN_006127d0
}