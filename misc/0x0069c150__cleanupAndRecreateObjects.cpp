// FUNC_NAME: cleanupAndRecreateObjects
void cleanupAndRecreateObjects(void* obj1, void* obj2) {
    // Release first object (destructor/deallocation)
    FUN_004d3bc0(obj1);
    
    int flag = FUN_00699ff0(); // Check a global condition flag (0 = disabled, non-zero = enabled)
    
    if (flag == 0) {
        // Flag disabled: proceed only if global index is within valid range
        // globalIndex (DAT_00e506ac) must be in [0, count) where count = (arrayEnd - arrayStart) / 4
        if ((-1 < DAT_00e506ac) && (DAT_00e506ac < (DAT_01129f90 - DAT_01129f8c) / 4)) {
            // Release second object and then first again (possibly double-release?)
            FUN_004d3bc0(obj2);
            FUN_004d3bc0(obj1);
            
            // Create two new objects/handles: first A, then B
            void* ptrA;
            void (*funcA)(void*);
            FUN_0069b380(&ptrA, &funcA);
            
            void* ptrB;
            void (*funcB)(void*);
            FUN_004d3e20(&ptrB, &funcB);
            
            // Invoke the associated handlers on the newly created objects
            if (ptrA != 0) {
                funcA(ptrA);
            }
            if (ptrB != 0) {
                funcB(ptrB);
            }
        }
    } else {
        // Flag enabled: release and recreate in reversed order
        FUN_004d3bc0(obj2);
        FUN_004d3bc0(obj1);
        
        // Create first B, then A (swap order compared to above)
        void* ptrB;
        void (*funcB)(void*);
        FUN_0069b380(&ptrB, &funcB);
        
        void* ptrA;
        void (*funcA)(void*);
        FUN_004d3e20(&ptrA, &funcA);
        
        // Invoke handlers in reversed order: first B, then A
        if (ptrB != 0) {
            funcB(ptrB);
        }
        if (ptrA != 0) {
            funcA(ptrA);
        }
    }
}