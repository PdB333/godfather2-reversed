// FUNC_NAME: NetPacketBuilder::calculatePacketSize
int __thiscall NetPacketBuilder::calculatePacketSize(int this, int packet, int additionalParam)
{
    int originalPacketPtr = packet; // Save original packet pointer for final size calculation
    int currentOffset = FUN_008bfa20(packet, &packet); // Get base header size and update packet pointer/offset
    int packet2 = packet; // After call, packet may have been updated (e.g. to offset after header)
    // Add size of variable-length data: each of two fields (at +0x24 and +0x28) contributes an int per element?
    currentOffset = currentOffset + originalPacketPtr + (*(int *)(packet2 + 0x28) + *(int *)(packet2 + 0x24)) * 4;
    // Add size of transform data (from field at +0x2c)
    int transformSize = FUN_008c1a30(currentOffset, *(int *)(packet2 + 0x2c));
    currentOffset += transformSize;
    // Add size of state data (from fields at +0x30 and +0x34)
    int stateSize = FUN_008c1b20(currentOffset, *(int *)(packet2 + 0x30), *(int *)(packet2 + 0x34));
    currentOffset += stateSize;
    // Add size of event data (from fields at +0x38 and +0x3c)
    int eventSize = FUN_008c5500(currentOffset, *(int *)(packet2 + 0x38), *(int *)(packet2 + 0x3c));
    currentOffset += eventSize;
    // Conditional custom data if object type matches a specific ID
    if (*(int *)(this + 0x54) == 0x637b907) {
        int customSize = 0;
        if (*(int *)(this + 0x230) != 0) {
            customSize = FUN_00892850(currentOffset, additionalParam);
        }
        currentOffset += customSize;
    }
    return currentOffset - originalPacketPtr; // Returns total packet size (excluding original offset)
}