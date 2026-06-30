// FUNC_NAME: InputManager::InputManager
// Address: 0x0047d700
// Constructor for InputManager.
// Sets up vtables, initializes sub-systems, removes from any existing linked list,
// then finalizes initialization and clears a global startup flag.

#include <cstdint>

class InputManager {
public:
    // Vtable pointers (offsets relative to this):
    void** m_vtableBase;       // +0x00
    void** m_vtableSecondary;  // +0x04
    // ... many fields between +0x08 and +0x3F ...
    void** m_vtableThird;      // +0x40 (param_1[0x10])
    void** m_vtableFourth;     // +0x4C (param_1[0x13])
    // ... fields between +0x50 and +0x7B ...
    int32_t* m_listHead;       // +0x7C (linked list pointer used during removal)
    int32_t* m_listNext;       // +0x80 (next pointer used during removal)
    // ... rest of members ...
};

// External functions called
extern void InitializeInputDevices();      // FUN_0047e2c0
extern void GetSingleton(void* globalData);// FUN_004086d0 (address &DAT_0120e93c)
extern void SetupDefaultBindings();        // FUN_0046c640

// Global variables
extern int32_t g_inputInitialized; // _DAT_0122340c

void __fastcall InputManager::InputManager() {
    // Set up initial vtables (likely base class/interfaces)
    this->m_vtableBase = (void**)0x00e3321c;
    this->m_vtableSecondary = (void**)0x00e33230;
    this->m_vtableThird = (void**)0x00e3324c;
    this->m_vtableFourth = (void**)0x00e3325c;

    // Call sub-initialization routines
    InitializeInputDevices();               // 0x0047e2c0
    GetSingleton(&DAT_0120e93c);            // 0x004086d0

    // Remove this object from any linked list it might already be in (e.g., if reusing a pooled instance)
    int32_t* listNode = this->m_listHead;   // +0x7C
    if (listNode != nullptr) {
        // listNode is a node with 'next' at offset +4 (i.e., listNode[1])
        int32_t* nextPtr = (int32_t*)*((int32_t**)(listNode + 1)); // listNode[1]
        if (nextPtr == &(this->m_listHead)) {
            // If the only node points to the head slot, adjust it directly
            *((int32_t**)listNode + 1) = this->m_listNext;
        } else {
            // Walk the circular list to find the node that points to the head
            int32_t* walker = nextPtr;
            while (walker[1] != &(this->m_listHead)) {
                walker = (int32_t*)walker[1];
            }
            // Remove the head by linking predecessor's next to stored next
            walker[1] = this->m_listNext;
        }
    }

    // Finalize initialization
    SetupDefaultBindings();                 // 0x0046c640

    // Switch to final vtable (after construction complete)
    this->m_vtableBase = (void**)0x00e33260;

    // Clear the global startup lock/flag
    g_inputInitialized = 0;
}