// FUNC_NAME: ManagedResource::assign
// Address: 0x0098c1c0
// Role: Assigns a new resource to this managed reference-counted object.
// Decrements the current reference count, copies resource data,
// optionally calls a cleanup callback if the new resource has active references,
// then finalizes the operation. Returns the previous data pointer via outResult.

#include <cstdint>

// Forward declarations of external helper functions (addresses from Ghidra)
extern "C" uint32_t __stdcall getDataFromResource(void* resource);  // FUN_00ab3c50
extern "C" void __stdcall copyDataToThis(void* dest, void* src);   // FUN_00ab4010
extern "C" void __stdcall finalizeResourceOperation(void* resource); // FUN_009c8f10

// Assumed memory layout for ManagedResource (this)
// +0x00: vtable pointer
// +0x04: stored data (e.g., pointer to resource data)
// +0x14: reference count

void __thiscall ManagedResource::assign(int thisPtr, uint32_t* outResult, void* newResource)
{
    // Decrement the reference count of this object
    int* refCount = (int*)(thisPtr + 0x14);
    (*refCount)--;

    // Extract data from the new resource
    uint32_t data = getDataFromResource(newResource);

    // Copy data from the new resource into this object's storage
    copyDataToThis((void*)(thisPtr + 4), newResource);

    // Check if the new resource still has active references (non-zero at +0x14)
    int* newResRef = (int*)((uint8_t*)newResource + 0x14);
    if (*newResRef != 0)
    {
        // Call a cleanup/decrement function via the resource's vtable (+0x20)
        // Passing the reference count as an argument (likely a callback pattern)
        void (*cleanupFunc)(int) = *(void (**)(int))((uint8_t*)newResource + 0x20);
        cleanupFunc(*newResRef);
    }

    // Finalize the operation (e.g., release temporary references, update counters)
    finalizeResourceOperation(newResource);

    // Output the retrieved data
    *outResult = data;
}