// FUNC_NAME: MotorComponent::updateTarget
void __thiscall MotorComponent::updateTarget(void* this) {
    int mode = *(int*)((char*)this + 0xc4); // +0xC4: mode (0 = position, 1 = rotation)
    float currentVal = *(float*)((char*)this + 200); // +0xC8: current value (e.g., motor position)
    
    if (mode == 0) {
        // Position target from source A
        void* source = FUN_0084b430(*(void**)((char*)this + 0x38)); // +0x38: source handle
        if (source != NULL) {
            float targetVal = *(float*)((char*)source + 4); // +4: target position
            float delta = targetVal - currentVal;
            if (delta != 0.0f) {
                *(float*)((char*)this + 200) = targetVal;
                FUN_008c7800(*(void**)((char*)this + 0x40), this, delta); // +0x40: motor output component
            }
        }
    }
    else if (mode == 1) {
        // Rotation target from source B
        void* source = FUN_0084b400(*(void**)((char*)this + 0x38));
        if (source != NULL) {
            float targetVal = *(float*)((char*)source + 8); // +8: target angle
            float delta = targetVal - currentVal;
            if (delta != 0.0f) {
                *(float*)((char*)this + 200) = targetVal;
                FUN_008c7800(*(void**)((char*)this + 0x40), this, delta);
            }
        }
    }
}