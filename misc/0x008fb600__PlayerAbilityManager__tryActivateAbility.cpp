// FUNC_NAME: PlayerAbilityManager::tryActivateAbility
// Function address: 0x008fb600
// Role: Attempts to activate an ability for a given entity, subject to cooldown and state checks.

char __thiscall PlayerAbilityManager::tryActivateAbility(int thisPtr, int entityId, float paramFloat)
{
    char result;
    int abilityIndex;
    int entityData;
    int currentAbility;
    float timeSinceLastUse;

    // Check cooldown: compare global time with last use time stored at +0x438
    timeSinceLastUse = g_gameTime - *(float *)(thisPtr + 0x438);
    if (timeSinceLastUse < *(float *)(thisPtr + 0x434) || timeSinceLastUse == *(float *)(thisPtr + 0x434))
    {
        return '\0'; // Cooldown not expired
    }

    // Get entity data from entityId
    entityData = FUN_008c74d0(entityId);
    abilityIndex = 0;
    if (entityData != 0)
    {
        int abilityType = *(int *)(entityData + 0x50);
        int temp = abilityType - 2;
        if (temp == 0)
        {
            abilityIndex = 2;
        }
        else if (abilityType == 3)
        {
            abilityIndex = temp;
        }
    }

    // Check if current ability index is less than the computed index and paramFloat is within range
    if ((*(int *)(thisPtr + 0x174) < abilityIndex) &&
        (*(float *)(thisPtr + 0x430) <= paramFloat && paramFloat != *(float *)(thisPtr + 0x430)))
    {
        int newAbility = FUN_008fa220(entityId, paramFloat);
        if (newAbility != 0)
        {
            // Determine current ability from +0x43c
            if (*(int *)(thisPtr + 0x43c) == 0)
            {
                currentAbility = 0;
            }
            else
            {
                currentAbility = *(int *)(thisPtr + 0x43c) - 0x48;
            }

            if (newAbility != currentAbility)
            {
                result = FUN_008fb4f0(newAbility, 0);
                if (result != '\0')
                {
                    *(float *)(thisPtr + 0x430) = paramFloat; // Update stored float
                }
                return result;
            }
        }
    }
    return '\0';
}