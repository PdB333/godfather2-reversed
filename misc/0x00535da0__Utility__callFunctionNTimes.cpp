// FUNC_NAME: Utility::callFunctionNTimes
void callFunctionNTimes(int count)
{
    // Execute the target function 'count' times
    if (count > 0) {
        do {
            processSingleStep();
            count--;
        } while (count != 0);
    }
}