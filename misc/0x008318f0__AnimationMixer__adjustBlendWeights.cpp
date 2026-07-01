// FUNC_NAME: AnimationMixer::adjustBlendWeights
void __thiscall AnimationMixer::adjustBlendWeights(int thisPtr, int* blendSourceList)
{
    float savedBaseWeight;
    int* pTotalWeight;
    float blendWeight;
    int* sourceNode;
    int sourceId;

    // For some global float that stores the base/animation weight
    pTotalWeight = (int*)DAT_0112dbac;  // pointer to a global weight storage (e.g., total blend weight)
    
    // First, call some initialization or data‑fetching functions
    FUN_008334a0();               // unknown – possibly reset internal time/weight
    savedBaseWeight = *(float*)DAT_00d5780c;   // capture current base weight

    FUN_00836540();               // unknown – possibly compute new base weight
    blendWeight = *(float*)DAT_00d5780c;       // new base weight after the call

    // Loop over a list of blend sources (param_2). Ghidra decompiled this as a single iteration,
    // but the actual code likely iterates over a linked list or array terminated by a null pointer.
    // We document the offsets used: sourceNode[0] points to a structure (vtable or data), sourceNode[1] is a float weight.
    for (sourceNode = blendSourceList; sourceNode != (int*)0x0; sourceNode = (int*)*sourceNode) // *sourceNode likely next pointer
    {
        sourceId = **(int**)(sourceNode[0] + 0xc);   // get ID from the source object at +0x0c
        if (sourceId == *(int*)(thisPtr + 0xc))       // compare with this object's ID at +0x0c
        {
            blendWeight -= *(float*)&sourceNode[1];    // subtract the source's weight from the blend weight
            FUN_00836550(sourceNode[0] + 0x30, *(float*)&sourceNode[1]);  // call source's weight application function at +0x30
        }
    }
    // Apply the remaining blend weight to this object's own weight function
    FUN_00836550(thisPtr + 0x30, blendWeight);

    // Store the original base weight back into the global total weight field
    *(float*)(pTotalWeight + 0x1c) = savedBaseWeight;
}