// FUNC_NAME: EffectManager::updateEffectSlots
void __fastcall EffectManager::updateEffectSlots() {
    int count = 8;
    int* inputArray = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x128); // +0x128: array of 8 input pointers/IDs
    char buffer[76] = {}; // stack buffer for name or data

    for (int i = 0; i < count; i++) {
        int* inputSlot = &inputArray[i];
        int inputValue = *inputSlot;
        if (inputValue == 0) {
            int* outputArray = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x148); // +0x148: array of 8 output objects
            outputArray[i] = 0;
        } else {
            int systemContext = getSystemContext(); // FUN_005466a0() – global system singleton
            copyTransformData(systemContext + 0xe0, inputValue + 0xe0); // FUN_00aa1cf0 – copy 0xe0-sized data (likely transform or state)

            TlsGetValue(globalTLSDAT); // thread-local storage fetch (result unused)

            int newObject = poolAlloc(0x160, 0x31); // FUN_00aa2680 – allocate 352-byte block with tag 0x31
            *reinterpret_cast<short*>(newObject + 4) = 0x160; // set size field at offset +4

            int objectID = *reinterpret_cast<int*>(inputValue + 0x10); // +0x10: object identifier
            int nameHandle = makeEffectName(9, 0x1f, 0); // FUN_00540c60 – create string/hash
            int createdObject = createEffectObject(objectID, buffer, nameHandle); // FUN_009f7230 – builds new effect object

            int* outputArray = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x148); // +0x148: output array
            outputArray[i] = createdObject;

            int renderTarget = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xf8); // +0xf8: some render target/context
            updateGlobalState(); // FUN_0043b490 – global update
            sendNotification(0x2001, renderTarget, 0); // FUN_009f01f0 – send event with code 0x2001
        }
    }
}