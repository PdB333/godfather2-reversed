// FUNC_NAME: Player::updateActionState
void __fastcall Player::updateActionState(Player* this)
{
    int* pGlobalObj;
    int index;
    int* pActionArray;

    // Get global action manager (DAT_01129948 + 0x1c)
    pGlobalObj = *(int**)(g_someManager + 0x1c);
    index = 0;
    if (pGlobalObj != nullptr) {
        index = *(int*)(pGlobalObj + 0x18); // Current action index from global
    }

    // If this player has an active action slot (e.g., weapon or ability)
    if (*(int*)(this + 0xf4) != 0) {
        // Mark action as active (bit 0 at offset 0x118)
        *(uint32_t*)(this + 0x118) |= 1;

        // Compute pointer into action array (each entry 0xC bytes)
        pActionArray = (int*)(*(int*)(this + 0xf0) + index * 0xC);
        *(int**)(this + 0xfc) = pActionArray; // Store pointer to current action

        // Read first field of action entry (likely a pointer to another object)
        index = *pActionArray;
        *(int*)(this + 0x12c) = 0; // Clear some timer/counter

        // Follow pointer chain to set another field
        int* pNext = *(int**)(index + 0x110);
        if (*pNext != 0) {
            *(int*)(this + 0x11c) = *pNext;
        }
    }

    // Notify global manager (call virtual function at vtable+0x28 with arg 0)
    if (pGlobalObj != nullptr) {
        (**(void (__thiscall**)(int))(*(int*)(pGlobalObj + 4) + 0x28))(0);
    }
}