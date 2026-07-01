// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(uint param_1, uint param_2) {
    // Check if the global state pointer (DAT_01223484) and its +0xc member are non-null
    if ((DAT_01223484 != 0) && (*(int *)(DAT_01223484 + 0xc) != 0)) {
        // Call helper functions with the given parameters
        FUN_008b5c70(param_1);
        FUN_008b5c90(param_2);
        // Pass pointer to global data table (PTR_LAB_00d79770) and a flag (1) to another function
        FUN_008b5cb0(&PTR_LAB_00d79770, 1);
    }
}