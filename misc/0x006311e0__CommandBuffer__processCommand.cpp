// FUNC_NAME: CommandBuffer::processCommand
// Address: 0x006311e0
// Reads a command from the input buffer (readCursor) and writes a SET_FLOAT command to the output buffer (writeCursor).
// If the read command is GET_FLOAT (type 4), it obtains the float via a callback. Skips commands that yield a sentinel float value.

#define COMMAND_SET_FLOAT 3
#define COMMAND_GET_FLOAT 4

extern float g_sentinelFloat; // DAT_00e2b05c
extern const char* g_logNumber; // PTR_s_number_00e2a8a8

int CommandBuffer::processCommand() {
    float resultFloat;
    int* readPtr = *(int**)(this + 0xC); // +0xC: readCursor (current read position in input buffer)
    int* writePtr = *(int**)(this + 0x8); // +0x8: writeCursor (current write position in output buffer)

    // Check if read pointer is valid and ahead of write pointer
    if (writePtr <= readPtr) goto error;
    if (readPtr == nullptr) goto error;

    if (*readPtr != COMMAND_SET_FLOAT) {
        if (*readPtr != COMMAND_GET_FLOAT) goto error;
        int status = readExternalFloat(&resultFloat); // FUN_00636850
        if (status == 0) goto error;
        // Substitute a temporary command on the stack to treat GET as SET
        int tempCmd = COMMAND_SET_FLOAT;
        float tempFloat = resultFloat;
        readPtr = &tempCmd; // point to local command with the retrieved float
    }

    resultFloat = (float)readPtr[1]; // the float value from the command

    // Sentinel float indicates "ignore this command"; log and reset to 0
    if (resultFloat == g_sentinelFloat) {
        while (true) {
            readPtr = *(int**)(this + 0xC);
            if (writePtr <= readPtr || readPtr == nullptr) {
                break;
            }
            if (*readPtr == COMMAND_SET_FLOAT) {
                break;
            }
            if (*readPtr == COMMAND_GET_FLOAT) {
                int status = readExternalFloat(&resultFloat);
                if (status != 0) break;
            }
            logPrint(g_logNumber); // FUN_00627ac0
error:
            resultFloat = 0.0f;
            break;
        }
    }

    // Write a SET_FLOAT command with the resulting float
    int* outCmd = *(int**)(this + 0x8);
    *outCmd = COMMAND_SET_FLOAT;
    double d = (double)resultFloat;
    performFloatOperation(); // FUN_00b9d99d
    outCmd[1] = (float)d;
    *(int*)(this + 0x8) = *(int*)(this + 0x8) + 8; // advance write cursor

    return 1;
}