// Xbox PDB: EARS_Modules_RagdollComponent_RagdollComponent
// FUNC_NAME: RagdollWindowManager::RagdollWindowManager(uint id)
// Function address: 0x00997f10
// Role: Constructor for a ragdoll window manager, likely part of EA EARS physics/ragdoll system.
// Initializes internal fields, allocates and constructs an array of 3 "ragdoll window" objects (size 0x70 each),
// and configures a physics simulation resource.

#include <windows.h> // for TlsGetValue, etc.

// Forward declarations for internal helper functions (their actual names unknown)
void* __cdecl allocAligned(size_t size, int alignment);   // FUN_009c8ef0
void* __cdecl allocNoVtable(size_t size);                 // FUN_009c8e50
int __cdecl createPhysicsResource(int type, int param);   // FUN_00aa2680
void* __cdecl getPhysicsSimulationBase(int index);        // FUN_009fe6e0
void __cdecl initRagdollWindow(void* window);             // FUN_00556f40
void __cdecl logDebugMessage(int* flagPtr, const char* msg); // FUN_00408240

// External global data (likely constants or global state)
extern unsigned int DAT_00d5ccf8;     // +0x00A0? 
extern unsigned int DAT_00d9228c;     // some hash or constant
extern unsigned int DAT_00d92290;     // another constant
extern unsigned int _DAT_00d5cf70;    // global state for physics resource
extern unsigned int DAT_00d5f378;     // global state for physics resource
extern unsigned int DAT_01139810;     // TLS index for ragdoll thread data
extern int DAT_0113096c;             // debug flag

// Vtable references (actual addresses not needed in C++)
extern void* PTR_FUN_00d922e0; // primary vtable pointer
extern void* PTR_LAB_00d922cc; // secondary vtable pointer (possibly interface)
extern void* PTR_FUN_00d922b8; // vtable pointer for allocated child object

class RagdollWindowManager {
public:
    RagdollWindowManager(unsigned int id);
    // Destructor and other methods omitted

private:
    // Member layout (offsets in bytes from this)
    // +0x00: vtable pointer (primary)
    // +0x04: unknown1 (0x21)
    // +0x08: unknown2 (0)
    // +0x0C: m_id (from param_2)
    // +0x10: vtable pointer (secondary)
    // +0x14: unknown3 (&PTR_LAB_00d58278?) - but overwritten later with &PTR_LAB_00d922cc
    // Actually, from code: param_1[4] = &PTR_LAB_00d922cc; so offset +0x10
    // Let's map:
    // [0]: vtable1
    // [1]: m_field1 (0x21)
    // [2]: m_field2 (0)
    // [3]: m_id (param_2)
    // [4]: vtable2
    // [5]: m_field5 (0)
    // [6]: m_field6? (actually param_1[4] first set to &PTR_LAB_00d58278, then overwritten)
    // Better to follow original indices. Reconstruct as:

    unsigned int* vtable;          // +0x00
    unsigned int field_04;        // +0x04 (0x21)
    unsigned int field_08;        // +0x08 (0)
    unsigned int m_id;            // +0x0C (param_2)
    unsigned int* vtable2;        // +0x10 (secondary vtable)
    unsigned int field_14;        // +0x14 (0)
    unsigned int field_18;        // +0x18 (0)
    unsigned int field_1C;        // +0x1C (0)
    unsigned int field_20;        // +0x20 (0)
    unsigned int field_24;        // +0x24 (0)
    unsigned int field_28;        // +0x28 (0x80000000)
    unsigned int field_2C;        // +0x2C (0x80000000)
    unsigned int field_30;        // +0x30 (0)
    unsigned int field_34;        // +0x34 (0)
    unsigned int field_38;        // +0x38? Actually indices 0x12,0x10,0x11,0x13 etc.
    // ... Too many to list here. For reconstruction, we'll skip member fields but note key offsets.
};

