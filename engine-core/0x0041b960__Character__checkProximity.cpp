// FUNC_NAME: Character::checkProximity

bool Character::checkProximity( void* thisPointer )
{
    // Thread-local storage to get per-thread game context
    void* threadLocalContext = *(void**)(__readfsdword(0x2C));
    void* simulationContext = *(void**)(*(int**)threadLocalContext + 8);
    
    // Offset +0x18 from this: maybe an index into a bone/transform table
    int boneIndex = *(int*)((char*)thisPointer + 0x18);
    
    // Read two floats from the simulation context at offsets based on boneIndex
    float baseValue = *(float*)((char*)simulationContext + 0x70 + boneIndex);
    float scaledValue = *(float*)((char*)simulationContext + 0x6C + boneIndex) * DAT_00e2b04c;
    
    // Copy a 3-float vector (position/orientation) from the context
    float* vectorPtr = (float*)((char*)simulationContext + 0x30 + boneIndex);
    float localVector[3];
    localVector[0] = vectorPtr[0];
    localVector[1] = vectorPtr[1];
    localVector[2] = vectorPtr[2];
    
    // Clamp baseValue to be at least scaledValue
    if (baseValue <= scaledValue)
        baseValue = scaledValue;
    
    // Overwrite the first component of the local vector with the clamped value
    localVector[0] = baseValue;
    
    // Call collision/intersection test function (returns 2 for "hit")
    int result = FUN_004bdae0(localVector);
    return result == 2;
}