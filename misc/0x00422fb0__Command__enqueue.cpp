// FUNC_NAME: Command::enqueue
void __thiscall Command::enqueue(int arg0, int arg1) {
    // +0x140: flags (set to 1 = queued)
    // +0x14c: first argument (e.g., target/message type)
    // +0x150: second argument (e.g., data)
    *(int*)((int)this + 0x14c) = arg0;
    *(int*)((int)this + 0x140) = 1;
    *(int*)((int)this + 0x150) = arg1;

    // Possibly process immediately if already allowed
    FUN_00423900();

    // Check if command queuing is enabled (via TLS flag at offset 0x34 from TLS slot base)
    // FS:[0x2c] → pointer to TLS slot table → dereference to get slot data → offset 0x34 = flag
    int tlsFlag = *(int*)(*(int**)(*(uint8_t*)__readfsdword(0x2c) + 0x34));
    if (tlsFlag == 0) {
        // Push command onto a global command queue (static buffer at DAT_01206880 + 0x14)
        int** currentWritePtr = (int**)(DAT_01206880 + 0x14);
        *currentWritePtr = (int*)&PTR_LAB_0110b6b8;  // store type vtable/identifier
        *currentWritePtr += 4;                       // advance pointer (size of one int)
        // Write this object and its arguments (12 bytes total)
        *(*currentWritePtr) = (int)this;
        *(*currentWritePtr + 4) = arg0;
        *(*currentWritePtr + 8) = arg1;
        *currentWritePtr += 12;                      // advance by 3 ints
    }
    return;
}