// FUNC_NAME: tryPlaySoundByHash
void __fastcall tryPlaySoundByHash(void* thisPtr, void* esiParam) {
    int hashResult = 0;
    const int kSoundHash = 0xAE986323; // Likely a hash for a specific sound resource

    // Call virtual function at offset 0x10 on object at this+0x44
    // This function takes a hash and returns a pointer/handle via hashResult
    void* streamManager = *(void**)((int)thisPtr + 0x44); // +0x44
    int* vtableStream = *(int**)streamManager;
    typedef bool (__thiscall* StreamLookupFunc)(void*, int, int*);
    StreamLookupFunc lookupFunc = (StreamLookupFunc)(vtableStream[0x10 / 4]);
    bool found = lookupFunc(streamManager, kSoundHash, &hashResult);

    if (found && esiParam != nullptr) {
        // Call virtual function at offset 0x98 on object pointed by esiParam
        int* vtableSound = *(int**)esiParam;
        typedef void (__thiscall* SoundPlayFunc)(void*, int);
        SoundPlayFunc playFunc = (SoundPlayFunc)(vtableSound[0x98 / 4]);
        int soundData = FUN_005565f0(); // Returns additional data for playback
        playFunc((void*)((int)thisPtr + 0x48), soundData); // +0x48
    }
}