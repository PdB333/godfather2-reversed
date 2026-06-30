// FUNC_NAME: Player::canPerformAction
// Address: 0x007192a0
// Role: Checks two internal state fields (offsets 0x2004 and 0x24cc) and a global condition before allowing an action.
// The object at this+0x18 points to a large data structure (likely PlayerData) with state IDs.
// Values 0 and 0x48 appear to be sentinel states (e.g., STATE_INVALID, STATE_DEAD).

// Forward declaration of the global check function
bool __fastcall FUN_00723680(int param_1);

bool __fastcall Player::canPerformAction(Player* this) {
    // Dereference this->data (at +0x18) then read state field at +0x2004
    int* data = *(int**)((int)this + 0x18);
    int stateA = *(int*)((int)data + 0x2004);
    bool result = false;

    // Check if stateA is valid (not 0 and not 0x48)
    if (stateA != 0 && stateA != 0x48) {
        // Read second state field at +0x24cc
        int stateB = *(int*)((int)data + 0x24cc);
        if (stateB != 0 && stateB != 0x48) {
            // Global condition check (e.g., is game active, is player alive)
            result = FUN_00723680(0xffffffff) != 0;
        }
    }
    return result;
}