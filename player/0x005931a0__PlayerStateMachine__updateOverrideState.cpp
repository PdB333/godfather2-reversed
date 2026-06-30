// FUNC_NAME: PlayerStateMachine::updateOverrideState
// Address: 0x005931a0
// This function determines if an override flag should be set to 2 or 0
// based on a bitmask test of an index derived from a data structure.
// The index comes from either offset 0x10 or 0x24 depending on the
// low byte of data->type (< 10 selects 0x10, else 0x24).

void PlayerStateMachine::updateOverrideState()
{
    // Get state data from manager (FUN_0056fdd0)
    StateData* stateData = GetStateData();
    if (stateData == nullptr)
        return;

    // Override source pointer at this+0x08
    if (this->pOverrideSource != nullptr)
    {
        // Data pointer at this+0x04
        DataStruct* data = this->pData;

        // Low byte of uint at data+0x04 determines which index to use
        uint typeByte = data->type & 0xFF;

        int index;
        if (typeByte < 10)
            index = data->indexLow;   // +0x10
        else
            index = data->indexHigh;  // +0x24

        // Only proceed if index is non-negative
        if (index >= 0)
        {
            // Override source structure: field at +0x04 points to a bitmask array
            uint* bitmaskArray = this->pOverrideSource->bitmaskArray; // double indirection: pOverrideSource+4 -> uint*

            int wordIndex = index >> 5;
            int bitIndex  = index & 0x1F;

            // Test the bit in the array
            if (bitmaskArray[wordIndex] & (1 << bitIndex))
            {
                // Set override flag to 2
                stateData->overrideFlag = 2;
                return;
            }
        }
    }

    // Default: clear override flag
    stateData->overrideFlag = 0;
}