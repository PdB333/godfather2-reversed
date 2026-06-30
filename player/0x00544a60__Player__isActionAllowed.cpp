// FUNC_NAME: Player::isActionAllowed
bool __fastcall Player::isActionAllowed(int *this) {
    char cVar1;
    // Call virtual function at vtable+0x198 (likely "isStateActive" or similar)
    cVar1 = (*(code **)(*this + 0x198))();
    if (cVar1 != '\0' && *(int *)(*(int *)((char *)this + 0x360) + 8) != 0) {
        return true;
    }
    return false;
}