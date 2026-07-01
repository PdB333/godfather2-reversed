// FUNC_NAME: initializeAndApply
// This function appears to be a simple wrapper that performs two sequential operations.
// It calls FUN_004dafd0 with a duplicated first argument (likely a this pointer or object handle),
// then passes the result to FUN_0098cbb0 along with all original parameters.
// The exact semantics are unknown, but it may be part of an initialization or update routine.
void initializeAndApply(uint32_t self, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
    uint32_t temp = FUN_004dafd0(self, self, arg1, arg2, arg3);
    FUN_0098cbb0(temp, self, arg1, arg2, arg3);
}