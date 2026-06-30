// FUNC_NAME: AIActionProcessor::processActions
// Function at 0x005f2280, processes a queue of 8-byte action records.
// Returns 0 if state becomes 5 (stopped), 1 otherwise.
// Uses global float constants _DAT_00e2e210 and _DAT_00e4463c.

extern float _DAT_00e2e210; // multiplier for ushort action value
extern float _DAT_00e4463c; // multiplier for int action parameter

// Forward declarations for helper functions (likely same class or engine functions)
void refreshActionList(); // 0x005f2fd0
void debugLog(byte b1, int i2, byte b3, byte b4, byte b5); // 0x005dbc10 overload
void debugLog(ushort u1, byte b2); // 0x005dbc10 overload
void handleActionCase1(); // 0x005f1860
void handleActionCase2(); // 0x005f18d0
void handleActionCase3(); // 0x005f1bc0
void handleEndOfList(); // 0x005f2150

uint AIActionProcessor::processActions(float deltaTime)
{
    // Current state at +0x68
    uint state = *(uint *)(this + 0x68);
    if (state == 4) {
        return 1; // active but return immediately
    }
    if (state == 5) {
        return 0; // completely stopped
    }

    // Ensure the action list is ready
    refreshActionList();

    // Pointer to current action record (+0x8c) and end boundary (+0x88)
    uint currentRecordPtr = *(uint *)(this + 0x8c);
    uint endRecordPtr = *(uint *)(this + 0x88);

    // Process all actions in the list
    if (currentRecordPtr < endRecordPtr) {
        do {
            // First 2 bytes of record: ushort value scaled by global
            float scaledValue = (float)*(ushort *)(currentRecordPtr) * _DAT_00e2e210;
            float currentTimer = *(float *)(this + 0x74);
            // If timer hasn't reached this threshold and threshold is different, advance timer
            if (currentTimer <= scaledValue && scaledValue != currentTimer) {
                *(float *)(this + 0x74) = currentTimer + deltaTime;
                return 1;
            }

            // Debug logging with various offsets (likely for telemetry)
            debugLog(*(byte *)(this + 100), *(int *)(this + 0x5c),
                     *(byte *)(this + 0x65), *(byte *)(*(int *)(this + 8) + 2),
                     *(byte *)(this + 0x66));
            debugLog(*(ushort *)(currentRecordPtr), *(byte *)(currentRecordPtr + 1));

            int recBase = currentRecordPtr; // may be used in switch
            switch (*(byte *)(currentRecordPtr + 2)) {
            case 1:
                handleActionCase1();
                break;
            case 2:
                handleActionCase2();
                break;
            case 3:
                handleActionCase3();
                break;
            case 4:
                // Set float at +0x54 from int parameter
                *(float *)(this + 0x54) = (float)*(int *)(currentRecordPtr + 4) * _DAT_00e4463c;
                debugLog(*(byte *)(this + 0x65));
                break;
            case 5:
                // Set float at +0x58 from int parameter (no scaling)
                *(float *)(this + 0x58) = (float)*(int *)(currentRecordPtr + 4);
                break;
            case 6:
                // Set float at +0x3c with scaling and set flag bit 1 at +0x4a
                {
                    float f = (float)*(int *)(currentRecordPtr + 4) * _DAT_00e4463c;
                    *(ushort *)(this + 0x4a) |= 2;
                    *(float *)(this + 0x3c) = f;
                    debugLog(*(byte *)(this + 100), *(int *)(this + 0x5c),
                             *(byte *)(this + 0x65));
                }
                break;
            }

            // Reset timer and advance to next record
            *(float *)(this + 0x74) = 0.0f;
            uint flags = *(ushort *)(this + 0x6c);
            if ((flags & 1) == 0) {
                currentRecordPtr += 8; // each record is 8 bytes
            } else {
                flags &= 0xfffe;
                *(ushort *)(this + 0x6c) = (ushort)flags;
            }
        } while (currentRecordPtr < endRecordPtr);
    }

    // After processing all records, handle end-of-list indicator
    if (*(char *)(this + 0x67) != -1) {
        handleEndOfList();
        *(byte *)(this + 0x67) = 0xff; // reset sentinel
        return (uint)(*(int *)(this + 0x68) != 5);
    }

    // Determine new state based on flags at +0x6c
    ushort flags = *(ushort *)(this + 0x6c);
    if ((flags & 0x78) == 0) {
        *(uint *)(this + 0x68) = 5; // stopped
    } else if ((flags & 0x100) == 0) {
        *(uint *)(this + 0x68) = 4; // paused/active
        return (uint)(*(int *)(this + 0x68) != 5);
    }
    return (uint)(*(int *)(this + 0x68) != 5);
}