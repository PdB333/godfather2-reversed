// FUNC_NAME: AnimCurve::FindNextKeyframeIndex
int __fastcall AnimCurve::FindNextKeyframeIndex(int unusedThis, int curvePtr, float currentTime)
{
    // Get thread-local byte offset into keyframe data
    int byteOffset = *(int *)(**(int **)(__readfsdword(0x2C) + 8));
    
    // Get base pointer to keyframe data from curve structure (+0x18)
    int keyframeBase = *(int *)(curvePtr + 0x18);
    
    // Read current keyframe time at offset 0x70 + byteOffset
    float currentKeyTime = *(float *)(keyframeBase + 0x70 + byteOffset);
    
    // If current time is past the current keyframe time
    if (currentKeyTime < currentTime)
    {
        float prevKeyTime = *(float *)(keyframeBase + 0x70 + byteOffset);
        int resultPtr = keyframeBase + byteOffset;
        float nextKeyValue = *(float *)(keyframeBase + 0x78 + byteOffset);
        
        // Compute an index/pointer based on comparison of previous and next key values
        // (decompilation of CONCAT22 and condition assembly)
        int flag = (prevKeyTime == nextKeyValue) ? 0x40 : 0x00;
        flag |= (__isnan(prevKeyTime) || __isnan(nextKeyValue)) ? 0x04 : 0x00;
        flag |= 0x02; // always set
        flag |= (prevKeyTime < nextKeyValue) ? 0x01 : 0x00;
        resultPtr = (resultPtr & 0xFFFF0000) | ((resultPtr & 0xFF) << 8) | (flag & 0xFF);
        
        // Compute blend alpha and check threshold
        float blendAlpha = (currentTime - prevKeyTime) / (currentKeyTime - prevKeyTime);
        float globalBlendRef = *(float *)0x00e2b1a4; // g_globalBlendRef
        float globalThreshold = *(float *)0x00e2e084; // g_globalThreshold
        
        if ((globalBlendRef - blendAlpha < globalThreshold) && (currentTime < currentKeyTime + currentTime)) // param_3 is passed but not clearly used? Actually param_3 is used as addition later
        {
            return resultPtr;
        }
    }
    
    // Return pointer to current keyframe data
    return keyframeBase + byteOffset;
}