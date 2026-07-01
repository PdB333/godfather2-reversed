// FUNC_NAME: TweenController::updateTween
void __thiscall TweenController::updateTween(int this, float deltaTime, int tweenType)
{
    float clampMin;
    float clampMax;
    float newValue;
    float clampedValue;

    clampMin = DAT_00d777d0; // global min clamp value
    clampMax = DAT_00d777cc; // global max clamp value

    switch(tweenType) {
    case 0: // POSITION_X
    case 2: // SCALE_X
    case 4: // ROTATION_Z
        newValue = *(float *)(this + 4) + deltaTime; // +0x04 currentValue
        clampedValue = clampMin;
        if ((clampMin < newValue) && (clampedValue = newValue, clampMax <= newValue)) {
            clampedValue = clampMax;
        }
        *(float *)(this + 4) = clampedValue;
        break;
    default:
        goto end;
    case 6: // OPACITY
    case 10: // UNUSED_10
        newValue = *(float *)(this + 0xc) + deltaTime; // +0x0C anotherValue
        if (clampMin < newValue) {
            if (clampMax <= newValue) {
                newValue = clampMax;
            }
            *(float *)(this + 0xc) = newValue;
        }
        else {
            *(float *)(this + 0xc) = clampMin;
        }
    }

    newValue = *(float *)(this + 0x10) + deltaTime; // +0x10 thirdValue
    if ((clampMin < newValue) && (clampMin = newValue, clampMax <= newValue)) {
        clampMin = clampMax;
    }
    *(float *)(this + 0x10) = clampMin; // +0x10 update

    // Update array of tweens at offset +0x14
    *(float *)(this + 0x14 + tweenType * 4) = *(float *)(this + 0x14 + tweenType * 4) + deltaTime;

    FUN_0093b0e0(); // likely a post-update notification

end:
    return;
}