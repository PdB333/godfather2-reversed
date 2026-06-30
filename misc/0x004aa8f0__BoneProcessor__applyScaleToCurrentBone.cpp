// FUNC_NAME: BoneProcessor::applyScaleToCurrentBone
void BoneProcessor::applyScaleToCurrentBone() {
    // Get per-thread data (FS segment +0x2c -> some TLS struct)
    int* tlsBase = *(int**)(__readfsdword(0x2c) + 0x2c); // TLS pointer
    int currentIndex = *(int*)(tlsBase + 8); // +0x08: current bone/vertex index

    // Get pointer to animation buffer from this->+0x18 (likely an array or struct)
    float* animBuffer = *(float**)(this + 0x18); // this+0x18: pointer to base of data

    // Element base (each element is float4 aligned)
    float* element = (float*)((int)animBuffer + currentIndex);

    // Read scalar weight from element+0x90 (offset 0x90)
    float weight = *(float*)((int)element + 0x90);

    // Read source 4-vector from element+0x50
    float* srcVec = (float*)((int)element + 0x50);
    float v0 = srcVec[0];
    float v1 = srcVec[1];
    float v2 = srcVec[2];
    float v3 = srcVec[3];

    // Write scaled vector to element+0x40
    *(float*)((int)element + 0x40) = weight * v0;
    *(float*)((int)element + 0x44) = weight * v1;
    *(float*)((int)element + 0x48) = weight * v2;
    *(float*)((int)element + 0x4c) = weight * v3;

    // Set flag at TLS-based array location: tlsBase[0x10] + originalAnimBuffer? 
    // Actually: *(int*)(tlsBase + 8) + 0x4c + *(int*)(this+0x18) -> 
    // tlsBase[2] is already currentIndex, but they re-read tlsBase[2] instead of using currentIndex? 
    // Reusing the value from tlsBase+8 (currentIndex) and adding animBuffer base
    int flagArray = *(int*)(tlsBase + 8); // same as currentIndex
    *(int*)(flagArray + 0x4c + *(int*)(this + 0x18)) = s_flagConstant; // DAT_00e2b1a4 (likely 1 or true)

    // Call subsequent processing function
    processNextStep(); // FUN_004aab40
}