// FUNC_NAME: Vehicle::updateSpeed

float Vehicle::updateSpeed(void* inputData) {
    float currentSpeed = *(float*)((int)this + 0x140);
    int* activeFlag = (int*)((int)inputData + 0xAA0);
    
    if (inputData != 0) {
        int param = 0;
        if (*activeFlag != 0) {
            float time = FUN_00549a00();
            if (time <= *(float*)0x00e44598) {
                param = 0;
            } else {
                param = 0;
            }
        }
        
        float newSpeed = (float)FUN_004b9c30(
            param,
            *(undefined4*)((int)this + 0x140),
            *(float*)0x00d5eee0
        );
        *(float*)((int)this + 0x140) = newSpeed;
        
        if (newSpeed > 1.0f) {
            *(float*)((int)this + 0x140) = *(float*)0x00d5780c;
            return *(float*)((int)this + 0x140);
        }
        if (newSpeed < 0.0f) {
            *(float*)((int)this + 0x140) = 0.0f;
        }
    }
    
    return *(float*)((int)this + 0x140);
}