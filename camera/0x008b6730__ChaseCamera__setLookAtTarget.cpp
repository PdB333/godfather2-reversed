//FUNC_NAME: ChaseCamera::setLookAtTarget

void __thiscall ChaseCamera::setLookAtTarget(int *target)
{
    // +0x8c: pointer to LookAtData (0x1c bytes)
    LookAtData *data = this->lookAtData;

    // Free existing look-at data if present
    if (data != nullptr) {
        deallocate(data);
        this->lookAtData = nullptr;
    }

    // Allocate new 0x1c-byte block for look-at data
    LookAtData *newData = (LookAtData *)allocate(0x1c);
    if (newData != nullptr) {
        newData->field_0 = 0;
        newData->field_4 = 0;
        newData->magic1 = 0xbadbadba;
        newData->magic2 = 0xbeefbeef;
        newData->magic3 = 0xeac15a55;
        newData->magic4 = 0x91100911;
        newData->field_18 = 0;
    }
    this->lookAtData = newData;

    // If a target entity is provided, copy camera data from global camera manager
    if (target != nullptr) {
        int cameraData = getCameraData(g_cameraManager); // FUN_0043b870(DAT_01131018)
        this->lookAtData->field_0 = *(int *)(cameraData + 0x54);
        this->lookAtData->field_4 = *(int *)(cameraData + 0x6c);
    }

    // Zero out remaining fields
    LookAtData *lookAt = this->lookAtData;
    lookAt->field_8 = 0;
    lookAt->field_C = 0;
    lookAt->field_10 = 0;
    lookAt->field_14 = 0;
    lookAt->field_18 = 0;

    // Attempt to retrieve additional look-at info from the target via virtual method (hash 0x3fb43b57)
    int *lookAtInfo = nullptr;
    bool success = ((bool (__thiscall *)(int, int **))(*((int *)target)[4]))(0x3fb43b57, &lookAtInfo);
    if (success && lookAtInfo != nullptr) {
        lookAt->field_8  = *(int *)(lookAtInfo + 0x290 / 4); // offset 0x290
        lookAt->field_C  = *(int *)(lookAtInfo + 0x294 / 4); // offset 0x294
        lookAt->field_10 = *(int *)(lookAtInfo + 0x298 / 4); // offset 0x298
        lookAt->field_14 = *(int *)(lookAtInfo + 0x29c / 4); // offset 0x29c
        lookAt->field_18 = *(int *)(lookAtInfo + 0x2a0 / 4); // offset 0x2a0
    }
}