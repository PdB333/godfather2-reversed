// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x00509d70
// Destructor for EARSObject; frees an internal buffer and returns it to a global memory pool.
// On entry, param_1 (this) is __fastcall (ECX). Offsets:
//   +0x00: vtable pointer (set to base vtable during destruction)
//   +0x04: pointer to a memory block (the buffer to free)
//   +0x08: second vtable pointer (set to cleanup vtable after destruction)

extern void* g_memoryManager;           // DAT_01206880 – global memory manager base
extern void* PTR_FUN_00e380e8;          // base vtable for this class
extern void* PTR_LAB_01123be8;          // vtable for free node
extern void* PTR_LAB_00e38180;          // vtable for cleanup state
extern void  FUN_009c8eb0(void* ptr);   // deallocator / free routine

class EARSObject {
public:
    void* vtable;            // +0x00
    void* m_pBuffer;         // +0x04  – dynamically allocated buffer
    void* vtable2;           // +0x08  – secondary vtable (e.g. base class)
    // ... other fields
    
    __fastcall ~EARSObject();
    // destructor defined below
};

__fastcall EARSObject::~EARSObject() {
    // Step 1: Swap vtable to base vtable (likely part of destruction chain)
    this->vtable = &PTR_FUN_00e380e8;
    
    // Step 2: If we have an attached buffer, free it and potentially recycle its memory
    if (this->m_pBuffer != nullptr) {
        int* pBuffer = (int*)this->m_pBuffer;
        int iValue = *pBuffer;   // First word of buffer (maybe a size or id)
        
        // Free the buffer memory
        FUN_009c8eb0(pBuffer);
        this->m_pBuffer = nullptr;
        
        // If the first word was non‑zero, add it to a global free list
        if (iValue != 0) {
            // g_memoryManager + 0x14 is a pointer to a free list head (int**)
            int** ppFreeList = (int**)((char*)g_memoryManager + 0x14);
            // Prepend a new node; set its vtable and store the value
            **(int***)ppFreeList = &PTR_LAB_01123be8;
            (*ppFreeList)++;               // advance head by 4 bytes (node size)
            **(int**)ppFreeList = iValue;  // store the value
            (*ppFreeList)++;               // advance again
        }
        
        // Set second vtable to cleanup state
        this->vtable2 = &PTR_LAB_00e38180;
        return;
    }
    
    // No buffer – set second vtable and return
    this->vtable2 = &PTR_LAB_00e38180;
    return;
}