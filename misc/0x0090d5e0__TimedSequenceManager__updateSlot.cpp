// FUNC_NAME: TimedSequenceManager::updateSlot
// Address: 0x0090d5e0
// Updates a timed sequence slot, advancing the frame index when accumulated time exceeds thresholds.
// Returns a status value with low byte = 1 if successful, high 24 bits = original ID high bits.
uint TimedSequenceManager::updateSlot(uint32_t identifier, int8_t* outFrameValue)
{
    uint32_t slotId = FUN_004dafd0(identifier); // Get sequence ID from identifier
    uint32_t currentTime = g_currentTime; // DAT_01205210
    uint32_t slotIndex = 0;

    // Find the matching slot index among 14 known IDs
    while (slotId != s_knownSequenceIDs[slotIndex]) {
        slotIndex++;
        if (slotIndex > 0xD) { // 14 slots (0 through 13)
            // No matching slot found; return status with low byte 0? Actually returns uVar2 & 0xffffff00
            return slotId & 0xFFFFFF00; // Low byte zero, upper bytes preserved
        }
    }

    int32_t slotOffset = slotIndex * 0x20; // Each slot is 0x20 bytes
    SequenceSlot* slot = (SequenceSlot*)((char*)g_sequenceSlotsBase + slotOffset); // Base 0x00e54a18

    uint32_t lastTimestamp = slot->lastTimestamp; // +0x0C
    if (lastTimestamp + 1000 < currentTime) {
        // More than 1 second since last update, reset index
        slot->currentIndex = 0; // +0x04
    } else {
        if (currentTime == lastTimestamp) {
            // Same timestamp, no time delta
            goto skipAccumulation;
        }
        // Accumulate delta time
        slot->accumulator += g_deltaTime; // +0x08, DAT_01206804
        uint32_t idx = slot->currentIndex;
        // Check if accumulator exceeds threshold for current frame
        if (slot->accumulator <= slot->thresholds[idx]) { // threshold array at +0x14, each 8 bytes
            goto skipAccumulation;
        }
        // Advance to next frame
        slot->currentIndex = (idx + 1) % slot->modulus; // modulus at +0x00
    }
    // Reset accumulator
    slot->accumulator = 0; // +0x08

skipAccumulation:
    slot->lastTimestamp = currentTime; // +0x0C
    // Output the frame value (byte) from the frame array at +0x10, each 8 bytes
    *outFrameValue = slot->frameValues[slot->currentIndex]; // +0x10
    // Return status: low byte = 1, upper 24 bits from slotId >> 8
    return (slotId >> 8) | 0x1;
}