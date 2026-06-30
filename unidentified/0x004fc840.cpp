// FUNC_004fc840: Vector4::setFromAngles(float azimuth, float zenith)
// Sets a direction vector from spherical coordinates:
//   zenith = angle from Y-axis (0 = straight up, PI = straight down)
//   azimuth = angle around Y-axis (0 = along +X, increases counterclockwise)
// The vector is stored as (x, y, z, w) where w is always 0.
void Vector4::setFromAngles(float azimuth, float zenith)
{
    // +0x00: x
    // +0x04: y
    // +0x08: z
    // +0x0C: w

    if (zenith == 0.0f)
    {
        // Straight up: (0, 1, 0, 0)
        this->x = 0.0f;
        this->y = DAT_00e2b1a4; // expected 1.0f
        this->z = 0.0f;
        this->w = 0.0f;
        return;
    }

    double dZenith = (double)zenith;
    double cosZ = /* cos(dZenith) */ FUN_00b99fcb(); // likely cosf
    double sinZ = /* sin(dZenith) */ FUN_00b99e20(); // likely sinf

    this->y = (float)cosZ; // component from zenith

    float sinZF = (float)sinZ; // reused later

    if (azimuth == 0.0f)
    {
        // Azimuth zero: (0, cos(zenith), sin(zenith), 0)
        this->x = 0.0f;
        this->z = sinZF;
        this->w = 0.0f;
        return;
    }

    double dAzimuth = (double)azimuth;
    double cosA = /* cos(dAzimuth) */ FUN_00b99fcb(); // likely cosf
    double sinA = /* sin(dAzimuth) */ FUN_00b99e20(); // likely sinf

    this->x = (float)cosA * sinZF;
    this->z = (float)sinA * sinZF;
    this->w = 0.0f;
}