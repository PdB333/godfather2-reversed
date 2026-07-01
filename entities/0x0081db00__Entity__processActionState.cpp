// FUNC_NAME: Entity::processActionState
// Address: 0x0081db00
// This function processes an action state (actionState) for an entity (this).
// It checks flags, selects a behavior function pointer, and applies it to a list of animation nodes.

void __thiscall Entity::processActionState(void* this_ptr, int* actionState) {
    int* someData = (int*)actionState[0x3c]; // pointer to e.g. animation data (offset +0xF0)
    actionState[0x3b] = 0;                  // clear some flag at +0xEC

    if (actionState[2] == 0)                // action state invalid or finished?
        goto skip;

    prepareActionState(actionState);         // FUN_0081d0d0 - e.g., reset interpolation or state

    uint flags = actionState[0x1c];          // behavior flags at +0x70
    void (*behaviorFunc)() = nullptr;

    if ((flags & 4) == 0) {                  // bit 2 not set
        if ((flags & 2) != 0) {              // bit 1 set
            behaviorFunc = (void (*)())0x008184b0; // behavior_SomeQuickAction
        } else {
            // If currentAction (offset 0x1f) is non-zero and not 0x48 (likely "none"),
            // and actionProgress (offset 0x21) is non-zero, and no blend flags (bits 0 and 3),
            // then skip update entirely.
            if ((actionState[0x1f] != 0) && (actionState[0x1f] != 0x48) &&
                (actionState[0x21] != 0) && ((flags & 9) == 0)) {
                goto skip;
            }
            // Lookup behavior from a type table stored at this+0x24
            int* typeTable = *(int**)((int)this_ptr + 0x24);
            int actionType = actionState[0];        // +0x00: type index
            // Table entry stride is 0x1c bytes (7 ints), function pointer at offset 0x18
            behaviorFunc = (void (*)())(typeTable[actionType * 7 + 6]);
            if (behaviorFunc == nullptr) {
                behaviorFunc = (void (*)())0x00818440; // defaultBehavior
            }
        }
    } else {
        behaviorFunc = (void (*)())0x00818490; // behavior_AnotherQuickAction
    }

    if (behaviorFunc != nullptr) {
        int* animBase = *(int**)((int)this_ptr + 0x10); // base of animation node array
        int animCount = *(int*)((int)this_ptr + 0x14);  // number of nodes
        int animEnd = (int)animBase + animCount * 0xc;   // each node is 12 bytes
        iterateAnimationNodes(animBase, animEnd, animCount, behaviorFunc); // FUN_0081d7a0
        postProcessActionState(actionState);             // FUN_0081c2d0
    }

skip:
    // Condition: if currentAction is zero or 0x48, or actionProgress is zero,
    // then set someData->+0x7c check; also assign actionState[0x2c]=0 as side effect.
    if (((actionState[0x1f] == 0) || (actionState[0x1f] == 0x48) || (actionState[0x21] == 0)) &&
        (actionState[0x2c] = 0, *(char*)((int)someData + 0x7c) != '\0')) {
        actionState[0x39] = 0;  // clear flag at +0xe4
    }
}

// Helper declarations (not part of this function, but used within):
// void prepareActionState(int* actionState);       // 0x0081d0d0
// void iterateAnimationNodes(int* base, int* end, int count, void (*func)()); // 0x0081d7a0
// void postProcessActionState(int* actionState);   // 0x0081c2d0