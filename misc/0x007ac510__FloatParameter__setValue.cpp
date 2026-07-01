// FUNC_NAME: FloatParameter::setValue
void __thiscall FloatParameter::setValue(float newValue) {
    // +0x04: current float value; +0x64 (100): dirty flag (byte)
    if (newValue != *(float *)(this + 4)) {
        *(unsigned char *)(this + 100) = 1;
        *(float *)(this + 4) = newValue;
    }
}