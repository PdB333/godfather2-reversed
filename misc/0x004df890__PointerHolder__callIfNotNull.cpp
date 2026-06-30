// FUNC_NAME: PointerHolder::callIfNotNull
void __thiscall PointerHolder::callIfNotNull(int* param_1, int param_2)
{
    // Checks if the stored pointer (first field of the class) is non-zero,
    // then calls a function on it, passing the second parameter.
    // This is a safe wrapper to avoid calling on null pointers.
    if (*param_1 != 0) {
        callTargetFunction(*param_1, param_2);  // 0x0051c530
    }
}