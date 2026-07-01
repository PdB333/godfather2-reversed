// FUNC_NAME: Entity::~Entity
// Address: 0x00925fd0
// Destructor for Entity class. Cleans up string members, removes from list, and clears a global flag.

// Global data
extern void* g_pManager; // DAT_01129924 - pointer to manager singleton
extern char g_someString[]; // DAT_0112ddd8 - global string buffer
extern uint32_t g_gameState; // DAT_01223394 - global state structure (bitfield at +0x6c)

// External functions
extern bool isManagerValid(); // FUN_009c7920 - checks if manager is valid
extern void stringOperation(void* str, int mode); // FUN_00408a00 - string init/clear (mode 0 = clear)
extern void updateGlobalState(); // FUN_00912030 - updates global state
extern void removeFromList(void* list, void* label, int flag); // FUN_005c02f0 - removes element from list

// Member offsets
// +0x10: list node (used in removeFromList)
// +0x94: string member (size 12 bytes? Actually 4+4+1? But treated as string object)
// +0x13a5: initialization flag (byte)

void __fastcall Entity::~Entity(void* this) {
    int* managerPtr = (int*)g_pManager;
    char initFlag = *(char*)((uint8_t*)this + 0x13a5);

    if (initFlag == 0) {
        // Not fully initialized: cleanup via manager if valid
        if (g_pManager != nullptr && isManagerValid()) {
            // Call virtual function at vtable index 1 (likely release/destroy)
            (*(void (**)(void))(*managerPtr + 4))();
        }
    } else {
        // Fully initialized: clear global string and then call stringOperation
        // Build a temporary string object from global string
        struct {
            uint32_t data;   // pointer or value
            uint32_t zero1;
            uint8_t  zero2;
        } tempStr;
        tempStr.data = *(uint32_t*)g_someString; // Actually DAT_0112ddd8 is a pointer? Assume it's a value
        tempStr.zero1 = 0;
        tempStr.zero2 = 0;
        stringOperation(&tempStr, 0); // Clear/init string
    }

    updateGlobalState();

    // Remove this object from a list using the node at +0x10
    removeFromList((uint8_t*)this + 0x10, &LAB_00925f10, 1); // LAB_00925f10 is a label/identifier

    // Clean up string member at +0x94
    struct {
        uint32_t data;
        uint32_t zero1;
        uint8_t  zero2;
    } memberStr;
    memberStr.data = *(uint32_t*)((uint8_t*)this + 0x94);
    memberStr.zero1 = 0;
    memberStr.zero2 = 0;
    stringOperation(&memberStr, 0);

    // Clear bit 3 (0x8) in global state at offset 0x6c
    *(uint32_t*)((uint8_t*)&g_gameState + 0x6c) &= ~0x8;
}