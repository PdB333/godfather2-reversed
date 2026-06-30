// FUNC_NAME: Entity::getDistanceScore
float Entity::getDistanceScore(int* otherFamily) // param_1 is this, param_2 is otherFamily (Family*)
{
    // Constants from globals
    const float minScore = DAT_00e5174c; // Minimum clamp
    const float maxScore = DAT_00d61958; // Maximum clamp
    const float familyMultiplier = _DAT_00d5ca64; // Multiplier if entity is a family member

    float score = minScore; // Default score

    // Virtual function at vtable+0xc0 - likely "isAlive" or "isActive", returns float
    float aliveStatus = (this->*reinterpret_cast<float(__thiscall*)(void*)>(*(void**)this + 0xc0))();

    if ((aliveStatus > 0.0f) && (otherFamily != nullptr))
    {
        // Get two positions from global functions (likely current entity position and some target position)
        // FUN_00471610 returns a pointer to a transform struct (int*) with position at +0x30, +0x34, +0x38
        int* pos1 = reinterpret_cast<int*>(FUN_00471610()); // Assume returns position of entity itself
        int* pos2 = reinterpret_cast<int*>(FUN_00471610()); // Assume returns position of family leader

        float dx = *reinterpret_cast<float*>(pos2 + 0x30 / 4) - *reinterpret_cast<float*>(pos1 + 0x30 / 4);
        float dy = *reinterpret_cast<float*>(pos2 + 0x34 / 4) - *reinterpret_cast<float*>(pos1 + 0x34 / 4);
        float dz = *reinterpret_cast<float*>(pos2 + 0x38 / 4) - *reinterpret_cast<float*>(pos1 + 0x38 / 4);

        float distSq = dx*dx + dy*dy + dz*dz;
        score = maxScore - distSq; // Higher proximity gives higher score

        // Check if this entity is the owner of the family's first member entry
        // offset 0x1c78 in Family points to a member list; subtract 0x48 to get parent object pointer
        int* memberBase = nullptr;
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(otherFamily) + 0x1c78) != 0)
        {
            memberBase = reinterpret_cast<int*>(
                *reinterpret_cast<int*>(reinterpret_cast<char*>(otherFamily) + 0x1c78) - 0x48);
        }

        if (memberBase == reinterpret_cast<int*>(this))
        {
            score *= familyMultiplier; // Loyalty bonus for being the family leader/member
        }

        // Clamp score to valid range
        if (score > maxScore)
            score = maxScore;
        else if (score < minScore)
            score = minScore;
    }

    return score;
}