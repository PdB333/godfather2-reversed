// FUNC_NAME: TaskQueue::processTasks
uint8_t TaskQueue::processTasks() {
    // this pointer assumed in ECX; function returns the first byte of the object (a success flag)
    uint8_t* flagPtr = reinterpret_cast<uint8_t*>(this);
    uint8_t* activeFlag = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x24);

    *flagPtr = 1; // default success

    // Check if the active flag (bit 0) is set
    if ((*activeFlag & 1) == 0) {
        return 0;
    }

    // Pre-processing step
    somePreprocess();

    TaskNode* node = *reinterpret_cast<TaskNode**>(reinterpret_cast<uintptr_t>(this) + 0x2C);
    if (node != nullptr) {
        uint32_t count = *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x28);
        if (count != 0) {
            uint32_t i = 0;
            uint8_t currentFlag = 1;
            do {
                if (node == nullptr) {
                    *flagPtr = 0;
                } else {
                    int valid = isNodeValid(node->value); // FUN_005dc670
                    if (valid == 0) {
                        *flagPtr = 0;
                    } else {
                        char result = performAction(); // FUN_005dd510
                        *flagPtr = currentFlag;
                        if (result == '\0') {
                            *flagPtr = 0;
                        }
                    }
                    node = node->next; // next at offset 0x28 from node
                }
                i++;
                currentFlag = *flagPtr;
            } while (i < count);
        }
    }
    return *flagPtr;
}

// Supporting structures and external function declarations (for clarity)
struct TaskNode {
    uint32_t value; // +0x00
    // ... other fields ...
    TaskNode* next; // +0x28
};

// Static/external functions
void somePreprocess(); // FUN_005ddd30
int isNodeValid(uint32_t value); // FUN_005dc670
char performAction(); // FUN_005dd510