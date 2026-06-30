// FUN_004c5d70: someClass::UpdateActiveEffect
void __fastcall someClass::UpdateActiveEffect( /* this unused in ECX */ int param_2)
{
    // FUN_004166b0: bool checkTargetActive() // also may set a pointer in EDX? but we treat as returning bool
    bool isActive = static_cast<bool>(FUN_004166b0());
    
    // extraout_EDX: pointer from the call (value in EDX after FUN_004166b0) – assumed to be a pointer to current effect target
    // DAT_012058e8: global active effect target variable
    // Condition checks that effect is active and the returned pointer matches the global active target
    int* effectTarget; // pretend this captures the EDX value
    if (isActive && (DAT_012058e8 == effectTarget))
    {
        // +0x10, +0xB8: fields of effectTarget object
        // param_2 + 0xF0: offset 0xF0 from the second parameter (likely an object position or handle)
        FUN_0060b020(*(int*)(effectTarget + 0x10), // effect source identifier?
                     *(int*)(effectTarget + 0xB8), // effect offset?
                     param_2 + 0xF0);             // target position / index
    }
}