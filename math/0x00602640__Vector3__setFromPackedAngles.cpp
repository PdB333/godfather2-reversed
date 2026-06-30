// FUNC_NAME: Vector3::setFromPackedAngles
// Address: 0x00602640
// Role: Unpacks a 24-bit compressed angle (two 12-bit components: low pitch, high yaw) into a 3D direction vector.
// Calls helpers to compute sine/cosine of pitch and yaw (likely wrappers for fsin/fcos).
// Constants _DAT_00e44664 and _DAT_00e44660 are conversion factors from 12-bit to radians (~2*PI/4096).
// _DAT_00e2b1a4 is assumed to be 1.0f (default vertical vector component).

class Vector3 {
public:
    float x, y, z;

    // Sets this vector from a packed angle (24-bit: 12 bits pitch, 12 bits yaw).
    void setFromPackedAngles(uint packedAngles) {
        static const float kPitchScale = *(float*)0x00e44664; // e.g., (2*PI)/4096.0
        static const float kYawScale   = *(float*)0x00e44660; // same conversion
        static const float kDefaultY    = *(float*)0x00e2b1a4; // likely 1.0f

        if (packedAngles == 0) {
            // Default direction: up (positive Y)
            x = 0.0f;
            y = kDefaultY;
            z = 0.0f;
            return;
        }

        // Extract pitch (low 12 bits) and yaw (high 12 bits)
        uint pitchRaw = packedAngles & 0xFFF;
        uint yawRaw   = (packedAngles >> 12) & 0xFFF;

        // Convert to radians
        float pitchRad = (float)pitchRaw * kPitchScale;
        float yawRad   = (float)yawRaw   * kYawScale;

        // Compute components of the direction vector.
        // Ghidra decompilation suggests the following (with possible stack reordering):
        // - Cos(pitch) is stored as the Y component (vertical).
        // - Sin(pitch) and cos/sin(yaw) are used for X and Z (horizontal).
        // The original assembly may have used x87 fsin/fcos calls; the helper functions
        // FUN_00b99fcb and FUN_00b99e20 are presumed to be wrappers for sin/cos.
        // For clarity, we use standard math.

        float cosPitch = cosf(pitchRad);
        float sinPitch = sinf(pitchRad);
        float cosYaw   = cosf(yawRad);
        float sinYaw   = sinf(yawRad);

        // Based on typical EA engine: pitch = elevation from horizontal, yaw = azimuth.
        // Result: (cos(yaw)*cos(pitch), sin(pitch), sin(yaw)*cos(pitch))
        // However, the original stores cos(pitch) in Y, so pitch is likely angle from vertical (0=up).
        // Assuming that: Y = cos(pitch), horizontal magnitude = sin(pitch).
        // Then X = cos(yaw) * sin(pitch), Z = sin(yaw) * sin(pitch).
        // This matches the pattern: after storing Y=cos(pitch), the code uses yaw and pitch in multiplications.
        // We adopt this interpretation.

        x = cosYaw * sinPitch;
        y = cosPitch;          // matches ESI[1] = cos(pitch)
        z = sinYaw * sinPitch;
    }
};