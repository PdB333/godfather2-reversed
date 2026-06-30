// FUNC_NAME: NetSession::finalizeDisconnect
undefined4 __thiscall NetSession::finalizeDisconnect(void) {
    // Check if currently connected (flag at +0x1744)
    if (*(char *)(this + 0x1744) != '\0') {
        // Build a disconnect message structure (type=1, args=0)
        struct {
            int type;   // +0x00
            int arg1;   // +0x04
            int arg2;   // +0x08
            char arg3;  // +0x0C
        } msg = {1, 0, 0, 0};

        // Send the disconnect command
        FUN_005e2440(&msg); // likely sendDisconnectMessage

        // Yield for several frames to allow network processing
        for (int i = 0; i < 5; i++) {
            FUN_005e8610(); // processNetworkTick / pump messages
        }

        // Clean up network resources
        *(int *)(this + 0x173c) = 0;                     // clear connection state / counter
        FUN_009c8f10(*(void **)(this + 0x1738));         // release resource at +0x1738
        *(void **)(this + 0x1738) = 0;                   // null out pointer
        *(int *)(this + 0x1740) = 0;                     // clear another pointer
        *(char *)(this + 0x1744) = 0;                    // mark as disconnected
    }
    return 1;
}