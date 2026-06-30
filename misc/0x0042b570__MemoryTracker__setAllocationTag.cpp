// FUNC_NAME: MemoryTracker::setAllocationTag
// Address: 0x0042b570
// Role: Sets the current allocation tag for the calling thread and optionally pushes it to the global allocation stack.
// The tag is a 16-bit identifier used for debugging/tracking memory allocations.
// The per-thread state is accessed via FS segment (TLS slot at offset 0x2c).
// If the thread's recording flag (at +0x34) is not 1, the tag is pushed onto a global stack
// residing at DAT_01206880+0x14. Each record is 8 bytes: 4-byte pointer (to a sentinel/vtable) + 2-byte tag + 2-byte padding.

// Note: The exact struct names are inferred; adjust based on full game sources.
struct ThreadMemoryState {
    char unknown_0x00[0x20];      // 0x00
    unsigned short currentTag;    // 0x20
    char unknown_0x22[0x12];      // 0x22
    int recordingEnabled;         // 0x34 (0 = enabled, 1 = disabled?)
};

// Global memory tracker (likely a singleton)
// DAT_01206880 is the base address; +0x14 holds a pointer to the top of the allocation stack.
extern char* DAT_01206880;          // base of memory tracker data
extern void* PTR_LAB_0110b838;      // sentinel/vtable pointer for record type

void __cdecl MemoryTracker::setAllocationTag(unsigned short tag)
{
    // Retrieve per-thread memory state from thread-local storage (FS:0x2c)
    ThreadMemoryState* threadState = *(ThreadMemoryState**)__readfsdword(0x2c);
    
    // Store the current tag (offset 0x20)
    threadState->currentTag = tag;

    // Check if recording is enabled (offset 0x34)
    if (threadState->recordingEnabled != 1) {   // 1 means disabled?
        uint** stackTopPtr = (uint**)(DAT_01206880 + 0x14);   // pointer to stack top
        uint* stackTop = *stackTopPtr;
        
        // Write sentinel pointer (first 4 bytes of record)
        *stackTop = (uint)&PTR_LAB_0110b838;
        
        // Advance stack pointer by 4 bytes
        stackTop = (uint*)((char*)stackTop + 4);
        
        // Write the 16-bit tag
        *(unsigned short*)stackTop = tag;
        
        // Advance by size of tag (2) + padding to maintain 4-byte alignment
        // Effectively each record is 8 bytes (4+2+2 padding)
        stackTop = (uint*)(((unsigned int)((char*)stackTop + 5)) & 0xFFFFFFFC);
        
        // Update the global stack top pointer
        *stackTopPtr = stackTop;
    }
}