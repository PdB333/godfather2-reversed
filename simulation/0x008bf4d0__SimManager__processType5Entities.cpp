// FUNC_NAME: SimManager::processType5Entities
uint8_t __thiscall SimManager::processType5Entities(void) {
    uint8_t result = 0;
    uint8_t flag;
    uint32_t objCount = *(uint32_t *)(this + 0x1A8);           // Number of objects in array
    if (objCount != 0) {
        uint32_t i = 0;
        do {
            int *obj = *(int **)(*(int *)(this + 0x1A4) + i * 4); // Array of pointers at +0x1A4
            flag = 0;
            if ((obj != NULL) && (*(int *)(obj + 4) == 5)) {      // Type field at offset +4, value 5 means specific type
                flag = 1;
                FUN_008c80d0(0);                                 // Begin processing for type 5 objects
                FUN_008c8a20(1, 0);                               // Finalize processing
            }
            result |= flag;
            i++;
        } while (i < objCount);
    }
    return result;                                                // Returns 1 if any type 5 object was processed
}