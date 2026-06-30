// FUNC_NAME: AudioMixer::processModulationQueue
// Function address: 0x00631490
// Role: Reads modulation commands from an input queue, optionally skips sentinel values,
// computes cosine of the float parameter, and writes a new command to an output queue.

#include <cmath>

// Forward declarations for helper functions (callees)
bool isModulationActive();            // from 0x00636850
void advanceReadPointer();             // from 0x00627ac0
double cos(double value);              // from 0x00b9cce0 (standard libc)

// Command structure: 8 bytes
struct Command {
    int type;      // +0x00
    float value;   // +0x04
};

// Special sentinel value that triggers skipping
const float kCommandSkippedValue = *(float*)0x00e2b05c;   // DAT_00e2b05c

int AudioMixer::processModulationQueue() {
    // 'this' has:
    // +0x08: write pointer (output queue current position)
    // +0x0c: read pointer (input queue current position)
    Command* readPtr = *(Command**)(this + 0x0c);
    Command* writePtr = *(Command**)(this + 0x08);

    // If queue is empty or read pointer beyond write, skip
    if (writePtr <= readPtr) goto skipToOutput;
    if (readPtr == nullptr) goto skipToOutput;

    // Check type of current command
    if (readPtr->type != 3) {
        if (readPtr->type != 4) goto skipToOutput;
        if (!isModulationActive()) goto skipToOutput;
        // Treat type 4 as type 3 when modulation is active
        Command temp;
        temp.type = 3;
        temp.value = readPtr->value;
        readPtr = &temp;
    }

    // Retrieve the float value from the command
    float currentValue = readPtr->value;

    // If the value equals the sentinel, skip ahead until a valid command is found
    if (currentValue == kCommandSkippedValue) {
        while (true) {
            advanceReadPointer();

            // Re-read the current read pointer
            readPtr = *(Command**)(this + 0x0c);
            writePtr = *(Command**)(this + 0x08);

            // Check conditions: queue empty or invalid command
            if (writePtr <= readPtr || readPtr == nullptr) {
                currentValue = 0.0f;
                break;
            }
            // Valid command if type is 3, or type 4 with active modulation
            if (readPtr->type == 3) {
                currentValue = readPtr->value;
                break;
            }
            if (readPtr->type == 4 && isModulationActive()) {
                currentValue = readPtr->value;
                break;
            }
            // Otherwise continue skipping
        }
    }

    // Compute cosine of the final value
    double cosResult = cos((double)currentValue);

    // Write output command to the write pointer
    Command* outPtr = *(Command**)(this + 0x08);
    outPtr->type = 3;
    outPtr->value = (float)cosResult;

    // Advance write pointer by command size
    *(int*)(this + 0x08) = (int)outPtr + sizeof(Command);

    return 1;
}