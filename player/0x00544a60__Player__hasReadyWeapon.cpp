// FUNC_NAME: Player::hasReadyWeapon
bool __fastcall Player::hasReadyWeapon(int* thisPtr) {
    // Call virtual function at vtable offset 0x198 (index 102)
    // Returns char (likely bool)
    char cVar1 = ((char (__thiscall*)(void*))(*(int*)(*(int*)thisPtr + 0x198)))(thisPtr);
    if (cVar1 != 0) {
        // Check field at this+0x360 (a pointer), then offset +8 of that pointer
        int* fieldPtr = *(int**)((char*)thisPtr + 0x360);
        if (fieldPtr != 0 && *(int*)((char*)fieldPtr + 8) != 0) {
            return true;
        }
    }
    return false;
}