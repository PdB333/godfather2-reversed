// FUNC_NAME: RotationHelper::applyScaledRotation
void __thiscall RotationHelper::applyScaledRotation(float* thisPtr, float scale)
{
    // thisPtr points to a 4-float struct (offset +0x00, +0x04, +0x08, +0x0C)
    // Typically: m_comp0 (angle or magnitude), m_comp1 (scaled copy), m_comp2, m_comp3 (auxiliary)
    thisPtr[1] = thisPtr[0] * scale;
    // FUN_004b9c30 takes (scaledValue, m_comp3, m_comp2) and returns result stored in m_comp3
    thisPtr[3] = FUN_004b9c30(thisPtr[0] * scale, thisPtr[3], thisPtr[2]);
}