// FUNC_NAME: ManagerClass::dispatchAndUpdateArray
void dispatchAndUpdateArray(void* context, uint objectOrValue, int* arrayInfo) {
    // arrayInfo: first int is base pointer to float array, second int is number of elements
    // objectOrValue: when non-zero, treated as pointer to object; when zero, treated as float constant
    
    uint* idPtr;
    uint id;
    code* handler;
    
    // Access object at offset +4 to get pointer to identifier array
    idPtr = *(uint**)(objectOrValue + 4);
    id = idPtr[1]; // Second uint in that array is the type ID
    
    // Validate ID against global bounds (DAT_01205574 is probably max+1)
    if ((-1 < (int)id) && (id < DAT_01205574)) {
        // Global table at DAT_01205570, entries 12 bytes each, function pointer at offset +4
        handler = *(code**)(DAT_01205570 + 4 + id * 0xc);
        if (handler != NULL) {
            (*handler)(context, id, &objectOrValue);
        }
    }
    
    int* basePtr = (int*)arrayInfo[0]; // Base address of float array
    int size = arrayInfo[1];           // Number of elements in array
    
    if (objectOrValue == 0) {
        // Write constant DAT_00e2e230 to array[id]
        if ((uint)size <= id) {
            int dummy = 0;
            FUN_00591c00(&dummy); // Assertion/error handler
        }
        *(float*)(basePtr + id) = *(float*)&DAT_00e2e230; // Store constant
    } else {
        // Compute DAT_00e2b1a4 / objectOrValue (treated as float)
        if ((uint)size <= id) {
            int dummy = 0;
            FUN_00591c00(&dummy);
        }
        float computed = *(float*)&DAT_00e2b1a4 / *(float*)&objectOrValue;
        *(float*)(basePtr + id) = computed;
        
        // Clamp to max DAT_00e44658
        if ((uint)size <= id) {
            int dummy = 0;
            FUN_00591c00(&dummy);
        }
        if (*(float*)&DAT_00e44658 < *(float*)(basePtr + id)) {
            *(float*)(basePtr + id) = *(float*)&DAT_00e44658;
        }
    }
}