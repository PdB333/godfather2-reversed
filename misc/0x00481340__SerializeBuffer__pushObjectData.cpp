// FUNC_NAME: SerializeBuffer::pushObjectData
// Function address: 0x00481340
// Role: Writes 16 bytes from a source object (at offsets 0x60 and 0x68) into a global stack buffer.
// The buffer pointer is stored at g_pBuffer->m_stackPointer (+0x14).
// After alignment and writing, the stack pointer advances by 16 bytes.

// Global buffer context (singleton)
extern BufferContext* g_pBuffer;  // DAT_01206880

// Table of function pointers (used as initial stack base)
extern void* PTR_LAB_0110bb70[];

// Buffer context structure (inferred)
struct BufferContext {
    char pad_0x00[0x14];          // +0x00: unknown
    void* m_stackPointer;         // +0x14: current write pointer
};

// Source object structure (only offsets 0x60-0x6F used)
struct SourceObject {
    char pad_0x00[0x60];          // +0x00: unknown
    uint64_t m_dataLow;           // +0x60: first 8 bytes
    uint64_t m_dataHigh;          // +0x68: next 8 bytes
};

void __fastcall SerializeBuffer::pushObjectData(SourceObject* pSrc) {
    BufferContext* pCtx = g_pBuffer;
    // Initialize stack pointer to the start of the global table + 4 (skip header?)
    *(uint32_t*)(&pCtx->m_stackPointer) = (uint32_t)&PTR_LAB_0110bb70;
    pCtx->m_stackPointer = (char*)pCtx->m_stackPointer + 4;

    uint32_t* pStackPtr = (uint32_t*)&pCtx->m_stackPointer;
    // Align current pointer upward to 16-byte boundary
    uint64_t* alignedPtr = (uint64_t*)((*pStackPtr + 0x0F) & ~0x0F);
    *pStackPtr = (uint32_t)alignedPtr;

    // Copy 16 bytes from source object
    alignedPtr[0] = *(uint64_t*)((char*)pSrc + 0x60);
    alignedPtr[1] = *(uint64_t*)((char*)pSrc + 0x68);

    // Advance stack pointer by 16 bytes
    *pStackPtr = *pStackPtr + 0x10;
}