// FUNC_NAME: processNumberInput
// Address: 0x006280d0
// Role: Checks conditions and executes a "number" command if both conditions are false/zero.

// External functions (guessed names based on behavior)
extern long double isNumberModeActive();   // Returns float10, compared to 0
extern int isNumberModeEnabled();          // Returns int, compared to 0
extern void executeNumberCommand(const char* command); // Takes a string pointer

void processNumberInput(void)
{
    // Check if number mode is active (float condition)
    if (isNumberModeActive() == 0.0L)
    {
        // Check if number mode is enabled (int condition)
        if (isNumberModeEnabled() == 0)
        {
            // Execute the "number" command
            executeNumberCommand("number");
        }
    }
    return;
}