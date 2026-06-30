// FUNC_NAME: SecretKeyGenerator::generateSubKey
// Address: 0x0065e570
// Role: Generates a derived sub-key from a master key using a hash/expansion algorithm.
// Returns a shared buffer object containing the 32-byte sub-key.

void SecretKeyGenerator::generateSubKey(SharedBuffer** outBuffer, const SecretKeyGenerator* other)
{
    // +0x10: session id or key id
    // +0x14: initialized flag
    // +0x0c: master key (4 bytes, possibly handle or pointer)
    if (*(int*)((char*)other + 0x10) == *(int*)((char*)this + 0x10) && *(char*)((char*)this + 0x14) != '\0')
    {
        // Timer for key generation
        int localSizeBuf[3]; // +0x800 usage
        localSizeBuf[0] = 0x800; // 2048 bytes scratch buffer size

        longlong timerStart = getTimer(); // FUN_0065c340
        // Derive key: parameters are this->masterKey, other->masterKey, global constant, output size
        generateKeyData(*(undefined4*)((char*)this + 0xc), *(undefined4*)((char*)other + 0xc), &GLOBAL_01204978, localSizeBuf); // FUN_00663c10
        longlong timerEnd = getTimer(); // FUN_0065c340
        logElapsedTime(timerEnd - timerStart); // FUN_0065c4a0
        logMessage("Timer: %s Elapsed: %g ms", "secretSubKeyGen", (double)timerEnd - timerStart); // FUN_0065bc40

        // Hash context initialized from scratch buffer
        char hashContext[208]; // local_d0
        initHashContext(hashContext); // FUN_006595c0
        updateHashContext(hashContext, &GLOBAL_01204978); // FUN_00659640
        finalizeHashContext(hashContext); // FUN_00659730

        // Create a shared buffer for the sub-key
        char subKeyBuf[32]; // local_f0, holds the 32-byte sub-key output
        // The subKeyBuf is actually populated by the hash finalization, but decompiler shows it used directly.
        // Assume hashContext finalization writes to subKeyBuf.

        void* newBuffer = operatorNew(0x18); // FUN_009c8e50 allocate SharedBuffer object
        SharedBuffer* sharedBuf = nullptr;
        if (newBuffer != nullptr)
        {
            sharedBuf = (SharedBuffer*)newBuffer;
            sharedBuf->vtable = &VIRTUAL_TABLE_00e42d64;
            sharedBuf->refCountExternal = 0; // +0x04
            sharedBuf->refCount = 0;         // +0x08
            sharedBuf->data = subKeyBuf;     // +0x0c
            sharedBuf->size = 0x20;          // +0x10 (32 bytes)
            sharedBuf->owned = 0;            // +0x14
        }

        // If not owned, allocate and copy data
        if (sharedBuf != nullptr && !sharedBuf->owned)
        {
            void* allocatedData = (void*)malloc(0x20);
            memcpy(allocatedData, sharedBuf->data, sharedBuf->size);
            sharedBuf->data = allocatedData;
            sharedBuf->owned = 1;
        }

        // Increment reference count
        if (sharedBuf != nullptr)
            sharedBuf->refCount += 1;

        *outBuffer = sharedBuf;
        return;
    }

    *outBuffer = nullptr;
}