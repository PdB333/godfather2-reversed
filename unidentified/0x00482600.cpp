// FUN_00482600: Container::addEntry

#include <cstdint>

// Represents a node in the container (allocated by allocateNode)
struct ContainerNode {
    uint16_t field0;      // param_4
    uint8_t field2;       // param_7
    uint8_t field3;       // param_5
    uint16_t field4;      // copied from container->someValue +0x08
    // uint8_t pad[2];    // implicit gap
    uint32_t field8;      // param_3 (offset 8)
} __attribute__((packed)); // likely packed, as offsets show no padding

// The container class layout
class Container {
public:
    // +0x00: vtable? unknown
    // +0x08: uint16_t someValue;   // used as return and stored in node
    // +0x10: uint16_t* dataArray;  // array of 2-byte elements
    // +0x14: int32_t count;
    // +0x18: int32_t capacity;
    // Other members...
    uint16_t someValue;   // offset 0x08
    uint16_t* dataArray;  // offset 0x10
    int32_t count;        // offset 0x14
    int32_t capacity;     // offset 0x18

    // callees (defined elsewhere)
    ContainerNode* allocateNode(uint32_t param2); // FUN_00482c90
    void resizeArray(int32_t newCapacity);         // FUN_00483120
};

// __thiscall
uint16_t Container::addEntry(uint32_t param2, uint32_t param3,
                              uint16_t param4, uint8_t param5,
                              uint16_t param6, uint8_t param7)
{
    // Allocate a new node – note: passes address of param2, likely to read its value
    ContainerNode* node = allocateNode(param2);

    // Fill node fields
    node->field0 = param4;                        // offset 0
    node->field2 = param7;                        // offset 2
    node->field3 = param5;                        // offset 3
    node->field8 = param3;                        // offset 8
    node->field4 = this->someValue;               // offset 4

    // Grow the data array if needed
    if (this->count == this->capacity) {
        int32_t newCapacity = (this->capacity == 0) ? 1 : (this->capacity * 2);
        this->resizeArray(newCapacity);
    }

    // Append param6 to the dynamic array
    uint16_t* dest = this->dataArray + this->count; // offset = count * 2
    this->count++;
    if (dest != nullptr) {
        *dest = param6;
    }

    // Return the stored someValue (same as node->field4)
    return this->someValue;
}