// FUNC_NAME: UI2DTransform::setComponent
// Address: 0x005b6030
// Role: Sets a component of a 2D transform (position, scale, rotation) based on index.
// Offsets: +0x10 = scaleX? +0x24,0x28,0x2c = unknown, +0x38-0x44 = rotation matrix, +0x48 = posX, +0x4c = posY, +0x50 = pointer to parent/child transform data, +0x64 = dirty flag

extern float DAT_00e2e780;  // scale factor (pixels per unit?)
extern float DAT_00e44640;  // another scale factor
extern float DAT_00e445c8;  // degrees-to-radians conversion
extern float DAT_00e44564;  // translation offset (e.g., screen center)

void __thiscall UI2DTransform::setComponent(float value, uint8_t flag, int index)
{
    // Pre-update/validation call
    this->preUpdateTransform();

    // Set dirty flag at offset +0x64 (100 decimal)
    *(uint8_t *)(this + 0x64) = flag;

    // Store value into array at +0x50 (pointer to transform data) at index
    *(float *)(*(int *)(this + 0x50) + index * 4) = value;

    switch (index)
    {
    case 0:
        // Position X
        *(float *)(this + 0x48) = value;
        return;
    case 1:
        // Position Y
        *(float *)(this + 0x4c) = value;
        return;
    case 2:
    case 3:
    case 6:
        // Scale X, Scale Y, Rotation? - fall through to complex transform
        break;
    default:
        return;
    case 7:
        // Unknown component (scale X?)
        *(float *)(this + 0x10) = value * DAT_00e2e780;
        return;
    case 8:
        // Unknown component
        *(float *)(this + 0x24) = value * DAT_00e44640;
        return;
    case 9:
        // Unknown component
        *(float *)(this + 0x28) = value * DAT_00e44640;
        return;
    case 10:
        // Unknown component
        *(float *)(this + 0x2c) = value * DAT_00e44640;
        return;
    }

    // For indices 2,3,6: compute rotation/scale from parent transform data
    int transformData = *(int *)(this + 0x50);
    float scaleX = *(float *)(transformData + 8) * DAT_00e2e780;
    float scaleY = *(float *)(transformData + 0xc) * DAT_00e2e780;

    if (*(float *)(transformData + 0x18) == 0.0f)
    {
        // No rotation
        *(float *)(this + 0x38) = scaleX;
        *(uint32_t *)(this + 0x3c) = 0;
        *(uint32_t *)(this + 0x40) = 0;
        *(float *)(this + 0x44) = scaleY;
        return;
    }

    // Rotation angle (in degrees? converted to radians)
    float angleRad = *(float *)(transformData + 0x18) * DAT_00e445c8;
    float cosA = cosf(angleRad);
    float sinA = sinf(angleRad);

    // Set 2x2 rotation matrix (column-major?) at +0x38
    *(float *)(this + 0x38) = cosA * scaleX;
    *(float *)(this + 0x3c) = sinA * scaleX;
    *(float *)(this + 0x40) = DAT_00e44564 - sinA * scaleY;
    *(float *)(this + 0x44) = cosA * scaleY;
}