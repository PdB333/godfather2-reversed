// FUNC_NAME: Object::compareTo (compares two objects of same type, returns combined key and inequality flag)
// Function at 0x00693bb0

#include <cstdint>

class Object {
public:
    // +0x00: type identifier (vtable/type info pointer or type ID)
    // +0x04: unique identifier (32-bit)
    uint32_t m_typeId;
    uint32_t m_uniqueId;

    // Compare this object with another. Requires both to have valid and matching typeId.
    // Returns a 32-bit value:
    //   bits 31-8 = (this->m_uniqueId >> 8)  // high 24 bits of uniqueId
    //   bit 0     = 1 if this->m_uniqueId != other->m_uniqueId, else 0
    uint32_t __thiscall compareTo(Object* other) {
        if ((this->m_typeId == 0) || (this->m_typeId != other->m_typeId)) {
            // Type mismatch or this object invalid → assertion failure
            assertionFailure();
        }
        uint32_t highPart = this->m_uniqueId >> 8;          // 24-bit base key
        uint32_t lowPart = (this->m_uniqueId != other->m_uniqueId) ? 1 : 0; // inequality flag
        return (highPart << 8) | lowPart;
    }

private:
    void assertionFailure(); // calls FUN_00b97aea
};