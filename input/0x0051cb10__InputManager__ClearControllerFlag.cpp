// FUNC_NAME: InputManager::ClearControllerFlag
// Function at 0x0051cb10: Iterates over a linked list of controller state nodes and clears a flag (bit 29) 
// either for all nodes (if param2 == 0) or for the node matching a derived index (param2).
// Globals: DAT_01205514 = g_pControllerListHead
// Struct ControllerNode at offsets:
//   +0x0C: uint32 flags
//   +0x14: ControllerNode* next
//   +0xC4: void* vtableOrType (used to compute index by subtracting 0x48)

struct ControllerNode
{
    uint8_t unknown_0x00[0x0C];   // padding/unknown
    uint32_t flags;                // +0x0C
    uint8_t unknown_0x10[0x04];    // +0x10
    ControllerNode* next;          // +0x14
    uint8_t unknown_0x18[0xAC];    // +0x18 to +0xC3
    void* typePointer;             // +0xC4
    // ... more fields ?
};

extern ControllerNode* g_pControllerListHead;  // DAT_01205514

// param1 (ECX) is unused, likely a dummy or this from a static call
static void __fastcall ClearControllerFlag(int param1, int param2)
{
    ControllerNode* node = g_pControllerListHead;
    while (node != nullptr)
    {
        if (param2 == 0)
        {
            // Clear bit 29 (0x20000000) in the flags field
            node->flags &= 0xDFFFFFFFu;  // ~0x20000000
        }
        else
        {
            // Compute an index from the type pointer (probably a vtable offset)
            int index = 0;
            if (node->typePointer != nullptr)
            {
                index = reinterpret_cast<int>(node->typePointer) - 0x48;
            }
            if (param2 == index)
            {
                // Clear flag for this node
                node->flags &= 0xDFFFFFFFu;
            }
        }
        node = node->next;
    }
}