// FUNC_NAME: Manager::insertOrUpdateEntry
// Address: 0x00708f80
// Role: Inserts or updates an entry in a container indexed by a 128-bit key.
// Uses an intrusive linked list where each node has a back-pointer (offset +8)
// pointing to the address of the pointer that references it.
void __thiscall Manager::insertOrUpdateEntry(int *this, int *key, int **outNodePtr)
{
    // Key is considered non-empty if any of its 4 ints are non-zero
    if (key[0] != 0 || key[1] != 0 || key[2] != 0 || key[3] != 0) {
        // Get a global context (e.g., thread-specific data or memory pool)
        int context = getGlobalContext();                     // FUN_00471610
        // Initialize a temporary buffer (76 bytes) using the context
        uchar buffer[76];
        initializeBuffer(buffer, context);                   // FUN_0044b4e0

        // Call virtual function at vtable+0x58 to get an allocation context
        // Signature: (int)(int arg0, int *this, int arg2, int arg3)
        int allocContext = (*(int (__thiscall **)(int, int *, int, int))
                           (*this + 0x58))(0, this, 0xffffffff, 0);

        // Allocate or locate a node; returns pointer to a slot (pointer-to-pointer)
        // Also outputs an old node (if any) via stack variable 'oldNode'
        int oldNode;
        int **slot = (int **)findOrCreateNode(&oldNode, key, buffer, allocContext);
                                            // FUN_004df330

        // If the output pointer already points to a node, detach it
        if (*outNodePtr != nullptr) {
            *(int *)(*outNodePtr + 8) = 0;  // Clear back-pointer
            *outNodePtr = nullptr;
        }

        // Get the new node from the slot
        int *newNode = *slot;
        *outNodePtr = newNode;
        if (newNode != nullptr) {
            // Set the node's back-pointer to point to our output pointer
            *(int **)(newNode + 8) = outNodePtr;
            // Clear the slot (so the node is under our ownership)
            *slot = nullptr;
        }

        // If there was an old node (replaced entry), detach its back-pointer
        if (oldNode != 0) {
            *(int *)(oldNode + 8) = 0;
        }
    }
}