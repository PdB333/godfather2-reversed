// FUNC_NAME: CommandQueueManager::processNextCommand

// Function address: 0x00469230
// Role: Processes the next command from a command queue, interprets type 3 (object lookup by index) and type 4 (conditional object lookup),
//       retrieves three floats from the object's vtable call, stores them in a global result buffer, and pushes a type 2 command with a pointer to that buffer.

#include <cstdint>

// Global data structures (offsets based on usage)
// gObjectList: pointer to array of object pointers; gObjectList+0x04 = base, gObjectList+0x0C = count
// gResultData: stores three floats at offsets +0x14, +0x18, +0x1C

extern uint8_t gObjectList;  // DAT_012233a0
extern uint8_t gResultData;  // DAT_01223474

// Forward declaration
int __fastcall FUN_00636850(int a); // Presumably checks some condition

int CommandQueueManager::processNextCommand(int thisPtr)
{
    int* currentPtr;
    int tempVar;
    int* commandPtr;
    uint32_t index;
    float* resultPtr;
    float floatVal;
    int commandStack[2]; // temporary command for conditional path

    currentPtr = thisPtr;
    resultPtr = (float*)(&gResultData + 0x14); // offset +0x14
    int** queueEndPtr = *(int***)(thisPtr + 0x8); // queue end pointer? (write position)
    int* queueHeadPtr = *(int**)(thisPtr + 0xC);  // queue read position

    // If queue is empty or read position >= write position, go to default push
    if (queueHeadPtr >= queueEndPtr || queueHeadPtr == nullptr)
        goto pushDefault;

    // Check command type at current head
    if (*queueHeadPtr != 3)
    {
        if (*queueHeadPtr != 4)
            goto pushDefault;

        // Type 4: additional condition check via external function
        tempVar = FUN_00636850(&thisPtr);
        if (tempVar == 0)
            goto pushDefault;
    }

    // Re-read current pointer (could have changed after check? but unchanged in this path)
    commandPtr = *(int**)(thisPtr + 0xC);
    if (commandPtr >= *(int**)(thisPtr + 0x8) || commandPtr == nullptr)
        goto readFloatZero;

    if (*commandPtr != 3)
    {
        if (*commandPtr == 4)
        {
            tempVar = FUN_00636850(&thisPtr);
            if (tempVar != 0)
            {
                // Type 4 passes condition: create a temporary type-3 command using the current address as data
                commandStack[0] = 3;          // type = 3
                commandStack[1] = thisPtr;    // data = this (used as float index)
                commandPtr = commandStack;    // point to temporary command
                goto readFloat;
            }
        }
        goto readFloatZero;
    }

readFloat:
    floatVal = *(float*)(commandPtr + 1); // Index as float

readFloatZero:
    floatVal = 0.0f;

    index = (uint32_t)floatVal;

    // Validate index against gObjectList array
    if ((int)index >= 0 && index < *(uint32_t*)(&gObjectList + 0xC))
    {
        int** objectArray = *(int***)(&gObjectList + 0x4);
        int* object = objectArray[index];
        if (object != nullptr)
        {
            // Call virtual function at offset 0xC (likely returns some object with data at +0x100)
            int (__thiscall *vfunc)(int*) = *(int (__thiscall**)(int*))(*(int*)object + 0xC);
            int resultObj = vfunc(object);
            if (resultObj != 0)
            {
                // Copy three floats from resultObj+0x100 to gResultData buffer
                *resultPtr = *(float*)(resultObj + 0x100);
                *(float*)(&gResultData + 0x18) = *(float*)(resultObj + 0x104);
                *(float*)(&gResultData + 0x1C) = *(float*)(resultObj + 0x108);

                // Push a new type 2 command with pointer to the result buffer
                float** writePos = *(float***)(thisPtr + 0x8);
                writePos[1] = resultPtr;
                *(int*)writePos = 2; // type 2
                *(int*)(thisPtr + 0x8) += 8; // advance write pointer by 2 ints

                return 1;
            }
        }
    }

pushDefault:
    // Default: push a null command (type 0)
    **(int**)(thisPtr + 0x8) = 0;
    *(int*)(thisPtr + 0x8) += 8;
    return 1;
}