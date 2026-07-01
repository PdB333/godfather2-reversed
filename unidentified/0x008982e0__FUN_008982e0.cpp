// FUNC_NAME: SomeClass::waitForInitialization
// Function address: 0x008982e0
// Role: Polls an async initialization routine up to 4 times; returns when ready.

void SomeClass::waitForInitialization()
{
    // Check if the object is valid
    if (this != 0) {
        // Check if initialization is complete
        char isComplete = this->isProcessComplete();
        // Retry up to 4 times
        for (byte attempt = 0; isComplete == '\0' && attempt < 4; ++attempt) {
            // Perform one step of initialization
            this->doProcessStep();
            // Re-check status
            isComplete = this->isProcessComplete();
        }
    }
}