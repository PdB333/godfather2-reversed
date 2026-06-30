// FUNC_NAME: InputSystem::recordRawInput
void __fastcall InputSystem::recordRawInput(uint inputMask, const float* translation, const float* rotation, float posX, float posY)
{
    // inputMask is passed in EAX from caller, contains bit flags
    // translation is a 4-element vector (likely position/translation)
    // rotation is a 4-element quaternion or matrix row
    // posX, posY are likely cursor/joystick coordinates

    if ((inputMask & 1) != 0) {
        // Bit 0 set: ignore the input, possibly clear current state
        InputSystem::clearInput(posX, posY, 0);
        return;
    }

    // Update max recorded coordinates (bounds tracking)
    if (gInputMaxX < posX) {
        gInputMaxX = posX;
    }
    if (gInputMaxY < posY) {
        gInputMaxY = posY;
    }

    // Copy rotation quaternion/vector into persistent storage (4 floats)
    gInputRotation[0] = rotation[0];
    gInputRotation[1] = rotation[1];
    gInputRotation[2] = rotation[2];
    gInputRotation[3] = rotation[3];

    // Copy translation vector (4 floats)
    gInputTranslation[0] = translation[0];
    gInputTranslation[1] = translation[1];
    gInputTranslation[2] = translation[2];
    gInputTranslation[3] = translation[3];

    // Accumulate input mask (set bits)
    gInputMask |= inputMask;

    // Increment frame counter by a global delta (likely time step)
    gInputFrameCount += gInputFrameDelta;
}