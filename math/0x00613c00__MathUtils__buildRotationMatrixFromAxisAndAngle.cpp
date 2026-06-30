// FUNC_NAME: MathUtils::buildRotationMatrixFromAxisAndAngle
#include <cmath>

// Global variables from addresses
// 0x011f69b0 .. 0x011f69d8: 3x3 rotation matrix (row-major)
static float gRotationMatrix[9];

// 0x00e2b1a4: length of the axis vector? / angle?
static float gAxisLength;

// 0x00e2af60: squared length of the axis vector?
static float gAxisSquaredLength;

// 0x00e2b05c: some scalar (1-cos? sin? depends)
static float gAxisSome;

// 0x011f7430: flags, bit 0 triggers debug update
static int gDebugFlags;

// Functions that return sin/cos of a global angle
double sinAngle(void);
double cosAngle(void);

// Debug update function (FUN_00614a50)
void updateDebugMatrix(void);

// __thiscall assumed: this pointer in ESI
class RotationHelper {
public:
    float axisX; // offset 0
    float axisY; // offset 4
    float axisZ; // offset 8

    void buildRotationMatrix(void);
};

void RotationHelper::buildRotationMatrix(void)
{
    // Get sin and cos of the rotation angle (angle from global?)
    double dSin = sinAngle();
    double dCos = cosAngle();
    float fSin = (float)dSin;
    float fCos = (float)dCos;

    // Constants from globals
    float fLen = gAxisLength;          // A
    float fSqrLen = gAxisSquaredLength; // B^2
    float fSome = gAxisSome;            // C

    // Normalization factor
    float fNorm = fLen / std::sqrt(fSqrLen); // = A/B

    // Matrix computations (simplified from decompiler)
    gRotationMatrix[2] = fNorm * fSome;      // gRotationMatrix[2] = A/B * C
    float fTemp = fLen * fNorm;              // = A * A/B = A^2/B
    gRotationMatrix[1] = fTemp;              // temporary, will be overwritten
    gRotationMatrix[0] = fTemp * gRotationMatrix[2]; // = A^2/B * (A/B * C) = A^3*C/B^2
    gRotationMatrix[3] = 0.0f;               // row0col1? actually gRotationMatrix[3] = gRotationMatrix[0] - 0
    // gRotationMatrix[0] unchanged
    gRotationMatrix[1] = gRotationMatrix[1] * gRotationMatrix[2]; // = A^2/B * (A/B*C) = same as gRotationMatrix[0]
    gRotationMatrix[8] = gRotationMatrix[1]; // row2col2 = same
    gRotationMatrix[1] = gRotationMatrix[1] - 0.0f; // unchanged
    gRotationMatrix[2] = fLen * gRotationMatrix[2] * gRotationMatrix[2]; // = A * (A/B*C)^2 = A^3*C^2/B^2
    gRotationMatrix[7] = gRotationMatrix[2]; // row2col1 = same
    gRotationMatrix[2] = 0.0f + gRotationMatrix[2]; // same

    // Store the axis from this object into matrix diagonal (offsets 0,4,8)
    gRotationMatrix[0] = this->axisX;
    gRotationMatrix[5] = this->axisY;
    gRotationMatrix[8] = this->axisZ; // overwrites previous value

    // Debug update if flag set
    if ((gDebugFlags & 1) != 0) {
        updateDebugMatrix();
    }
}