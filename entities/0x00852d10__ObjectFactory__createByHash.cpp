// FUNC_NAME: ObjectFactory::createByHash
// Address: 0x00852d10
// Role: Creates an instance of a class identified by a hash constant (0x4ecfbe13).
// Allocates 28 bytes (0x1c) for the object, then initializes it via a series of calls.
// Returns a pointer to the new object on success, or 0 on failure.

#include <cstdint>

// Forward declarations of internal engine functions (addresses from Ghidra)
void* __cdecl FUN_0043aff0(void* thisPtr, uint32_t classHash); // Likely constructor or initializer
void* __cdecl FUN_0043af00(uint32_t size);                     // Memory allocation (heap alloc)
bool  __cdecl FUN_0043b120(void);                              // Some condition check (e.g., singleton already exists)
void  __cdecl FUN_0043b210(void);                              // Cleanup or error handling
void* __cdecl FUN_0043abc0(void);                              // Finalize and return object pointer

// Constant identifying the class to create (likely a hash of the class name)
static const uint32_t kClassHash = 0x4ecfbe13;

// Static function that creates a singleton or instance of a specific class.
// The function is called from various places (e.g., 0x00856400) to ensure a single instance.
void* createObjectByHash(void)
{
    // Attempt to initialize or reference an existing object with the given hash.
    // The first argument (in_EAX) is likely a this pointer or context; here it's passed as the first parameter.
    // In the original assembly, this might be a __thiscall with an implicit this pointer.
    // For reconstruction, we treat it as a static function that receives a context pointer.
    // Since the decompiler shows in_EAX as undefined, we assume it's a global context or null.
    void* context = nullptr; // Placeholder for the implicit this pointer (if any)
    FUN_0043aff0(context, kClassHash);

    // Allocate memory for the object (28 bytes = 0x1c)
    void* newObject = FUN_0043af00(0x1c);
    if (newObject == nullptr)
        return nullptr;

    // Check if the object creation should proceed (e.g., not already created)
    bool canCreate = FUN_0043b120();
    if (canCreate)
    {
        // Cleanup or error path: free the allocated memory? (FUN_0043b210 might deallocate)
        FUN_0043b210();
        return nullptr;
    }

    // Finalize the object (e.g., call constructor, register in manager)
    void* result = FUN_0043abc0();
    return result;
}