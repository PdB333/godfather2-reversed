// FUN_005786c0: NetReplicator::processReplicationUpdate
int __thiscall NetReplicator::processReplicationUpdate(int targetNetId) {
    // +0x18: local netId (identifier for this replicator)
    // +0x2f0: pendingUpdate flag (cleared on invalid tick)

    char isActive = FUN_00579690(this, in_EAX); // probably checks if object is active
    if (isActive != '\0') {
        return 1;
    }

    FUN_00587d00(this, this); // deserialize or apply base update

    bool bIsMatching = *(int *)(this + 0x18) == targetNetId; // check if target matches local id
    int currentTick = FUN_00587da0(); // global game tick or frame counter

    volatile char localFlag = bIsMatching; // compiler artifact (unused)

    if (currentTick >= 0) {
        // valid tick: use global buffer for update
        undefined4 buffer = FUN_00579870(); // get active replication buffer
        int unusedLocal = targetNetId;      // alignment padding
        undefined4 result = FUN_00579450(this, buffer);
        return result;
    } else {
        // invalid tick: use dummy local buffer and reset pending flag
        FUN_00579870(); // side effect (e.g., increment reference)
        int unusedLocal = targetNetId;
        undefined1 localBuffer[12];
        undefined4 result = FUN_00579450(this, localBuffer);
        *(int *)(this + 0x2f0) = 0; // clear pending update flag
        return result;
    }
}