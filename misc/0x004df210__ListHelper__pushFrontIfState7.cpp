// FUNC_NAME: ListHelper::pushFrontIfState7
// Function address: 0x004DF210
// Role: Inserts a new node at the front of a global linked list (using pprev pointer technique) if the global state equals 7.
// Parameters: param1, param3, param4 are forwarded to node creation; param2 is unused.
// The global head pointer is stored at g_pListHead (address used as pprev target).
// The global state g_eGameState is checked for value 7 (likely a specific game state).
void __cdecl pushFrontIfState7(int param1, int param2, int param3, int param4)
{
    // Global head pointer of the linked list (address stored for pprev updates)
    Node* volatile* pHeadAddr = &g_pListHead; // corresponds to unaff_ESI in decompiled code
    Node* pNewNode = nullptr;

    // Reset the head pointer to null (clears previous list head)
    *pHeadAddr = nullptr;

    if (g_eGameState == 7)                     // DAT_01194540 == 7
    {
        // Perform any necessary initialization before creating the node
        initializeNodeContext();               // FUN_0051d730

        // Create a new node using the provided parameters (param2 is ignored)
        pNewNode = createNode(param1, param3, param4);  // FUN_0051c7c0

        // Note: the original code checks *pHeadAddr != 0, but it was just set to 0, so this path is never taken.
        // Possibly a leftover from a more complex operation.

        // Set the head pointer to the new node
        *pHeadAddr = pNewNode;

        // If the node was successfully created, store the address of the head pointer in node->field8 (offset 0x8)
        // This allows the node to later update the head pointer when removed (pprev technique)
        if (pNewNode != nullptr)
        {
            pNewNode->pprev = pHeadAddr;       // *(int**)(pNewNode + 0x8) = pHeadAddr
        }
    }
}