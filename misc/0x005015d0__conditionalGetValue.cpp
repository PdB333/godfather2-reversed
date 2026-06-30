// FUNC_NAME: conditionalGetValue
int __cdecl conditionalGetValue(int instance, int isActive)
{
    // If the activation flag is non-zero, retrieve the associated value from the instance.
    // Otherwise, return 0 as a fallback.
    if (isActive != 0) {
        return getInstanceValue(instance);
    }
    return 0;
}