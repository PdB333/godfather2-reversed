// FUNC_NAME: ChunkDeserializer::deserialize
// Function address: 0x008b2bf0
// Role: Reads a binary data chunk with specific tags (0-3) to populate object members at offsets +0x64, +0x78, +0x7C, +0x80-0x8C.
// The magic number 0x49a1b512 likely identifies the chunk type.

void __thiscall ChunkDeserializer::deserialize(int this, void* stream) {
    char hasMoreData;
    uint32_t tag;
    int iVar3;

    // Initialize the reader on the given stream
    initReader(stream);
    
    // Check magic number to verify chunk identity
    checkMagic(stream, 0x49a1b512);
    
    // Loop until all records in the chunk are consumed
    hasMoreData = isEndOfChunk();
    while (hasMoreData == '\0') {
        // Read the next record's tag
        tag = readTag();
        switch (tag) {
        case 0:
            // Read data into a child structure at this+0x64 (e.g., a child node or local transform)
            iVar3 = this + 0x64;
            readRecord(iVar3);
            applyTransform(iVar3);
            break;
        case 1:
            // Read a single value (likely float or int) into member at +0x78
            iVar3 = readRecord();
            *(uint32_t*)(this + 0x78) = *(uint32_t*)(iVar3 + 8);
            break;
        case 2:
            // Read a single value into member at +0x7C
            iVar3 = readRecord();
            *(uint32_t*)(this + 0x7C) = *(uint32_t*)(iVar3 + 8);
            break;
        case 3:
            // Read a 4-component value (quaternion or vector) into members at +0x80-0x8C
            readRecord();
            uint32_t* pVec = readVector4();
            *(uint32_t*)(this + 0x80) = pVec[0];
            *(uint32_t*)(this + 0x84) = pVec[1];
            *(uint32_t*)(this + 0x88) = pVec[2];
            *(uint32_t*)(this + 0x8C) = pVec[3];
            break;
        }
        // Advance to the next record
        advanceRecord();
        hasMoreData = isEndOfChunk();
    }
}

// Helper functions (internal, likely from the stream/reader class):
// These are based on the decompiled callees; their exact signatures and implementations are unknown.

void __thiscall initReader(void* stream);
void __thiscall checkMagic(void* stream, uint32_t magic);
char __thiscall isEndOfChunk(void);
uint32_t __thiscall readTag(void);
int __thiscall readRecord(void); // returns pointer to record data
int __thiscall readRecord(int outBuffer); // overload: reads into a buffer
void __thiscall applyTransform(int node);
uint32_t* __thiscall readVector4(void); // returns pointer to 4 uint32 (float)
void __thiscall advanceRecord(void);