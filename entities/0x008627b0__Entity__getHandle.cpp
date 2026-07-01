// FUNC_NAME: Entity::getHandle
// Address: 0x008627b0
// This method extracts an internal validity flag and an object identifier,
// then produces a 32-bit handle with type byte set to 0x01 if the object is valid.
// The low 24 bits are derived from the identifier (shifted right by 8).
// Used to encode an object's type/ID into a compact handle, possibly for
// networking or reference counting (EA EARS engine handle system).

#include <cstdint>

// Assume the object layout (32-bit alignment):
// +0x00: int m_validFlag;   // some pointer or non-zero when object is alive
// +0x04: (padding or unused)
// +0x08: int m_objectId;    // value used to build the handle (e.g. ghost index)

class Entity {
public:
    int   m_validFlag;  // offset 0x00
    // int   _pad;       // offset 0x04 (unused)
    int   m_objectId;   // offset 0x08

    // __thiscall
    uint32_t getHandle(int *outValidFlag, int *outObjectId) const;
};

uint32_t __thiscall Entity::getHandle(int *outValidFlag, int *outObjectId) const {
    int valid = this->m_validFlag;
    *outValidFlag = valid;

    if (valid != 0) {
        int id = this->m_objectId;
        *outObjectId = id;

        // Build handle: high byte = 0x01 (type/valid flag), low 24 bits = (id >> 8)
        return (0x01 << 24) | (static_cast<uint32_t>(id) >> 8);
    }

    *outObjectId = 0;
    return 0;
}