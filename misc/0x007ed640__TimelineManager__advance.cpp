// FUNC_NAME: TimelineManager::advance
void __thiscall TimelineManager::advance(int thisPtr, int* message) {
    // +0x14: pointer to TimelineData (contains list head and count)
    // +0x1c: currentTime (float)
    // +0x20: lastTimestamp (int64 low)
    // +0x28: lastTimestamp (int64 high)
    // +0x30: lastTimestamp fractional part?

    if (*message == DAT_012067cc) {
        // Handle message type: play/start
        FUN_007ed070(message[1], 0, 0);
        return;
    }
    if (*message != DAT_0112db7c) {
        return;
    }

    // Message type: update/advance
    if (*(int*)(*(int*)(thisPtr + 0x14) + 0x1c) == 0) {
        // No events in timeline
        *(int*)(thisPtr + 0x1c) = 0;
        *(int*)(thisPtr + 0x20) = -1;
        return;
    }

    // Get current timestamp
    int timestampParts[4]; // local_30, local_28, iStack_24, iStack_2c
    FUN_00826510(timestampParts);

    float deltaTime = 0.0f;
    if (*(int*)(thisPtr + 0x20) != -1) {
        // Previous timestamp stored
        int prevLow = *(int*)(thisPtr + 0x20);
        int prevHigh = *(int*)(thisPtr + 0x28);
        int prevFrac = *(int*)(thisPtr + 0x30);

        // Compute elapsed time (complex timestamp arithmetic)
        int curLow = timestampParts[0];
        int curHigh = timestampParts[1];
        int curFrac = timestampParts[2]; // Actually local_20 is separate

        // Reconstruct previous time as float
        float prevTime = (float)(prevHigh + (prevLow + prevFrac * 0x18) * 0x3c) +
                         (float)prevFrac * DAT_00e446b4;
        float curTime = (float)(curHigh + (curLow + curFrac * 0x18) * 0x3c) +
                        (float)curFrac * DAT_00e446b4;
        deltaTime = curTime - prevTime;
        if (deltaTime < 0.0f) {
            deltaTime = _DAT_00d6ffb4 - deltaTime; // Wrap around?
        }

        // Store current timestamp
        *(int*)(thisPtr + 0x20) = curLow;
        *(int*)(thisPtr + 0x28) = curHigh;
        *(int*)(thisPtr + 0x30) = curFrac;

        if (deltaTime <= 0.0f && *(int*)(thisPtr + 0x20) != -1) {
            goto LAB_007ed765;
        }
    } else {
        // First update: store current timestamp
        *(int*)(thisPtr + 0x20) = timestampParts[0];
        *(int*)(thisPtr + 0x28) = timestampParts[1];
        *(int*)(thisPtr + 0x30) = timestampParts[2];
    }

LAB_007ed765:
    // Accumulate delta time
    *(float*)(thisPtr + 0x1c) += deltaTime;

    // Process events in timeline list
    int eventCount = *(int*)(*(int*)(thisPtr + 0x14) + 0x1c);
    while (eventCount != 0) {
        int* listHead = *(int**)(*(int*)(thisPtr + 0x14) + 0x18);
        int* eventNode = (int*)*listHead;
        if (eventNode == listHead) {
            FUN_00b97aea(); // List empty? Assert?
        }

        float eventDuration = (float)eventNode[3];
        if (*(float*)(thisPtr + 0x1c) < eventDuration) {
            break; // Not enough time for next event
        }

        // Subtract event duration from accumulated time
        *(float*)(thisPtr + 0x1c) -= eventDuration;

        // Prepare to trigger event
        int* eventData = eventNode + 2; // +8 bytes offset
        // Setup callback context
        int callbackContext[8]; // local_4c
        // Initialize callback context
        callbackContext[0] = (int)&PTR_FUN_00d6ffac; // Some vtable?
        callbackContext[1] = 0;
        callbackContext[2] = 0;
        callbackContext[3] = 0;
        callbackContext[4] = 0;

        // Trigger event function
        FUN_007ec360(eventData);

        // Mark event as triggered
        eventNode[8] |= 1;

        // Notify timeline data about event
        FUN_007ecef0(callbackContext, *(int*)(thisPtr + 0x14),
                     **(int**)(*(int*)(thisPtr + 0x14) + 0x18));

        // Handle string/object operations
        int stringObj[2]; // local_44, local_3c
        stringObj[0] = callbackContext[1]; // local_10
        stringObj[1] = callbackContext[2]; // local_14
        // Clear some flag
        stringObj[1] &= 0xffffff00;

        if (callbackContext[3] == 0) { // local_8
            FUN_00408a00(stringObj, 0);
        } else {
            FUN_00408bf0(stringObj, callbackContext[3]);
        }

        // Cleanup callback context
        callbackContext[0] = (int)&PTR_FUN_00d6ffac;
        while (callbackContext[2] != 0) { // local_a
            FUN_00408090();
        }

        // Release if needed
        if (callbackContext[1] != 0 && (callbackContext[4] & 1) == 0) {
            (**(code**)*callbackContext[1])(1);
        }

        eventCount = *(int*)(*(int*)(thisPtr + 0x14) + 0x1c);
    }
    return;
}