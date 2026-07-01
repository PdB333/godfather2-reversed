// FUNC_NAME: ChaseCamera::updateTargetFromVehicle

void __thiscall ChaseCamera::updateTargetFromVehicle(int this)
{
    char isActive;
    int vehiclePtr;

    isActive = isGameActive();
    if (isActive != 0) {
        vehiclePtr = getPlayerVehicle();
        if ((vehiclePtr != 0) && (gCameraSmoothTime < *(float *)(vehiclePtr + 0x4a4))) {
            // Copy vehicle's world transform (position + orientation) to camera target
            // +0x4a0: vehicle position x, +0x4a4: position y, +0x4a8: position z, +0x4ac: orientation w (or similar)
            *(float *)(this + 0x2d30) = *(float *)(vehiclePtr + 0x4a0);
            *(float *)(this + 0x2d34) = *(float *)(vehiclePtr + 0x4a4);
            *(float *)(this + 0x2d38) = *(float *)(vehiclePtr + 0x4a8);
            *(float *)(this + 0x2d3c) = *(float *)(vehiclePtr + 0x4ac);
            updateCamera();
            setCameraTarget(*(int *)(this + 0x2494), this + 0x2d10, 0);
        }
    }
}