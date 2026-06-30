// FUNC_NAME: VFXManager::addEffect
void __thiscall VFXManager::addEffect(int this, int emitterInfo, int effectData)
{
    int index;
    int slotPtr;

    // If pool is full (64 slots), try to compact and possibly flush
    if (*(int *)(this + 0xa28) == 0x40)
    {
        compactPool();                      // FUN_007299c0
        if (*(int *)(this + 0xa28) == 0x40)
        {
            resetPool(0);                   // FUN_00729730(0)
        }
    }

    index = *(int *)(this + 0xa28);
    slotPtr = this + 0x28 + index * 0x28; // element size 0x28
    *(int *)(this + 0xa28) = index + 1;

    initEffectSlot(effectData);              // FUN_00729030

    // Set lifetime / time offset from emitter info
    *(float *)(slotPtr + 0x24) = *(float *)(emitterInfo + 0x68) + gTimeOffset; // DAT_01205228

    // Attach to parent transform if effect type is valid
    if ( (*(char *)(effectData + 0x1c) == '\0') &&
         (*(int *)(effectData + 8) != 0) &&
         (*(int *)(effectData + 8) != 0x48) )
    {
        int transformData = getTransformData();     // FUN_00471610
        *(byte *)(slotPtr + 0x1c) = 1;               // flag: attached to parent
        *(long long*)(slotPtr + 0x10) = *(long long*)(transformData + 0x30);
        *(int*)(slotPtr + 0x18) = *(int*)(transformData + 0x38);
    }
}