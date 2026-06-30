// FUNC_NAME: UnknownClass::selectRandomOutcome
uint __thiscall UnknownClass::selectRandomOutcome(uint threshold)
{
    uint randomValue;

    if (*(int *)(this + 0x2d0) != 0) // +0x2d0: flag indicating randomness is enabled
    {
        randomValue = getRandomValue(); // FUN_00701360 - returns a random uint
        if (threshold <= randomValue)
        {
            applyOutcome(*(uint32_t *)(this + 0x334), threshold); // +0x334: some context pointer
            return threshold;
        }
        randomValue = getRandomValue();
        if (randomValue < threshold)
        {
            threshold = getRandomValue(); // re-roll
            applyOutcome(*(uint32_t *)(this + 0x334), threshold);
        }
    }
    return threshold;
}