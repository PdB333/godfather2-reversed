// FUNC_NAME: LinkedList::extractRange
// Address: 0x00622b80
// Role: Extracts a sublist [startNode, endNode] from a doubly linked list with sentinel.
// The list uses a sentinel node (mSentinel at +0x1c). The sentinel has fields:
//   +0x00: prev pointer
//   +0x04: next pointer
//   +0x08: (likely data, not used here)
// The class also stores the list size at +0x20 (mSize).
// This function removes the nodes from start (param_3) to end (param_5) inclusive from the list.
// The output array param_1 receives [new list header, start of extracted range].
// In the special case where the range covers the entire list, the list is reset to empty.

// Assumes __thiscall: this pointer in EDI, parameters via stack.
// FUN_00b97aea is an assertion failure.
// FUN_006240a0 probably does nothing meaningful here (maybe a no-op or debug).
// FUN_00623fa0 returns the next node after a given one.
// FUN_006217f0 removes a node from the list (unlinks it).

void __thiscall LinkedList::extractRange(int* param_1, int param_2, int param_3, int param_4, int param_5)
{
    // this = unaff_EDI
    int iVar1;
    // placeholder for an 8-byte local used by FUN_006217f0
    char local_8[8];

    // Dereference sentinel to get its first field (typically prev, but here used as key)
    iVar1 = **(int**)(this + 0x1c); // iVar1 = mSentinel->prev

    // Validate input: param_2 must be non-zero and equal to this
    if ((param_2 == 0) || (param_2 != this)) {
        FUN_00b97aea(); // assertion failed
    }

    // If the start node equals the sentinel's prev (i.e., the list tail?) and the end node equals that same value
    if (param_3 == iVar1) {
        iVar1 = *(int*)(this + 0x1c); // re-read mSentinel
        // Validate param_4 similarly
        if ((param_4 == 0) || (param_4 != this)) {
            FUN_00b97aea();
        }
        // Check that the end node also matches the sentinel's prev
        if (param_5 == iVar1) {
            // Entire list is being extracted (range covers all nodes, i.e., from sentinel->prev to itself)
            // This path resets the list to empty.
            // FUN_006240a0 is called with something from sentinel->next? Likely a no-op.
            FUN_006240a0(*(undefined4*)(*(int*)(this + 0x1c) + 4)); // (sentinel->next) passed
            // Set sentinel->next = sentinel (circular empty list)
            *(int*)(*(int*)(this + 0x1c) + 4) = *(int*)(this + 0x1c);
            // Zero the size
            *(undefined4*)(this + 0x20) = 0;
            // Set sentinel->prev = sentinel
            *(undefined4*)*(undefined4*)(this + 0x1c) = *(undefined4*)(this + 0x1c);
            // Set sentinel->??? (offset 8?) = sentinel (maybe data field or unused)
            *(int*)(*(int*)(this + 0x1c) + 8) = *(int*)(this + 0x1c);
            // Output: first element = this (list header), second = sentinel->prev (which is now sentinel itself)
            param_1[1] = **(int**)(this + 0x1c); // sentinel->prev → sentinel
            *param_1 = this;
            return;
        }
    }

    // General case: iterate from start to end, removing nodes one by one
    while (true) {
        // Validate param_2 and param_4: they must be non-zero and equal (both should be this)
        if ((param_2 == 0) || (param_2 != param_4)) {
            FUN_00b97aea();
        }
        if (param_3 == param_5) break;
        // Move to next node (FUN_00623fa0 likely modifies some iterator or global state)
        FUN_00623fa0();
        // Remove the node at param_3 from the list, placing info in local_8
        FUN_006217f0(this, local_8, param_2, param_3);
    }
    // Output: first element = this (list header), second = start node (param_3)
    param_1[1] = param_3;
    *param_1 = param_2; // param_2 is this (same as this)
    return;
}