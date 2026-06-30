// FUNC_NAME: Matrix3x4::setDefault
// Function at 0x004f3c20: Initializes a 3x4 affine transformation matrix to a default diagonal scaling matrix.
// This sets the diagonal elements (m[0][0], m[1][1], m[2][2]) to the global default scale value,
// and all other elements (including translation) to zero.
// Used by FUN_0050f900 to initialize a matrix before further modifications.

// Global default scale factor (likely 1.0f)
extern float gDefaultScale;

class Matrix3x4 {
public:
    float m[3][4]; // row-major 3x4 matrix (12 floats)
                   // +0x00: row 0
                   // +0x10: row 1
                   // +0x20: row 2

    // Equivalent to constructing an identity matrix with uniform scale from gDefaultScale
    void setDefault() {
        m[0][0] = gDefaultScale;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[0][3] = 0.0f;

        m[1][0] = 0.0f;
        m[1][1] = gDefaultScale;
        m[1][2] = 0.0f;
        m[1][3] = 0.0f;

        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = gDefaultScale;
        m[2][3] = 0.0f;
    }
};