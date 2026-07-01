// FUNC_NAME: Transform::subtract
// Function at 0x0081fc80: Subtracts two transform structures (param_2 - param_3) and stores result in param_1.
// The transform is stored as a 4x4 column-major matrix (columns at +0x50, +0x60, +0x70, +0x80)
// plus extra vectors at +0x90 (3 floats) and +0xa0 (2 floats).
// Calls a preprocessing function on param_2 first.

struct Transform {
    // Column-major 4x4 matrix
    float col0[4]; // +0x50
    float col1[4]; // +0x60
    float col2[4]; // +0x70
    float col3[4]; // +0x80
    float extraVec3[3]; // +0x90
    float extraVec2[2]; // +0xa0
};

// Forward declaration of preprocessing function
void preprocessTransform(Transform* transform); // FUN_0081fac0

Transform* __thiscall Transform::subtract(Transform* this, Transform* other1, Transform* other2) {
    preprocessTransform(other1);

    // Subtract column 0
    this->col0[0] = other1->col0[0] - other2->col0[0];
    this->col0[1] = other1->col0[1] - other2->col0[1];
    this->col0[2] = other1->col0[2] - other2->col0[2];
    this->col0[3] = other1->col0[3] - other2->col0[3];

    // Subtract column 3 (order: col3, col2, col1 due to optimization)
    this->col3[0] = other1->col3[0] - other2->col3[0];
    this->col3[1] = other1->col3[1] - other2->col3[1];
    this->col3[2] = other1->col3[2] - other2->col3[2];
    this->col3[3] = other1->col3[3] - other2->col3[3];

    // Subtract column 2
    this->col2[0] = other1->col2[0] - other2->col2[0];
    this->col2[1] = other1->col2[1] - other2->col2[1];
    this->col2[2] = other1->col2[2] - other2->col2[2];
    this->col2[3] = other1->col2[3] - other2->col2[3];

    // Subtract column 1
    this->col1[0] = other1->col1[0] - other2->col1[0];
    this->col1[1] = other1->col1[1] - other2->col1[1];
    this->col1[2] = other1->col1[2] - other2->col1[2];
    this->col1[3] = other1->col1[3] - other2->col1[3];

    // Subtract extra vector at +0x90 (3 floats)
    this->extraVec3[0] = other1->extraVec3[0] - other2->extraVec3[0];
    this->extraVec3[1] = other1->extraVec3[1] - other2->extraVec3[1];
    this->extraVec3[2] = other1->extraVec3[2] - other2->extraVec3[2];

    // Subtract extra vector at +0xa0 (2 floats)
    this->extraVec2[0] = other1->extraVec2[0] - other2->extraVec2[0];
    this->extraVec2[1] = other1->extraVec2[1] - other2->extraVec2[1];

    return this;
}