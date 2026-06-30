// FUNC_NAME: ResourceHolder::~ResourceHolder
// Function address: 0x004f7910
// This is a destructor that releases a reference-counted resource and resets the vtable to the base class.

#include <cstdint>

// Forward declaration of the reference-counted object type
struct RefCountedObject {
    void** vtable;      // +0x00: virtual table pointer
    int32_t refCount;   // +0x04: reference count
    // Additional data follows
};

// Global base class vtable pointer (set during destruction to prevent virtual calls)
extern void* PTR_LAB_00e3729c[]; // actually a vtable pointer, not array

class ResourceHolder {
public:
    void** vtable;                              // +0x00: virtual table pointer (this class)
    // ... other members (not shown) ...
    RefCountedObject* m_resource;                // +0x20: pointer to reference-counted resource

    // Destructor (__thiscall, ecx = this)
    __thiscall ~ResourceHolder();
};

// Destructor implementation
__thiscall ResourceHolder::~ResourceHolder() {
    if (m_resource != nullptr) {
        // Decrement the reference count of the resource
        m_resource->refCount--;

        // If the reference count drops to zero, call the resource's destructor via vtable slot 1 (offset +4)
        if (m_resource->refCount == 0) {
            // vtable[1] is assumed to be the destructor (or appropriate cleanup function)
            ((void (*)(RefCountedObject*))m_resource->vtable[1])(m_resource);
        }

        // Clear the pointer to the resource
        m_resource = nullptr;
    }

    // Reset this object's vtable to the base class vtable to avoid virtual calls during remaining destruction
    this->vtable = &PTR_LAB_00e3729c;

    return;
}