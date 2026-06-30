// FUNC_NAME: matrixScaleTransform
// Reconstructs a 4x4 homogeneous transform matrix (column-major) by scaling the linear part
// and adjusting the translation such that the resulting transformation is equivalent to
// applying the input transform with a scaling along its local axes by the squares of the given factors.
// Parameter: inputTransform - source 4x4 matrix (float[16], column-major)
// Parameter: outputTransform - destination 4x4 matrix (float[16], column-major)
// Parameter: scaleFactors - 3-element vector containing the per-axis scale factors (their squares are used internally)

void matrixScaleTransform(float *inputTransform, float *outputTransform, float *scaleFactors)
{
    float m00, m01, m02, m03; // first column of input
    float m10, m11, m12, m13; // second column
    float m20, m21, m22, m23; // third column
    float m30, m31, m32, m33; // fourth column (translation part in m30, m31, m32)
    float sx2, sy2, sz2;      // squared scale factors
    float temp;

    // Extract input column vectors (column-major order)
    // Column 0
    m00 = inputTransform[0];  // +0x00
    m01 = inputTransform[1];  // +0x04
    m02 = inputTransform[2];  // +0x08
    m03 = inputTransform[3];  // +0x0C
    // Column 1
    m10 = inputTransform[4];  // +0x10
    m11 = inputTransform[5];  // +0x14
    m12 = inputTransform[6];  // +0x18
    m13 = inputTransform[7];  // +0x1C
    // Column 2
    m20 = inputTransform[8];  // +0x20
    m21 = inputTransform[9];  // +0x24
    m22 = inputTransform[10]; // +0x28
    m23 = inputTransform[11]; // +0x2C
    // Column 3
    m30 = inputTransform[12]; // +0x30
    m31 = inputTransform[13]; // +0x34
    m32 = inputTransform[14]; // +0x38
    m33 = inputTransform[15]; // +0x3C

    // Square the scale factors
    sx2 = scaleFactors[0] * scaleFactors[0];
    sy2 = scaleFactors[1] * scaleFactors[1];
    sz2 = scaleFactors[2] * scaleFactors[2];

    // Set output columns (column-major)
    // Column 0: scale first column by sx2
    outputTransform[0] = sx2 * m00;  // row0 col0
    outputTransform[1] = sy2 * m10;  // row0 col1  (note: uses second column of input)
    outputTransform[2] = sz2 * m20;  // row0 col2
    outputTransform[3] = 0.0f;       // row0 col3 = 0

    // Column 1: scale second column by sy2
    outputTransform[4] = sx2 * m01;  // row1 col0
    outputTransform[5] = sy2 * m11;  // row1 col1
    outputTransform[6] = sz2 * m21;  // row1 col2
    outputTransform[7] = 0.0f;       // row1 col3 = 0

    // Column 2: scale third column by sz2
    outputTransform[8] = sx2 * m02;  // row2 col0
    outputTransform[9] = sy2 * m12;  // row2 col1
    outputTransform[10] = sz2 * m22; // row2 col2
    outputTransform[11] = 0.0f;      // row2 col3 = 0

    // Column 3: translation adjusted so that origin is invariant under the scaling
    // The new translation = - (sx^2 * (m30*m00 + m31*m01 + m32*m02) )
    //                        - (sy^2 * (m30*m10 + m31*m11 + m32*m12) )
    //                        - (sz^2 * (m30*m20 + m31*m21 + m32*m22) )
    // Here fVar18, fVar19, fVar20 are initially zero (m30 - m30 etc.) so the expression simplifies.
    outputTransform[12] = - ( sx2 * (m30 * m00 + m31 * m01 + m32 * m02) );
    outputTransform[13] = - ( sy2 * (m30 * m10 + m31 * m11 + m32 * m12) );
    outputTransform[14] = - ( sz2 * (m30 * m20 + m31 * m21 + m32 * m22) );

    // The bottom-right element is set to a constant retrieved from global memory (assumed 1.0f)
    // +0x3C -> output[15] = DAT_00e2b1a4 (presumably 1.0f)
    outputTransform[15] = DAT_00e2b1a4;
}