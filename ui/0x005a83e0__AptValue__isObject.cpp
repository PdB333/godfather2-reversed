// FUNC_NAME: AptValue::isObject
// Address: 0x005a83e0
// Role: Checks whether the AptValue object is of a specific object type (0x800C)
//        and asserts if the this pointer is null.
// The type field is assumed to be the first 32-bit field of the object.
// A non-null object with type == 0x800C returns true, else false.

#include <cassert>

class AptValue {
public:
    uint32_t type; // +0x00: type tag (lower 15 bits = type id, bit 15 = object flag)
    // ... other fields

    // Check whether this value is of the specific object type (type id 0x0C with object flag set)
    bool isObject() __thiscall;
};

bool AptValue::isObject() {
    // Assert that the object pointer is valid
    assert(this != nullptr && "AptValue::isObject: null this pointer");

    // Check if the type tag matches the expected object type constant:
    // - Lower 15 bits equal 0x0C (type id)
    // - Bit 15 (0x8000) is set (object flag)
    return (this->type & 0x7FFF) == 0x0C  &&
           (this->type & 0x8000) != 0;
}