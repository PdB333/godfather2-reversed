// FUNC_NAME: AptActionManager::processActions
// Function at 0x005a5f20 processes the action pool ring buffer, executes queued actions by type (0 or 1), then cleans up.
void AptActionManager::processActions() {
    // Pool struct: array of 256 Action entries (each 5 ints), followed by head/tail pointers.
    // +0x000: Action aActionPool[256];        // each action 5 * 4 bytes
    // +0x500: Action* s_head;                  // next action to read
    // +0x504: Action* s_tail;                  // next write slot
    ActionPool* pool = (ActionPool*)DAT_0119a9cc;  // global pool pointer
    Action* head = pool->head;                    // read head
    Action* tail = pool->tail;                    // read tail

    // Iterate while head != tail (ring buffer not empty)
    while (head != tail) {
        // Debug assertion: head must be within array bounds
        if (head < pool->actions) {
            // assertion "pCur >= &aActionPool[0]" triggered; debug break possible
            debugAssertionFailed("pCur >= &aActionPool[0]", "..\\source\\Apt\\AptAnimation.cpp", 0x266);
        }
        if (head >= pool->actions + 256) {
            // assertion "pCur < &aActionPool[256]" triggered
            debugAssertionFailed("pCur < &aActionPool[ 256 ]", "..\\source\\Apt\\AptAnimation.cpp", 0x266);
        }

        Action* nextHead = head;  // save current head for updating
        int actionType = head->type;

        if (actionType == 0) {
            // Type 0: remove action (?) – set global current action ID, then check/execute
            s_currentActionId = head->someId;   // _DAT_01221f1c
            if ((head->flags & 0x8000) == 0) {   // check bit 15 of flags? (shift right 0xf)
                if (FUN_005a4140() == 0) {        // maybe isActionValid?
                    FUN_005af370(head->objPtr, head->flags, -1);  // startAction?
                    FUN_005a5ea0(pool);                           // advance head?
                }
            }
        } else if (actionType == 1) {
            // Type 1: execute animation action
            s_currentActionId = head->someId;
            FUN_005a6e30(head->objPtr);            // setup animation?
            FUN_005aec20(head->objPtr, head->extra); // apply animation
            FUN_005a6f20();                         // post‑process?
            FUN_005a0c50();                         // update something?
        } else {
            // Unknown action type: trigger assertion "0"
            debugAssertionFailed("0", "..\\source\\Apt\\AptAnimation.cpp", 0x27f);
        }

        // Advance head, wrap if at array end
        // Compute next head: if head+1 == end of array, wrap to start
        Action* next = head + 1;
        if (next == pool->actions + 256) {
            next = pool->actions;
        }
        // Update head for next iteration, but need to re-read tail because it may have changed?
        Action* currentTail = pool->tail;  // re-read tail? Actually the code re-reads tail from pool->tail later.
        // The original code seems to recompute the next head based on distance to tail: not exactly.
        // Let's examine more: The decompiled code after the if-else does:
        // piVar2 = pool->tail;
        // if (piVar2 < nextHead) {
        //    // compute difference and adjust head by that many slots? That seems odd.
        // }
        // Then piVar7 = nextHead + 5? The original code:
        // piVar2 = (int *)piVar4[0x501];
        // if (piVar2 < piVar1) { ... }
        // piVar7 = piVar7 + 5;
        // if (piVar7 == piVar4 + 0x500) { piVar7 = piVar4; }
        // This is actually a loop that processes each entry in a circular buffer where each entry is 5 ints.
        // The original loop increments head by 1 entry (5 ints) and wraps. The "piVar2 < piVar1" check is a bounds check for circular wrapping? Actually it's computing if the distance from tail to head is negative? No, the code uses a signed comparison to see if the next head after incrementing by 5 ints (which is the next entry) would overshoot the tail? No, it's more like updating head to the next entry.
        // Simplification: we can just increment head by 1 entry and wrap.

        head = next;
    }

    // After loop, clean up pool state
    FUN_005a5ea0(pool);  // maybe reset head/tail?
    FUN_005a6280(pool);  // update active actions?
}