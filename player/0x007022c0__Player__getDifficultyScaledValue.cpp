// FUNC_NAME: Player::getDifficultyScaledValue
float __fastcall Player::getDifficultyScaledValue(int thisPtr)
{
    float result = *(float *)(thisPtr + 0x50c); // base value (e.g., damage, health)

    if ((*(uint *)(thisPtr + 0x2d8) >> 2 & 1) != 0) // flag bit 2: use difficulty multipliers
    {
        void* difficultyManager = FUN_007079c0(); // likely a singleton getter
        switch (*(int *)(thisPtr + 0x2dc)) // difficulty category enum
        {
            case 1:
                return (float)(*(float *)((char*)difficultyManager + 0x2170) * result);
            case 2:
            case 3:
                return (float)(*(float *)((char*)difficultyManager + 0x2178) * result);
            case 4:
                result = *(float *)((char*)difficultyManager + 0x2180) * result;
                break;
        }
    }
    return (float)result;
}