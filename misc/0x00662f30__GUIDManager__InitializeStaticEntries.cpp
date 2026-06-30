// FUNC_NAME: GUIDManager::InitializeStaticEntries

#include <cstdlib>
#include <cstdint>

// Known helper functions (addresses guessed from context)
extern "C" {
    // Create two 16-byte UUIDs: returns 0 on success
    int CreateUUIDPair(void* uuid1, void* uuid2, int param);

    // Destroy/free a UUID pair
    void DestroyUUID(void* uuid1, void* uuid2, int param);

    // Allocate a 0x20-byte object
    void* AllocateObject();

    // Register a GUID string (size usually 64)
    int RegisterGUID(const char* guidString, int size);

    // Some check operation (returns 0 on success)
    int PerformCheck();

    // Operates on local UUIDs, returns 0 on success
    int GenerateUUIDFromLocal(void* uuidIn, int mode, void* uuidOut);

    // Higher-level operation using UUIDs and allocated objects
    int DoComplexOperation(void* uuid1, void* obj1, void* obj2, void* uuid2);

    // Wait for asynchronous completion (returns 0 on success)
    int WaitForCompletion();
}

// Structure representing one entry in the static GUID table (28 bytes)
struct GUIDEntry {
    int activeFlag;          // +0x00
    int unknown1;            // +0x04
    const char* guidStr1;    // +0x08
    int unknown2;            // +0x0C
    const char* guidStr2;    // +0x10
    const char* guidStr3;    // +0x14
    const char* guidStr4;    // +0x18
};

// Externally defined table (likely in data section)
extern const GUIDEntry g_guidTable[];

// Global flag that must be set before this function is called (or set by some inline code)
extern int g_initializationFlag;  // corresponds to local_2c

// FUNCTION: 0x00662f30
// Purpose: Initialize the static GUID table by registering each entry and performing
//          associated set-up operations. Returns 0 on success, 0xd on failure, 5 on retry.
int GUIDManager::InitializeStaticEntries()
{
    int result;
    void* allocatedObject1;       // _Memory (0x20 bytes)
    void* allocatedObject2;       // _Memory_00 (allocated via AllocateObject)
    uint8_t localUuid1[16];       // local_20
    uint8_t localUuid2[16];       // local_10
    int entryIndex;               // local_24

    // Generate initial UUID pair
    if (CreateUUIDPair(localUuid1, localUuid2, 0) != 0) {
        return 0xd;  // error UUID generation
    }

    // Allocate first 0x20-byte object
    allocatedObject1 = malloc(0x20);
    if (allocatedObject1 == nullptr) {
        DestroyUUID(localUuid1, localUuid2, 0);
        return 0xd;
    }

    // Attempt to create UUID pair for this object
    if (CreateUUIDPair(allocatedObject1, (uint8_t*)allocatedObject1 + 0x10, 0) != 0) {
        free(allocatedObject1);
        DestroyUUID(localUuid1, localUuid2, 0);
        return 0xd;
    }

    // Allocate second object
    allocatedObject2 = AllocateObject();
    if (allocatedObject2 == nullptr) {
        DestroyUUID(localUuid1, localUuid2, 0);
        DestroyUUID(allocatedObject1, (uint8_t*)allocatedObject1 + 0x10, 0);
        free(allocatedObject1);
        return 0xd;
    }

    // Iterate over GUID table entries until a null active flag
    entryIndex = 0;
    while (g_guidTable[entryIndex].activeFlag != 0) {
        int currentEntryOffset = entryIndex * sizeof(GUIDEntry);  // step 0x1c

        // Register first GUID string
        if (RegisterGUID(g_guidTable[entryIndex].guidStr1, 0x40) != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Register second GUID string
        if (RegisterGUID(g_guidTable[entryIndex].guidStr2, 0x40) != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Perform check #1
        if (PerformCheck() != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Check global initialization flag (must be non-zero to continue)
        if (g_initializationFlag == 0) {
            result = 5;
            goto cleanup;
        }

        // Perform check #2
        if (PerformCheck() != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Check initialization flag again
        if (g_initializationFlag == 0) {
            result = 5;
            goto cleanup;
        }

        // Register third GUID string
        if (RegisterGUID(g_guidTable[entryIndex].guidStr3, 0x40) != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Register fourth GUID string
        if (RegisterGUID(g_guidTable[entryIndex].guidStr4, 0x40) != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Generate a new UUID from the local UUID1, mode 1
        if (GenerateUUIDFromLocal(localUuid1, 1, localUuid1) != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Perform complex operation with UUIDs and allocated objects
        if (DoComplexOperation(localUuid1, allocatedObject1, allocatedObject2, localUuid2) != 0) {
            result = 0xd;
            goto cleanup;
        }

        // Wait for first operation to complete
        if (WaitForCompletion() != 0) {
            result = 5;
            goto cleanup;
        }

        // Wait for second operation
        if (WaitForCompletion() != 0) {
            result = 5;
            goto cleanup;
        }

        entryIndex++;
    }

    // Success
    result = 0;

cleanup:
    DestroyUUID(allocatedObject2, (uint8_t*)allocatedObject2 + 0x10, 0);
    free(allocatedObject2);
    DestroyUUID(allocatedObject1, (uint8_t*)allocatedObject1 + 0x10, 0);
    free(allocatedObject1);
    DestroyUUID(localUuid1, localUuid2, 0);
    return result;
}