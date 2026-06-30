// FUNC_NAME: SomeList::advanceToNextActive / skipInactiveNodes
// Function address: 0x00624190
// This function traverses a linked list starting from the node pointed by this+0x8,
// skipping nodes where the byte at offset 0x15 is zero (inactive).
// It stops when a node with non-zero flag is found, but does not store it anywhere.
// Likely used as part of a higher-level iteration loop.

class SomeList {
    // Assuming some list manager or iterator
public:
    void advanceToNextActive(void) __thiscall
    {
        int nodePtr;          // current node traversal pointer
        char flag;            // active flag at node+0x15

        nodePtr = *(int *)(this + 8);    // this+0x8: head/current node pointer
        flag = *(char *)(nodePtr + 0x15); // node offset 0x15: boolean active flag

        while (flag == '\0') {            // while node is inactive
            nodePtr = *(int *)(nodePtr + 8); // node offset 0x8: next node pointer
            flag = *(char *)(nodePtr + 0x15);
        }
        // No observable side effect; the loop doesn't write back to this object.
        return;
    }
};