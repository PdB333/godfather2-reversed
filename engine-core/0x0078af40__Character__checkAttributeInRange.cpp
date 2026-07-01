// FUNC_NAME: Character::checkAttributeInRange
// Address: 0x0078af40
// Role: Checks if an attribute value (e.g., speed, health) at +0x40 falls within a dynamically calculated range
// based on two base values (+0x54, +0x58), multiplied by a global setting, and clamped by an upper limit.

int __fastcall Character::checkAttributeInRange(int this)
{
    int data;
    float lowerBound;
    float upperBound;
    float tempLower;
    float tempUpper;

    // Dereference global settings pointer
    data = **(int**)(DAT_012233a0 + 4);   // s_pGameSettings->someData

    // Read base range limits from the object
    lowerBound = *(float*)(this + 0x54);  // +0x54 minBase
    upperBound = *(float*)(this + 0x58);  // +0x58 maxBase

    if ((data != 0) && (data += -0x1f30, data != 0)) // Adjust and check validity
    {
        // Apply global multiplier to compute a new range
        tempUpper = (lowerBound + upperBound) * _DAT_00d5c458;   // s_fRangeMultiplier
        tempLower = tempUpper - (upperBound - tempUpper);       // 2*tempUpper - upperBound
        tempUpper = upperBound;                                 // Original max becomes upper bound
        if (tempLower < 0.0f)
        {
            tempLower = 0.0f;
        }
        upperBound = tempUpper;
        if (DAT_00d5e288 < tempUpper)                          // s_fRangeMax clamp
        {
            upperBound = DAT_00d5e288;                          // s_fRangeMax
        }
    }

    // Check if attribute value is within computed range
    if ((lowerBound <= *(float*)(this + 0x40)) && (*(float*)(this + 0x40) <= upperBound))
    {
        return ((uint)data >> 8) << 8 | 1;                     // success: set low bit
    }
    return ((uint)data >> 8) << 8;                             // failure
}