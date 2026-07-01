// FUNC_NAME: TargetingManager::getMaxThreatScore
float __thiscall TargetingManager::getMaxThreatScore(void)
{
    float maxScore = 0.0f;

    // m_targetCount at offset +0x98
    if (this->m_targetCount != 0)
    {
        // m_pTargetList at offset +0x94 (array of 8-byte entries)
        for (uint32_t i = 0; i < this->m_targetCount; ++i)
        {
            uint32_t rawPtr = *(uint32_t *)(this->m_pTargetList + i * 8); // first 4 bytes of entry

            // Skip sentinel values: 0 and 0x48 (special marker)
            if (rawPtr != 0 && rawPtr != 0x48)
            {
                uintptr_t basePtr = rawPtr - 0x48; // adjust to base object

                if (basePtr != 0)
                {
                    // Virtual function at vtable+0x1b0 returns a float (e.g., threat score)
                    typedef float (__thiscall *GetScoreFunc)(uintptr_t);
                    GetScoreFunc getScore = (GetScoreFunc)(*(uint32_t *)basePtr + 0x1b0);
                    float score = getScore(basePtr);

                    if (maxScore < score)
                    {
                        maxScore = score;
                    }
                }
            }
        }
    }

    return maxScore;
}