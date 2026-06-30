//FUNC_NAME: GlobalObjectRegistry::registerObject
// Address: 0x005332e0
// Role: Registers a global object into a linked list, assigns an ID, and calls its virtual init functions.

// Object structure (fields at known offsets)
struct RegisteredObject {
    void** vtable;          // +0x00
    RegisteredObject* prev; // +0x04 (linked list previous head)
    int id;                 // +0x08 (assigned ID)
    int index;              // +0x0C (monotonic counter)
    // ... other fields at +0x10, +0x14, etc.
};

// Global state
static RegisteredObject* g_pHead;          // DAT_012058ec
static int g_objectCount;                  // DAT_012058f8
static RegisteredObject* g_pNewObject;     // DAT_01219a70 (object being registered)
static int g_newObjectId;                  // _DAT_01219a78 (temporary ID storage)

// External function: generates a unique ID from a value
int generateId(int value); // FUN_0060d740

void GlobalObjectRegistry::registerObject() {
    RegisteredObject* obj = g_pNewObject; // DAT_01219a70

    // Call virtual function at vtable+4 (returns some value)
    int vtableResult = (*(int (__thiscall**)(RegisteredObject*))(obj->vtable[1]))(obj);

    // Generate and store ID
    obj->id = generateId(vtableResult); // _DAT_01219a78 = FUN_0060d740(uVar1)

    // Call virtual function at vtable+0x10 (initialization step)
    (*(void (__thiscall**)(RegisteredObject*))(obj->vtable[4]))(obj);

    // Link into singly linked list (insert at head)
    obj->prev = g_pHead;                 // _DAT_01219a74 = DAT_012058ec
    g_objectCount++;                     // DAT_012058f8 = DAT_012058f8 + 1
    g_pHead = obj;                       // DAT_012058ec = &DAT_01219a70
    obj->index = g_objectCount;          // _DAT_01219a7c = DAT_012058f8
}