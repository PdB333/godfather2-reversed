// FUNC_NAME: EAString::init(bool isHeapAllocated)

// Function address: 0x0043e0f0
// Role: String class constructor/reinitializer. Clears internal state and optionally frees the object if heap-allocated.
// Uses small string optimization: inline buffer of 16 bytes (15 chars + null) when capacity <= 15, else heap buffer.

// Assumed struct layout (offsets from this pointer):
// +0x00: void* vtable
// +0x0C: union {
//           char*  heapData;     // when mCapacity > 15
//           char   inlineBuffer[16]; // when mCapacity <= 15
//         } mData
// +0x1C (param_1[7]): int32_t mLength
// +0x20 (param_1[8]): int32_t mCapacity

class EAString;

void* EAString::init(bool isHeapAllocated)
{
    // Set vtable to base class (initial placeholder)
    *reinterpret_cast<void**>(this) = &PTR_FUN_00da9810;

    // If the current capacity exceeds the small buffer limit,
    // free the heap-allocated buffer.
    if (mCapacity > 15)
    {
        // Free the heap data pointer at offset +0x0C
        FUN_009c8eb0(mData.heapPtr); // likely operator delete
    }

    // Reset to small buffer configuration
    mCapacity = 15;                // maximum inline capacity
    mLength   = 0;                 // empty string
    mData.inlineBuffer[0] = '\0'; // null-terminate inline buffer

    // Set vtable to the actual class vtable (derived or final)
    *reinterpret_cast<void**>(this) = &PTR_LAB_00e31044;

    // If the object was allocated on the heap, delete it.
    // This suggests the function can act as a "clear and release" for pooled objects,
    // or it is a placement constructor where the caller passes a flag to indicate ownership.
    if (isHeapAllocated)
    {
        FUN_009c8eb0(this); // free the entire object
    }

    return this; // note: might return a dangling pointer if isHeapAllocated is true
}