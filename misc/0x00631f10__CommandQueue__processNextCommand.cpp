// FUNC_NAME: CommandQueue::processNextCommand
// Address: 0x00631f10
// Role: Processes the next command in a command buffer (queue). Commands are 8-byte entries:
//   [0..3]: type (int)
//   [4..7]: value (float)
// Types: 3 = deterministic command, 4 = random command (resolved to type 3 via random float)
// The function reads from the read pointer, if valid and type 3 or 4, resolves it,
// scales the value, and writes a new type 3 command to the write pointer.
// If the value matches a sentinel (gInvalidFloat), it skips to the next valid command.

struct CommandQueue {
    int* writePtr;      // +0x08: pointer to next write slot
    int* readPtr;       // +0x0C: pointer to current read slot
};

// Global constants (from data references)
extern const float gInvalidFloat;   // DAT_00e2b05c
extern const float gTimeScale;      // DAT_00e445c8
extern const char* gNumberString;   // PTR_s_number_00e2a8a8

// Callee declarations
int getRandomFloat(float* out);   // FUN_00636850: generates random float, returns 1 if successful
void debugPrint(const char* msg); // FUN_00627ac0: debug print (prints "number" here)

int CommandQueue::processNextCommand(CommandQueue* this) {
    int* currentRead = this->readPtr;
    int* currentWrite = this->writePtr;

    // If no commands to process, go to end and return 0 float.
    if (currentWrite <= currentRead || currentRead == nullptr) {
        goto skipAndSetZero;
    }

    int cmdType = *currentRead;
    if (cmdType != 3) {
        if (cmdType != 4) {
            goto skipAndSetZero;
        }
        // Type 4: random command, resolve to type 3 with random float
        float randomValue;
        int success = getRandomFloat(&randomValue);
        if (success == 0) {
            goto skipAndSetZero;
        }
        // Use local variables to simulate a new command entry
        int newType = 3;
        float newValue = randomValue;
        currentRead = &newType;  // point to the new local command
    }

    // Now currentRead points to a command of type 3 (resolved)
    float floatValue = reinterpret_cast<float*>(currentRead)[1]; // second field
    if (floatValue == gInvalidFloat) {
        // Skip until we find a valid command
        while (true) {
            currentRead = this->readPtr;
            if (currentWrite <= currentRead || currentRead == nullptr) {
                break;
            }
            int type = *currentRead;
            if (type != 3) {
                if (type != 4) {
                    // Not a valid command type, continue loop
                    debugPrint(gNumberString);
                    continue;
                }
                float tempFloat;
                int success = getRandomFloat(&tempFloat);
                if (success == 0) {
                    debugPrint(gNumberString);
                    continue;
                }
                // This type 4 is also valid after resolution, so exit loop
                break;
            }
            // Type 3 is valid, exit loop
            break;
        }
        // If we exited because no valid command, set floatValue to 0
        if (currentWrite <= currentRead || currentRead == nullptr) {
            floatValue = 0.0f;
        } else {
            // Re-read the resolved float (should be type 3 now)
            floatValue = reinterpret_cast<float*>(currentRead)[1];
        }
    }

    // Write the processed command to the write buffer
    int* dest = this->writePtr;
    float scaledValue = floatValue * gTimeScale;
    dest[0] = 3;                      // type
    reinterpret_cast<float*>(dest)[1] = scaledValue;

    // Advance write pointer by 8 bytes (one command)
    this->writePtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this->writePtr) + 8);

    return 1;  // success

skipAndSetZero:
    floatValue = 0.0f;
    // Fall through to write (but write pointer is not advanced? Actually the code writes anyway)
    // The original code after the label writes with local_14=0.0 and advances write pointer.
    // This seems weird but we replicate as closely as possible.
    int* dest2 = this->writePtr;
    dest2[0] = 3;
    reinterpret_cast<float*>(dest2)[1] = 0.0f;
    this->writePtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this->writePtr) + 8);
    return 1;
}