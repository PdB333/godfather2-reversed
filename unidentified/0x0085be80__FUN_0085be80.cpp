// FUNC_NAME: SomeClass::updateStateBasedOnTimeAndInput

void __thiscall SomeClass::updateStateBasedOnTimeAndInput(int this, int unused, float* data)
{
    float* dataPtr;
    char* flagPtr;
    float currentTime;
    bool condition;

    // Get current time from virtual function at vtable+0x1a8
    currentTime = (float)(**(code **)(**(int **)(this + 4) + 0x1a8))();

    dataPtr = data;
    condition = g_threshold < *data; // data[0] > g_threshold

    if (data[2] == g_someFlag) {
        // Check if time is within limit, data[1] > threshold, data[0] <= threshold, and global flag is set
        if ((g_timeLimit > currentTime) && (data[1] > g_threshold) && (!condition) && (g_enabled != '\0')) {
            condition = true;
            goto LAB_0085bf3f;
        }
    } else {
        if (g_timeLimit <= currentTime) {
            condition = !condition;
            goto LAB_0085bf3f;
        }
        if (g_enabled != '\0') {
            if ((data[1] <= g_threshold) || (condition)) {
                condition = false;
            } else {
                condition = true;
            }
            goto LAB_0085bf3f;
        }
    }
    condition = false;

LAB_0085bf3f:
    setGlobalBool(condition);
    flagPtr = (char*)getFlagPointer(&data); // Returns pointer to a flag
    dataPtr[2] = (float)(*flagPtr != '\0');
    return;
}