//FUNC_NAME: Sentient::isInCombat
bool Sentient::isInCombat() {
    // +0x58: pointer to a state/controller object (e.g., CombatKnowledge or CharacterState)
    int* pState = *(int**)(this + 0x58);

    // +0x858: flag or pointer in the state object; if zero, use one path, else another
    if (*(int*)(pState + 0x858) == 0) {
        int local_4 = 0;
        int local_8 = 0;

        // +0x9c: pointer to a behavior subobject; the actual behavior base is at offset -0x48
        int* pBehaviorBase;
        if (*(int*)(this + 0x9c) == 0) {
            pBehaviorBase = nullptr;
        } else {
            pBehaviorBase = (int*)(*(int*)(this + 0x9c) - 0x48);
        }

        // Virtual function at vtable offset 0x1cc on the behavior object
        // Likely a method that fills local_8/local_4 with some state info
        if (pBehaviorBase) {
            (*(void (**)(int*))(*(int*)pBehaviorBase + 0x1cc))(&local_8);
        }

        // Call helper function with the state, behavior base, and local_8
        char result;
        if (*(int*)(this + 0x9c) == 0) {
            result = FUN_00884ac0(&local_8, pState, 0);
        } else {
            result = FUN_00884ac0(&local_8, pState, *(int*)(this + 0x9c) - 0x48);
        }
        return result == '\0';
    } else {
        // Alternative path when the flag at +0x858 is non-zero
        int* pBehaviorBase2;
        if (*(int*)(this + 0x9c) == 0) {
            pBehaviorBase2 = nullptr;
        } else {
            pBehaviorBase2 = (int*)(*(int*)(this + 0x9c) - 0x48);
        }
        char result = FUN_00884b90(pState, pBehaviorBase2);
        return result == '\0';
    }
}