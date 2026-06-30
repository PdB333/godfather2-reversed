// FUNC_NAME: ProximityTrigger::testProximity
void __thiscall ProximityTrigger::testProximity(const Vector3 &point) // param_1 = &point
{
    // Fetch the target object's position from the global game scene
    // Thread-local storage at fs:0x2c yields a pointer to the game context,
    // which contains an object table at offset +8.  Each object has a float[3] position
    // at offset +0x80.  The current trigger stores its target object index at +0x10.
    float *targetPos = (float *)(*(int *)(*(int *)(*(int *)__readfsdword(0x2c) + 0) + 8) + 0x80 + this->m_targetObjectIndex);
    
    // Squared distance between the given point and the target object (x,y,z)
    float dx = point.x - targetPos[0];
    float dy = point.y - targetPos[1]; // param_1[1] - pfVar1[1]
    float dz = point.z - targetPos[2];
    float distSq = dx*dx + dy*dy + dz*dz;
    
    // Check if the squared distance lies within the configured range
    // m_minDistSq (+0x30), m_maxDistSq (+0x34)
    if (this->m_minDistSq <= distSq && distSq < this->m_maxDistSq)
    {
        // Notify a proximity event (e.g., player entered trigger volume)
        FUN_004f8980();
    }
}