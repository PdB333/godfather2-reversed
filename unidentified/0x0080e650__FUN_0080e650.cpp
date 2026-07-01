// FUNC_NAME: SomeClass::maybePlaySoundOrVFX
bool __thiscall SomeClass::maybePlaySoundOrVFX(int this, undefined4 param_2, undefined4 param_3, char param_4, undefined4 param_5)
{
    char cVar1;
    uint uVar2;
    
    // Get flags from object at this+0x50 (likely a component or state) at offset 0x830
    uVar2 = *(uint *)(*(int *)(this + 0x50) + 0x830);
    if (param_4 != '\0') {
        uVar2 = uVar2 & 0xfbffffff; // Clear bit 25 (0x4000000) when param_4 is true
    }
    
    // Call to play something (sound/VFX) with the (possibly modified) flags
    // 0x60336 might be a sound or event ID
    cVar1 = FUN_0054ebf0(param_3, param_2, 0x60336, uVar2, 0, 0, param_5, 0, 0);
    return cVar1 == '\0'; // Return true if function succeeded (returned 0)
}