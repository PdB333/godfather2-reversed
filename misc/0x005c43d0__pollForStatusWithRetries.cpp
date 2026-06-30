// FUNC_NAME: pollForStatusWithRetries
uint pollForStatusWithRetries(void) {
    uint result;
    int i;

    i = 0;
    result = in_EAX & 0xffffff00; // Preserve upper bits of initial value
    if (0 < g_maxRetries) {
        do {
            result = checkStatus(); // Returns 0 if not ready, non-zero if ready
            if ((char)result != '\0') {
                return result; // Success
            }
            i = i + 1;
        } while (i < g_maxRetries);
    }
    // Return last result (could be failure code or default)
    return result;
}