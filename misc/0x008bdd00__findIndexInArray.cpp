// FUNC_NAME: findIndexInArray
// Function address: 0x008bdd00
// Role: Linear search in an array of 28-byte elements (7 floats) for a key consisting of 3 floats, a byte, and a float.
// Returns index if found, 0xFFFFFFFF (-1) if not found.

struct ArrayElement {
    float x;          // +0x00
    float y;          // +0x04
    float z;          // +0x08
    char type;        // +0x0C (byte)
    char pad[3];      // +0x0D padding
    float value;      // +0x10
    float extra1;     // +0x14 (unused in comparison)
    float extra2;     // +0x18 (unused in comparison)
}; // total 0x1C (28 bytes)

struct ArrayDescriptor {
    ArrayElement* elements; // +0x00
    uint32_t count;         // +0x04
};

uint __thiscall findIndexInArray(ArrayDescriptor* arrayInfo, const ArrayElement* key)
{
    uint index = 0;
    if (arrayInfo->count == 0) {
        return 0xFFFFFFFF;
    }
    ArrayElement* current = arrayInfo->elements;
    while (true) {
        // Compare first 3 floats (position)
        if (current->x == key->x &&
            current->y == key->y &&
            current->z == key->z &&
            // Compare type byte (cast to char)
            *(char*)&current->type == *(char*)&key->type &&
            // Compare value float (note: decompiler showed pointer comparison, but this is likely a value comparison)
            current->value == key->value)
        {
            return index;
        }
        index++;
        current++;
        if (index >= arrayInfo->count) {
            return 0xFFFFFFFF;
        }
    }
}