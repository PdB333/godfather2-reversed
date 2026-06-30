// FUNC_NAME: TransformData::computeFromState
// Address: 0x0056ae20
// Role: Fills a TransformData structure (5 float fields) by calling two helper functions.
// The structure likely holds a quaternion (first 4 floats) and an additional scalar (e.g., angle or weight).
// Called functions: 
//   computeQuaternion() – fills the quaternion part (success flag returned)
//   computeScalar() – returns the fifth value (no arguments, uses global/internal state)
// __thiscall: 'this' pointer (TransformData*) passed in ESI (custom calling convention)

void TransformData::computeFromState()
{
    float quatX, quatY, quatZ, quatW;  // local storage for quaternion components
    int success = computeQuaternion(&quatX, &quatY, &quatZ, &quatW);
    if (success == 0) {
        return;
    }
    // Copy quaternion into this structure's first four fields (offsets 0x00, 0x04, 0x08, 0x0C)
    this->field0 = quatX;  // +0x00
    this->field1 = quatY;  // +0x04
    this->field2 = quatZ;  // +0x08
    this->field3 = quatW;  // +0x0C
    // Compute and store the fifth field (offset 0x10)
    this->field4 = computeScalar();  // +0x10
}

// Helper function declaration (address 0x0056ad40)
// Returns 0 on failure, non-zero on success
int computeQuaternion(float* outX, float* outY, float* outZ, float* outW);

// Helper function declaration (address 0x0056acb0)
// Returns a single float value
float computeScalar(void);