// FUNC_NAME: StreamCipher::processData

void StreamCipher::processData(unsigned char* input, unsigned char* output, int length)
{
    // Copy key material from this+0x6c (129 dwords = 516 bytes) to local buffer
    unsigned int keyCopy[129]; // +0x6c: key material (4*129 bytes)
    unsigned int* src = reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0x6c);
    for (int i = 0; i < 129; ++i)
    {
        keyCopy[i] = src[i];
    }

    // Process each byte
    while (length > 0)
    {
        // When state index reaches 16, scramble the state and reset index
        if (this->stateIndex == 16) // stateIndex at offset 0x270
        {
            this->scrambleState(this->state, this->state, keyCopy); // state at offset 0x5c (16 bytes)
            this->stateIndex = 0;
        }

        // XOR input with current state byte; output and update state
        unsigned char temp = this->state[this->stateIndex] ^ *input;
        *output = temp;
        this->state[this->stateIndex] = temp; // replace state byte with ciphertext
        ++this->stateIndex;
        ++input;
        ++output;
        --length;
    }
}