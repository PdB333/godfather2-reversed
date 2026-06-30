// FUNC_NAME: StreamManager::releaseAllSlots
void __thiscall StreamManager::releaseAllSlots() {
    // Timer slots: 5 slots at offset 0x10, each 20 bytes (5 ints)
    int* pTimerSlot = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18); // points to slot.m_callback
    int timerIndex = 5;
    do {
        int currentIndex = timerIndex;
        // Check if slot is active (bit31 not set)
        if ((pTimerSlot[-2] & 0x80000000) != 0x80000000) {
            if (pTimerSlot[1] != 0) {
                typedef void (*TimerCallback)(int reason, void* arg);
                reinterpret_cast<TimerCallback>(pTimerSlot[1])(3, reinterpret_cast<void*>(pTimerSlot[2])); // reason=3 (release)
            }
            // Reset slot to free state (bit31 set)
            pTimerSlot[-2] = 0x80000000;
            pTimerSlot[-1] = 0;
            pTimerSlot[0] = 0;
            pTimerSlot[1] = 0;
            pTimerSlot[2] = 0;
            // Decrement active timer count at offset 0x74
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x74) -= 1;
        }
        pTimerSlot += 5; // next slot (20 bytes)
        timerIndex = currentIndex - 1;
    } while (timerIndex != 0);

    // Connection/stream slots: 2 slots at offset 0x1a8, each 56 bytes (0xe ints)
    int* pConnSlot = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1a8); // start of slot array
    int connIndex = 2; // after first loop, iVar3 was set to 2
    do {
        if ((pConnSlot[0] != -1) && (*reinterpret_cast<int*>(static_cast<char*>(g_pStreamManager) + 0x208) == pConnSlot[0])) {
            *reinterpret_cast<int*>(static_cast<char*>(g_pStreamManager) + 0x208) = -1;
            patchFunction(&LAB_006fd640); // FUN_005e6640 - likely a patch/replace call
        }
        // Check if associated data at offset 0x198 is valid
        int* dataPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x198);
        if (dataPtr[0] != 0) {
            // Callback: function at offset 0x180, args: dataPtr, 4 (reason?), arg2 at offset 0x17c
            if (*reinterpret_cast<int(*)(void*, int, void*)>(this + 0x180)) {
                (*reinterpret_cast<int(*)(void*, int, void*)>(this + 0x180))(
                    dataPtr[0],
                    4,
                    *reinterpret_cast<void**>(this + 0x17c));
            }
            // Release the data block
            void* result = allocateMemory(); // FUN_005e3260
            deallocateMemory(dataPtr[0], result); // FUN_005e2ad0
            // Check slot flags: byte at slot+4 (pConnSlot[1] low byte)
            if ((reinterpret_cast<unsigned char*>(pConnSlot + 1)[0] & 0x08) != 0) {
                handleStreamEvent(); // FUN_006fd240
            }
            callNotifyRelease(); // FUN_006fd030
        }
        pConnSlot += 14; // next slot (56 bytes)
        connIndex--;
    } while (connIndex != 0);
}