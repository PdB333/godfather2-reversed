// FUNC_NAME: EffectManager::removeAllEntries
void __fastcall EffectManager::removeAllEntries(int* thisPtr) {
    if (thisPtr[1] != 0) {
        uint index = 0;
        int count = (*(int (__thiscall**)(int*))(*thisPtr + 0x10))(thisPtr); // vfunc getCount
        if (count != 0) {
            int* entryPtr = thisPtr + 5; // start of entry array (+0x14 offset)
            do {
                if (*entryPtr != 0) {
                    // removeEffect(manager, effectPtr, effectName)
                    FUN_0060add0(thisPtr[1], *entryPtr, &DAT_01225db0);
                }
                index++;
                entryPtr += 5; // each entry is 20 bytes
                count = (*(int (__thiscall**)(int*))(*thisPtr + 0x10))(thisPtr); // re-check count each iteration
            } while (index < count);
        }
    }
    return;
}