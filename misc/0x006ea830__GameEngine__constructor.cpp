// FUNC_NAME: GameEngine::constructor
undefined4* __thiscall GameEngine::constructor(GameEngine* thisObj, byte flags)
{
    // Set vtable pointer
    thisObj->vtable = (void**)&PTR_FUN_00d5fd40;

    // Set secondary vtable / function pointer at +0x0C
    thisObj->secondaryVtable = (void**)&PTR_LAB_00d5fd3c;

    // Initialize global singleton / lock
    globalInit(&g_GlobalEngineData);

    // Check and release child object at +0x30 (param_1[0xc])
    if (thisObj->childObject != nullptr) {
        releaseObject(thisObj->childObject);
    }

    // Update secondary vtable after initialization
    thisObj->secondaryVtable = (void**)&PTR_LAB_00d5fd38;

    // Reset global flag
    g_EngineState = 0;

    // Another global initialization step
    globalInitStep2();

    // If the low bit of flags is set, destruct self (e.g., deallocate on heap)
    if ((flags & 1) != 0) {
        destructSelf(thisObj);
    }

    return thisObj;
}