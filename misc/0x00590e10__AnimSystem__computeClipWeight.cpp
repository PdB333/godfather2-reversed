// FUNC_NAME: AnimSystem::computeClipWeight
float AnimSystem::computeClipWeight(AnimClipData* pClipData, int* pWeightArray)
// Reconstructed function at 0x00590e10. Computes a per-frame blend weight for an animation clip,
// using a speed scale from the owning object and a weighted index from a keyframe array.
{
    float* pfFloatArray;
    int* piIndexData;
    uint uIndex;
    int dummy;

    // Check if the clip has any active frames (+0x01 is a count/flag)
    if (pClipData->activeCount < 1) {
        return 1.0f;
    }

    pfFloatArray = pClipData->pFloatArray;       // +0x04 : pointer to per-frame float data
    piIndexData  = pClipData->pIndexData;         // +0x0C : pointer to index structure

    updateRandom(); // FUN_00591160 – update random seed or internal state

    float weight = DAT_00e2b1a4;                  // global default weight constant

    // Blend speed from the owning object's speed scale (+0x104) with clip base speed
    if ((this->m_speedScale != 0.0f) && (*pfFloatArray != 0.0f)) {
        weight = this->m_speedScale / *pfFloatArray;
    }

    // Read the short at offset +0x02 of the index data – this is the current index into the weight array
    uIndex = (uint)(*(short*)((int)piIndexData + 2));

    // Guard against index out of bounds
    if ((uint)pWeightArray[1] <= uIndex) {
        dummy = 0;
        debugAssert(&dummy); // FUN_00591c00 – assert/break
    }

    // Apply the stored weight from the array (pWeightArray[0] is base address of float array)
    weight *= *(float*)(pWeightArray[0] + uIndex * 4);

    // Prevent zero weight – fall back to default
    if (weight == 0.0f) {
        weight = DAT_00e2b1a4;
    }

    return weight;
}