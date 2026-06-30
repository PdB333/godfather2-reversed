// FUNC_NAME: NetMessage::parseRaw

// Function address: 0x0065e3a0
// Role: Parses a raw network message (possibly encrypted/encoded) and populates internal fields.
// This function processes a string buffer from param_2 (struct with +0x0c string ptr, +0x10 length).
// It decodes/decrypts content into a buffer, creates an object, and sets status flags.

#include <cstdint>

struct NetMessage {
    // +0x00: vtable
    // +0x04: unknown
    // +0x08: unknown
    // +0x0c: uint8_t* decodedBuffer;  // Allocated buffer of size 0x38
    // +0x10: uint32_t fourCC;         // Extracted from bytes 1-4 of source string
    // +0x14: bool isEncrypted;        // true if source first byte != '\0'
    // +0x18: DataChunk* chunk;        // Created object (vtable at 0x00e42d64, ref counted)
    // +0x1c: unknown
    // +0x20: uint8_t readyFlag;       // Set to 1 after successful parse
};

struct DataChunk {
    // vtable at 0x00e42d64
    // +0x04: int32_t refCount;   // initial 0
    // +0x08: int32_t refCount2;  // initial 0
    // +0x0c: uint8_t* dataPtr;   // pointer to source string (param_2+0x0c)
    // +0x10: int32_t dataLen;    // from param_2+0x10
    // +0x14: uint8_t flag;       // initial 0
};

// Forward declarations (function addresses from Ghidra)
extern "C" void* _malloc(uint32_t size);
extern "C" int32_t decodeBuffer(const uint8_t* src, uint32_t srcLen, uint8_t* dst); // FUN_00663a00
extern "C" int32_t decryptBuffer(const uint8_t* src, uint32_t srcLen, uint8_t* dst); // FUN_00663850
extern "C" void* allocateSmallBlock(uint32_t size); // FUN_009c8e50 (usually 0x18)
extern "C" void referenceObject(DataChunk* obj); // FUN_0065e830 (increment refCount?)
extern "C" void globalReset(); // FUN_0064b4e0
extern "C" void someInit(); // FUN_0065e0e0

// Global temporary buffer used during decryption
extern uint8_t g_tempBuffer[5]; // DAT_01204978 - 7b (4 bytes + 1 byte at +4)

// Vtable location for DataChunk
extern void* g_DataChunkVtable; // PTR_LAB_00e42d64

void NetMessage::parseRaw(int32_t param_1, int32_t param_2) {
    NetMessage* self = (NetMessage*)param_1;
    int32_t srcBuffer = param_2; // Actually a struct

    // Initialize ready flag to 0
    *(uint8_t*)(self + 0x20) = 0;

    // Allocate a buffer of size 0x38 for decoded data
    uint8_t* decodedBuffer = (uint8_t*)_malloc(0x38);

    // Retrieve string pointer and length from param_2 struct
    uint8_t* srcString = *(uint8_t**)(srcBuffer + 0x0c);
    uint32_t srcLen = *(uint32_t*)(srcBuffer + 0x10);

    // First byte of source string determines encryption flag
    self->isEncrypted = (srcString[0] != '\0');

    // Extract 4-byte identifier (big-endian) from bytes 1-4
    if (srcLen > 4) {
        self->fourCC = (srcString[1] << 24) | (srcString[2] << 16) | (srcString[3] << 8) | srcString[4];

        int32_t decodeResult = decodeBuffer(srcString + 5, srcLen - 5, decodedBuffer);
        if (decodeResult == 0) {
            self->decodedBuffer = decodedBuffer;

            if (!self->isEncrypted) {
                // Non-encrypted: create a DataChunk object from the raw source
                DataChunk* chunk = (DataChunk*)allocateSmallBlock(0x18);
                if (chunk != nullptr) {
                    chunk = (DataChunk*)0; // actual allocation happens only if not null
                } else {
                    // allocation succeeds, set fields
                    chunk->refCount = 0;
                    chunk->refCount2 = 0;
                    chunk->vtable = (void*)&g_DataChunkVtable;
                    chunk->dataLen = srcLen;
                    chunk->dataPtr = srcString;
                    chunk->flag = 0;
                }

                // Release previous chunk (if any) by decrementing ref and possibly destroying
                DataChunk* oldChunk = self->chunk;
                if (oldChunk != nullptr) {
                    oldChunk->refCount--;
                    if (oldChunk->refCount == 0) {
                        // Call vtable destructor at offset 8
                        void (*destructor)(DataChunk*) = (void(*)(DataChunk*))(*(void**)(oldChunk->vtable) + 8);
                        destructor(oldChunk);
                    }
                }

                self->chunk = chunk;
                if (chunk != nullptr) {
                    chunk->refCount++;
                }

                globalReset();
                self->readyFlag = 1;

            } else {
                // Encrypted: write fourCC to temporary global temp buffer (big-endian)
                g_tempBuffer[0] = (uint8_t)(self->fourCC >> 24);
                g_tempBuffer[1] = (uint8_t)(self->fourCC >> 16);
                g_tempBuffer[2] = (uint8_t)(self->fourCC >> 8);
                g_tempBuffer[3] = (uint8_t)(self->fourCC);
                // Note: g_tempBuffer has 5 bytes, last one remains (DAT_0120497d)

                int32_t decryptParam = 0x7fb; // seems to be a flag or size
                int32_t decryptResult = decryptBuffer(&g_tempBuffer[4], &decryptParam, 1, decodedBuffer);
                if (decryptResult == 0) {
                    int32_t newLen = decryptParam + 5; // original length after decryption?

                    DataChunk* chunk = (DataChunk*)allocateSmallBlock(0x18);
                    if (chunk != nullptr) {
                        chunk->refCount = 0;
                        chunk->refCount2 = 0;
                        chunk->vtable = (void*)&g_DataChunkVtable;
                        chunk->dataLen = newLen;
                        chunk->dataPtr = (uint8_t*)&g_tempBuffer; // points to temp buffer?
                        chunk->flag = 0;
                    }

                    referenceObject(chunk); // increments ref
                    globalReset();

                    int32_t allocResult = (int32_t)allocateSmallBlock(0x18);
                    if (allocResult == 0) {
                        referenceObject(chunk);
                        globalReset();
                        self->readyFlag = 1;
                        return;
                    }

                    someInit();
                    referenceObject(chunk);
                    globalReset();
                    self->readyFlag = 1;
                    return;
                }
            }
        }
    }
}