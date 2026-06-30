// FUNC_NAME: SimNpc::handleMessage
void __thiscall SimNpc::handleMessage(int thisPtr, EARSMessage* msg) {
    // Get message type hash (first virtual function returns hash)
    uint32 msgHash = msg->getType();

    if (msgHash < 0x6d994274) {
        if (msgHash != 0x6d994273) {
            if (msgHash == 0x27a0f69c) {
                // State check: if state is idle or dead, ignore
                if (*(int*)(thisPtr + 0x78) == 0 || *(int*)(thisPtr + 0x78) == 0x48) {
                    return;
                }
                // Get current transform (rotation + position)
                int transformPtr = getWorldTransform(); // FUN_00471610
                float rotZ = *(float*)(transformPtr + 0x38);
                uint64 rotXY = *(uint64*)(transformPtr + 0x30);
                transformPtr = getWorldTransform();
                float posZ = *(float*)(transformPtr + 0x28);
                uint64 posXY = *(uint64*)(transformPtr + 0x20);
                transformPtr = getWorldTransform();
                uint64 targetRotXY = *(uint64*)(transformPtr + 0x30);
                float targetRotZ = *(float*)(transformPtr + 0x38);

                // Split 64-bit values into float components
                float vx = (float)(posXY & 0xFFFFFFFF);
                float vy = (float)(posXY >> 32);
                float vz = posZ;
                float tx = (float)(rotXY & 0xFFFFFFFF);
                float ty = (float)(rotXY >> 32);
                float tz = rotZ;
                float targetX = (float)(targetRotXY & 0xFFFFFFFF);
                float targetY = (float)(targetRotXY >> 32);
                float targetZ = targetRotZ;

                // Check if distance/angle is within threshold
                if (vy * (ty - targetY) + vx * (tx - targetX) + vz * (tz - targetZ) <= gThreshold) {
                    // Adjust target by offset
                    vx = gOffsetX - vx;
                    vy = gOffsetY - vy;
                    vz = gOffsetZ - vz;
                }
                // Set animation or movement
                setAnimation(thisPtr + 0x8c, &vx, 0, gPriority, 0, 1); // FUN_00754d30
                return;
            }
            if (msgHash == 0x6862a74c) {
                // State machine setup
                initStateMachine(); // FUN_0075cd50
                int subPtr = *(int*)(thisPtr + 0x5c);
                uint64 callback1 = concatAddress(FUN_007347e0, subPtr);
                // Set up first callback
                setCallback1(callback1, 0.0f, (uint64)&label_0073b090); // FUN_0073ad80
                callback1 = concatAddress(FUN_00716160, subPtr + 0x2194);
                setCallback2(callback1, 0.0f, (uint64)&label_0073b0a0); // FUN_0073adb0
                uint64 callback3 = concatAddress(FUN_0073b340, thisPtr);
                setCallback3(callback3, 0, 0x73b0b000000000); // FUN_0073ade0
                return;
            }
            // Default handler
            defaultHandler(); // FUN_0073e4d0
            return;
        }
        // Hash 0x6d994273: write back state and transform
        msg->value1 = *(uint64*)(thisPtr + 0x8c);
        msg->value2 = *(int*)(thisPtr + 0x94);
        float factor;
        if (*(int*)(thisPtr + 0x78) == 0 || *(int*)(thisPtr + 0x78) == 0x48) {
            factor = 0.0f;
        } else {
            int speedPtr = getSpeedInfo(); // FUN_0043b870
            factor = *(float*)(speedPtr + 0x28) * gSpeedScale;
        }
        msg->value3 = factor * factor;
    } else if (msgHash != 0x923adb9e) {
        if (msgHash == 0xc5459866) {
            handleCrowdEvent(); // FUN_0073b180
            return;
        }
        if (msgHash == 0xe4b1f57a) {
            handleFleeEvent(); // FUN_0073b140
            return;
        }
        defaultHandler();
        return;
    }
    // Default case for hash 0x923adb9e (and possibly 0x6d994274 if not caught above)
    uint64 callback = concatAddress(FUN_0073b340, thisPtr);
    msg->callback = callback;
    msg->otherData = 0;
    msg->moreData = 0x73b0b000000000;
}