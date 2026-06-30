// FUNC_NAME: StreamManager::initStreamBuffer
//
// Address: 0x00609e40
// Role: Initializes a 0x10-byte stream buffer descriptor with a 1MB buffer size,
//       registers it with the stream manager, and sets global state.

// Global pointers (assumed from data references)
extern void* (*g_allocFunc)(uint size, void* tag); // DAT_01205868
extern void* g_streamManager;                      // DAT_01205750
extern void (*g_continueFunc)(int);                // PTR_FUN_00f15a3c
extern int g_initDone;                             // DAT_01205844
extern void* g_streamBuffer;                       // DAT_01205840

// Stream buffer descriptor structure (size = 0x10 bytes)
struct StreamBuffer {
    uint    bufferSize;       // +0x00 (set to 0x100000)
    void*   selfPointer;      // +0x04 (set to &this)
    void*   unknown;          // +0x08 (set to this)
    byte    flags;            // +0x0C (set to 1)
    // remainder unused (0x10 total)
};

void StreamManager::initStreamBuffer()
{
    int iVar1;
    int iVar2;
    
    // Tag/identifier data passed to allocator
    int tagData[3] = { 2, 0x10, 0 };
    
    // Allocate a 0x10-byte descriptor
    iVar1 = g_allocFunc(0x10, tagData);
    if (iVar1 != 0) {
        // Initialize descriptor fields
        ((StreamBuffer*)iVar1)->bufferSize = 0x100000;   // +0x04
        ((StreamBuffer*)iVar1)->selfPointer = (void*)iVar1;   // +0x08
        ((StreamBuffer*)iVar1)->flags = 1;               // +0x0C (single byte)
        
        // Call stream manager method (vtable+0x68)
        // Signature: int (__thiscall *)(void* this, uint, uint, int, int, void*, int)
        // Parameters: bufferSize=0x100000, alignment=0x208, zeros, descriptor, flags=0
        iVar2 = (**(int (__thiscall**)(void*, uint, uint, int, int, void*, int))
                 (*(void**)g_streamManager + 0x68))
                (g_streamManager, 0x100000, 0x208, 0, 0, (void*)iVar1, 0);
        
        if (iVar2 != 0 && iVar2 == 0x8876007C) {  // -0x7789fe84
            g_continueFunc(2);
        }
    }
    
    g_initDone = 0;
    g_streamBuffer = (void*)iVar1;
}