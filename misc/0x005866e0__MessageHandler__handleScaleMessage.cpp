// FUNC_NAME: MessageHandler::handleScaleMessage
// Function at 0x005866e0
// Processes a message with type byte 0x02: scales a 4-component float array (e.g., quaternion or vector) from message offset +0x8,
// stores the scaled result in an internal buffer pointed by this+0x8, and overrides the fourth component with a global constant.

void MessageHandler::handleScaleMessage(int thisPtr, int* messageBuffer, float scaleFactor)
{
    // Check message type byte (first byte of the buffer)
    if (*(char*)messageBuffer == 0x02)
    {
        // Call a time/scale‑related update function (address 0x582bf0)
        updateTimeStep(scaleFactor);

        // Read pointer to target float array from object at offset +0x8
        float* targetArray = *(float**)(thisPtr + 8);

        // The source float array is referenced by a pointer stored at messageBuffer offset +0x8 (third uint32)
        float* sourceArray = (float*)messageBuffer[2]; // messageBuffer[2] = *(uint32*)(messageBuffer+8)

        // Scale each component
        targetArray[0] = scaleFactor * sourceArray[0];
        targetArray[1] = scaleFactor * sourceArray[1];
        targetArray[2] = scaleFactor * sourceArray[2];
        targetArray[3] = scaleFactor * sourceArray[3];

        // Override the fourth component with a global constant (e.g., identity w=1.0 or fixed alpha)
        targetArray[3] = DAT_00e2b1a4;
    }
}