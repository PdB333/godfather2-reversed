// FUNC_NAME: GlobalManager::setPointer
void GlobalManager::setPointer(void* pointer) // argument passed in EAX
{
    // Store the pointer in global variable gGlobalPointer (0x01127804)
    gGlobalPointer = pointer;

    // Check if all initialization prerequisites are met:
    // 1. gInitializationMarker (0x012058e8) points to the sentinel address (0x01127760)
    // 2. gInitStep1 (0x01127774) equals gInitStep2 (0x01127874)
    // 3. gSomeFlag (0x01127844) is non-zero
    if ((_DAT_012058e8 == &PTR_PTR_01127760) &&
        (_DAT_01127774 == _DAT_01127874) &&
        (_DAT_01127844 != 0))
    {
        // All conditions satisfied; call initialization finalizer (0x006063b0)
        FUN_006063b0();
    }
}