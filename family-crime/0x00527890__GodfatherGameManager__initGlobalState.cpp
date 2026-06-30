// FUNC_NAME: GodfatherGameManager::initGlobalState

// Function address: 0x00527890
// Role: Initializes a global game manager singleton and registers it in a linked list of managers.

// Structure for a node in the global manager list (size 0x10)
// +0x00: pointer (likely vtable or base data)
// +0x04: next pointer in the singly linked list
// +0x08: result from virtual function (e.g., handle)
// +0x0C: unique ID assigned from the global count
struct ManagerListNode {
    void* vtbl;       // +0x00
    ManagerListNode* next; // +0x04
    int data;         // +0x08
    int id;           // +0x0C
};

// Global singleton instance (at 0x01197d70)
struct GlobalState {
    int field_0;   // +0x00
    int field_4;   // +0x04
    int field_8;   // +0x08
    int field_C;   // +0x0C
    int field_10;  // +0x10
    int field_14;  // +0x14
    int field_18;  // +0x18
    int field_1C;  // +0x1C
    int field_20;  // +0x20
};

// External globals
extern int g_constant1;   // DAT_00e2b118
extern int g_constant2;   // DAT_00e2b1a4
extern int g_constant3;   // DAT_00e446c4

// Pointer to the global manager instance (PTR_PTR_01125aa0)
extern ManagerListNode g_managerNode;  // at 0x01125aa0

// Global list head pointer (DAT_012058ec)
extern ManagerListNode* g_listHead;

// Global list count (DAT_012058f8)
extern int g_listCount;

void GodfatherGameManager::initGlobalState()
{
    GlobalState* g_state = (GlobalState*)0x01197d70;  // singleton global state

    // Zero out the state structure
    g_state->field_0 = 0;
    g_state->field_4 = 0;
    g_state->field_8 = 0;
    g_state->field_C = 0;

    // Set fields from game constants
    g_state->field_10 = g_constant1;
    g_state->field_14 = g_constant2;
    g_state->field_18 = g_constant3;
    g_state->field_1C = g_constant2;
    g_state->field_20 = 0;

    // Call virtual function at offset 4 on the manager object (e.g., getHandle)
    int result = ((int (*)())(*(void**)((int)&g_managerNode + 4)))();
    // Transform the result and store in the node
    g_managerNode.data = FUN_0060d740(result);  // _DAT_01125aa8

    // Call virtual function at offset 0x10 (e.g., finalizeInit)
    ((void (*)())(*(void**)((int)&g_managerNode + 0x10)))();

    // Insert this node at the head of the global manager list
    g_managerNode.next = g_listHead;      // _DAT_01125aa4 = DAT_012058ec
    g_listCount++;                         // DAT_012058f8 = DAT_012058f8 + 1
    g_listHead = &g_managerNode;          // DAT_012058ec = &g_managerNode
    g_managerNode.id = g_listCount;       // _DAT_01125aac = DAT_012058f8
}