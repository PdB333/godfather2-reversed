// FUNC_NAME: EARSObject::release
// Address: 0x00c843e0
// Role: Releases the object by calling virtual methods and deallocating memory with a custom allocator tag (0x6e676c6b = "klgn").
// Calls vtable+0x20 (likely shutdown), optionally vtable+4 (destructor if refCount != 0),
// then frees sub-allocation at +0x1AC and calls cleanup on substructure at +0x1B8,
// finally frees self.

#include <cstdint>

// Forward declarations for external functions
void __cdecl MemoryDeallocate(void* ptr, uint32_t allocTag, int allocInfo);
void __cdecl SubStructCleanup(void* substruct);

// External allocator tag constant (four-character code "klgn")
constexpr uint32_t kAllocTag = 0x6e676c6b;

class EARSObject {
public:
    // Vtable pointer (offset 0x00)
    void** vtable;

    // Reference count or deletion flag (offset 0x04)
    int32_t refCount;

    // Allocation info / size (offset 0x08)
    int32_t allocInfo;

    // Sub-object pointer at offset 0x1AC (param_1[0x6b])
    void* subAllocation;

    // Substructure at offset 0x1B8 (param_1[0x6e])
    // The exact type is unknown but is cleaned by SubStructCleanup
    uint8_t substruct[?]; // placeholder for sizeof

    // Virtual method definitions (vtable offsets)
    typedef void (__thiscall* VirtualFn0x20)(EARSObject* self, int param);
    typedef void (__thiscall* VirtualFn0x04)(EARSObject* self);

    // Actual destructor/release implementation
    void release() {
        // Call virtual method at vtable+0x20 (likely a pre-release/shutdown)
        VirtualFn0x20 shutdownFunc = reinterpret_cast<VirtualFn0x20>(this->vtable[0x20 / 4]);
        shutdownFunc(this, 0);

        // If refCount is non-zero, call virtual destructor at vtable+0x04
        if (this->refCount != 0) {
            VirtualFn0x04 destructorFunc = reinterpret_cast<VirtualFn0x04>(this->vtable[0x04 / 4]);
            destructorFunc(this);
        }

        // Deallocate the sub-object using the custom allocator with tag "klgn"
        MemoryDeallocate(this->subAllocation, kAllocTag, this->allocInfo);

        // Clean up the substructure at offset 0x1B8
        SubStructCleanup(&this->substruct);

        // Finally deallocate this object itself
        MemoryDeallocate(this, kAllocTag, this->allocInfo);
    }
};