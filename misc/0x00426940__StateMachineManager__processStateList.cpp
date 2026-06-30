// FUNC_NAME: StateMachineManager::processStateList
// Address: 0x00426940
// Iterates through a linked list of state objects, transitions them through states 1->3->4,
// and for state 4 pushes them into a circular buffer (pending completion queue).
// Returns 1 if any state changed, 0 otherwise.

char StateMachineManager::processStateList() {
    char anyChanged = 0;
    FUN_00ab4db0(&DAT_00e2e6f0);  // Acquire mutex

    // Check global flag (likely singleton context or thread state)
    // TIB or TLS offset: *(int *)(**(int **)(FS_OFFSET + 0x2c) + 0x34) == 1
    if (*(int *)(**(int **)(__readfsdword(0x2c)) + 0x34) == 1) {
        // Path when flag == 1 (e.g., main thread)
        ObjectNode* current = this->stateListHead;  // +0x4c
        while (current != nullptr) {
            int* state = reinterpret_cast<int*>(current->objectPtr);  // first field is state
            switch (*state) {
                case 1:
                case 2:
                    *state = 3;
                    break;
                case 3:
                    *state = 4;
                    break;
                case 4:
                {
                    // State 4: complete and push into ring buffer
                    void* obj = FUN_00426f10(local_4);  // likely get object reference
                    void* item = *(void**)obj;
                    FUN_004c6aa0();  // likely cleanup/destroy
                    int idx = this->writeIndex + this->elementCount;  // +0x44, +0x48
                    this->elementCount++;
                    if (idx >= this->ringBufferSize) {  // +0x40
                        idx -= this->ringBufferSize;
                    }
                    this->ringBuffer[idx] = current->objectPtr;  // +0x3c base pointer
                    goto continueLoop;
                }
                default:
                    break;
            }
            anyChanged = 1;
continueLoop:
            current = current->next;  // second field is next pointer
        }
    } else {
        // Path when flag != 1 (e.g., worker thread)
        ObjectNode* current = this->stateListHead;
        while (current != nullptr) {
            int* state = reinterpret_cast<int*>(current->objectPtr);
            switch (*state) {
                case 1:
                case 2:
                    *state = 3;
                    break;
                case 3:
                    *state = 4;
                    break;
                case 4:
                    // Already in final state, skip
                    break;
                default:
                    break;
            }
            anyChanged = 1;
            current = current->next;
        }
        if (anyChanged) {
            // Update global vtable pointer at DAT_01206880 + 0x14
            int** globalPtr = reinterpret_cast<int**>(DAT_01206880 + 0x14);
            *globalPtr = reinterpret_cast<int*>(&PTR_LAB_0110b758);
            **globalPtr += 4;  // likely increment vtable index
        }
    }

    FUN_00ab4e70();  // Release mutex
    return anyChanged;
}