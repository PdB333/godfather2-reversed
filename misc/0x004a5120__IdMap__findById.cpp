// FUNC_NAME: IdMap::findById
// Reconstructed C++ for function at 0x004a5120
// This function performs a linear search over an array of object references,
// looking for an object whose ID (stored at offset +0x04 of the object) matches
// the given key. If found, it writes the associated value to the output pointer
// and returns true; otherwise returns false.

#include <cstdint>

// Forward declaration of the object type with an ID field at offset +0x04.
struct Object {
    uint32_t field_0x00;   // unknown, offset 0x00
    uint32_t id;           // ID field at offset 0x04
};

// Structure representing an entry in the map: a pointer to an Object and an associated int value.
struct ObjectRef {
    Object* object;        // pointer to object with ID
    int32_t value;         // associated value
};

// Class that holds an array of ObjectRef entries and a count.
// Layout:
//   offset 0x34: pointer to ObjectRef array
//   offset 0x38: uint32 count of entries
class IdMap {
public:
    // Find an entry by object ID. Returns true and writes the associated value to 'outValue' on success.
    bool findById(int32_t key, int32_t* outValue) {
        bool found = false;
        uint32_t i = 0;
        uint32_t count = *(uint32_t*)((uint8_t*)this + 0x38);
        if (count != 0) {
            ObjectRef* entries = *(ObjectRef**)((uint8_t*)this + 0x34);
            // Linear search through the array
            while (entries[i].object->id != static_cast<uint32_t>(key)) {
                i++;
                if (count <= i) {
                    return found; // false
                }
            }
            // Found matching entry
            found = true;
            *outValue = entries[i].value;
        }
        return found;
    }
};