// FUNC_NAME: MathUtils::lerpWithClamp
void __thiscall MathUtils::lerpWithClamp(float *result, float target, float current, float deltaTime)
{
    // param_1 = result pointer (in_EAX)
    // param_2 = deltaTime (from XMM0)
    // target = in_XMM0_Da / deltaTime (actually the input target value)
    // current = param_1 (the current value)
    
    float t = target / deltaTime;  // param_2 = in_XMM0_Da / param_2
    *result = t;
    
    if ((int)current < 2) {  // param_1 < 2
        t = 0.0f;
        result[2] = 0.0f;  // +0x8
    }
    else {
        if (t < 0.0f) {
            result[1] = 0.0f;  // +0x4
            result[2] = 1.4013e-45f;  // +0x8, denormalized float
            *result = 0.0f;
            result[3] = t;  // +0xC
            *(bool *)(result + 4) = (int)result[2] < (int)result[1];  // +0x10
            return;
        }
        
        float maxVal = (float)((int)current - 1);  // fVar2 = (float)(param_1 + -1)
        if (t <= maxVal) {
            float floorT = (float)(int)t;  // fVar1 = (float)(int)param_2
            maxVal = (float)((int)floorT + 1);  // fVar2 = (float)((int)fVar1 + 1)
        }
        else {
            float floorT = (float)((int)current - 2);  // fVar1 = (float)(param_1 + -2)
            *result = (float)(int)maxVal;  // *in_EAX = (float)(int)fVar2
        }
        t = t - (float)(int)floorT;  // param_2 = param_2 - (float)(int)fVar1
        result[2] = maxVal;  // +0x8
    }
    
    result[1] = floorT;  // +0x4
    result[3] = t;  // +0xC
    *(bool *)(result + 4) = (int)result[2] < (int)floorT;  // +0x10
}