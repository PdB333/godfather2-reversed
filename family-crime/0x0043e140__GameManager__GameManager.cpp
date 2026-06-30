// FUNC_NAME: GameManager::GameManager
// Reconstructed constructor for the main game manager singleton.
// Initializes vtables, sets global pointers, calls sub-object constructor,
// and registers static data.

class GameManager {
public:
    // Vtable pointer (first field)
    void *vtable;

    // Other fields based on offsets (size unknown)
    // +0x04: unknown field (int)
    int field_04;
    // +0x08: pointer to vtable for something (reassigned later)
    void *field_08;
    // +0x0C: unknown (int, set to 1)
    int field_0C;
    // +0x10: unknown (int, set to 0)
    int field_10;
    // +0x14: pointer to vtable for another interface
    void *field_14;
    // +0x18: unknown (int, set to 0)
    int field_18;
    // +0x1C: unknown (int, set to 0)
    int field_1C;
    // +0x20: sub-object (size unknown) – passed to sub-constructor
    // We'll treat as a generic pointer to sub-object
    void *subObject;

    // Constructor (__fastcall with this in ECX)
    GameManager *__fastcall constructor();
};

// External function pointers (likely global function pointers for singleton access)
extern GameManager *g_pGameManager; // DAT_012233f4
extern void (*g_updateFunc)();       // DAT_012059dc
extern void (*g_renderFunc)();       // DAT_012059e0

// External function prototypes
void *__fastcall GetSomeHeapOrPool(); // FUN_009c8f80
int *__fastcall InitializeSubObject(int *output, void *param); // FUN_004265d0
void __fastcall SubObjectConstructor(void *subObj); // FUN_0043ea50
void __fastcall RegisterStaticData(void *data, int offset); // FUN_0049c6e0

// Static data pointers (unknown purpose)
extern void *g_StaticData1; // DAT_00e31014
extern void *g_StaticData2; // DAT_00e31018

GameManager *GameManager::constructor() {
    // Initialize fields
    field_04 = 0;
    field_08 = &PTR_FUN_00e2f19c; // Base vtable
    field_0C = 1;
    field_10 = 0;
    field_14 = &PTR_LAB_00e3107c; // Another base vtable

    // Set global singleton pointer
    g_pGameManager = this;

    // Set initial vtable pointer
    vtable = &PTR_FUN_00e3105c;

    // Override with derived vtables
    field_08 = &PTR_LAB_00e31068;
    field_14 = &PTR_LAB_00e31078;

    // Clear remaining fields
    field_18 = 0;
    field_1C = 0;

    // Local stack variables (unused after init)
    int local_14 = 0;
    int local_10 = 0;
    int local_c  = 0;

    // Call some heap/pool routine
    void *heapPtr = GetSomeHeapOrPool();
    // Call virtual method at offset +0x08 on heap object (vtable dispatch)
    ((code *)heapPtr->vtable[2])(); // offset +0x08

    // Initialize sub-object (passes address of local stack and heap pointer)
    int *result = InitializeSubObject(&local_14, heapPtr);

    // Call sub-object constructor at +0x20 (offset 8 uint32s = 32 bytes)
    SubObjectConstructor(&subObject); // param_1 + 8

    // If initialization succeeded, destroy heap object?
    if (result != 0) {
        ((code *)heapPtr->vtable[1])(result, 0); // offset +0x04 (destructor)
    }

    // Release heap object?
    ((code *)heapPtr->vtable[3])(); // offset +0x0C

    // Register static data
    RegisterStaticData(&g_StaticData1, 1);
    RegisterStaticData(&g_StaticData2, 1);

    // Set global function pointers for update/render (or similar)
    g_updateFunc = FUN_0043e980;
    g_renderFunc = FUN_0043e9c0;

    return this;
}