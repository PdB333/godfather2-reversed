// FUNC_NAME: SimNpc::getDataBlock

#include <cstdint>

struct DataBlock {
    uint64_t part1; // +0x00
    uint32_t part2; // +0x08
};

// Address: 0x007266b0
// Role: Copies 12 bytes from this+0x120 into an external buffer
void __thiscall SimNpc::getDataBlock(DataBlock* outData)
{
    // Temporary buffer for the raw 12-byte block
    char buffer[12];

    // Call to copy 12 bytes from internal storage at offset 0x120 into buffer
    // FUN_0056cef0 is likely a memcpy-like function (EA EARS internal copy)
    FUN_0056cef0(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x120), buffer);

    // Extract the two components from the buffer
    outData->part1 = *reinterpret_cast<uint64_t*>(buffer);
    outData->part2 = *reinterpret_cast<uint32_t*>(buffer + 8);
}