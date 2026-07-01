// FUNC_NAME: ScriptedSequencePlayer::playSequence
void __thiscall ScriptedSequencePlayer::playSequence(int thisPtr, undefined4 contextData, char autoStart)
{
    // Set bit 0 at offset 0x894 - maybe indicates sequence is active or has been started
    *(uint *)(thisPtr + 0x894) |= 1;

    // Initialize a hash context (local_c is likely a hash state, local_8 a constant)
    // This pattern is common for EA's EARS hash functions
    struct {
        uint32_t hashState; // +0x00
        uint32_t hashConstant; // +0x04
    } hashContext;
    hashContext.hashState = 0;
    hashContext.hashConstant = 0xd42a2c49; // Standard EA hash seed

    // Begin hash computation (resets internal state)
    FUN_00774ff0(); // likely hashBegin or similar

    // Look up the "scriptedSequenceTable" hash table using the context
    uint32_t tableResult = thunk_FUN_004dafd0("scriptedSequenceTable", &hashContext);

    // Perform a hash lookup with a specific sequence ID (0xe8b1c0e8)
    int sequenceInstance = FUN_006215a0(0xe8b1c0e8, tableResult, &hashContext);

    // Set some context data (maybe associates the sequence with a game object or player)
    FUN_00774e60(contextData);

    // If there was an old sequence instance at +0x8a0, signal it to stop (virtual call at vtable+4)
    if (*(int **)(thisPtr + 0x8a0) != (int *)0x0) {
        (**(code **)(**(int **)(thisPtr + 0x8a0) + 4))(1); // call Stop(1) or similar
    }

    // Store the new sequence instance at +0x8a0
    *(int *)(thisPtr + 0x8a0) = sequenceInstance;

    // If autoStart is true, set the "auto start" flag (bit 0) at offset 0x64 of the sequence instance
    if (autoStart != '\0') {
        *(uint *)(sequenceInstance + 0x64) |= 1;
    }
}