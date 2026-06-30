// FUNC_NAME: Entity::computeDirectionalForce
float __thiscall Entity::computeDirectionalForce(float* posA, float* posB, float influenceWeight)
{
    float result = 0.0f;
    
    // Check state flag: non-zero and not 0x48 (disabled or invalid?)
    if ((*(int*)(this + 4) != 0) && (*(int*)(this + 4) != 0x48))
    {
        // Get singleton manager that holds a reference position
        void* manager = getSomeManager(); // FUN_00471610
        float baseX = *posA;
        float baseY = posA[1];
        float baseZ = posA[2];
        
        // Manager's position at offsets 0x30, 0x34, 0x38
        float refX = *(float*)((char*)manager + 0x30);
        float refY = *(float*)((char*)manager + 0x34);
        float refZ = *(float*)((char*)manager + 0x38);
        
        // Vector from posA to posB
        float dirToTarget[3];
        dirToTarget[0] = *posB - baseX;
        dirToTarget[1] = posB[1] - baseY;
        dirToTarget[2] = posB[2] - baseZ;
        *(int*)&dirToTarget[3] = 0; // padding or unused
        
        // Normalize direction to target
        normalizeVector(dirToTarget); // FUN_0056afa0
        
        // Vector from posA to reference position
        float dirToRef[3];
        dirToRef[0] = refX - baseX;
        dirToRef[1] = refY - baseY;
        dirToRef[2] = refZ - baseZ;
        *(int*)&dirToRef[3] = 0; // padding or unused
        
        // Normalize reference direction
        normalizeVector(dirToRef); // FUN_0056afa0
        
        // Dot product of the two normalized vectors
        float dot = dirToRef[0] * dirToTarget[0] + dirToRef[1] * dirToTarget[1] + dirToRef[2] * dirToTarget[2];
        
        // Clamp dot between two global constants (min/max alignment thresholds)
        float minDot = DAT_00d5ccf8;      // g_minDotProduct
        float maxDot = _DAT_00d5780c;     // g_maxDotProduct
        if (dot <= minDot)
            dot = minDot;
        else if (dot >= maxDot)
            dot = maxDot;
        
        // Compute final influence: linear combination with global tuning factors
        result = (g_directionalForceMultiplier * dot * influenceWeight * g_forceBase + influenceWeight * g_forceBase) * g_forceScale;
    }
    
    return result;
}