// Constructors may call operator new internally; here we assume the object memory is already allocated.
RagdollWindowManager::RagdollWindowManager(unsigned int id)
{
    // Initialize basic fields and vtables
    this->m_id = id;
    this->field_04 = 0x21;          // Possibly type or size indicator
    this->field_08 = 0x0;           // Reset
    this->field_14 = 0;             // Clear many fields
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_28 = 0x80000000;    // Sentinel values (negative int)
    this->field_2C = 0x80000000;
    this->field_30 = 0;
    this->field_34 = 0;
    this->field_38 = 0x80000000;
    // ... (more fields zeroed)
    unsigned int* const_0d922e0 = &PTR_FUN_00d922e0; // dummy, real address
    this->vtable = const_0d922e0;
    this->vtable2 = &PTR_LAB_00d922cc; // secondary vtable

    // Allocate and construct 3 ragdoll window objects (each 0x70 bytes)
    // The allocation function takes size 0x160 (352) and alignment 0x10? Actually local_c=2, local_8=0x10, local_4=0.
    // Possibly a custom allocator.
    struct AllocDesc {
        int unknown1;
        int unknown2;
        int flag;
    } allocDesc = {2, 0x10, 0};
    void* rawMem = allocAligned(0x160, (int)&allocDesc); // FUN_009c8ef0
    if (rawMem != nullptr) {
        // The first 4 bytes are a count (3), then array of 3 elements of size 0x70
        unsigned int* header = (unsigned int*)rawMem;
        header[0] = 3; // element count
        // Use vector constructor iterator to call FUN_00556780 on each element? 
        // Actually _vector_constructor_iterator_ is called with a function pointer at LAB_00556780.
        // That function likely initializes each element.
        // We'll simulate with a loop:
        char* arrayData = (char*)(header + 1); // skip count
        for (int i = 0; i < 3; ++i) {
            // Call the per-element constructor (FUN_00556780) - unknown name
            // The actual code uses _vector_constructor_iterator_ which calls a function.
            // We'll assume a simple loop:
            // ((void (*)(void*))(0x00556780))(arrayData + i * 0x70);
        }
        this->field_1e = (unsigned int)arrayData; // offset +0x78? Actually param_1[0x1e] => byte offset 0x78
    } else {
        this->field_1e = 0; // null
    }

    // Initialize an array of 3 elements starting at offset +0x1f (byte offset 0x7C)
    // Each element is 0x70 bytes. 3 * 0x70 = 0x150.
    // The function initRagdollWindow is called on each element.
    char* windowArray = (char*)&this->field_1f; // index 0x1f in uint* => byte offset 0x7C
    for (int i = 0; i < 3; ++i) {
        initRagdollWindow(windowArray); // FUN_00556f40
        windowArray += 0x70;
    }

    // Thread-specific: get TLS value for ragdoll thread data
    unsigned int tlsValue = (unsigned int)TlsGetValue((DWORD)DAT_01139810);

    // Create a physics resource (size 0x24, alignment 0x2c)
    int resourceHandle = createPhysicsResource(0x24, 0x2c); // FUN_00aa2680
    // The offset +4 of resource is set to 0x24
    *(unsigned short*)(resourceHandle + 4) = 0x24;

    // Get the physics simulation base for index 0
    void* simBase = getPhysicsSimulationBase(0); // FUN_009fe6e0
    // Set fields in the simulation base: offset 0x14 and 0x18 from simBase
    *(unsigned int*)((char*)simBase + 0x14) = _DAT_00d5cf70;
    *(unsigned int*)((char*)simBase + 0x18) = DAT_00d5f378;

    // Store the resource handle
    this->field_26 = resourceHandle; // offset +0x98? (0x26*4=0x98)

    // Allocate a small object (4 bytes) and set its vtable
    unsigned int* smallObj = (unsigned int*)allocNoVtable(4); // FUN_009c8e50
    if (smallObj != nullptr) {
        smallObj[0] = (unsigned int)&PTR_FUN_00d922b8;
    }
    this->field_27 = (unsigned int)smallObj; // offset +0x9C

    // Log a debug message
    logDebugMessage(&DAT_0113096c, "ragdoll_window_start"); // FUN_00408240

    // return this (implicitly)
}