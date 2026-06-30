// FUNC_NAME: LayerManager::resetAllLayers

void __thiscall LayerManager::resetAllLayers(int this)
{
    int slotIdx;
    int *slotStatePtr; // Points to the state field (offset +0x08) of each 12-byte layer slot

    // Check if the global "layers active" bit (bit1 at +0x3d4) is set
    if ((*(uint *)(this + 0x3d4) >> 1 & 1) != 0)
    {
        // Iterate over 20 layer slots (array of 12-byte structs starting at this+0x2C)
        // Each slot: [0x00] flag (bit1 = active), [0x04] (unused?), [0x08] state (1 = playing)
        slotStatePtr = (int *)(this + 0x34); // Points to state field of first slot
        slotIdx = 20;
        do
        {
            // Check flag at slot+0x00 (slotStatePtr-2) and state at slot+0x08
            if ((((uint)*(slotStatePtr - 2) >> 1 & 1) != 0) && (*slotStatePtr == 1))
            {
                releaseLayer(); // Stop/cleanup the layer (calls 0x006abee0)
            }
            slotStatePtr += 3; // Advance 12 bytes (3 ints) to next slot's state field
            slotIdx--;
        } while (slotIdx != 0);

        // Reset layer count to 20
        *(int *)(this + 0x3d0) = 20;
        // Clear the "layers active" bit
        *(uint *)(this + 0x3d4) &= 0xfffffffd;
        // Reset other counters
        *(int *)(this + 0x3d8) = 0;
        *(int *)(this + 0x3e0) = 0;
    }
}