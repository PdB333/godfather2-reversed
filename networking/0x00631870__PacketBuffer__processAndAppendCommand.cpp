// FUNC_NAME: PacketBuffer::processAndAppendCommand
// Function at 0x00631870  
// Processes commands from a read buffer (type 3 = data, type 4 = sequenced) and appends a new command with square root of the value.
// Object layout: +0x8 = write pointer, +0xc = read pointer (both pointing into a command buffer of 8-byte entries: type (int) + value (float))

#include <cmath> // for sqrtf

// Forward declaration of helper functions
bool FUN_00636850(float* outFloat); // probably validates/decodes a sequence number
void FUN_00627ac0(const char* message); // debug/error output

// Global constant (likely -1.0f or similar sentinel)
extern float DAT_00e2b05c;

int PacketBuffer::processAndAppendCommand()
{
    // Parse current command from read pointer
    int* readPos = *(int**)(this + 0xc);        // +0xc: read cursor
    int* writePos = *(int**)(this + 0x8);        // +0x8: write cursor

    // If buffer is empty or invalid, skip processing
    if (writePos <= readPos || readPos == nullptr)
        goto emptyBuffer;

    int commandType = *readPos;
    float commandValue;

    // If command type is 4 (sequenced), try to decode it first
    if (commandType == 4)
    {
        float decodedValue;
        if (FUN_00636850(&decodedValue) == 0)
            goto emptyBuffer; // decode failed, skip

        // Simulate a type 3 command with the decoded value
        int tempType = 3;
        float tempValue = decodedValue;
        readPos = &tempType; // temporarily point to local data
        commandValue = decodedValue;
    }
    else if (commandType != 3)
    {
        goto emptyBuffer; // unknown type, skip
    }
    else
    {
        commandValue = (float)readPos[1]; // value from command
    }

    // If the value equals the sentinel, skip all following commands until a valid one is found
    if (commandValue == DAT_00e2b05c)
    {
        while (true)
        {
            readPos = *(int**)(this + 0xc);
            if (writePos <= readPos || readPos == nullptr)
                break;

            int nextType = *readPos;
            if (nextType != 3 && (nextType != 4 || FUN_00636850(&commandValue) == 0))
                break;

            // Log error for each skipped command
            FUN_00627ac0("number");
        }
    }

emptyBuffer:
    // If we reach here, write a new command (type 3) with the square root of the current value
    commandValue = 0.0f; // default if no valid command was found
    // Re-read write pointer (it may have been updated by the loop?)
    int* newWrite = *(int**)(this + 0x8);
    *newWrite = 3;                               // type = 3
    newWrite[1] = *(int*)&sqrtf(commandValue);    // store square root as float
    *(int**)(this + 0x8) = newWrite + 2;          // advance write pointer by 8 bytes (2 ints)

    return 1;
}