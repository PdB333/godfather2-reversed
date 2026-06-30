// FUN_00485a00: SharedObject::create

#include <cstdint>

// Forward declarations for vtable-based interfaces

class IFactory {
public:
    // vtable offset 0: allocate memory
    virtual void* alloc(uint32_t size, void* handle) = 0;   // vtable[0]
    // vtable offset 8: retain (increment reference count)
    virtual void retain() = 0;                              // vtable[2]
};

class IObject {
public:
    // vtable offset 8: retain
    virtual void retain() = 0;                              // vtable[2]
};

// Struct returned by this function (allocated 0x10 bytes)
struct SharedObject {
    IObject* m_pTarget;          // +0x00: pointer to the global object
    uint32_t m_nHandleThird;    // +0x04: third word from alloc handle (unused)
    uint32_t m_nFlags;          // +0x08: set to 1 (purpose unknown)
    IFactory* m_pFactory;       // +0x0C: pointer to the allocator/factory
};

// External globals/functions
extern IObject* g_pGlobalObject;    // DAT_0120542c
IFactory* GetFactory();             // FUN_009c8f80

// Creates a new SharedObject that holds a reference to the global object
SharedObject* SharedObject::create() {
    IFactory* pFactory = GetFactory();

    // 3-word handle structure, initialized to zero
    struct Handle {
        uint32_t a, b, c;
    };
    Handle handle = {0, 0, 0};

    // Allocate 0x10 bytes using the factory's vtable[0] (allocate with handle)
    SharedObject* pObj = static_cast<SharedObject*>(pFactory->alloc(0x10, &handle));

    // Initialize fields
    pObj->m_nFlags = 1;
    pObj->m_pFactory = pFactory;

    // Retain the factory (vtable[2], offset 8)
    pFactory->retain();

    // Set target to the global object
    pObj->m_pTarget = g_pGlobalObject;

    // If the global object exists, retain it as well
    if (g_pGlobalObject != nullptr) {
        g_pGlobalObject->retain();
    }

    // Store the third word of the handle (always 0 in this context)
    pObj->m_nHandleThird = handle.c;

    return pObj;
}