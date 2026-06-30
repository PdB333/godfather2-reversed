// FUNC_NAME: DataChunkProcessor::processChunk
#include <cstdint>

// Reconstructed from 0x00618a70
// Class: DataChunkProcessor - handles data chunk reading/writing
// Fields (offsets from this in ESI):
// +0x0c: uint32_t flags
// +0x18: int32_t state (1 = special mode)
// +0x1c: int32_t dataSize
// +0x28: void* bufferPtr
// +0x2c: int32_t bufferSize (dataSize * elementSize? calculated at end)
// +0x40: int32_t elementSize
// +0x44: void* outputPtr

// Manager object (passed via EAX) has vtable at +0x14:
// +0x44: readData(void* buffer, int32_t size)
// +0x4c: writeData(int32_t size, void* inBuf, void* outBuf, int32_t flags)

int __thiscall DataChunkProcessor::processChunk(void* manager) {
    int32_t* mgr = reinterpret_cast<int32_t*>(manager);
    int32_t* mgrVtable = reinterpret_cast<int32_t*>(mgr[0x14 / 4]); // manager->vtable
    int32_t flags = 0;
    if (this->state == 1) {
        flags = 0x10; // special flag when state == 1
    }

    uint32_t localFlags = this->flags;
    if ((localFlags & 2) == 0) {
        // Normal mode (flag 2 not set)
        if ((localFlags & 4) == 0) {
            // Submode A
            // Call readData on manager
            typedef void (*ReadFunc)(void*, int32_t, uint8_t*);
            ReadFunc read = reinterpret_cast<ReadFunc>(mgrVtable[0x44 / 4]);
            uint8_t localBuf[36]; // local_24
            read(mgr, this->dataSize, localBuf);

            // Call writeData on manager (output to some stack area)
            typedef void (*WriteFunc)(void*, int32_t, uint8_t*, uint8_t*, int32_t);
            WriteFunc write = reinterpret_cast<WriteFunc>(mgrVtable[0x4c / 4]);
            uint8_t* dummyOut = nullptr; // stack0xffffffbc
            write(mgr, this->dataSize, nullptr, dummyOut, 0, flags);
        } else {
            // Submode B
            typedef void (*ReadFunc)(void*);
            ReadFunc read = reinterpret_cast<ReadFunc>(mgrVtable[0x44 / 4]);
            uint8_t localBuf[24]; // auStack_3c
            read(mgr); // called with no extra args? (decompiled may be incomplete)

            typedef void (*WriteFunc)(void*, int32_t, uint8_t*, uint8_t*, int32_t);
            WriteFunc write = reinterpret_cast<WriteFunc>(mgrVtable[0x4c / 4]);
            uint8_t* dummyOut = nullptr; // stack0xffffffbc
            write(mgr, 0, localBuf, dummyOut, 0, flags);
            // puVar3 = localBuf + dataSize * iVar4 (iVar4 = 0) → no change
        }
    } else {
        // Flag 2 set: alternate mode
        typedef void (*ReadFunc)(void*, int32_t, uint8_t*);
        ReadFunc read = reinterpret_cast<ReadFunc>(mgrVtable[0x44 / 4]);
        uint8_t localBuf[36]; // local_24
        read(mgr, 0, localBuf); // size = 0

        typedef void (*WriteFunc)(void*, int32_t, uint8_t*, uint8_t*, int32_t);
        WriteFunc write = reinterpret_cast<WriteFunc>(mgrVtable[0x4c / 4]);
        uint8_t* dummyOut = reinterpret_cast<uint8_t*>(&stack0xffffffbc); // actually stack var
        write(mgr, this->dataSize, nullptr, dummyOut, 0, flags);
    }

    // Store output pointers
    this->outputPtr = reinterpret_cast<uint8_t*>(puVar3); // derived from localBuf or dummyOut
    this->bufferPtr = reinterpret_cast<uint8_t*>(piVar1); // from stack
    this->bufferSize = this->elementSize * reinterpret_cast<intptr_t>(piVar1); // product

    return 1; // always success
}