// FUNC_NAME: BNKStreamManager::~BNKStreamManager
// Function address: 0x0075a550
// Role: Destructor for BNKStreamManager. Cleans up owned child objects, releases stream pointers, and performs global audio cleanup.

#include <cstdint>

// Forward declarations of called functions
typedef void (*ReleaseStreamFunc)(void*);  // FUN_005f7860
typedef void (*DeleteObjectFunc)(void*);   // FUN_004daf90 (likely operator delete)
typedef void (*StopAllSoundFunc)(int);     // FUN_005512c0
typedef void (*SetGlobalVolumeFunc)(float); // FUN_007f6420 (0x48 as float volume)
typedef void (*ShutdownSoundSystemFunc)(); // FUN_004ac1e0

// Assumed memory layout for BNKStreamManager (offsets in dwords offset/4)
struct BNKStreamManager
{
    // +0x00: vtable pointer (set to global vtable at 0x00d65070)
    void* vtable;                     // +0x00

    // Other fields (from param_1 offsets):
    // +0x6C (0x1B): Pointer to parent object (e.g., StreamManager)
    void* parentManager;              // +0x6C

    // +0x70 (0x1C): Owned stream object that is released (not deleted)
    void* releaseStreamPtr;           // +0x70

    // +0x74 (0x1D): Owned stream object that is deleted via virtual destructor
    void* deleteStreamPtr;            // +0x74

    // +0x7C (0x1F): Additional owned object (freed)
    void* extraObj1;                  // +0x7C

    // +0x84 (0x21): Additional owned object (freed)
    void* extraObj2;                  // +0x84
};

// Helper: call virtual destructor (first vtable entry) with argument 1 (delete)
inline void callVirtualDelete(void* obj)
{
    if (obj)
    {
        void** vtable = *(void***)obj;
        typedef void (*DestructorFunc)(void*, int);
        ((DestructorFunc)(vtable[0]))(obj, 1);
    }
}

void __fastcall BNKStreamManager_destructor(BNKStreamManager* thisPtr)
{
    // Set vtable to correct class (base destructor pattern)
    extern uint32_t PTR_LAB_00d65070; // Global vtable for BNKStreamManager
    thisPtr->vtable = &PTR_LAB_00d65070;

    // Release owned stream at +0x70
    if (thisPtr->releaseStreamPtr)
    {
        // Call FUN_005f7860 on this object (likely releases it without deletion)
        ((ReleaseStreamFunc)(0x005f7860))(thisPtr->releaseStreamPtr);
        thisPtr->releaseStreamPtr = nullptr;
    }

    // Delete owned stream at +0x74 via virtual destructor, then free memory
    void*& deletePtr = thisPtr->deleteStreamPtr;
    if (deletePtr)
    {
        callVirtualDelete(deletePtr);  // Invokes destructor (first vtable entry)
        if (deletePtr)                 // If destructor did not null the pointer (safety check)
        {
            ((DeleteObjectFunc)(0x004daf90))(&deletePtr);
            deletePtr = nullptr;
        }
    }

    // Clear a flag (bit 0) in the parent object's field at offset +0xE4
    // Interpretation: parentManager->flags &= ~1;
    if (thisPtr->parentManager)
    {
        uint32_t* flags = (uint32_t*)((char*)thisPtr->parentManager + 0xE4);
        *flags &= 0xFFFFFFFE;
    }

    // Global audio cleanup: stop all sounds (param 0) and set volume to 0.0f (0x48 as IEEE float)
    ((StopAllSoundFunc)(0x005512c0))(0);
    ((SetGlobalVolumeFunc)(0x007f6420))(0.0f);  // 0x48 is 0x00000000 as float (0.0f), or possibly 0.48f? Use consistent.

    // Free extra objects
    if (thisPtr->extraObj2)
    {
        ((DeleteObjectFunc)(0x004daf90))(&thisPtr->extraObj2);
    }
    if (thisPtr->extraObj1)
    {
        ((DeleteObjectFunc)(0x004daf90))(&thisPtr->extraObj1);
    }

    // Final free of the deleteStreamPtr again (already null, safe)
    if (thisPtr->deleteStreamPtr)
    {
        ((DeleteObjectFunc)(0x004daf90))(&thisPtr->deleteStreamPtr);
    }

    // Final global shutdown (likely releases remaining sound resources)
    ((ShutdownSoundSystemFunc)(0x004ac1e0))();

    return;
}