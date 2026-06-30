// FUNC_NAME: TableSerializer::serializeTable
// Address: 0x00630330
// Role: Serializes a table of string pairs from input stream to output buffer.
// The table is read as a sequence of (key, value) string pairs, each 8 bytes.
// The input stream contains two floats: start index and end index (inclusive).
// If the first element is not type 5 (table marker), it prints "table" and sets start=1.
// Uses a temporary buffer to accumulate overflow data.

#include <cstdint>

// Forward declarations of helper functions (from other code)
int32_t getTableHandle(int32_t* globalPtr, int32_t* outHandle); // FUN_00627fe0
int32_t readFloatFromStream();                                   // FUN_00628080
void printDebugString(const char* str);                          // FUN_00627ac0
int32_t getNumElements(int32_t param);                           // FUN_00628820
int32_t* getNextPair();                                          // FUN_00637f10
int32_t isStringType();                                          // FUN_00625830
void postProcessElement();                                       // FUN_00628c50
void advanceToNextPair(int32_t handle, int32_t context);         // FUN_00628b20
int32_t checkBufferSpace();                                      // FUN_00627290
void setWritePosition(int32_t* ptr, int32_t offset);            // FUN_00626f80
void resetBuffer(int32_t param);                                 // FUN_00626fd0
void pushBuffer(int32_t param);                                  // FUN_00627010
void popBuffer();                                                // FUN_006270e0
int32_t copyBuffer(int32_t* dest, int8_t* src, int32_t size);   // FUN_00638920
void finalize();                                                 // FUN_00626460
void errorReport(int32_t* thisPtr, int32_t code, const char* msg); // FUN_00627a20

int32_t __thiscall TableSerializer::serializeTable(int32_t* thisPtr)
{
    int32_t* readPos;
    int32_t* writePos;
    int32_t* stackPtr;
    float in_XMM0_Da;          // float from SIMD register
    float fVal1, fVal2;
    int32_t startIndex, endIndex, currentIndex;
    int32_t iVar5, iVar7;
    int32_t local_228, local_224;
    int32_t local_21c;         // handle from getTableHandle
    int32_t* pairPtr;
    int32_t* writePtr;
    int32_t returnVal;
    int32_t pairCount;
    uint8_t tempBuffer[520];   // stack buffer for overflow data
    uint8_t* tempEnd = tempBuffer;
    int32_t tempUsed = 0;

    // Get handle to the table (e.g., the string table manager)
    returnVal = getTableHandle(&DAT_00e2f044, &local_21c);

    // Read the first float (start index) from the input stream (readPos + 0x10)
    readPos = reinterpret_cast<int32_t*>(thisPtr[3]);  // +0xC
    fVal1 = DAT_00e2b1a4;                              // global default float
    if ((readPos < writePos) && (readPos != nullptr) && (*readPos > 0))
    {
        fVal1 = readFloatFromStream();                 // read a float
    }

    // Read the second float (end index) from the input stream (readPos + 0x18)
    readPos = reinterpret_cast<int32_t*>(thisPtr[3]) + 2; // +0x18 offset (two ints)
    startIndex = static_cast<int32_t>(fVal1);          // store first float as int
    if ((readPos < writePos) && (readPos != nullptr) && (*readPos > 0))
    {
        fVal2 = readFloatFromStream();
    }
    else
    {
        fVal2 = 0.0f;
    }

    // Check if the first tag in the stream is a table marker (5)
    readPos = reinterpret_cast<int32_t*>(thisPtr[3]); // +0xC again
    if ((writePos <= readPos) || (readPos == nullptr) || (*readPos != 5))
    {
        // Not a table marker; assume it's a named table
        startIndex = 1;
        printDebugString("table");   // maybe debug output
        // iVar5 = return value from some function (extraout_ECX)
        // The decompiler shows extraout_ECX; we'll treat as follow-up
        // This likely sets up the number of elements
    }

    local_228 = static_cast<int32_t>(fVal2); // endIndex from second float
    if (iVar5 == 0) // iVar5 came from the check above; need to track
    {
        // If not set, get number of elements from the stream
        endIndex = getNumElements(1); // FUN_00628820(1)
        startIndex = local_224;       // use previously stored start?
        local_228 = endIndex;
    }
    else
    {
        endIndex = local_228;
    }

    // Prepare for loop over elements from startIndex to endIndex
    tempEnd = tempBuffer;
    int32_t savedThis = reinterpret_cast<int32_t>(thisPtr);
    pairCount = 0;

    if (startIndex <= endIndex)
    {
        do
        {
            // Get pointer to the next pair from some manager
            pairPtr = getNextPair();           // FUN_00637f10
            // Write the pair to the output stream (8 bytes)
            writePtr = reinterpret_cast<int32_t*>(thisPtr[2]);  // +0x8
            writePtr[0] = pairPtr[0];
            writePtr[1] = pairPtr[1];
            thisPtr[2] = reinterpret_cast<int32_t>(writePtr + 2); // advance write pointer by 8 bytes

            // Verify that the written data is a string type
            if (isStringType() == 0)
            {
                errorReport(thisPtr, 1, "table contains non-strings");
                // In a real game, this would be an assertion or crash
            }

            postProcessElement();

            // Advance to next pair unless it's the last element
            if (currentIndex != local_228) // local_228 is endIndex
            {
                advanceToNextPair(returnVal, local_21c);
                startIndex = local_224; // update start? (seems odd, but preserved)
            }

            currentIndex++;
            startIndex = currentIndex;
        } while (currentIndex <= endIndex);
    }

    // Calculate how much data was temporarily stored (if any)
    int32_t tempSize = static_cast<int32_t>(tempEnd - tempBuffer);
    if (tempSize != 0)
    {
        // Check if there is room in the internal buffer stack
        int32_t* stack = reinterpret_cast<int32_t*>(thisPtr[4]); // +0x10
        if (stack[8] <= stack[9]) // offsets 0x20 and 0x24
        {
            // Need to push a new buffer
            returnVal = checkBufferSpace();    // FUN_00627290
            setWritePosition(thisPtr, 0);      // FUN_00626f80
            resetBuffer(0);                    // FUN_00626fd0
            setWritePosition(thisPtr, 0);      // FUN_00626f80
            pushBuffer(returnVal);             // FUN_00627010
            popBuffer();                       // FUN_006270e0
        }

        // Write marker (4) to output stream
        writePtr = reinterpret_cast<int32_t*>(thisPtr[2]);
        *writePtr = 4;
        // Copy temporary buffer contents to output
        returnVal = copyBuffer(thisPtr, tempBuffer, tempSize); // FUN_00638920
        writePtr[1] = returnVal;
        thisPtr[2] = reinterpret_cast<int32_t>(writePtr + 2);

        tempEnd = tempBuffer;
        pairCount++;
    }

    finalize(); // FUN_00626460
    return 1;   // success
}