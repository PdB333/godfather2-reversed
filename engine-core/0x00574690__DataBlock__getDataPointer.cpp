// FUNC_NAME: DataBlock::getDataPointer
// Function address: 0x00574690
// Role: Returns a pointer to the actual data block represented by this DataBlock.
// If the index is 0, it copies the entire DataBlock (64 bytes) to a static buffer and returns that.
// Otherwise, it looks up the index in a mapping table provided by the context (param_2 at +0xB4).
// If the mapped byte is not 0xFF, it returns a pointer into a global table of 0x40-byte blocks.
// Otherwise, it returns a pointer into the static buffer at offset index * 0x10.

class DataBlock {
public:
    int index; // +0x00
    uint32_t data[15]; // +0x04, 60 bytes of payload (total 64 bytes)
};

// Static globals (from DAT_01205584 and _DAT_01205580)
static uint32_t g_defaultDataBuffer[16]; // 64-byte default buffer
static uint32_t g_largeDataTable[0x1000]; // Example size, actual unknown

uint32_t* __thiscall DataBlock::getDataPointer(void* context) {
    uint32_t* result;
    int idx = this->index;
    
    if (idx == 0) {
        // Copy this DataBlock's 64 bytes to the static default buffer
        g_defaultDataBuffer[0] = this->data[0];
        g_defaultDataBuffer[1] = this->data[1];
        g_defaultDataBuffer[2] = this->data[2];
        g_defaultDataBuffer[3] = this->data[3];
        g_defaultDataBuffer[4] = this->data[4];
        g_defaultDataBuffer[5] = this->data[5];
        g_defaultDataBuffer[6] = this->data[6];
        g_defaultDataBuffer[7] = this->data[7];
        g_defaultDataBuffer[8] = this->data[8];
        g_defaultDataBuffer[9] = this->data[9];
        g_defaultDataBuffer[10] = this->data[10];
        g_defaultDataBuffer[11] = this->data[11];
        g_defaultDataBuffer[12] = this->data[12];
        g_defaultDataBuffer[13] = this->data[13];
        g_defaultDataBuffer[14] = this->data[14];
        g_defaultDataBuffer[15] = this->data[15];
        return g_defaultDataBuffer;
    }
    
    // Check if context has a mapping table at offset +0xB4
    uint8_t** mappingTablePtr = *(uint8_t***)((char*)context + 0xB4);
    if (mappingTablePtr != nullptr) {
        uint8_t mappedIndex = mappingTablePtr[idx];
        if (mappedIndex != 0xFF) {
            // Return pointer into large data table (0x40-byte blocks)
            return (uint32_t*)((uint8_t*)g_largeDataTable + mappedIndex * 0x40);
        }
    }
    
    // Fallback: return pointer into default buffer at offset idx * 0x10 (16 bytes)
    return g_defaultDataBuffer + idx * 4; // 4 dwords = 16 bytes
}