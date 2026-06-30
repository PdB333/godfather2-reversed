// FUNC_NAME: SomeAudioManager::releaseStreamHandle
void __fastcall SomeAudioManager::releaseStreamHandle(int thisPtr)
{
    int* streamHandle = (int*)(thisPtr + 0xe8); // +0xe8: pointer to stream handle object

    if (*streamHandle != 0) {
        undefined4 uVar2 = 0;
        undefined4 uVar1 = getAudioResource(0, 0); // FUN_006fbc40: retrieve resource context
        releaseStream(*streamHandle, 0, uVar1, uVar2); // FUN_006f3eb0: stop/release stream
        finalizeAudioCleanup(); // FUN_006fbc70: global audio cleanup
        *streamHandle = 0;
    }
}