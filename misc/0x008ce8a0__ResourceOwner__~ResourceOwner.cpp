// FUNC_NAME: ResourceOwner::~ResourceOwner
// Address: 0x008ce8a0
// Role: Destructor for a derived class that releases a resource at offset 0x28 then restores base vtable.

extern const void* PTR_FUN_00d7cb78; // Derived class vtable
extern const void* PTR_LAB_00e2f638; // Base class vtable

// Callee at 0x004daf90: releases a resource (likely frees memory or decrements refcount)
extern void releaseResource(void* ptr);

class ResourceOwner {
public:
    const void* vtable;            // +0x00: vtable pointer
    // ... other members ...
    void* someResource;            // +0x28 (param_1[10]): pointer to resource to release
    // ... more members ...

    ~ResourceOwner();
};

ResourceOwner::~ResourceOwner() {
    // Set vtable to derived class (ensures correct virtual dispatch during destructor body)
    this->vtable = &PTR_FUN_00d7cb78;

    // Release owned resource if present
    if (this->someResource != nullptr) {
        releaseResource(this->someResource);
    }

    // Restore vtable to base class for subsequent base destructor call
    this->vtable = &PTR_LAB_00e2f638;
}