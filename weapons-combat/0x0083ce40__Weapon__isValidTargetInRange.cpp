// FUNC_NAME: Weapon::isValidTargetInRange
// Address: 0x0083ce40
// Role: Checks if a target (entity ID/pointer) is within effective range of this weapon, considering valid target lists.

extern float g_minRange;          // _DAT_00d577a0
extern float g_rangeModifierA;    // DAT_00d5eee4
extern float g_rangeModifierB;    // _DAT_00d5780c

// Forward declarations of helper functions:
float getRangeScalingFactor();                   // FUN_0083ba00
float getTargetDistance(uint target);            // FUN_004702b0, assumes param2 is target ID
void* getTargetListById(int listId);             // FUN_0043c2c0, returns pointer to linked list header

bool __thiscall Weapon::isValidTargetInRange(uint target)
{
    float effectiveRange = *(float*)(this + 0x68); // m_range

    // If below minimum global threshold, no target possible
    if (effectiveRange <= g_minRange)
        return false;

    // Check flag at bit 17 (0x20000)
    if ((*(uint*)(this + 0xA8) >> 17) & 1) // m_flags
    {
        float scalingFactor = getRangeScalingFactor();
        // Quadratic range modifier: effectiveRange = ((A + factor) * factor + B) * range
        effectiveRange = (float)(((double)(g_rangeModifierA + scalingFactor) * (double)scalingFactor + (double)g_rangeModifierB) * (double)effectiveRange);
    }

    int targetListId = *(int*)(this + 0xF4); // m_targetListId
    if (targetListId == -1)
    {
        // Use inline target type array
        int count = *(int*)(this + 0x98); // m_validTargetCount
        if (count != 0)
        {
            int* arrayBase = *(int**)(this + 0x94); // m_validTargetArray (array of 8-byte entries)
            for (uint i = 0; i < (uint)count; i++)
            {
                int targetType = *(int*)(arrayBase + i * 2); // first dword of each 8-byte entry
                if (targetType != 0 && targetType != 0x48)   // skip invalid or special type
                {
                    float distanceToTarget = getTargetDistance(target);
                    if ((double)distanceToTarget < (double)effectiveRange)
                    {
                        return true;
                    }
                }
                if (i == (uint)(count - 1))
                    break;
            }
        }
    }
    else
    {
        // Use linked list from global manager
        void** listHeader = (void**)getTargetListById(targetListId);
        for (int* node = (int*)*listHeader; node != nullptr; node = (int*)node[1]) // list node: first int = data, second int = next pointer
        {
            if (*node != 0)
            {
                float distanceToTarget = getTargetDistance(target);
                if ((double)distanceToTarget < (double)effectiveRange)
                {
                    return true;
                }
            }
        }
    }
    return false;
}