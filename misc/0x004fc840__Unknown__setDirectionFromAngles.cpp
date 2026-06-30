// FUNC_NAME: Unknown::setDirectionFromAngles
// Address: 0x004fc840
// Converts spherical angles (azimuth, elevation) to a 3D direction vector stored in a float[4] member at offsets +0x00, +0x04, +0x08, +0x0C.
// When elevation is 0, direction points straight up along Y (0,1,0,0).
// Otherwise, direction = (sin(azimuth)*sin(elevation), cos(elevation), cos(azimuth)*sin(elevation), 0).

void __thiscall Unknown::setDirectionFromAngles(float azimuth, float elevation) {
    // Assumed member: float mDirection[4]; // offsets: +0x00 x, +0x04 y, +0x08 z, +0x0C w

    if (elevation == 0.0f) {
        mDirection[1] = 1.0f;   // +0x04: y = 1
        mDirection[2] = 0.0f;   // +0x08: z = 0
        mDirection[0] = 0.0f;   // +0x00: x = 0
        mDirection[3] = 0.0f;   // +0x0C: w = 0
        return;
    }

    float sinElev = sin(elevation);
    float cosElev = cos(elevation);

    mDirection[1] = cosElev;    // +0x04: y = cos(elevation)

    if (azimuth == 0.0f) {
        mDirection[0] = 0.0f;   // +0x00: x = 0
        mDirection[2] = sinElev; // +0x08: z = sin(elevation)
        mDirection[3] = 0.0f;   // +0x0C: w = 0
        return;
    }

    float sinAzim = sin(azimuth);
    float cosAzim = cos(azimuth);

    mDirection[0] = sinAzim * sinElev; // +0x00: x = sin(azimuth)*sin(elevation)
    mDirection[2] = cosAzim * sinElev; // +0x08: z = cos(azimuth)*sin(elevation)
    mDirection[3] = 0.0f;              // +0x0C: w = 0
}