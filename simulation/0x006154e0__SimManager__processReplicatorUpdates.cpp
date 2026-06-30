// FUNC_NAME: SimManager::processReplicatorUpdates
// Function address: 0x006154e0
// Processes ghosts/replicators for a given connection or object ID.
// Known context: EARS engine replication layer.
// Uses global table at 0x011a0f28 with stride 0x38 (56 bytes per entry).
// Typical entries: state at +0 (0x02 = ghost?, 0x03 = ?), count at +0x01 (number of children/replicators).

int SimManager::processReplicatorUpdates(uint connectionId) {
    // Bounds check on connection ID (max 0x1000 entries)
    char *entry;
    if (connectionId < 0x1000) {
        entry = (char *)(0x011a0f28 + connectionId * 0x38);
    } else {
        entry = nullptr;
    }

    // Validate entry state: must be 0x02 or 0x03 (likely GhostState_Active or GhostState_Updating)
    if (entry == nullptr || (*entry != 0x02 && *entry != 0x03)) {
        return 0;
    }

    // Process each child replicator (count stored at offset +1)
    int numChildren = (int)(uint)(byte)entry[1];
    if (numChildren == 0) {
        return 1;
    }

    for (int i = 0; i < numChildren; ++i) {
        __declspec(align(4)) char buffer[32]; // local_50, size 0x20

        // Retrieve replicator data: connectionId, field/event type=6, child index, output buffer
        int result = getReplicatorData(connectionId, 6, i, buffer);
        if (result == 0) {
            return 0;
        }

        // Process the data (likely unpacks to three fields: local_c, local_10, local_30)
        processReplicatorData(buffer[0], *(uint*)(buffer+4), *(uint*)(buffer+8)); // dummy interpretation

        // Clear or finalize the buffer
        clearReplicatorBuffer(buffer);
    }
    return 1;
}