// FUNC_NAME: Sentient::hasCombatTarget
bool __fastcall Sentient::hasCombatTarget(void* thisPtr) {
    // Checks if the combat target pointer at offset +0x14c is non-null
    return *(int*)((char*)thisPtr + 0x14c) != 0;
}