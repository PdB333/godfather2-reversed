// FUNC_NAME: Entity::applyCommand
void __thiscall Entity::applyCommand(Entity* thisPtr, int commandData, int param3, int param4)
{
    int tlsPtr;
    int dataPtr;
    char globalFlag;

    globalFlag = FUN_004166b0(); // probably IsGamePaused() or similar
    if ((globalFlag != '\0') && ((DAT_011f7430 & 1) != 0)) {
        FUN_00614a50(); // some sound? or debug output?
    }

    // Access TLS (Thread Local Storage) - likely getting current frame or object list
    tlsPtr = **(int **)(__readfsdword(0x2c) + 0x2c); // +0x2c is typical TEB offset for thread data

    FUN_00490d70(); // some update

    dataPtr = *(int *)(thisPtr + 4); // +0x4: pointer to internal data block

    // Write to fields in data block using offsets from commandData and TLS
    *(int *)(dataPtr + 0x1b4) = *(int *)(*(int *)(commandData + 0x18) + 0x70 + *(int *)(tlsPtr + 8));
    *(int *)(dataPtr + 0xf0) = *(int *)(*(int *)(commandData + 0x18) + 0x78 + *(int *)(tlsPtr + 8));

    FUN_00418540(commandData, param3, param4); // probably finalize command processing
    return;
}