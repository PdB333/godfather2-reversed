// FUNC_NAME: CheckCharacterValidity
// Function address: 0x006904e0
// Helper function to validate a character and update a boolean output.
// Checks if 'character' is a recognized input (not null, not -1), sets 'outValid' accordingly.
// Returns 1 if invalid character cleared an active flag, 0 otherwise.

int CheckCharacterValidity(void* unused, char character, char* outValid)
{
    // Skip if character is null terminator or sentinel (-1)
    if ((character != '\0') && (character != (char)-1))
    {
        // Call to internal character validation (likely checks if character belongs to a specific set)
        bool isValid = (IsCharRecognized(character) != 0);

        // If invalid and the output flag is currently true, clear it and return success
        if (!isValid && (*outValid != '\0'))
        {
            *outValid = false;
            return 1;
        }

        // Otherwise set the flag to the validation result
        *outValid = isValid;
    }
    return 0;
}