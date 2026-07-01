// FUNC_NAME: EARS::Framework::BaseNode::constructor
// Function address: 0x007a0f80
// Role: Base constructor for a node-like object, initializing vtable pointers and internal links.
// This constructor sets up a self-referential pointer likely for a linked list or delegation chain.

#include <cstdint>

// VTable pointers (from data sections)
extern void* PTR_LAB_00e317dc;  // Base vtable (1st)
extern void* PTR_LAB_00d6a9e0;  // Derived vtable (2nd)
extern void* PTR_LAB_00d6a784;  // Function table pointer?

// Forward declaration of helper functions
int __fastcall generateSomeID();             // FUN_00481610
void __fastcall debugAllocation(int, int);   // FUN_0064d390 (maybe allocation tracking)
void __fastcall initializeWithID(int);       // FUN_00454a10

class BaseNode {
public:
    // Vtable is at offset 0; also has function tables and internal links
    // Offsets from this (in bytes):
    // +0x00: vtable pointer
    // +0x14 (5): self-referential pointer to offset 0x28 (10)
    // +0x18 (6): some integer
    // +0x24 (9): flag (set to 1)
    // +0x28 (10): function table pointer (or second vtable)
    // +0x30 (12): direct function pointer (code label, probably a method entry point)
    // +0x34 (13): another integer (set to 0)

    void** vtable;          // +0x00
    // ... other members up to offset 0x14
    BaseNode* selfLink;     // +0x14 (points to offset 0x28)
    int someInt;            // +0x18
    int flag;               // +0x24
    void* funcTable;        // +0x28
    void (*processFunc)();  // +0x30 (function pointer)
    int anotherInt;         // +0x34
};

// Constructor
BaseNode* __thiscall BaseNode::constructor(BaseNode* this, int param2) {
    int uVar1;

    if (param2 == 0) {
        uVar1 = 0;
    } else {
        uVar1 = generateSomeID();  // Likely generates a unique ID/ handle
    }

    // Debug or allocation tracking call
    debugAllocation(1, 1);

    // Initialize vtable to first base class
    this->vtable = &PTR_LAB_00e317dc;

    // Clear member at offset +0x18
    this->someInt = 0;

    // Initialize with the generated ID (or 0)
    initializeWithID(uVar1);

    // Set flag to 1
    this->flag = 1;

    // Override vtable to derived class (this is the final vtable)
    this->vtable = &PTR_LAB_00d6a9e0;

    // Set function table pointer
    this->funcTable = &PTR_LAB_00d6a784;

    // Set direct function pointer (likely a process routine)
    this->processFunc = &LAB_0079b130;  // External label, actual function at 0x0079b130

    // Clear another integer
    this->anotherInt = 0;

    // Self-referential link: point offset +0x14 to the address of offset +0x28
    // This creates a circular link, possibly for a linked list or delegation
    this->selfLink = reinterpret_cast<BaseNode*>(reinterpret_cast<uintptr_t>(this) + 0x28);

    return this;
}