// FUNC_NAME: NetworkConnection::processIncomingData
void __thiscall NetworkConnection::processIncomingData(int param_1) {
    uint local_30[3];
    undefined local_20[28]; // unknown usage

    // Copy 12 bytes from source pointed to by EAX into local buffer
    local_30[0] = *(uint *)(*(int *)in_EAX);
    local_30[1] = *(uint *)(*(int *)in_EAX + 4);
    local_30[2] = *(uint *)(*(int *)in_EAX + 8);

    // Store a global value (likely session or context identifier)
    local_30[3] = DAT_00e2b1a4;

    // Call handler with the constructed data and parameter
    FUN_00aa36a0(&local_30, param_1);

    // Check a state variable: this->someStruct[0x18] + 0xd8 == 7
    if (*(char *)(*(int *)(unaff_ESI + 0x18) + 0xd8) == 7) {
        FUN_009f4240(1, 1, 0);  // Possibly log or display something
    }

    // Finalization step (likely clears or releases resources)
    FUN_009f4c70(local_20);

    return;
}