// FUNC_NAME: StateManager::processState
void StateManager::processState(int param_1) {
    // Get thread-local context flag from FS segment
    // FS:[0x2c] -> some structure, offset 0x34 gives a slot selection flag
    int slotFlag = *(int*)(**(int**)((char*)__readfsdword(0x2c) + 0x34));
    
    // Select the appropriate state block based on slotFlag
    // this + 4 is start of an array of two StateStruct objects (size 0x98 each)
    StateStruct* state = reinterpret_cast<StateStruct*>(
        reinterpret_cast<char*>(this) + 4 + (slotFlag != 0 ? 0x98 : 0)
    );
    
    // Save previous counter and possibly other state
    state->prevCounter = state->counter; // +0x04 = *(state->counter) at offset 0
    if (state->counter > 0) {
        // Copy 8-byte 'delta' values from offsets 0x08 and 0x10 to offsets 0x88 and 0x90
        *(uint64_t*)((char*)state + 0x88) = *(uint64_t*)((char*)state + 0x08);
        *(uint64_t*)((char*)state + 0x90) = *(uint64_t*)((char*)state + 0x10);
    }
    state->counter = 0; // reset
    
    // Select a debug/log buffer based on slotFlag
    int* logBufferBase = (slotFlag != 0) ? &DAT_012068e8 : &DAT_01206880;
    char* logPtr = *(char**)(logBufferBase + 0x14); // deref to get current write position
    
    // Write a function pointer and a boolean flag to the log buffer
    *(void**)logPtr = &PTR_LAB_01124c20; // some global function/address
    logPtr += 4;
    *(int*)logPtr = (slotFlag != 0) ? 1 : 0;
    logPtr += 4;
    
    // Update the buffer pointer in the log buffer base
    *(char**)(logBufferBase + 0x14) = logPtr;
    
    // Call the core update function with many parameters
    FUN_004ea560(this, param_1, 0, -1, 0, 0, 2);
}