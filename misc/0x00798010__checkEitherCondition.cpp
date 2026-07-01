// FUNC_NAME: checkEitherCondition
// Function address: 0x00798010
// Checks two conditions using helper functions and returns 1 if either is true (logical OR).
// param_1 likely points to an object (e.g., this), param_2 and param_3 are arguments for each sub-check.
bool checkEitherCondition(void* context, uint param_2, uint param_3)
{
    char result;

    // First condition check: context + param_2
    result = FUN_006ae1a0(context, param_2);
    if (result != '\0') {
        return true;
    }

    // Second condition check: context + param_3
    result = FUN_006ae200(context, param_3);
    if (result != '\0') {
        return true;
    }

    return false;
}