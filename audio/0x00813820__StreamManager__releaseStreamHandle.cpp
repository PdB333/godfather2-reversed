// FUNC_NAME: StreamManager::releaseStreamHandle
void __fastcall StreamManager::releaseStreamHandle(int thisPtr)
{
    // Check if stream handle at offset +0x74 is non-null
    if (*(int*)(thisPtr + 0x74) != 0) {
        // Call deallocation/command function with the handle, constant 0x16 (likely a release command or size), and a buffer at +0x3c
        FUN_004035f0(*(int*)(thisPtr + 0x74), 0x16, thisPtr + 0x3c);
        // Clear the handle to indicate release
        *(int*)(thisPtr + 0x74) = 0;
    }
}