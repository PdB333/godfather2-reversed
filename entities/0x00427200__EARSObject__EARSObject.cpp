// FUNC_NAME: EARSObject::EARSObject

class EARSObject {
public:
    // Field offsets (relative to this):
    // +0x24: m_flags (byte)
    // +0x28: m_handle (int) - initialized to -1
    // +0x2c: m_counter (int) - initialized to 0
    // +0x40: m_field40 (int) - initialized to 0
    // +0x44: m_field44 (int) - initialized to 0
    // +0x48: m_field48 (int) - initialized to 0
    // +0x4c: m_field4C (int) - initialized to 0
    // +0x50: m_field50 (int) - initialized to 0
    // +0x54: m_handle54 (int) - result from create function
    // +0x58: m_pObject58 (void*) - pointer to allocated object with vtable

    EARSObject();
};

// Size parameters for resource allocation
struct SizeParams {
    int width;   // 2
    int height;  // 16
    int depth;   // 0
};

// External functions called by the constructor
void* FUN_009c89c0();                                    // Allocator/manager factory
int  FUN_004265d0(SizeParams* params, void* allocator); // Create resource/handle

// External vtable-based method called on the allocated object
// Equivalent to: pObject->vtable[2](); (offset 0x08)
extern void (*g_initFunc)(void*); // vtable entry at index 2

EARSObject::EARSObject()
{
    // Initialize basic members
    *(uint8_t*)(this + 0x24) = 0;     // m_flags = false
    *(int*)(this + 0x2c) = 0;         // m_counter = 0
    *(int*)(this + 0x28) = -1;        // m_handle = -1
    *(int*)(this + 0x40) = 0;         // m_field40 = 0
    *(int*)(this + 0x44) = 0;         // m_field44 = 0

    // Prepare size parameters for resource creation
    SizeParams sizeParams = { 2, 16, 0 };

    // Allocate internal object from manager
    void* allocObject = FUN_009c89c0();
    int handle = FUN_004265d0(&sizeParams, allocObject);

    // Store handle and pointer
    *(int*)(this + 0x54) = handle;      // m_handle54 = handle
    *(void**)(this + 0x58) = allocObject; // m_pObject58 = allocObject

    // Call virtual method on the allocated object (offset 8 in vtable)
    (*(void (**)(void*))(*(void**)allocObject + 8))(allocObject);

    // Zero out remaining fields
    *(int*)(this + 0x48) = 0;
    *(int*)(this + 0x50) = 0;
    *(int*)(this + 0x4c) = 0;

    // Return this (implicit in C++ constructor)
}