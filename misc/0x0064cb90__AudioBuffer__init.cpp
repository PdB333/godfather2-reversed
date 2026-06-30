// FUNC_NAME: AudioBuffer::init
int __fastcall AudioBuffer::init(int resourceId) {
    int result;
    int local_4;  // size read from stream

    // Load stream data into internal buffer at offset 0x138
    result = readStream(resourceId, &this->mInternalBuffer[0], &local_4);

    // Free any previously dynamically allocated buffer
    if (this->mAllocated) {
        this->mAllocated = false;
        free(this->mBuffer);
    }

    // Set up buffer metadata (use internal buffer)
    this->mSize = local_4;                     // +0x10: number of samples or frames
    this->mBuffer = &this->mInternalBuffer[0]; // +0x0c: pointer to data (internal)
    this->mStride = local_4 * 8;               // +0x2c: total byte size (samples * bytes per sample?)
    this->field_30 = 0;                        // +0x30
    this->field_18 = 0;                        // +0x18
    this->field_1c = 0;                        // +0x1c
    this->field_1d = 0;                        // +0x1d
    this->field_38 = 0;                        // +0x38
    this->field_34 = 0;                        // +0x34

    return result;
}