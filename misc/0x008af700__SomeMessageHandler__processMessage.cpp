// FUNC_NAME: SomeMessageHandler::processMessage
void __thiscall SomeMessageHandler::processMessage(void* thisPtr, int* message) {
    // Initialize/parse the message header?  (FUN_0046c6a0)
    ParMessageHeader(message);
    int msgId = *message; // First int is message type

    // Dispatch based on message ID
    if (msgId == MSG_PLAY_SOUND) {
        // Check if we can play (maybe network state or animation flag)
        char canPlay = CouldPlaySound(); // FUN_00481620
        if (canPlay != 0 || *(int*)((char*)thisPtr + 0x9c) == 4) {
            // Call virtual at vtable offset 0xe8 (relative to base vtable at this-0x3c)
            (**(code**)(**(int**)((char*)thisPtr - 0x3c) + 0xe8))();
            return;
        }
    }
    else if (msgId == MSG_SET_TARGET) {
        if (message[1] != 0) {
            // Call virtual at vtable offset 0xe0 with parameter
            (**(code**)(**(int**)((char*)thisPtr - 0x3c) + 0xe0))(message[1]);
            return;
        }
    }
    else if (msgId == MSG_STOP_ANIMATION) {
        // Clear some state?  (FUN_004035f0 is likely SetTimer or Delay)
        SetKillTimer(*(int*)((char*)thisPtr + 0x10c), 2, -(uint)(thisPtr != (void*)0x3c) & (uint)thisPtr);
        char isAnimStopped = IsAnimationStopped(); // FUN_008ae1d0
        if (isAnimStopped != 0) {
            // Call virtual at vtable offset 0xb0
            (**(code**)(**(int**)((char*)thisPtr - 0x3c) + 0xb0))();
            return;
        }
    }
    else {
        // Remaining message IDs
        if ((msgId != MSG_START_EVENT) && (msgId != MSG_END_EVENT)) {
            if (msgId == MSG_CLEAR_KILL_TIMER) {
                int timerHandle = *(int*)((char*)thisPtr + 0x10c);
                // Reset timer
                SetKillTimer(timerHandle, 0x1ff, -(uint)(thisPtr != (void*)0x3c) & (uint)thisPtr);
                *(int*)((char*)thisPtr + 0x10c) = 0;
                return;
            }
            else if (msgId == MSG_KILL_TIMER) {
                int timerHandle = *(int*)((char*)thisPtr + 0x10c);
                // Same as above
                SetKillTimer(timerHandle, 0x1ff, -(uint)(thisPtr != (void*)0x3c) & (uint)thisPtr);
                *(int*)((char*)thisPtr + 0x10c) = 0;
                return;
            }
            else if (msgId == MSG_NETWORK_SYNC) {
                char isServer = IsServerSide(); // FUN_00481640
                if (isServer == 0) {
                    return;
                }
                // Call virtual at vtable offset 0x34 from pointer at this+0x14
                (**(code**)(**(int**)((char*)thisPtr + 0x14) + 0x34))();
                return;
            }
            // Unknown message, ignore
            return;
        }
        // msgId is MSG_START_EVENT or MSG_END_EVENT
        if (*(void**)message[1] != (void*)0x0) {
            // Call virtual at vtable offset 0xec with extra flag
            int flag = (msgId == MSG_START_EVENT) ? 1 : 0;
            (**(code**)(**(int**)((char*)thisPtr - 0x3c) + 0xec))(*(int*)message[1], flag);
        }
    }
}