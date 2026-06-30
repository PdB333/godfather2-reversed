// FUNC_NAME: GameObject::isPointInBoundingBox
int GameObject::isPointInBoundingBox(float* point) {
    // Access per-thread data via FS segment (TLS)
    int tlsBase = *(int*)(**(int**)(__readfsdword(0x2c) + 8));
    
    // Offset 0x18 stores an index into a bounding box array
    int boxIndex = *(int*)(this + 0x18);  // +0x18: bounding box index
    
    // Center of bounding box (3 floats starting at tlsBase + 0x30 + boxIndex*12? Actually just base + 0x30 + boxIndex? No: the address is float*)
    float* boxCenter = (float*)(tlsBase + 0x30 + boxIndex);  // +0x30: array of bounding box centers (X,Y,Z)
    
    // Half-size scalar (a single float at tlsBase + boxIndex + 0x70) multiplied by global scale
    float halfSize = *(float*)(tlsBase + boxIndex + 0x70) * g_boxScale;  // DAT_01205330 -> g_boxScale
    
    // The following constants define an effective half-size offset? Actually fVar4 = g_offsetA - halfSize - g_offsetB
    float lowerBound = g_offsetA - halfSize - g_offsetB;  // DAT_00e44564 -> g_offsetA, DAT_00e2cd54 -> g_offsetB
    float upperBound = halfSize + g_offsetB;  // from logic: *param_2 - *pfVar1 < fVar3 where fVar3 = halfSize + g_offsetB? No: fVar3 = halfSize * scale? Wait recalc: fVar3 = halfSize * g_boxScale? Actually fVar3 = *(float *)(tlsBase + boxIndex + 0x70) * g_boxScale; so halfSize is that product.
    
    // Actually correct halfSize after multiplication:
    float scaledHalf = halfSize; // already scaled
    
    // The condition checks if point is within [center - lowerBound, center + scaledHalf] ? No: lowerBound = g_offsetA - scaledHalf - g_offsetB, which is weird.
    // From decompiled: fVar4 = DAT_00e44564 - fVar3 - DAT_00e2cd54; Then check if fVar4 < (point - center) < fVar3. So the box extends from center - fVar4? Actually fVar4 is negative? Since fVar4 = constant - half - constant, could be negative. Typical bounding box would be center - halfSize to center + halfSize. Here it's center + (-fVar4) to center + fVar3? The condition: fVar4 < diff < fVar3. So if fVar4 is negative, it's like -half to +half. So fVar4 is the negative bound? No, it's an inequality, so if fVar4 < diff, that means diff > fVar4, and diff < fVar3. So the range is (fVar4, fVar3). If fVar4 is negative and fVar3 positive, then point is between negative and positive offset. So the half-size is actually fVar3 (upper) and -fVar4 (lower). That implies fVar4 = -(halfSize - something)? Anyway, we'll keep the logic as is.
    
    // Compare point with box center on each axis
    float dx = point[0] - boxCenter[0];
    if (!(lowerBound < dx && dx < scaledHalf)) return 0;
    
    float dy = point[1] - boxCenter[1];
    if (!(lowerBound < dy && dy < scaledHalf)) return 0;
    
    float dz = point[2] - boxCenter[2];
    if (!(lowerBound < dz && dz < scaledHalf)) return 0;
    
    return 1;
}