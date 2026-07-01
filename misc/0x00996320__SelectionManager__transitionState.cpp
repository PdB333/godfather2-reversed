// FUNC_NAME: SelectionManager::transitionState
void __thiscall SelectionManager::transitionState(int newState) {
    if (newState == 4) {
        return;
    }

    // Get global highlight color from DAT_01223480+0x24 (likely RGBA, mask alpha)
    uint globalColor = *(uint *)(0x01223480 + 0x24);
    uint colorMask = globalColor & 0xFFFFFF00;

    // If current state is 3 (e.g., hovered) and there are entities, apply highlight/alpha
    if (*(int *)(this + 0x50) == 3) {
        int count = *(int *)(this + 0x38);
        for (int i = 0; i < count; i++) {
            char *entry = *(char **)(this + 0x34) + i * 0xC0; // Each entity is 0xC0 bytes
            if (*(int *)(entry + 8) != 0) {
                FUN_009fb5f0(*(undefined4 *)(entry + 8), colorMask); // setHighlight
            }
            if (*(int *)(entry + 4) != 0) {
                FUN_009fa920(*(undefined4 *)(entry + 4), colorMask); // setAlpha
            }
        }
    }

    // If flags bit 2 set and current state is 2 (selected), call per-entity function (e.g., commit color)
    if ((*(byte *)(this + 0x4c) & 2) != 0 && *(int *)(this + 0x50) == 2) {
        int count = *(int *)(this + 0x38);
        for (int i = 0; i < count; i++) {
            char *entry = *(char **)(this + 0x34) + i * 0xC0;
            FUN_009ebfc0(&local_5, *(undefined4 *)(entry + 0xB4)); // getColorFromEntity?
        }
    }

    // Call global state enter/exit handlers
    if (newState == 1) {
        FUN_00995660(); // enterState1
    } else {
        FUN_009955f0(); // enterOtherState
    }

    // Special case: flags bit2 set and transitioning to state 2
    if ((*(byte *)(this + 0x4c) & 2) != 0 && newState == 2) {
        int count = *(int *)(this + 0x38);
        for (int i = 0; i < count; i++) {
            char *entry = *(char **)(this + 0x34) + i * 0xC0;
            FUN_009ebe70(*(undefined4 *)(entry + 0xB4)); // finalizeSelection
        }
        *(uint *)(this + 0x4c) |= 8;
        *(int *)(this + 0x50) = 2;
        return;
    }

    // For state 3, apply with constant value 1 (e.g., full brightness)
    if (newState == 3) {
        int count = *(int *)(this + 0x38);
        for (int i = 0; i < count; i++) {
            char *entry = *(char **)(this + 0x34) + i * 0xC0;
            if (*(int *)(entry + 8) != 0) {
                FUN_009fb5f0(*(undefined4 *)(entry + 8), 1);
            }
            if (*(int *)(entry + 4) != 0) {
                FUN_009fa920(*(undefined4 *)(entry + 4), 1);
            }
        }
    }

    // Update flags and state
    *(uint *)(this + 0x4c) |= 8;
    *(int *)(this + 0x50) = newState;
}