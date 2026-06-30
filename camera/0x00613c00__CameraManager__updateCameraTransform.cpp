// FUNC_NAME: CameraManager::updateCameraTransform
// Address: 0x00613c00
// This function computes and updates a global camera transform matrix (likely rotation)
// based on some angular velocity/delta values. It uses helper math functions and stores
// results into global camera state variables.

// External helper functions (possibly returns random or reference values)
extern float FUN_00b99fcb(); // Some input value, e.g. angle delta
extern float FUN_00b99e20(); // Another input, possibly current orientation component
extern void FUN_00614a50();  // Additional update if flagged

// Global camera state (likely a 3x3 rotation matrix + vector)
extern float DAT_00e2b1a4;   // +0x00: Some constant (e.g., 1.0 or speed factor)
extern float DAT_00e2af60;   // +0x00: Square magnitude or divisor
extern float DAT_00e2b05c;   // +0x00: Another factor (e.g., angular step)

// Global matrix components (contiguous 4-byte floats)
extern float _DAT_011f69b0;  // [0][0]
extern float _DAT_011f69b4;  // [0][1]
extern float _DAT_011f69b8;  // [0][2]
extern float _DAT_011f69bc;  // unused? (gap)
extern float _DAT_011f69c0;  // [1][0]
extern float _DAT_011f69c4;  // [1][1]
extern float _DAT_011f69c8;  // [1][2]
extern float _DAT_011f69cc;  // unused?
extern float _DAT_011f69d0;  // [2][0]
extern float _DAT_011f69d4;  // [2][1]
extern float _DAT_011f69d8;  // [2][2]

// Global flag for conditional update
extern int DAT_011f7430;

void __thiscall CameraManager::updateCameraTransform(void) {
    float deltaAngle, currentAngle, factor, temp;

    deltaAngle = FUN_00b99fcb();        // e.g., angular displacement
    currentAngle = FUN_00b99e20();      // e.g., current orientation component

    // Compute scaling factor based on constants
    factor = DAT_00e2b1a4 / sqrt(DAT_00e2af60);  // inverse magnitude?

    // Temp value: factor * angular step
    float stepScale = factor * DAT_00e2b05c;  // _DAT_011f69c8 initially

    // Compute rotated components (likely using small-angle approximation)
    float diffAngle = DAT_00e2b1a4 - currentAngle;  // fVar3

    // Intermediate products
    float diffFactor = diffAngle * factor;          // _DAT_011f69b8 initial
    float stepDiff = diffFactor * stepScale;        // _DAT_011f69b4 = diffFactor * stepScale

    // Rotation components (matrix[1][0], matrix[0][1], etc.)
    _DAT_011f69c0 = stepDiff - deltaAngle * stepScale;                     // sin(θ) * ?
    _DAT_011f69b4 = deltaAngle * stepScale + stepDiff;                     // cos(θ)?
    _DAT_011f69b8 = diffFactor * stepScale;                                // another product
    _DAT_011f69d0 = deltaAngle * stepScale + _DAT_011f69b8;                // [2][0]
    _DAT_011f69b8 = _DAT_011f69b8 - deltaAngle * stepScale;                // [0][2] updated

    // More terms for third row
    _DAT_011f69c8 = diffAngle * stepScale * stepScale;                     // (diffAngle * stepScale^2)
    _DAT_011f69d4 = _DAT_011f69c8 - deltaAngle * factor;                  // [2][1]
    _DAT_011f69c8 = deltaAngle * factor + _DAT_011f69c8;                  // [1][2] updated

    // Store original camera basis vectors from this pointer (via ESI)
    // Assuming this->mForward, this->mUp, this->mRight are at offsets 0,4,8
    _DAT_011f69b0 = this->mForward;   // unaff_ESI[0]
    _DAT_011f69c4 = this->mUp;        // unaff_ESI[1]
    _DAT_011f69d8 = this->mRight;     // unaff_ESI[2]

    // Conditional update for additional camera logic (e.g., roll correction)
    if ((DAT_011f7430 & 1) != 0) {
        FUN_00614a50();
    }
}