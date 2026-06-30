// FUNC_NAME: QuadRenderManager::initializeQuadIndices

#include <cstring> // for memset

// Engine globals (from Ghidra, addresses approximate)
extern void* gMemoryManager;               // DAT_01205868
extern void* gResourceManager;             // DAT_01205750
extern void* gQuadDescriptorGlobal;        // DAT_01205848
extern void* gIndexBufferGlobal;           // DAT_0120584c
extern void* gQuadVertexBufferGlobal;      // DAT_01205840
extern int   gQuadVertexBufferSize;        // DAT_01205844

extern char  gQuadHashTable[1024];          // DAT_011f3dd8
extern char  gQuadHashTable2[1024];         // DAT_011f39d8
extern char  gQuadIndexBufferData[32768];   // DAT_011eb8f0

extern int   gQuadEntryCount;              // DAT_012224a8
// Each entry is 12 bytes: 8 bytes (two function pointers) + 4 bytes (flags/size)
extern char  gQuadEntryArray[12 * 32];      // starting at DAT_01222328, size unknown

// Error handler (exported)
extern void reportError(int code);          // PTR_FUN_00f15a3c(2) - prints error

// Helper functions (renamed from Ghidra)
extern int  allocateIndexBuffer();          // via *gMemoryManager, returns pointer
extern int  createIndexBuffer(int size, int type, int usage, int count, void* desc, int extra);
extern int  finalizeIndexBuffer();          // via *gQuadDescriptorGlobal

// Called from FUN_0060be40 (unknown)
extern void textureManagerInit();

// Called when hash table limit hit (error case)
extern void handleHashTableOverflow();      // FUN_00609bf0

// Structures
struct QuadIndexBufferDesc {
    void*    vtbl;          // +0x00: vtable pointer
    int      selfPtr;       // +0x04: pointer to self
    char     unknownByte;   // +0x08: flags byte (stored at offset +2)
    char     pad1[3];       // alignment
    int      numIndices;    // +0x0C: number of indices (0x600 = 1536)
    short    field_0x10;    // +0x10: short at offset 4 from start? Actually short at +0x10
    short    field_0x12;    // +0x12: short at +0x12
    int      bufferPtr;     // +0x14: pointer to index buffer data (initially 0)
};

void initializeQuadIndices() {
    QuadIndexBufferDesc* desc;
    int allocSize;
    int newAlloc;
    int result;
    short* indexPtr;
    short* indexEnd;
    short baseVertex;

    // Clear state tables
    memset(gQuadHashTable, 0xFF, 0x400);    // 1024 bytes to -1
    gQuadHashTable2[0] = 0xFF;              // DAT_00f15988 (global byte)
    gQuadHashTable2[4] = 0xFF;              // DAT_00f1598c
    gQuadVertexBufferSize = 0;
    memset(gQuadHashTable2, 0xFF, 0x400);   // also at DAT_011f39d8
    memset(gQuadIndexBufferData, 0, 0x8000); // 32KB

    // Allocate index buffer control block (size 40? actually 32 + 8)
    // First call: *(code**)*gMemoryManager()() returns pointer
    gIndexBufferGlobal = (void*)((int(*)(void))(*((void**)gMemoryManager)))();
    // Clear first 4 8-byte fields
    ((int*)gIndexBufferGlobal)[0] = 0;
    ((int*)gIndexBufferGlobal)[1] = 0;
    ((int*)gIndexBufferGlobal)[2] = 0;
    ((int*)gIndexBufferGlobal)[3] = 0;
    ((int*)gIndexBufferGlobal)[2] = 0;  // note: overlap? Actually writes at offset 8? But let's keep as is.
    // Set field at byte offset +4 to 4 (size descriptor?)
    *(int*)((char*)gIndexBufferGlobal + 4) = 4;

    // Allocate vertex buffer object (size 0x100000 = 1MB)
    allocSize = (int)(*((int(*)(void))(*((void**)gMemoryManager)))();
    *(int*)(allocSize + 8) = allocSize;        // self-reference
    *(int*)(allocSize + 4) = 0x100000;          // size field
    *(char*)(allocSize + 0x0C) = 1;             // flag

    // Register vertex buffer with resource manager
    result = ((int(*)(void*, int, int))(*((void**)gResourceManager) + 0x68))(gResourceManager, 0x100000, 0x208);
    if (result != 0 && result == 0x8876017C) { // -0x7789fe84
        reportError(2);
    }

    gQuadVertexBufferSize = 0;
    gQuadVertexBufferGlobal = (void*)allocSize;

    // Allocate index buffer descriptor (size 0x20)
    desc = (QuadIndexBufferDesc*)((int(*)(int, int*))(*((void**)gMemoryManager)))(0x20, (int*)&allocSize); // careful with stack param
    desc->selfPtr = (int)desc;                 // self-reference
    desc->numIndices = 0x600;                  // 1536 indices
    desc->bufferPtr = 0;                       // pointer to index data, init 0
    *(char*)(&desc->unknownByte + 0) = 0;      // byte at offset 2? Actually offset 2 from start
    *(short*)((char*)desc + 0x10) = 0;
    *(short*)((char*)desc + 0x12) = 0;

    // Create index buffer resource
    result = ((int(*)(void*, int, int, int, int, QuadIndexBufferDesc*, int))(*((void**)gResourceManager) + 0x6C))
                (gResourceManager, 0xC00, 8, 0x65, 1, desc, 0);
    if (result != 0 && result == 0x8876017C) {
        reportError(2);
    }

    // Determine flags based on byte in descriptor
    int flags = 0;
    if (*(char*)(&desc->unknownByte) != 0) { // test byte at +2
        flags = 0x3000;
    }

    gQuadDescriptorGlobal = desc;

    // Finalize index buffer (map memory)
    ((void(*)(void*, int, int, int*, int))(*((int*)desc->vtbl) + 0x2C))
        ((void*)desc->vtbl, 0, 0, &desc->bufferPtr, flags);

    // Now fill index buffer with quad indices (256 quads, each 6 shorts)
    indexPtr = (short*)desc->bufferPtr;
    indexEnd = indexPtr + 0x600; // 1536 shorts
    baseVertex = 2;
    while (indexPtr < indexEnd) {
        indexPtr[0] = baseVertex - 2;
        indexPtr[1] = baseVertex - 1;
        indexPtr[2] = baseVertex;
        indexPtr[3] = baseVertex - 2;
        indexPtr[4] = baseVertex;
        indexPtr[5] = baseVertex + 1;
        indexPtr += 6;
        baseVertex += 4;
    }

    // Additional initialization
    textureManagerInit();

    // Finalize the buffer
    ((void(*)(void*))(*((int*)desc->vtbl) + 0x30))((void*)desc->vtbl);

    // Register quad patches in the hash table
    for (int i = 0; i < gQuadEntryCount; ++i) {
        if (gQuadEntryArray[i * 12] > 0x80) {  // check byte at start of each entry
            handleHashTableOverflow();
            return;
        }
    }

    // Add a new entry if there is room (max 32 entries)
    if (gQuadEntryCount < 32) {
        int offset = gQuadEntryCount * 12;
        // Store two function pointers: 0x00609e20 and 0x00609e40
        *(long long*)(gQuadEntryArray + offset) = 0x609E4000609E20LL; // little-endian
        // Store flags/size: bit31 set, plus uVar6>>8 (0 or 0x30)
        uint newFlags = (flags >> 8) & 0xFFFFFF; // lower 24 bits
        *(uint*)(gQuadEntryArray + offset + 8) = (0x80 << 24) | newFlags;
        gQuadEntryCount++;
    }
}