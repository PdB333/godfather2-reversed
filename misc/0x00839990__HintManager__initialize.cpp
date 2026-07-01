// FUNC_NAME: HintManager::initialize
void __thiscall HintManager::initialize(int this)
{
    int* piVar1;
    char cVar2;
    uint hintResult;
    const char* logString;
    int arg2;
    char arg3;

    *(uint*)(this + 0xe4) = 2;  // Set state to "initializing" (offset +0xE4)
    hintResult = 10;
    if (*(int*)(this + 0x8c) == 0)  // Check if hint count is zero
    {
        hintResult = 14;  // Different hint resource ID
    }
    hintResult = HintSystem::allocateHandle(0, *(int*)(this + 0x8c), hintResult, 0, 0, 0);
    *(uint*)(this + 0xf8) = hintResult;  // Store allocated handle at offset +0xF8
    HintData::loadAll();  // Static function to load hints from data

    // Check if GameManager singleton exists and if it reports "hints already loaded"
    if ( (**(int**)(DAT_012233a0 + 4) != 0) &&
         (piVar1 = (int*)(**(int**)(DAT_012233a0 + 4) - 0x1f30), piVar1 != (int*)0x0) )
    {
        // Virtual call at vtable+0x28c (likely isHintSystemActive)
        cVar2 = (*(char (__thiscall**)(int))(*piVar1 + 0x28c))(piVar1);
        if (cVar2 != '\0')
        {
            logString = DAT_0112a618;  // String: "Hint system already loaded"
            goto LAB_00839a1c;
        }
    }
    logString = DAT_0112a5cc;  // String: "Hint system initialized"

LAB_00839a1c:
    arg2 = 0;
    arg3 = 0;
    FUN_00408a00(&logString, 0);  // Log with format string (likely Debug::print)
    return;
}