// FUNC_NAME: initializeGameSystems
// Address: 0x004dfd70
// Initializes a lookup table of 40 entries (16 bytes each, two shorts at offsets 0 and 2),
// allocates and constructs a 0x48-byte session object, and calls three additional startup routines.

struct LookupEntry {
    short field0;          // +0x00 (offset within entry)
    short field1;          // +0x02
    char  padding[12];     // +0x04, total size 0x10
};

// Global data at fixed addresses
extern int g_activeHandle;              // DAT_010c2328
extern LookupEntry* g_lookupArray;      // DAT_011947f8 (base for header, array starts at +4)
extern void* g_session;                 // DAT_01205510

void* allocateMemory(int size);        // FUN_009c8e50
void* constructSession();              // FUN_004ded00
void initSubsystemA();                 // FUN_004e3ef0
void initSubsystemB();                 // FUN_004e9190
void initNetworkComponents();          // FUN_004dfdd0

void initializeGameSystems(void) {
    // Invalidate global handle
    g_activeHandle = -1;

    // Initialize 40 lookup entries.
    // The array of LookupEntry begins at offset 4 from g_lookupArray base.
    // psVar1 starts at the 'field1' (offset +2) of the first entry.
    short index = 0;
    short* currentField1 = (short*)((intptr_t)g_lookupArray + 6);

    while ((intptr_t)currentField1 < 0x1194a7e) {
        currentField1[-1] = 0;         // field0 = 0
        *currentField1      = index;   // field1 = current index
        currentField1 += 8;            // move to next entry (16 bytes forward)
        index++;
    }

    // Allocate and construct session object (size 0x48)
    void* mem = allocateMemory(0x48);
    if (mem == (void*)0) {
        g_session = (void*)0;
    } else {
        g_session = constructSession();
    }

    // Chain to further initialization
    initSubsystemA();
    initSubsystemB();
    initNetworkComponents();
}