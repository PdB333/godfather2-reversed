// FUNC_NAME: ActionPairRegistrar::ActionPairRegistrar

struct TwoInts {
    int first;
    int second;
};

// External function: registers a pair of integer values (likely object IDs or similar)
extern void registerEntry(int a, int b);

// Class with a self-referential doubly linked list head and two registration slots
// The constructor initializes the list and registers two data pairs.
class ActionPairRegistrar {
public:
    void** vtable;              // +0x00
    int field_04;               // +0x04 (storage for param_6)
    byte field_08;              // +0x08 (zeroed)

    // Doubly linked list node (next and prev point to self on construction)
    ActionPairRegistrar* listNext; // +0x0C
    ActionPairRegistrar* listPrev; // +0x10

    // Zeroed region (from 8‑byte zero at +0x14 and separate byte/int clears)
    int field_14;               // +0x14
    byte field_18;              // +0x18
    int field_1C;               // +0x1C

    int field_24;               // +0x24 (param_4)
    int field_28;               // +0x28 (param_5)

    // __thiscall constructor
    ActionPairRegistrar(TwoInts* objA, TwoInts* objB, int param4, int param5, int param6) {
        field_04 = param6;
        field_08 = 0;

        // Initialize empty circular doubly linked list
        listNext = this;        // self-pointing next
        listPrev = this;        // self-pointing prev

        field_14 = 0;
        field_18 = 0;
        field_1C = 0;

        field_24 = param4;
        field_28 = param5;
        vtable = (void**)&PTR_FUN_00d5cec4;   // vtable from global

        // Register both data pairs
        registerEntry(objA->first, objA->second);
        registerEntry(objB->first, objB->second);
    }
};