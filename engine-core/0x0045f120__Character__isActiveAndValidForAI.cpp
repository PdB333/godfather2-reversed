// FUNC_NAME: Character::isActiveAndValidForAI
bool __fastcall Character::isActiveAndValidForAI()
{
    // +0x218: pointer to AI state data (could be AIInfo or StateData)
    void* pAIInfo = *(void**)(this + 0x218);
    bool result = false;

    if (pAIInfo != nullptr)
    {
        // +0x10: flags bitmask (bits 0,1,25 = 0x2000003)
        uint flags = *(uint*)((int)pAIInfo + 0x10);
        // +0x24: distance or value compared to global threshold
        float value = *(float*)((int)pAIInfo + 0x24);
        
        // Comma operator: first assign comparison result to result,
        // then check if any relevant flag bits are set.
        // If flag bits are set, force result to true.
        result = (value <= g_fMaxInteractionDistance); // DAT_00e2b1a4
        if ((flags & 0x2000003) != 0)
        {
            result = true;
        }
    }

    return result;
}