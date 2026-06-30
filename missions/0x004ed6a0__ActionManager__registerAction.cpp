// FUNC_NAME: ActionManager::registerAction
// Address: 0x004ed6a0
// Registers an Action object with the action manager, keyed by an owner pointer.
// The action is allocated with EA memory allocator (hint: alignment 16, flags 2).
// The object is inserted into a hash table belonging to the global action manager.

#include <cstdint>

// -----------------------------------------------------------------------
// Forward declarations and external symbols
// -----------------------------------------------------------------------

// Global action manager instance (DAT_01223398)
extern class ActionManager* g_pActionManager;

// Global timestamp or unique ID (DAT_00e2b1a4)
extern uint32_t g_currentTimestamp;

// Vtable for the Action class (PTR_LAB_00e3738c)
extern void* VTABLE_Action;

// Memory allocator with alignment hints (FUN_009c8ed0)
void* __cdecl eaAllocate(size_t size, const void* hint);

// Insert a new action into the manager's hash table (FUN_00423cf0)
void insertIntoActionHashTable(void* key, class Action** ppAction, uint32_t slot);

// -----------------------------------------------------------------------
// Action structure (size 0x40)
// -----------------------------------------------------------------------
struct Action {
    void** vtable;            // +0x00
    int param3;               // +0x04
    int param4;               // +0x08
    int param5;               // +0x0C
    int field_10;             // +0x10 (unused)
    int field_14;             // +0x14 (unused)
    int field_18;             // +0x18 (unused)
    int field_1C;             // +0x1C (unused)
    int field_20;             // +0x20 (unused)
    int param2;               // +0x24 (ID/type)
    int field_28;             // +0x28 (unused)
    int field_2C;             // +0x2C (0xFFFFFFFF)
    uint32_t timestamp;       // +0x30 (current timestamp)
    int field_34;             // +0x34 (unused)
    int field_38;             // +0x38 (unused)
    // +0x3C padding to 0x40
};

// -----------------------------------------------------------------------
// Implementation
// -----------------------------------------------------------------------
void __thiscall ActionManager::registerAction(void* owner, int id,
                                              int param3, int param4, int param5)
{
    // Allocation hint: alignment=16, flags=2, unused=0
    struct AllocHint {
        int unknown;   // 2
        int alignment; // 16
        int flags;     // 0
    } hint = { 2, 0x10, 0 };

    // Allocate memory for a new Action object
    Action* newAction = (Action*)eaAllocate(0x40, &hint);
    if (newAction != nullptr) {
        // Set vtable for Action class
        newAction->vtable = &VTABLE_Action;

        // Initialize fields from parameters
        newAction->param3    = param3;
        newAction->param4    = param4;
        newAction->param5    = param5;
        newAction->param2    = id;
        newAction->timestamp = g_currentTimestamp;

        // Clear remaining fields
        newAction->field_10 = 0;
        newAction->field_14 = 0;
        newAction->field_18 = 0;
        newAction->field_1C = 0;
        newAction->field_20 = 0;
        newAction->field_28 = 0;
        newAction->field_2C = 0xFFFFFFFF;
        newAction->field_34 = 0;
        newAction->field_38 = 0;
    }

    // Compute hash slot based on owner pointer
    // g_pActionManager->hashTableInfo->size (at offset +8 from manager, then +8 from that)
    uint32_t hashTableSize = *(uint32_t*)(*(uint32_t*)((uint8_t*)g_pActionManager + 8) + 8);
    uint32_t slot = (uint32_t)owner % hashTableSize;

    // Insert the action (or null) into the hash table, keyed by owner
    insertIntoActionHashTable(owner, &newAction, slot);
}