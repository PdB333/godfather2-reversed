// FUNC_NAME: ResolutionManager::updateResolutionData
void __fastcall ResolutionManager::updateResolutionData(int this)
{
    short* resolutionEntry1;
    short* resolutionEntry2;
    
    // Check if resolution index is valid (max 4096 entries)
    if (*(uint*)(this + 0x16c) < 0x1000) {
        // Each resolution entry is 0x38 bytes (56 bytes)
        resolutionEntry1 = (short*)(&DAT_011a0f28 + *(uint*)(this + 0x16c) * 0x38);
    } else {
        resolutionEntry1 = (short*)0x0;
    }
    
    // Store width from entry offset +2
    DAT_01218e40 = *(resolutionEntry1 + 1); // +2 bytes = width
    
    if (*(uint*)(this + 0x16c) < 0x1000) {
        resolutionEntry2 = (short*)(&DAT_011a0f28 + *(uint*)(this + 0x16c) * 0x38);
    } else {
        resolutionEntry2 = (short*)0x0;
    }
    
    // Store height from entry offset +4
    DAT_01218e42 = *(resolutionEntry2 + 2); // +4 bytes = height
    
    // Calculate aspect ratios using base resolution (DAT_00e2b1a4 likely diagonal or reference)
    DAT_01218e44 = DAT_00e2b1a4 / (float)(int)*(resolutionEntry1 + 1); // width aspect
    DAT_01218e48 = DAT_00e2b1a4 / (float)(int)*(resolutionEntry2 + 2); // height aspect
    
    return;
}