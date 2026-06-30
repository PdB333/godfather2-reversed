// FUNC_NAME: GameConnection::unpackPlayerInput
void __thiscall GameConnection::unpackPlayerInput(GameConnection* this, int unused, BitStream* bitStream)
{
    char oldFlag1;
    char oldFlag2;
    uint bitPos;
    byte bitMask;
    uint newBitPos;
    bool bitValue;
    bool secondBitValue;
    int inputStatePtr;
    byte* dataPtr;
    uint totalBits;
    // Defined as stack variables for temporary storage
    undefined4 inputTransform[4];
    undefined4 matrix[8];  // Actually used as 4-element? The decompiled stack is large, but we'll simplify.
    // The exact stack layout is unclear; we'll approximate.

    // Allocate input state if needed
    if (this->inputState == 0) {
        inputStatePtr = createInputState();  // FUN_009c8f80() returns something; we assume it's a function that creates an object
        // The actual allocation call: (**(code**)*puVar4)(0x70, &local_9c) where local_9c is a descriptor {2, 0x10, 0}
        // We'll assume a custom allocator.
        if (inputStatePtr != 0) {
            // Initialize the allocated block at offset 0x60-0x64
            *(byte*)(inputStatePtr + 0x60) = 0;
            *(byte*)(inputStatePtr + 0x61) = 0;
            *(byte*)(inputStatePtr + 0x62) = 0;
            *(byte*)(inputStatePtr + 0x63) = 0;
            *(byte*)(inputStatePtr + 0x64) = 1;
        }
        this->inputState = inputStatePtr;
    }

    // --- Read first flag (bit 0) ---
    bitPos = bitStream->currentBitPos;
    totalBits = bitStream->totalBits;
    if (totalBits < bitPos) {
        bitStream->errorFlag = 1;
    } else {
        dataPtr = bitStream->data;
        bitMask = dataPtr[bitPos >> 3];
        newBitPos = bitPos + 1;
        bitStream->currentBitPos = newBitPos;
        if ((bitMask & (1 << (bitPos & 7))) != 0) {
            oldFlag1 = *(char*)(this->inputState + 0x62);
            if (totalBits < newBitPos) {
                bitStream->errorFlag = 1;
                bitValue = false;
            } else {
                bitValue = (dataPtr[newBitPos >> 3] & (1 << (newBitPos & 7))) != 0;
                bitStream->currentBitPos = bitPos + 2;
            }
            // Store the second bit as the new value for this flag
            *(bool*)(this->inputState + 0x62) = bitValue;
            if (bitValue == false && oldFlag1 != '\0') {
                // Falling edge: reset action flags (or something)
                *(byte*)(this->inputState + 0x60) = 0;
                *(byte*)(this->inputState + 0x61) = 0;
            }
        }
    }

    // --- Read second flag (bit 1) ---
    bitPos = bitStream->currentBitPos;
    totalBits = bitStream->totalBits;
    if (totalBits < bitPos) {
        bitStream->errorFlag = 1;
    } else {
        dataPtr = bitStream->data;
        bitMask = dataPtr[bitPos >> 3];
        newBitPos = bitPos + 1;
        bitStream->currentBitPos = newBitPos;
        if ((bitMask & (1 << (bitPos & 7))) != 0) {
            oldFlag2 = *(char*)(this->inputState + 0x63);
            if (totalBits < newBitPos) {
                bitStream->errorFlag = 1;
                bitValue = false;
            } else {
                bitValue = (dataPtr[newBitPos >> 3] & (1 << (newBitPos & 7))) != 0;
                bitStream->currentBitPos = bitPos + 2;
            }
            *(bool*)(this->inputState + 0x63) = bitValue;
            if (bitValue == false && oldFlag2 != '\0') {
                *(byte*)(this->inputState + 0x60) = 0;
                *(byte*)(this->inputState + 0x61) = 0;
            }
        }
    }

    // --- Read optional third flag (bit 2) ---
    bitPos = bitStream->currentBitPos;
    totalBits = bitStream->totalBits;
    if (totalBits < bitPos) {
        bitStream->errorFlag = 1;
        return;
    }
    dataPtr = bitStream->data;
    bitMask = dataPtr[bitPos >> 3];
    bitStream->currentBitPos = bitPos + 1;
    if ((bitMask & (1 << (bitPos & 7))) != 0) {
        // Read a transform/vector from the bitstream
        readTransformFromBitStream(bitStream, inputTransform);  // FUN_004a97b0 (assumed signature)
        // Allocate or initialize a matrix (size 0x20? actually 32 bytes)
        allocateMatrix(0x20, matrix);  // FUN_0064b9e0 (assumed)
        // Check if we have a local player controller (or something)
        if (this->localPlayer != 0 && (*(uint*)(this->localPlayer + 0x30) & 2) != 0) {
            // Copy the input transform into a new buffer with adjustments
            // This looks like a manual copy of 4-vector elements
            undefined4 temp[8];
            // The decompiled code copies many variables; we simplify to a memcpy-like operation
            temp[0] = inputTransform[0];
            temp[1] = inputTransform[1];
            temp[2] = inputTransform[2];
            temp[3] = inputTransform[3];
            // More assignments (the code shows interleaved copies)
            // For brevity, we'll assume it's copying the transform into a structure compatible with applyTransform
            // Then call applyTransform with the temp buffer, a global constant, and the matrix.
            applyTransform(temp, DAT_01205224, matrix);  // FUN_0046d8c0
        }
    }
    return;
}