// FUNC_NAME: copyAnimationTransformData

// Reconstructed from 0x004AAC50
// This function copies a large block of animation transform data (4x4 matrices + vector)
// from a source object (ESI) to a destination object (EDI), sets up vtables,
// and updates a thread-local flag indicating the copy is active.
// The structure layout suggests two 4x4 matrices (rows at offsets 0xA0, 0xB0, ... 0x110)
// plus an extra 4-float vector at 0x120/0x12C.

#include <cstdint>

// External vtable pointers (set by the game engine)
extern void* PTR_FUN_00e35674;  // First vtable for destination object
extern void* PTR_LAB_00e35678;  // Second vtable for destination object (at offset +0x08)

// Constants for offsets within the source and destination objects
constexpr uint32_t SOURCE_TRANSFORM_START = 0xA0;  // 160 bytes of transform data
constexpr uint32_t SOURCE_TRANSFORM_END   = 0x130; // 304 bytes (inclusive of last vector)
constexpr uint32_t DEST_HEADER_SIZE       = 0x40;  // 64 bytes header (vtables, flags, etc.)
constexpr uint32_t DEST_TRANSFORM_OFFSET  = 0x10;  // dword index into destination (byte offset = 0x40)
constexpr uint32_t DEST_FLAG_OFFSET       = 0x0E;  // byte flag in destination (mask 0x40)
constexpr uint32_t GLOBAL_FLAG_OFFSET     = 0x800; // OR mask for thread-local flag

// The thread-local storage pointer (FS:0x2C) – assumed to point to a global structure
// containing a pointer at offset +8 that leads to a flag array.
// In practice, the game uses FS:[0x2C] to access a per-thread context.
extern uint32_t __readfsdword(uint32_t offset);  // intrinsics for FS segment

// Forward declaration of called function (initializes source transforms)
void initializeSourceTransforms(void* sourceObject);

void __thiscall copyAnimationTransformData(void* thisPtr /* ESI */, void* destObject /* EDI */)
{
    // ESI = source object (thisPtr)
    // EDI = destination object (destObject)
    // The function is called with ECX = source, and the caller sets EDI = destination.
    
    // Step 1: Prepare/initialize the source transforms (calls FUN_004AA3B0)
    initializeSourceTransforms(thisPtr);
    
    // Step 2: Set the vtables for the destination object
    *(void**)destObject                  = &PTR_FUN_00e35674; // primary vtable
    *(void**)((uint8_t*)destObject + 8)  = &PTR_LAB_00e35678; // secondary vtable (multiple inheritance)
    
    // Step 3: If the destination's flag at offset 0x0E does not have bit 0x40 set,
    //         copy the transform data from source to destination.
    if (!(*(uint8_t*)((uint8_t*)destObject + DEST_FLAG_OFFSET) & 0x40))
    {
        // Copy the 144 bytes (36 DWORDs) of transform data from source to destination.
        // Data is arranged as 4x4 matrices followed by a 4-float vector.
        // Source layout (offsets from source base):
        //  0xA0..0xAF  -> 4 floats (first row of matrix 1)
        //  0xB0..0xBF  -> 4 floats (second row)
        //  ... (eight rows total for two 4x4 matrices)
        //  0x120..0x12B -> 3 floats (vector XYZ)
        //  0x12C        -> 1 float  (vector W or scalar)
        // Destination layout (dword offsets from dest base):
        //  0x10..0x13  -> first row of matrix 1
        //  0x14..0x17  -> second row, etc.
        //  0x30..0x32  -> vector XYZ
        //  0x33        -> zero (explicitly set)
        //  0x34        -> vector W or scalar
        
        // Get pointers to source and destination data
        uint32_t* src  = (uint32_t*)((uint8_t*)thisPtr + SOURCE_TRANSFORM_START);
        uint32_t* dest = (uint32_t*)((uint8_t*)destObject + DEST_HEADER_SIZE);
        
        // Copy 35 DWORDs (two 4x4 matrices = 32 DWORDs + extra 3 DWORDs of vector)
        // Then handle the remaining two DWORDs (one from source, one zero)
        for (int i = 0; i < 35; ++i)
        {
            dest[i] = src[i];
        }
        // Explicitly set element 0x33 (offset 0xCC from dest base) to zero
        dest[0x33] = 0;
        // Copy the last DWORD from source (at offset 0x12C) to dest element 0x34
        dest[0x34] = src[35]; // src[35] corresponds to source offset 0x12C (since src+35*4 = 0xA0+0x8C=0x12C)
        
        // Step 4: Update a thread-local flag to indicate the copy was performed.
        // The flag is accessed via FS:[0x2C] -> pointer at +8 -> global structure -> offset +0x7C + dest_index[6]
        // This is likely used to mark the destination object as "dirty" or "updated".
        uint32_t* tlsSlot = (uint32_t*)__readfsdword(0x2C);   // Get pointer from FS:0x2C
        uint32_t* basePtr = *(uint32_t**)((uint8_t*)tlsSlot + 8); // Dereference to global structure
        uint32_t  destIndex = *(uint32_t*)((uint8_t*)destObject + 0x18); // Some index from destination (offset 6 dwords = 0x18)
        uint32_t* flagWord = (uint32_t*)((uint8_t*)basePtr + 0x7C + destIndex);
        *flagWord |= 0x800;  // Set the flag bit
    }
    // No return value
}