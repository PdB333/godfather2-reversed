// FUNC_NAME: Entity::release (destructor-like cleanup with conditional deletion)
// Address: 0x006f7180
// Role: Releases resources and optionally deallocates the object. Calls base class release, then if param2 bit 0 is set, deletes this with a known size (0xF8).

// Assuming base class type; actual name unknown
class EntityBase {
public:
    virtual void release(); // = FUN_006f6e00
};

// Assuming 0xF8 is the object size; actual size may vary
class Entity : public EntityBase {
public:
    // Destructor-like release function
    // @param flags: if bit 0 set, deallocate this object (custom delete with size)
    Entity* release(byte flags) {
        // Call base class cleanup
        EntityBase::release();

        if (flags & 1) {
            // Custom operator delete with size 0xF8 (248 bytes)
            operator delete(this, 0xF8);
        }

        return this;
    }
};