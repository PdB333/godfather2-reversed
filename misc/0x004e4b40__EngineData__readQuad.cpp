// FUNC_NAME: EngineData::readQuad

#include <cstdint>

void EngineData::readQuad(void* handle, void* outData)
{
    // Access thread-local storage via FS segment offset 0x2C (TIB pointer).
    uint32_t** tlsTable = (uint32_t**)(__readfsdword(0x2C));
    // Dereference once, then offset 8 bytes (2 uint32_t* slots) to get the global data base address.
    uint32_t dataBase = *(uint32_t*)(*tlsTable + 2);
    // Data block array starts at offset 0x80 from the base.
    uint32_t* blockArray = (uint32_t*)(dataBase + 0x80);
    // Index into the array is stored at offset 0x10 of the handle object (byte offset).
    uint32_t index = *(uint32_t*)((uint8_t*)handle + 0x10);
    // Source pointer: blockArray + index (index is byte offset, not element count).
    uint32_t* src = (uint32_t*)((uint8_t*)blockArray + index);
    // Copy 4 uint32 values (16 bytes) to output.
    ((uint32_t*)outData)[0] = src[0];
    ((uint32_t*)outData)[1] = src[1];
    ((uint32_t*)outData)[2] = src[2];
    ((uint32_t*)outData)[3] = src[3];
}