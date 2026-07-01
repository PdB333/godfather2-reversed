// FUNC_NAME: AudioBuffer::addConstantOffset
void __thiscall AudioBuffer::addConstantOffset(float *this, int bufferWithOffsetAndCount) {
    int count = *(int *)(bufferWithOffsetAndCount + 0x2c); // +0x2c: number of floats to process
    if (count != 0) {
        float offset = *(float *)bufferWithOffsetAndCount; // first float at buffer is the constant to add
        for (int i = 0; i < count; ++i) {
            this[i] += offset;
            FUN_0093b0e0(); // likely a yield / callback during processing
        }
    }
}