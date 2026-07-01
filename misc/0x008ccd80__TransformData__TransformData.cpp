// FUNC_NAME: TransformData::TransformData
// Function address: 0x008ccd80
// Role: Constructor for TransformData, initializes from a data block (param_2) by extracting two sets of four floats (position and rotation) based on element IDs.

#include <cstdint>

// Forward declarations
struct DataBlockElement;
struct DataBlock;

// Constants for element IDs (likely hashed strings)
const int32_t ID_POSITION = -0x56f3c215; // 0xA90C3DEB
const int32_t ID_ROTATION = -0x3efcc671; // 0xC103398F

// Element type constant
const int32_t ELEMENT_TYPE_FLOAT4 = 0x10;

// Data block element structure (size >= 24 bytes)
struct DataBlockElement {
    int32_t* data;          // +0x00: pointer to actual data
    int32_t unknown1;       // +0x04
    int32_t unknown2;       // +0x08
    int32_t id;             // +0x10 (piVar1[4])
    int32_t type;           // +0x14 (piVar1[5])
    // ... possibly more
};

// Data block structure (partial)
struct DataBlock {
    // ... (unknown fields)
    int32_t* elementArray;  // +0x1C: pointer to array of DataBlockElement pointers
    uint16_t elementCount;  // +0x20: number of elements
    // ...
};

// TransformData class (size >= 48 bytes)
class TransformData {
public:
    // Vtable pointer at offset 0
    void* vtable;           // +0x00: set to &PTR_FUN_00d7c768

    // Two sets of four floats (e.g., position and rotation quaternion)
    float rotation[4];      // +0x0C (param_1[3] to param_1[6])
    float position[4];      // +0x1C (param_1[7] to param_1[10])

    // Constructor
    TransformData(DataBlock* dataBlock, int32_t extraParam);
};

// External base constructor (likely for a parent class)
extern void baseConstructor(DataBlock* dataBlock, int32_t extraParam);

// External vtable symbol
extern void* PTR_FUN_00d7c768;

TransformData::TransformData(DataBlock* dataBlock, int32_t extraParam) {
    // Call base class constructor
    baseConstructor(dataBlock, extraParam);

    // Set vtable
    this->vtable = &PTR_FUN_00d7c768;

    // Zero out both float arrays
    for (int i = 0; i < 4; ++i) {
        this->position[i] = 0.0f;
        this->rotation[i] = 0.0f;
    }

    // Iterate over data block elements
    uint16_t count = *(uint16_t*)((uint8_t*)dataBlock + 0x20);
    if (count != 0) {
        int32_t** elementArray = *(int32_t***)((uint8_t*)dataBlock + 0x1C);
        for (uint16_t i = 0; i < count; ++i) {
            DataBlockElement* element = (DataBlockElement*)elementArray[i];
            if (element->type == ELEMENT_TYPE_FLOAT4) {
                int32_t* dataPtr = element->data;
                if (element->id == ID_POSITION) {
                    // Copy position data (offsets 0x0C, 0x10, 0x14, 0x18 from dataPtr)
                    this->position[0] = *(float*)(dataPtr + 3);  // +0x0C
                    this->position[1] = *(float*)(dataPtr + 4);  // +0x10
                    this->position[2] = *(float*)(dataPtr + 5);  // +0x14
                    this->position[3] = *(float*)(dataPtr + 6);  // +0x18
                } else if (element->id == ID_ROTATION) {
                    // Copy rotation data (offsets 0x0C, 0x10, 0x14, 0x18 from dataPtr)
                    this->rotation[0] = *(float*)(dataPtr + 3);  // +0x0C
                    this->rotation[1] = *(float*)(dataPtr + 4);  // +0x10
                    this->rotation[2] = *(float*)(dataPtr + 5);  // +0x14
                    this->rotation[3] = *(float*)(dataPtr + 6);  // +0x18
                }
            }
        }
    }
}