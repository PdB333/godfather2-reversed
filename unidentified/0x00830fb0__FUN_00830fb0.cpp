//FUNC_NAME: SomeClass::setFourValuesWithReciprocalSecond
void __thiscall SomeClass::setFourValuesWithReciprocalSecond(void* this, const float* input) {
    // Copy four floats from input to offsets 0x40, 0x44, 0x48, 0x4c
    *(float*)((char*)this + 0x40) = input[0];
    *(float*)((char*)this + 0x44) = input[1];
    *(float*)((char*)this + 0x48) = input[2];
    *(float*)((char*)this + 0x4c) = input[3];
    // Replace the second float with global_constant / input[1]
    // Global _DAT_00d5780c is likely a constant (e.g., 1.0f or 1000.0f)
    extern float _DAT_00d5780c;
    *(float*)((char*)this + 0x44) = _DAT_00d5780c / *(float*)((char*)this + 0x44);
}