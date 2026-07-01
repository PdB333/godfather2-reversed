// FUN_NAME: PathManager::computeMaxSpeed
// Function: 0x008be890 - Computes the maximum value from the second float in an array of pairs.
// The array is stored as a pointer at +0x18C, with count at +0x190.
// Each pair is 8 bytes (two floats). Result stored at +0x198.
void __thiscall PathManager::computeMaxSpeed()
{
    float currentValue;
    unsigned int i = 0;
    float* pFloat;

    // +0x198: max value, initialize to 0
    *(float*)(this + 0x198) = 0.0f;

    // +0x190: number of elements in the array
    if (*(int*)(this + 0x190) != 0)
    {
        // +0x18C: pointer to the base of the array.
        // Starting from +4 (skip first float of first element) gives address of second float.
        pFloat = (float*)(*(int*)(this + 0x18C) + 4);

        do
        {
            currentValue = *pFloat;

            // Keep the largest value found (strictly greater)
            if (*(float*)(this + 0x198) <= currentValue && currentValue != *(float*)(this + 0x198))
            {
                *(float*)(this + 0x198) = currentValue;
            }

            i++;
            pFloat += 2; // skip to next element's second float (each element is 2 floats)
        } while (i < *(unsigned int*)(this + 0x190));
    }
}