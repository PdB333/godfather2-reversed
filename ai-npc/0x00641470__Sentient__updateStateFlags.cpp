// FUNC_NAME: Sentient::updateStateFlags
// Address: 0x00641470
// Role: Updates a state flag in a state table based on an ID. If state ID equals 12 (0xC), it sets bit 6 in the flags array at a given index; otherwise calls a fallback handler.

void Sentient::updateStateFlags(void)
{
    // Pointer to state table structure (offset +0x1C from this)
    uint **pStateTable = *(uint ***)(this + 0x1C);
    uint *pFlag;
    
    // Read state ID (likely from a register or call output)
    int stateId;
    int index;
    FUN_0063f4f0();  // Reads or computes stateId and index into local variables (stateId, index)
    
    if (stateId == 0xC) {
        // Access the flags array at offset +0x0C of the state table, indexed by 'index'
        pFlag = (uint *)(*(int *)(*pStateTable + 0xC) + index * 4);
        // Clear bits 7–15 and set bit 6 (0x40)
        *pFlag = (*pFlag & 0xFFFF807F) | 0x40;
        return;
    }
    // Fallback handling for other state IDs
    FUN_0063fd40();
}