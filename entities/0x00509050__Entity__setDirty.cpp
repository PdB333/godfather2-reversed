// FUNC_NAME: Entity::setDirty
// Function address: 0x00509050
// Role: Sets or clears bit 1 (value 2) of the flags field at offset +0x08
// Typically used to mark the object as dirty/needing update

class Entity {
public:
    // Offset +0x08: flags (bitfield)
    uint32_t m_flags;

    // Sets/clears the dirty flag (bit 1, value 2)
    void __thiscall setDirty(bool dirty) {
        if (dirty) {
            m_flags |= 2;
        } else {
            m_flags &= ~2;
        }
    }
};