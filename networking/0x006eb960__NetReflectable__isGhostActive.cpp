// FUNC_NAME: NetReflectable::isGhostActive
bool __thiscall NetReflectable::isGhostActive(int this)
{
    // +0x44: flags bitmask; bit 0 checked for active flag
    // +0x1C: object type ID; 0 = uninitialized, 0x48 = specific state (e.g., GhostState::Ready)
    if ((*(byte *)(this + 0x44) & 1) != 0 &&
        (*(int *)(this + 0x1C) == 0 || *(int *)(this + 0x1C) == 0x48)) {
        return true;
    }
    return false;
}