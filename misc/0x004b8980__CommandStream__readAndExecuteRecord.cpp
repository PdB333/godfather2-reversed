// FUNC_NAME: CommandStream::readAndExecuteRecord

#include <cstdint>

// This function reads a command record from the stream and dispatches it via a handler.
// The stream is pointed to by 'this', which has a read cursor at offset 0x18.
// Record layout (relative to start of 8-byte-aligned portion):
//   [0]: 8 bytes (value as two 32-bit parts) actually read from aligned start
//   [8]: 4 bytes count (iVar5)
//   [12]: 4 bytes alignment (iVar6)
//   [12+padding]: count * 12 bytes of data (aligned to alignment boundary)
// The handler receives: cmd1, cmd2, value (64-bit), nextInfo (64-bit: high=next data start if count!=0, low=count), alignment.

typedef void (__stdcall *RecordHandler)(uint32_t cmd1, uint32_t cmd2, uint64_t value, uint64_t nextInfo, uint32_t alignment);

class CommandStream {
public:
    // +0x18: current read position
    uint8_t* mReadPos;

    void readAndExecuteRecord(void* handlerTable); // handlerTable[0] is the function pointer
};

void CommandStream::readAndExecuteRecord(void* handlerTable) {
    // Read first two 32-bit fields from current position
    uint32_t* cursor32 = reinterpret_cast<uint32_t*>(mReadPos);
    uint32_t cmd1 = cursor32[0];
    uint32_t cmd2 = cursor32[1];
    mReadPos = reinterpret_cast<uint8_t*>(cursor32 + 2); // advance 8 bytes

    // Align to 4-byte boundary (original code: (int)puVar2 + 0xb & ~3)
    // This effectively gives the same address as cursor32 after advancing.
    uint8_t* alignedStart = reinterpret_cast<uint8_t*>(
        (reinterpret_cast<uintptr_t>(cursor32) + 0xb) & ~(uintptr_t)3
    );

    // Read 8-byte value (valueLow, valueHigh)
    uint64_t* valuePtr = reinterpret_cast<uint64_t*>(alignedStart);
    uint64_t value = *valuePtr;
    uint32_t valueLow = static_cast<uint32_t>(value);
    uint32_t valueHigh = static_cast<uint32_t>(value >> 32);
    mReadPos = reinterpret_cast<uint8_t*>(valuePtr + 1); // advance 8 bytes

    // Read count (iVar5) - located at offset 8 from alignedStart
    int32_t count = *reinterpret_cast<int32_t*>(reinterpret_cast<uint64_t*>(alignedStart) + 1);
    // Set cursor to alignedStart+12
    mReadPos = alignedStart + 12;

    // Read alignment (iVar6) - located at offset 12 from alignedStart
    int32_t alignment = *reinterpret_cast<int32_t*>(alignedStart + 12);

    // Compute aligned start of data array (uVar8)
    uintptr_t dataStart = (reinterpret_cast<uintptr_t>(alignedStart) + alignment + 0xf) & ~(static_cast<uintptr_t>(alignment) - 1);

    // Update cursor to point past the data array (count * 12 bytes)
    mReadPos = reinterpret_cast<uint8_t*>(count * 12 + dataStart);

    // Construct the nextInfo 64-bit value
    uint64_t nextInfo = (static_cast<uint64_t>(count != 0 ? dataStart : 0) << 32) | static_cast<uint32_t>(count);

    // Dispatch to the handler
    RecordHandler handler = *reinterpret_cast<RecordHandler*>(handlerTable);
    handler(cmd1, cmd2, value, nextInfo, alignment);
}