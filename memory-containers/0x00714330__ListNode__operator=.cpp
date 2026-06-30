// FUNC_NAME: ListNode::operator=
// Reconstructed assignment operator for an intrusive linked list node or reference-counted handle.
// The structure has a pointer at +0x04 to a target object, which itself contains a back-link at +0x04
// pointing to this node's +0x04 field (used to maintain a doubly linked list of references).
// The node also stores a copy of the target's original +0x04 value at +0x08 (likely the next pointer in the list).
// An additional 20 bytes of data are copied starting at +0x0C.

int __thiscall ListNode::operator=(ListNode *this, ListNode *other)
{
    int **thisPrevPtr = (int **)(this + 4);      // +0x04: pointer to target object
    int **otherPrevPtr = (int **)(other + 4);   // +0x04

    if (thisPrevPtr != otherPrevPtr)
    {
        int *newTarget = *otherPrevPtr;          // value from other
        if (*thisPrevPtr != newTarget)
        {
            if (*thisPrevPtr != (int *)0)
            {
                FUN_004daf90(thisPrevPtr);       // release old target (e.g., decrement refcount)
            }
            *thisPrevPtr = newTarget;            // take ownership of new target

            if (newTarget != (int *)0)
            {
                // Target at +0x04 holds a back-link (pointer to the next node's "prev" pointer)
                // We copy the next pointer from the target and update the target's back-link to us.
                *(int **)(this + 8) = *(int **)(newTarget + 4);   // +0x08 = target->+0x04
                *(int **)(newTarget + 4) = thisPrevPtr;            // target->+0x04 = &this->+0x04
            }
        }
    }

    // Copy remaining data (likely vtable or other fields)
    *(long long *)(this + 0x0C) = *(long long *)(other + 0x0C);   // +0x0C (8 bytes)
    *(int *)(this + 0x14) = *(int *)(other + 0x14);               // +0x14
    *(int *)(this + 0x18) = *(int *)(other + 0x18);               // +0x18
    *(int *)(this + 0x1C) = *(int *)(other + 0x1C);               // +0x1C
    *(int *)(this + 0x20) = *(int *)(other + 0x20);               // +0x20

    return (int)this;
}