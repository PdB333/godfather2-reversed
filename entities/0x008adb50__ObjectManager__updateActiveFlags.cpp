// FUNC_NAME: ObjectManager::updateActiveFlags
void __fastcall ObjectManager::updateActiveFlags(int thisPtr)
{
    int obj;
    undefined4 handle;
    undefined1 *str;
    int *lookupResult;
    int conditionResult;
    int flagStruct1;
    int flagStruct2;
    int flagStruct3;
    int flagStruct4;
    undefined **iteratorTable;
    int currentObj;
    int iteratorState;
    int nextObj;
    undefined1 *defaultStr;
    code *advanceFunc;

    // Check if the "dirty" flag (bit 4 of field at +0x7C) is set
    if ((*(uint *)(thisPtr + 0x7C) >> 4 & 1) != 0) {
        obj = *(int *)(thisPtr + 0x60);
        if ((obj == 0) || (nextObj = obj, *(int *)(obj + 8) == 0)) {
            nextObj = 0;
        }
        currentObj = 0;
        iteratorTable = &PTR_FUN_00d79c8c;  // Global iterator function table
        defaultStr = 0;
        if (nextObj != 0) {
            defaultStr = (undefined1 *)obj;
        }
        // Iterate over the collection (linked list or array)
        while ((currentObj != 0) || (nextObj != 0)) {
            obj = (*(code *)*iteratorTable)();  // Get next object
            if ((*(byte *)(obj + 0x30) & 1) != 0) {  // Check if object is active (bit 0 at +0x30)
                handle = FUN_004bb600(obj);          // Get some handle from object
                FUN_004d3b50(handle);                // Set something with handle
                str = defaultStr;
                if (defaultStr == (undefined1 *)0x0) {
                    str = &DAT_0120546e;             // Default string constant
                }
                lookupResult = (int *)FUN_00568320(str);  // Lookup by string (hash table?)
                if (lookupResult != (int *)0x0) {
                    conditionResult = (**(code **)(*lookupResult + 0x44))();  // Virtual call: isConditionMet?
                    if (conditionResult == 0) {
                        // Condition not met: set flag to true
                        FUN_008ab7d0(&flagStruct1, obj + 8);
                        if (*(char *)(flagStruct1 + 4) != '\0') goto LAB_008adc68;
                        FUN_008ab7d0(&flagStruct2, obj + 8);
                        *(undefined1 *)(flagStruct2 + 4) = 1;
                        obj = (*(code *)*iteratorTable)(0);
                        FUN_0045c400(&DAT_0112edf4, obj + 8);  // Set flag data
                    }
                    else {
LAB_008adc68:
                        conditionResult = (**(code **)(*lookupResult + 0x44))();
                        if (conditionResult != 0) {
                            // Condition met: set flag to false
                            FUN_008ab7d0(&flagStruct3, obj + 8);
                            if (*(char *)(flagStruct3 + 4) != '\0') {
                                FUN_008ab7d0(&flagStruct4, obj + 8);
                                *(undefined1 *)(flagStruct4 + 4) = 0;
                                obj = (*(code *)*iteratorTable)(0);
                                FUN_0045c400(&DAT_0112ef7c, obj + 8);  // Set flag data
                            }
                        }
                    }
                }
                if (defaultStr != (undefined1 *)0x0) {
                    (*advanceFunc)(defaultStr);  // Cleanup or release
                }
            }
            (*(code *)iteratorTable[1])();  // Advance iterator
        }
    }
    return;
}