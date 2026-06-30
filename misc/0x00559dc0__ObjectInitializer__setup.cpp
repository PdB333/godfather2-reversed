// FUNC_NAME: ObjectInitializer::setup
void ObjectInitializer::setup(void* this, void* arg1, void* arg2, int unusedFlag) {
    // Local variables
    void** vtablePtrPtr = &PTR_LAB_00dcf98c; // Global vtable pointer table
    char local_8 = 0;                        // Unused flag
    int local_4 = unusedFlag;                // Stored but not used

    // Call base initialization with arguments reordered
    // arg1, this, arg2, and pointer to vtable pointer
    FUN_00c0a110(arg1, this, arg2, &vtablePtrPtr);
}