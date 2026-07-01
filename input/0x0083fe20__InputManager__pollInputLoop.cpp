//FUNC_NAME: InputManager::pollInputLoop
// Function address: 0x0083fe20
// Role: Main input polling loop that processes OS messages and input events until an exit condition is met.

void InputManager::pollInputLoop()
{
    char isRunning;

    // Initialize polling state
    beginPolling();
    setInputFilter(0xb4fcbb2a); // Set filter for input events (magic constant)

    isRunning = isPollingActive();
    while (isRunning == '\0') {
        processOSMessages(); // Handle OS-level messages (e.g., window events)

        int* inputEvent = getNextInputEvent(); // Returns pointer to 4-int event struct
        // Check if any of the first 4 fields are non-zero (valid event)
        if ((((*inputEvent != 0) || (inputEvent[1] != 0)) || (inputEvent[2] != 0)) || (inputEvent[3] != 0)) {
            handleInputEvent(inputEvent); // Process the input event
        }

        endPollingFrame(); // Finalize frame polling
        isRunning = isPollingActive();
    }
}