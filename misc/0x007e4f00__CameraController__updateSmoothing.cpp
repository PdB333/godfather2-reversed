// FUNC_NAME: CameraController::updateSmoothing
void __fastcall CameraController::updateSmoothing(CameraController* thisPtr) 
{
    // +0x58: pointer to camera data block
    CameraData* cameraData = *(CameraData**)((char*)thisPtr + 0x58);
    if (cameraData == nullptr) {
        return;
    }

    // Get desired rotation from virtual function at vtable+0xa4
    // Returns a Euler angle vector (pitch, yaw, roll?) stored in local vars
    float desiredPitch, desiredYaw, desiredRoll; // stack order: fStack_20(-0x20), fStack_1c(-0x1c), local_18(-0x18)
    (*(code**)(*(int*)cameraData + 0xa4))(&desiredYaw, (char*)cameraData + 0x1c0); // actually unknown order

    // Current rotation stored as floats in array-like fields
    // +0x23c: current pitch? +0x23d: current yaw? +0x23e: current roll?
    float currentPitch = *(float*)((char*)cameraData + 0x23c);
    float currentYaw   = *(float*)((char*)cameraData + 0x23d);
    float currentRoll  = *(float*)((char*)cameraData + 0x23e);

    // Differences: current - desired
    float deltaPitch = currentPitch - desiredPitch; // fStack_14
    float deltaYaw   = currentYaw   - desiredYaw;   // dVar5
    float deltaRoll  = currentRoll  - desiredRoll;   // fStack_c

    // Get some player/object rotation limit
    void* playerObj = (void*)FUN_00471610(); // returns a pointer with rotation speed?
    float rotationLimit = *(float*)((char*)playerObj + 0x20); // e.g., max rotation step

    // Normalize angle difference (atan2-like)
    float normalizedDeltaYaw = (float)FUN_004a1580(deltaPitch - rotationLimit); // horizontal? actually deltaPitch - rotationLimit

    // Apply vertical component? 
    FUN_007ac5d0(deltaYaw); // maybe applyPitch

    // Handle time-based smoothing
    // iStack_4 is likely current timestamp from a hidden call, e.g., GetTickCount()
    uint currentTime = (uint) /* some time function, not captured by decompiler */; 
    uint lastTime = *(uint*)((char*)thisPtr + 0x260);
    uint timeDelta = currentTime - lastTime;

    if (timeDelta > 149 && timeDelta < 250) {
        // Interpolate towards target with a factor
        float baseFactor = *(float*)((char*)cameraData + 0xa29); // some stored factor at +0xa29
        float smoothingFactor = baseFactor + (normalizedDeltaYaw - baseFactor) * _DAT_00d6fa58; // likely a global deltaTime factor
        normalizedDeltaYaw = smoothingFactor;
    }

    FUN_007ac5b0(normalizedDeltaYaw); // applyYaw with smoothed value
    FUN_007ac7d0(); // finalize rotation update
}