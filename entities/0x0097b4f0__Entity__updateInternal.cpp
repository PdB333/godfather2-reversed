// FUNC_NAME: Entity::updateInternal
void __fastcall Entity::updateInternal(int thisPtr)
{
    // +0x68: pointer to some component (e.g., TransformManager)
    // +0x10c: field within that component (e.g., scale or time offset)
    int timeValue = FUN_00471610(); // returns a timestamp or frame counter
    FUN_0097b440(
        *(int*)(thisPtr + 0x148),   // +0x148: render handle or pointer
        timeValue + 0x30,           // offset by 0x30 (48 units, possibly milliseconds)
        0,                          // some flag
        *(int*)(*(int*)(thisPtr + 0x68) + 0x10c) // value from component
    );
    FUN_00926830(_DAT_00d5c458, _DAT_00d5c458); // update global singleton (e.g., GodfatherGameManager)

    // DAT_01130020 +0x6c is likely a paused flag
    if (*(int*)(DAT_01130020 + 0x6c) == 0)
    {
        FUN_00916170(*(int*)(thisPtr + 0x148)); // continue update if not paused
    }
}