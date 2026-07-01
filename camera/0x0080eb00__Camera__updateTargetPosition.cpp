// FUNC_NAME: Camera::updateTargetPosition
// Address: 0x0080eb00
// Role: Updates camera target position with interpolation based on mode and threshold

void __thiscall Camera::updateTargetPosition(Camera *this, const InterpolationData *data)
{
    int mode;
    float t;
    float threshold;
    float resultX, resultY, resultZ;
    float *someGlobalPtr;

    // Copy interpolation data (4 pairs of int/float or float/float)
    // data[0]: (mode, startX)
    // data[1]: (startY, startZ)
    // data[2]: (dirX, dirY)
    // data[3]: (dirZ, threshold)
    *(uint64_t *)(this + 0x58) = *(uint64_t *)&data[0];
    *(uint64_t *)(this + 0x60) = *(uint64_t *)&data[1];
    *(uint64_t *)(this + 0x68) = *(uint64_t *)&data[2];
    *(uint64_t *)(this + 0x70) = *(uint64_t *)&data[3];

    // Determine interpolation factor based on mode
    t = 0.0f;
    mode = *(int *)(this + 0x58);
    if ((mode != 0) && (mode == 1)) {
        t = DAT_00d72dac; // Some global constant (e.g., 1.0f or interpolation speed)
    }

    threshold = *(float *)(this + 0x74);
    if (t <= threshold) {
        *(int *)(this + 0x78) = 0; // Flag: not exceeding threshold
        *(float *)(this + 0x7c) = t;
    } else {
        *(int *)(this + 0x78) = 1; // Flag: exceeding threshold
        *(float *)(this + 0x7c) = t;
    }

    // Linear interpolation: result = start + direction * t
    t = *(float *)(this + 0x7c);
    *(float *)(this + 0x80) = *(float *)(this + 0x68) * t + *(float *)(this + 0x5c); // resultX
    *(float *)(this + 0x84) = *(float *)(this + 0x6c) * t + *(float *)(this + 0x60); // resultY
    *(float *)(this + 0x88) = *(float *)(this + 0x70) * t + *(float *)(this + 0x64); // resultZ

    // Override Y with some global value (e.g., player height or camera target)
    someGlobalPtr = (float *)FUN_00471610(); // Returns pointer to some structure
    *(float *)(this + 0x84) = *(float *)(someGlobalPtr + 0x34); // Override resultY

    // Compute delta from direction to a global constant (e.g., for damping)
    *(float *)(this + 0x8c) = DAT_00e44564 - *(float *)(this + 0x68); // deltaX
    *(float *)(this + 0x90) = DAT_00e44564 - *(float *)(this + 0x6c); // deltaY
    *(float *)(this + 0x94) = DAT_00e44564 - *(float *)(this + 0x70); // deltaZ
}