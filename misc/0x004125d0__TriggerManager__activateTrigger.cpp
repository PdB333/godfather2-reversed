// FUNC_NAME: TriggerManager::activateTrigger
int __thiscall TriggerManager::activateTrigger(int triggerId)
{
    // Offsets:
    // this+0x20c: pointer to array of Trigger pointers (int* array)
    // this+0x210: count of triggers in the array
    int *triggerArray = *(int **)(this + 0x20c);
    int triggerCount = *(int *)(this + 0x210);
    
    if (triggerArray != triggerArray + triggerCount) {
        int *endPtr = triggerArray + triggerCount;
        int *currentPtr = triggerArray;
        
        while (true) {
            int triggerPtr = *currentPtr;  // Dereference to get Trigger* (int)
            if (*(int *)(triggerPtr + 0x18) == triggerId) {
                // Found trigger with matching ID
                // Set active flag at offset 0x15
                *(unsigned char *)(triggerPtr + 0x15) = 1;
                
                // Process actions list
                // Each action is 8 bytes (two 4-byte fields)
                int actionCount = *(int *)(triggerPtr + 0x20);
                if (actionCount != 0) {
                    int actionArrayPtr = *(int *)(triggerPtr + 0x1c);
                    unsigned int actionIndex = 0;
                    do {
                        // Each action entry: 8 bytes, split into two 4-byte values
                        unsigned int *actionEntry = (unsigned int *)(actionArrayPtr + actionIndex * 8);
                        
                        // Prepare context (using trigger ID + 8 as a key or name)
                        prepareActionContext(*(int *)(triggerPtr + 0x18) + 8);
                        
                        // Dispatch action: parameters are (global DAT_0122337c, action first dword, output, action second dword, trigger field+0x10, 0)
                        int *output[3]; // actually used as function pointer holder
                        dispatchAction(DAT_0122337c, *actionEntry, output, actionEntry[1], *(int *)(triggerPtr + 0x10), 0);
                        
                        // If output[0] is not null, call it as a function pointer
                        if (output[0] != 0) {
                            ((void (*)(void *))output[0])(output[0]);  // Note: original code uses local_c which is same as output[0]? This is reconstructed.
                        }
                        
                        actionIndex++;
                    } while (actionIndex < (unsigned int)actionCount);
                }
                break;
            }
            
            currentPtr++;
            if (currentPtr == endPtr) {
                break;
            }
        }
    }
    return 1;
}