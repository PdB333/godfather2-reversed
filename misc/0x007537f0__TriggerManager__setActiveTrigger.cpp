// FUNC_NAME: TriggerManager::setActiveTrigger

// Address: 0x007537f0
// Sets the currently active trigger node and updates trigger data.
// The trigger node is embedded at offset 0x48 within a larger owner object.
// The function uses a global singly-linked list where each node's 'next' 
// pointer references the head variable itself (sentinel trick).
//
// Parameters:
//   ownerObject - Pointer to an object containing the trigger node at +0x48.
//                 If null, the active trigger is cleared.
//   param2      - Stored in a global (gTriggerParamB).
//   param3      - Stored as the active trigger data (gActiveTriggerData).

// Inferred global data section (addresses from Ghidra exports)
static TriggerNode* gActiveTriggerListHead = nullptr; // 0x0112ae84
static int32_t      gActiveTriggerData       = 0;   // 0x0112ae70
static int32_t      gTriggerParamB           = 0;   // 0x0112ae74
static int32_t      gTriggerOldNext          = 0;   // 0x0112ae88 (saved but unused in this function)

// Two fields copied from the global game manager singleton (FUN_00471610 = GameManager::getInstance())
static uint64_t     gTriggerGUIDHigh;                // 0x0112ae78 (8 bytes)
static uint32_t     gTriggerGUIDLow;                 // 0x0112ae80 (4 bytes)

// Structure of a trigger node (offsets relative to node start)
struct TriggerNode {
    int32_t       unknown;     // +0x00
    TriggerNode*  next;        // +0x04
};
static_assert(offsetof(TriggerNode, next) == 0x04, "Node layout mismatch");

// Forward declaration of the game manager singleton accessor
class GameManager;
GameManager* __cdecl GameManager_getInstance(); // FUN_00471610

// Helper: destroy a trigger node and potentially remove it from the list
void __cdecl destroyTriggerNode(TriggerNode** head); // FUN_004daf90

// Main function
void __cdecl TriggerManager_setActiveTrigger(void* ownerObject, int32_t param2, int32_t param3)
{
    // Compute the pointer to the embedded trigger node
    TriggerNode* newNode = (ownerObject != nullptr)
                               ? reinterpret_cast<TriggerNode*>(static_cast<char*>(ownerObject) + 0x48)
                               : nullptr;

    // Copy GUID‑like data from the global game manager
    GameManager* gameMgr = GameManager_getInstance();
    gTriggerGUIDHigh = *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(gameMgr) + 0x20);
    gTriggerGUIDLow  = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(gameMgr) + 0x28);
    gTriggerParamB   = param2;

    // If the same node is already active, just update the data
    if (gActiveTriggerListHead == newNode) {
        gActiveTriggerData = param3;
        return;
    }

    // Different node: remove the old active trigger if present
    if (gActiveTriggerListHead != nullptr) {
        destroyTriggerNode(&gActiveTriggerListHead);
    }

    // Set the new head
    gActiveTriggerListHead = newNode;

    // If the new node exists, insert it into the list.
    // Its 'next' pointer is set to the address of the head variable itself,
    // forming a sentinel‑based list where the head variable acts as the first node.
    if (newNode != nullptr) {
        // Save the previous next value (unused, but stored to a global)
        gTriggerOldNext = reinterpret_cast<int32_t>(newNode->next);
        // Point the node's next to the head variable (sentinel)
        newNode->next = reinterpret_cast<TriggerNode*>(&gActiveTriggerListHead);
    }

    // Store the trigger data
    gActiveTriggerData = param3;
}