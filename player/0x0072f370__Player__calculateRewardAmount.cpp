// FUNC_NAME: Player::calculateRewardAmount
int __thiscall Player::calculateRewardAmount(void)
{
    float score = 0.0f;
    if (*(int *)(this + 0x1f44) != 0) { // m_pRewardData
        bool success = FUN_008934e0(*(int *)(this + 0x1f44), &score); // getBaseReward
        if (success && (*(uint *)(this + 0x1f98) & 0x10) != 0) { // flags: allowMultiplier
            int* multiplierPtr = **(int ***)(DAT_012233a0 + 4); // g_difficultyManager->pSettings
            if (multiplierPtr != nullptr && multiplierPtr != (int*)0x1f30) { // valid pointer check
                score *= *(float *)(multiplierPtr + 0x208); // difficultyMultiplier
            }
        }
    }
    int result = (int)(score + 0.5f); // round
    return result;
}