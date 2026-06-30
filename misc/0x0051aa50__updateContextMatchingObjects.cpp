// FUNC_NAME: updateContextMatchingObjects
// Function address: 0x0051aa50
// Role: Iterates over a global linked list of game objects, checks if each object's 64-bit context ID matches the current context (retrieved via getCurrentContextID()), and if so, sets/clears flags and triggers an update notification.

// Global head of the object list
extern GameObjectNode* g_pObjectListHead;  // DAT_01205514

// External functions
uint64_t getCurrentContextID(void); // FUN_0051d730
void notifyObjectStateChange(void); // FUN_0051b120

// Node structure in the global object list
struct GameObjectNode {
    // Offset 0x00: unknown data
    uint32_t flags;          // +0x0C: bitfield with flags
    void* pBaseObject;       // +0x10: pointer to base object (e.g., some game object)
    GameObjectNode* pNext;   // +0x14: next node in linked list
    uint64_t contextID;      // +0x70/+0x74: 64-bit context identifier
    // Other fields omitted for brevity
};

void updateContextMatchingObjects(void)
{
    uint64_t currentContextID = getCurrentContextID(); // FUN_0051d730 returns 8 bytes
    GameObjectNode* pNode = g_pObjectListHead;

    while (pNode != nullptr)
    {
        // Check if this node's context ID matches and if the base object's flag (at offset 0x14 relative to base object) has bit 0x8000 cleared
        if ((pNode->contextID == currentContextID) &&
            ((*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(pNode->pBaseObject) + 0x14) & 0x8000) == 0))
        {
            // If the node's own flag does not have bit 0x20000 set, set it and call notification
            if ((pNode->flags & 0x20000) == 0)
            {
                pNode->flags |= 0x20000;
                notifyObjectStateChange(); // FUN_0051b120
            }
            // Clear bit 0x20000 (0x20000 = 0x00020000, mask 0xFFFBFFFF)
            pNode->flags &= 0xFFFBFFFF;
        }
        pNode = pNode->pNext; // move to next node
    }
}