// Xbox PDB: EARS_Apt_UIHudMinimap_UIHudMinimap
// FUNC_NAME: UIHudMinimap::UIHudMinimap
// Address: 0x009457a0
// Role: Constructor for the global minimap HUD singleton

#include <cstring>

// Forward declarations for external functions (known from decompilation)
extern void baseConstructor(void); // FUN_005bf9b0
extern void createMemoryPool(int size, int alignment, const char* name, int unknown1, int unknown2); // FUN_004de0b0
extern void* allocateMemory(size_t size); // FUN_009c8e80, FUN_009c8e50 (overloaded)
extern void* createFXPool(void); // FUN_00941c90
extern void* createSomething(void); // FUN_009c89c0
extern int initializeSomething(void* params, void* obj); // FUN_004265d0

// Global storage set by this constructor
extern UIHudMinimap* g_pUIHudMinimap; // DAT_0112af90
extern int* g_pSomeGlobalArray1; // DAT_01130614
extern int* g_pSomeGlobalArray2; // DAT_01130618
extern int g_GlobalInt1; // DAT_01130600
extern int g_GlobalInt2; // DAT_01130604
extern int g_GlobalInt3; // DAT_01130608
extern int g_GlobalInt4; // DAT_0113060c

// The class layout (partial, many fields are unknown)
class UIHudMinimap {
public:
    void** vtable;           // +0x00
    void** vtable2;          // +0x04
    // ... many unknown words
    // offsets based on param_1[0x13] etc. (each index = 4 bytes)
    void* field_0x4C;        // +0x4C  (param_1[0x13])
    void* field_0x50;        // +0x50  (param_1[0x14])
    int field_0x54;          // +0x54  (param_1[0x15])
    int field_0x58;          // +0x58  (param_1[0x16])
    char pad_0x5C[0x58];     // +0x5C  (param_1[0x17] to +0xB3)
    int field_0xB4;          // +0xB4  (param_1[0x2D])
    void* field_0xB8;        // +0xB8  (param_1[0x2E])
    void* field_0xF0;        // +0xF0  (param_1[0x3C])
    int field_0xF4;          // +0xF4  (param_1[0x3D])
    int field_0xF8;          // +0xF8  (param_1[0x3E])
    short field_0xFC;        // +0xFC  (*(short*)(this+0xFC))
    short field_0xFE;        // +0xFE  (*(short*)(this+0xFE))
    int field_0x100;         // +0x100 (param_1[0x40])
    int field_0x104;         // +0x104 (param_1[0x41])
    int field_0x108;         // +0x108 (param_1[0x42])
    // total size > 0x10C bytes
};

UIHudMinimap* __thiscall UIHudMinimap::UIHudMinimap(UIHudMinimap* this)
{
    void* pVFXData;
    int* pTempObj;
    void** ppArrayObj;
    int* pInternalObj;

    // Call base class constructor
    baseConstructor();

    // Initialise various vtable pointers and flags
    this->field_0x4C = (void*)0x00d8b33c;   // vtable pointer for specific interface
    g_pUIHudMinimap = this;                // store singleton reference

    this->field_0x50 = (void*)0x00e2f19c;  // function pointer
    this->field_0x54 = 1;                  // some enable flag
    this->field_0x58 = 0;                  // counter

    this->vtable = (void**)0x00d8b3b0;    // main vtable
    this->vtable2 = (void**)0x00d8b38c;   // secondary vtable

    // Re‑write vtable entries (maybe overriding base class)
    this->field_0x4C = (void*)0x00d8b388;
    this->field_0x50 = (void*)0x00d8b378;

    // Zero 0x58 bytes starting at offset 0x5C (param_1[0x17])
    memset(reinterpret_cast<char*>(this) + 0x5C, 0, 0x58);

    this->field_0xB4 = 0;                  // likely a flag

    // Create a fixed‑size memory pool for VFX sprites
    createMemoryPool(0x10, 0x10, "UIHudMinimap::VFXPool", 0, 0x10);

    this->field_0xB8 = (void*)0x00d8b334; // another vtable

    // Allocate memory for VFX data (0x80 bytes)
    pVFXData = allocateMemory(0x80);
    this->field_0xF0 = pVFXData;

    // Initialise VFX control fields
    this->field_0xF4 = 0;                  // count
    this->field_0xF8 = 0x10;               // capacity
    this->field_0xFC = 0;                  // some short
    this->field_0xFE = 0;                  // another short (direct byte offset 0xFE)
    this->field_0x104 = 0;                 // unknown
    this->field_0x108 = 0;                 // unknown

    // Create a separate VFX pool object (size 8) or NULL
    pTempObj = (int*)allocateMemory(8);
    if (pTempObj != nullptr) {
        pVFXData = createFXPool();
    } else {
        pVFXData = nullptr;
    }

    // Copy global constants into global memory
    g_GlobalInt1 = *(int*)0x00d5c458;      // _DAT_00d5c458
    g_GlobalInt2 = *(int*)0x00e448a4;      // DAT_00e448a4
    g_GlobalInt3 = *(int*)0x00d5d7b8;      // DAT_00d5d7b8
    g_GlobalInt4 = 0;

    this->field_0x100 = (int)pVFXData;     // store the VFX pool pointer

    // Allocate and initialise an object of size 0x14 (for a collection iteration?)
    ppArrayObj = (void**)allocateMemory(0x14);
    if (ppArrayObj != nullptr) {
        int params[3] = { 2, 0x10, 0 };    // stack local: count, element size, flags
        pInternalObj = (int*)createSomething();
        int result = initializeSomething(params, pInternalObj);
        ppArrayObj[3] = (void*)result;
        ppArrayObj[4] = pInternalObj;

        // Call virtual function on the created object (offset +8 in its vtable)
        (*(void(**)(void))(pInternalObj[0] + 8))();

        // Zero first three dwords
        ppArrayObj[0] = nullptr;
        ppArrayObj[2] = nullptr;
        ppArrayObj[1] = nullptr;

        g_pSomeGlobalArray1 = (int*)ppArrayObj; // DAT_01130614
    } else {
        g_pSomeGlobalArray1 = nullptr;
    }

    // Repeat the same allocation for a second global array
    ppArrayObj = (void**)allocateMemory(0x14);
    if (ppArrayObj != nullptr) {
        int params[3] = { 2, 0x10, 0 };
        pInternalObj = (int*)createSomething();
        int result = initializeSomething(params, pInternalObj);
        ppArrayObj[3] = (void*)result;
        ppArrayObj[4] = pInternalObj;

        (*(void(**)(void))(pInternalObj[0] + 8))();

        ppArrayObj[0] = nullptr;
        ppArrayObj[2] = nullptr;
        ppArrayObj[1] = nullptr;

        g_pSomeGlobalArray2 = (int*)ppArrayObj; // DAT_01130618
    } else {
        g_pSomeGlobalArray2 = nullptr;
    }

    return this;
}