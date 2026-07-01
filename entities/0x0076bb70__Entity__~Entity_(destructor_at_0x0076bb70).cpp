// FUNC_NAME: Entity::~Entity (destructor at 0x0076bb70)

// Structure layout (based on offsets used in destructor):
// +0x00: vtable pointer
// +0x68: m_subObject (pointer to sub-object, likely another heap-allocated component)
// +0x8C: m_flags (bitfield; bit 1 indicates some resource needs cleanup)
struct Entity {
    void** vtable;
    // ... other fields between +0x04 and +0x67 ...
    void* m_subObject; // +0x68
    // ... other fields ...
    uint32_t m_flags; // +0x8C
};

// External functions called (unknown names; given placeholder labels):
extern void __cdecl cleanupResource(uint32_t type);
extern void __thiscall destroySubObject(void* subObjectPtr); // destructor for sub-object at +0x68
extern void __cdecl globalCleanup(void);

void __thiscall Entity::~Entity(Entity* this) {
    // Set vtable to derived class vtable (first step of destruction)
    this->vtable = &PTR_LAB_00d66008;

    // Check bit 1 of flags at +0x8C. If set, release associated resource (type = 0)
    if ((this->m_flags >> 1) & 1) {
        cleanupResource(0);
    }

    // Switch vtable to base class vtable (second step)
    this->vtable = &PTR_LAB_00d63090;

    // Clean up sub-object at +0x68 if it exists (likely a component or sub-entity)
    if (this->m_subObject != nullptr) {
        // Destroy the sub-object; the argument is a pointer to the pointer?
        // The call uses address of m_subObject (param_1+0x1a), so we pass &m_subObject
        destroySubObject(&this->m_subObject);
    }

    // Perform global cleanup (may free memory or decrement global reference counts)
    globalCleanup();
}