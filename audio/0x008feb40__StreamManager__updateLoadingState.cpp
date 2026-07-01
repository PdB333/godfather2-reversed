// FUNC_NAME: StreamManager::updateLoadingState
void __fastcall StreamManager::updateLoadingState(int this) // __fastcall with this in ECX
{
    char cVar1;
    int iVar2;

    // Check if bit 4 (0x10) at offset 0xd0 is not set – prevents re‑entry
    if (((*(byte*)(this + 0xd0) >> 4) & 1) == 0) {
        cVar1 = isStreamingComplete(); // FUN_008fe340
        if (cVar1 == '\0') {
            // Set bit 4 to mark streaming started
            *(ushort*)(this + 0xd0) |= 0x10; // +0xd0: flags

            // If a global data buffer is ready, copy 0x8000 bytes into internal buffer at +0x3c
            if (DAT_012069c4 != 0) {
                copyData(this + 0x3c, &DAT_012069c4, 0x8000); // FUN_00408900 (memcpy‑like)
            }

            // Increment a counter (e.g., packet/block counter)
            *(int*)(this + 0xd4) += 1; // +0xd4: counter
        }
    }

    // Compare desired state from external function with current state at +0xdc
    iVar2 = getDesiredStreamState(); // FUN_008fe480
    if (iVar2 != *(int*)(this + 0xdc)) {
        // State changed: apply the new state
        applyStreamStateChange(); // FUN_008fddc0
        setStreamState(iVar2);     // FUN_008fe5e0 (set new state)
    }
}