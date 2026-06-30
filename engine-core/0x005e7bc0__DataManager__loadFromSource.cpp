// FUNC_NAME: DataManager::loadFromSource
// Function address: 0x005e7bc0
// Role: Copies three uint32 values from source data and a global constant into a local array, then calls a processing function.
// This likely deserializes or initializes some game object data from a buffer.

#include <cstdint>

// Forward declaration of the processing function (address 0x005e7440)
void FUN_005e7440(uint32_t* data);

// Global data referenced (address 0x00e2b1a4)
extern uint32_t DAT_00e2b1a4;

void DataManager::loadFromSource(uint32_t* sourceData) {
    // Stack buffer for 4 uint32 values
    uint32_t localData[4];

    // Copy three values from source
    localData[0] = sourceData[0];   // +0x00: first field
    localData[1] = sourceData[1];   // +0x04: second field
    localData[2] = sourceData[2];   // +0x08: third field

    // Fourth value comes from a global constant (likely a manager pointer or ID)
    localData[3] = DAT_00e2b1a4;    // +0x0C: global data

    // Call the processing function with the packed data
    FUN_005e7440(localData);
}