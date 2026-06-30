// FUNC_NAME: UnknownClass::generateRandomPair
// Function address: 0x00673560
// Role: Generates two random/unique values, potentially based on a flag stored at +0x1c.
// When the flag is zero, both outputs are fresh random values.
// When the flag is non-zero, the first output is forced to 0 and the second receives a random value.
void __thiscall UnknownClass::generateRandomPair(int *outValue1, int *outValue2)
{
    // This function retrieves a random value from FUN_00676010 (likely a random number generator or hash function)
    int randomValue = FUN_00676010();  // First call always happens

    // Check the flag stored at offset +0x1c in the object (likely a boolean indicating special state)
    if (*(int *)(this + 0x1c) == 0) {
        // Normal case: both outputs get independent random values
        int randomValue2 = FUN_00676010();  // Second call
        int randomValue3 = FUN_00676010();  // Third call
        *outValue1 = randomValue2;
        *outValue2 = randomValue3;
        return;
    }

    // Special case: first output is forced to 0, second gets the first random value
    *outValue1 = 0;
    *outValue2 = randomValue;
}