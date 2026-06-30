// FUNC_NAME: Entity::getRangeAndValidate
__thiscall bool Entity::getRangeAndValidate(float *outValue)
{
    // Call helper to get some entity pointer (e.g., player controller or vehicle)
    int entityPtr = CallHelper_005dc670(this); // returns pointer or 0
    if (entityPtr != 0) {
        // Read value at offset +0x280 (e.g., m_currentSpeed, m_range, etc.)
        float value = *(float *)(entityPtr + 0x280);
        *outValue = value;
        // Check if value is within global min/max bounds
        if (DAT_00e2b05c <= value && value <= DAT_00e2b1a4) {
            return true;
        }
    }
    return false;
}