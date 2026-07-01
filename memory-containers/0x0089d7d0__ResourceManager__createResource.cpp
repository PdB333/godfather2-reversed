// FUNC_NAME: ResourceManager::createResource
// Address: 0x0089d7d0
// Creates a resource object from a 16-byte signature, with optional context and callback.
// Returns a pointer to the created resource via outResource.

#include <cstdint>

// Forward declarations for internal functions (not shown)
extern void* getGlobalData(); // FUN_00471610
extern void computeHash(void* out, void* in); // FUN_0044b4e0
extern int* createResourceInternal(int* outHandle, int* signature, void* hashData, uint32_t flags, int zero, void* context, int negativeOne, int zero2); // FUN_004df330
extern void* allocateMemory(size_t size, int alignment); // FUN_004eb390
extern void registerCallback(void* callbackObj); // FUN_004df830

// Vtable for callback wrapper (PTR_LAB_00d77d04)
struct CallbackWrapperVTable {
    void (*destructor)(void*); // offset +4
    // other virtual functions
};

struct CallbackWrapper {
    CallbackWrapperVTable* vtable; // +0x00
    int refCount;                  // +0x04
    int callbackData;              // +0x08
};

// Magic signature constants (from decompiled checks)
const int32_t MAGIC_SIG0 = -0x45245246; // 0xBABDB9BA
const int32_t MAGIC_SIG1 = -0x41104111; // 0xBEEFBEEF
const int32_t MAGIC_SIG2 = -0x153ea5ab; // 0xEAC15A55
const int32_t MAGIC_SIG3 = -0x6eeff6ef; // 0x91100911

int** ResourceManager::createResource(int** outResource, int* signature, void* context, int* callback) {
    // Initialize output to null
    *outResource = nullptr;

    // Check if signature is the magic sentinel or all zeros; if so, skip creation
    bool isMagic = (signature[0] == MAGIC_SIG0 && signature[1] == MAGIC_SIG1 &&
                    signature[2] == MAGIC_SIG2 && signature[3] == MAGIC_SIG3);
    bool isZero = (signature[0] == 0 && signature[1] == 0 && signature[2] == 0 && signature[3] == 0);
    if (isMagic || isZero) {
        return outResource;
    }

    // Get 64 bytes of global data (e.g., a hash seed or table)
    uint32_t* globalData = (uint32_t*)getGlobalData();
    uint32_t localHashInput[16]; // 64 bytes
    for (int i = 0; i < 16; i++) {
        localHashInput[i] = globalData[i];
    }

    // Compute hash into a 76-byte buffer (size from decompiled)
    uint8_t hashBuffer[76];
    computeHash(hashBuffer, localHashInput);

    // Determine flags: 0x1ff if no context, else call virtual function at offset 0x58 on context
    uint32_t flags;
    if (context == nullptr) {
        flags = 0x1ff;
    } else {
        // Assume context is an object with a vtable; call method at offset 0x58
        // This is likely a function that returns some flags or size
        flags = (*(uint32_t (**)(void*))(*(uint32_t*)context + 0x58))(context);
    }

    // Prepare signature copy for the internal creation call
    int localSignature[4];
    localSignature[0] = signature[0];
    localSignature[1] = signature[1];
    localSignature[2] = signature[2];
    localSignature[3] = signature[3];

    // Internal creation: returns a handle (int*) and also sets an output handle via stack variable
    int stackHandle = 0; // iStack_a4
    int* result = createResourceInternal(&stackHandle, localSignature, hashBuffer, flags, 0, context, -1, 0);

    // Clean up any previous output
    if (*outResource != nullptr) {
        *(uint32_t*)(*outResource + 8) = 0; // Clear some field
        *outResource = nullptr;
    }

    // Assign the created resource
    int* newResource = result;
    *outResource = newResource;
    if (newResource != nullptr) {
        // Set a back-pointer from the resource to the output pointer (for reference tracking)
        *(int**)(newResource + 8) = outResource;
        *result = 0; // Clear the internal handle? (piVar3 = result, then *piVar3 = 0)
    }

    // If stackHandle was set, clear its back-pointer
    if (stackHandle != 0) {
        *(uint32_t*)(stackHandle + 8) = 0;
    }

    // If a resource was created and a callback is provided, wrap it
    if (*outResource != nullptr && callback != nullptr) {
        // Allocate a callback wrapper (12 bytes)
        CallbackWrapper* wrapper = (CallbackWrapper*)allocateMemory(12, 16);
        if (wrapper != nullptr) {
            wrapper->vtable = (CallbackWrapperVTable*)&PTR_LAB_00d77d04; // Global vtable
            wrapper->refCount = 0; // Will be incremented
            wrapper->callbackData = *callback;
        }

        // Increment ref count and register the callback
        wrapper->refCount++;
        wrapper->callbackData = *callback;
        registerCallback(wrapper);

        // Decrement ref count; if zero, call destructor via vtable+4
        wrapper->refCount--;
        if (wrapper->refCount == 0) {
            wrapper->vtable->destructor(wrapper);
        }
    }

    return outResource;
}