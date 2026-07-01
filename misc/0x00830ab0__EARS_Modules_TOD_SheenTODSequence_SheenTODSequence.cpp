// Xbox PDB: EARS_Modules_TOD_SheenTODSequence_SheenTODSequence
// FUNC_NAME: SheenSequence::SheenSequence
// Address: 0x00830ab0
// Role: Constructor for SheenSequence class (likely a rendering/effect sequence)
// Calls base constructor at 0x0082ecd0, sets vtable, initializes a scoped profile,
// loads a resource pointer from offset +0x10 (or uses global default), stores result at +0x0C.

#include <cstdint>

// Forward declarations for called functions (assumed from EA EARS engine)
void __fastcall BaseClassConstructor(void* this); // 0x0082ecd0
void __fastcall ProfileBegin(const char* name);  // 0x004d3bc0
void __fastcall ProfileEnd(void* scope);         // 0x004d3e20
void* __fastcall LoadResource(const char* name); // 0x004dafd0

// External vtable and default resource pointer
extern void* PTR_FUN_00d73964; // vtable for SheenSequence
extern const char DAT_0120546e; // default resource name (e.g., "default")

// Scoped profile structure (size 16 bytes)
struct ProfileScope {
    void* data;       // +0x00
    int padding[2];   // +0x04, +0x08 (unused)
    void (*deleter)(void*); // +0x0C
};

class SheenSequence {
public:
    // Vtable pointer at offset 0x00
    // Fields:
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: resource handle (void*)
    // +0x10: resource name pointer (const char*)

    void* __fastcall SheenSequence(void);
};

void* __fastcall SheenSequence::SheenSequence(void) {
    // Call base class constructor
    BaseClassConstructor(this);

    // Set vtable pointer
    *(void**)this = &PTR_FUN_00d73964;

    // Begin profiling scope with name "SheenSequence"
    ProfileBegin("SheenSequence");

    // Initialize local profile scope (will be cleaned up at end)
    ProfileScope scope;
    ProfileEnd(&scope);

    // Determine resource name: use this->resourceName if non-null, else global default
    const char* resourceName = *(const char**)((uint8_t*)this + 0x10);
    if (resourceName == nullptr) {
        resourceName = &DAT_0120546e;
    }

    // Load resource and store handle at offset +0x0C
    void* resourceHandle = LoadResource(resourceName);
    *(void**)((uint8_t*)this + 0x0C) = resourceHandle;

    // Clean up profile scope if data pointer is non-null
    if (scope.data != nullptr) {
        scope.deleter(scope.data);
    }

    return this;
}