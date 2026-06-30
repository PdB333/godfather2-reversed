// FUNC_NAME: Matrix4x4::transformVectors (0x006cb8a0)
// Purpose: Transform an array of 4-component vectors (x,y,z,w) by a 4x4 column-major matrix.
// The matrix is stored as float[16] in the object (this pointer).
// Input: count in EAX (register), param_1 = input array, param_2 = output array.
// Each vector occupies 4 floats. The loop processes 'count' vectors.

void __thiscall Matrix4x4::transformVectors(float const* input, float* output, int count)
{
    // Load matrix columns as local variables for speed
    float col0[4], col1[4], col2[4], col3[4];
    // matrix is this->m[16] stored in column-major order:
    // m[0]=col0.x, m[1]=col1.x, m[2]=col2.x, m[3]=col3.x
    // m[4]=col0.y, m[5]=col1.y, m[6]=col2.y, m[7]=col3.y
    // m[8]=col0.z, m[9]=col1.z, m[10]=col2.z, m[11]=col3.z
    // m[12]=col0.w, m[13]=col1.w, m[14]=col2.w, m[15]=col3.w
    float const* matrix = this->m;
    
    // Load all 16 floats (compiler likely kept them in registers)
    col0[0] = matrix[0];  // m00
    col0[1] = matrix[4];  // m01
    col0[2] = matrix[8];  // m02
    col0[3] = matrix[12]; // m03
    col1[0] = matrix[1];  // m10
    col1[1] = matrix[5];  // m11
    col1[2] = matrix[9];  // m12
    col1[3] = matrix[13]; // m13
    col2[0] = matrix[2];  // m20
    col2[1] = matrix[6];  // m21
    col2[2] = matrix[10]; // m22
    col2[3] = matrix[14]; // m23
    col3[0] = matrix[3];  // m30
    col3[1] = matrix[7];  // m31
    col3[2] = matrix[11]; // m32
    col3[3] = matrix[15]; // m33
    
    // Process each input vector
    while (count > 0) {
        float x = input[0];
        float y = input[1];
        float z = input[2];
        float w = input[3];
        
        // Output vector = M * input (with matrix stored column-major)
        output[0] = x * col0[0] + y * col0[1] + z * col0[2] + w * col0[3];
        output[1] = x * col1[0] + y * col1[1] + z * col1[2] + w * col1[3];
        output[2] = x * col2[0] + y * col2[1] + z * col2[2] + w * col2[3];
        output[3] = x * col3[0] + y * col3[1] + z * col3[2] + w * col3[3];
        
        // Advance to next vector (stride = 4 floats)
        input += 4;
        output += 4;
        --count;
    }
}