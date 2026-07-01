// FUNC_NAME: GameManager::handleCommand
void __thiscall GameManager::handleCommand(uint thisPtr, uint param2, uint param3)
{
    uint flags;
    byte bitFlag;

    // Initialize subsystems
    initSubSystem1();              // FUN_008f4160
    initSubSystem2();              // FUN_008f5190

    // Execute command with type 3, using the passed parameters
    executeCommand(3, param2, param3, 0);  // FUN_008f2200

    // Process some global state
    processGlobalState();          // FUN_00911b00

    // Set flag bit 0x800 at offset +0x10 (flags field)
    *(uint *)(thisPtr + 0x10) |= 0x800;

    // Extract bit from +0x1c (shift right 4) and store at +0x2270 (byte flag)
    flags = *(uint *)(thisPtr + 0x1c);
    bitFlag = (byte)(flags >> 4) & 1;
    *(byte *)(thisPtr + 0x2270) = bitFlag;

    // If the bit is clear, run additional cleanup
    if (bitFlag == 0) {
        cleanupAfterCommand();     // FUN_008f2460
    }

    // Get a resource from factory (type 1) and set it
    uint resourceHandle = createResource(1);  // FUN_008f1ff0
    setResource(resourceHandle, 1);           // FUN_008f5d30
}