// FUNC_NAME: CharacterController::updateMovement
// Address: 0x0075ded0
// Role: Updates character movement toward a target position, with scale and animation updates.
// Fields:
//   +0x90 (thisPtr[0x24]): function pointer for obtaining model handle (method A)
//   +0xA4 (thisPtr[0x29]): function pointer for obtaining model handle (method B, may override)
//   +0x58 (thisPtr[0x16]): pointer to animation/model object with vtable
//   +0xB0 (thisPtr[0x2c]): parameter passed to computeMoveScale

void __thiscall CharacterController::updateMovement(void* thisPtr, float deltaTime, float* targetPos)
{
    int* thisInt = (int*)thisPtr;
    int modelHandle;
    float10 moveScale;

    // Obtain model handle via either stored method
    if ((code*)thisInt[0x29] == nullptr) {
        modelHandle = ((code*)thisInt[0x24])();
    } else {
        modelHandle = ((code*)thisInt[0x29])(thisInt + 0x24);
    }

    // Cooldown check (likely 1000ms between debug prints)
    if (isCooldownElapsed(1000)) {
        debugPrintCharacter(0x20); // print space or debug symbol
    }

    // Validate model handle; if invalid, set its scale to (1,1)
    if (!isModelValid(modelHandle)) {
        (**(void (__thiscall**)(void*, int, int, int, float, float))(*thisInt + 0x2c))(
            (void*)modelHandle, 1, 1, 0, 1.0f, 1.0f);
    }

    // Compute movement magnitude from direction and target
    moveScale = (float10)computeMoveScale(thisInt[0x16], targetPos, thisInt[0x2c]);

    // Get global player/camera position (x at +0x30, z at +0x38)
    int playerPos = getPlayerPositionBase();
    float dz = *(float*)(playerPos + 0x38) - targetPos[2];
    float dx = *(float*)(playerPos + 0x30) - targetPos[0];

    // If squared distance from player exceeds global threshold, apply movement
    if (g_squareDistanceThreshold < dz * dz + dx * dx) {
        applyMovement(targetPos, (float)moveScale * deltaTime, 0);
    }

    // Call animation update on the model object (vtable offset 0x164)
    (*(void (__thiscall**)(void*))(*(int*)thisInt[0x16] + 0x164))((void*)thisInt[0x16]);
}