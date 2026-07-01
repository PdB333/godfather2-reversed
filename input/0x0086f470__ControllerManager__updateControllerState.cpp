// FUNC_NAME: ControllerManager::updateControllerState
void __thiscall ControllerManager::updateControllerState(int this, int controllerIndex)
{
    char cVar1;
    char *pcVar2;
    double fVar3;
    int *piVar4;
    int local_4;

    // Check if controller is active or if input should be processed
    if (((*(uint *)(this + 0x6c) >> 1 & 1) != 0) ||
       ((((*(float *)(this + 0x98) < _DAT_00d75f64 &&
          (*(int *)(*(int *)(this + 0x5c) + 0xb74) == 0)) &&
         (((*(uint *)(*(int *)(this + 0x5c) + 0xa18) >> 4 & 1) != 0 ||
          ((~*(byte *)(DAT_0112af68 + 0x170) & 1) != 0)))) ||
        (local_4 = this, cVar1 = isInputEnabled(controllerIndex), cVar1 == '\0'))))
    {
        piVar4 = &local_4;
        local_4 = 0;
        // Virtual call to check if input device is active
        cVar1 = (**(code **)(**(int **)(*(int *)(this + 0x54) + 4) + 0x10))(0x10e5319e);
        if (((cVar1 != '\0') && (piVar4 != (int *)0x0)) && (resetInputState(local_4), piVar4[0x2a8] != 0))
        {
            // Read raw input values and apply to processed state
            fVar3 = getLeftStickX();
            setLeftStickX((float)fVar3);
            fVar3 = getLeftStickY();
            setLeftStickY((float)fVar3);
            fVar3 = getRightStickX();
            setRightStickX((float)fVar3);
            pcVar2 = (char *)getButtonA(&local_4);
            setButtonA(*pcVar2 != '\0');
            pcVar2 = (char *)getButtonB(&local_4);
            setButtonB(*pcVar2 != '\0');
        }
    }
    return;
}