// FUNC_NAME: getObjectHash

void __fastcall getObjectHash(void* object, uint32_t* outHash)
{
    // FUN_004025a0 takes object (in EAX) and returns an internal structure pointer
    void* internalStruct = (void*)FUN_004025a0((int)object);
    if (internalStruct != nullptr) {
        // Offset +0x2c: hash value in the internal structure
        *outHash = *(uint32_t*)((int)internalStruct + 0x2c);
        return;
    }
    // Default hash constant (0xFE16702F) when no valid structure found
    *outHash = 0xfe16702f;
}