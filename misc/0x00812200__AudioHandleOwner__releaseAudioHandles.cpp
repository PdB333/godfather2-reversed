// FUNC_NAME: AudioHandleOwner::releaseAudioHandles
void __thiscall AudioHandleOwner::releaseAudioHandles(AudioHandleOwner* this) {
    uint32_t* handlePtr;
    uint32_t handle;
    AudioHandleNode* node;
    AudioHashTable* hashTbl;
    int32_t count;

    AudioHashTable* g_audioHashTable = (AudioHashTable*)g_audioHashTableGlobal; // DAT_0122337c
    if (((uint8_t*)this)[0x50] & 1) // Already released?
        return;

    handlePtr = (uint32_t*)((uint8_t*)this + 0x58); // Array of 6 handles
    count = 6;
    do {
        handle = *handlePtr;
        if (handle != 0) {
            // Lookup handle in hash table owned by g_audioHashTable
            // Hash table: base pointer at +0x50, bucket count at +0x54
            uint32_t bucketIndex = handle % *(uint32_t*)((uint8_t*)g_audioHashTable + 0x54);
            AudioHandleNode** bucketArray = *(AudioHandleNode***)((uint8_t*)g_audioHashTable + 0x50);
            for (node = bucketArray[bucketIndex]; node != nullptr; node = node->next) {
                if (node->id == handle) {
                    if (node->resource != nullptr) {
                        releaseAudioResource(node->resource); // FUN_00404c40
                    }
                    break;
                }
            }
        }
        handlePtr++;
        count--;
    } while (count != 0);

    // Mark as released
    *(uint32_t*)((uint8_t*)this + 0x50) |= 1;
}