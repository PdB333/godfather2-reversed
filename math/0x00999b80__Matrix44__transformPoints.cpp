// FUNC_NAME: Matrix44::transformPoints
void __thiscall Matrix44::transformPoints(float *matrix, float *inPoints, float *outPoints)
{
    float m00 = matrix[0];
    float m01 = matrix[1];
    float m02 = matrix[2];
    float m03 = matrix[3];
    float m10 = matrix[4];
    float m11 = matrix[5];
    float m12 = matrix[6];
    float m13 = matrix[7];
    float m20 = matrix[8];
    float m21 = matrix[9];
    float m22 = matrix[10];
    float m23 = matrix[11];
    float m30 = matrix[12];
    float m31 = matrix[13];
    float m32 = matrix[14];
    float m33 = matrix[15];
    
    int count = in_EAX; // Number of points to transform, passed in EAX
    int i = 0;
    while (i < count) {
        float x = inPoints[i * 4];
        float y = inPoints[i * 4 + 1];
        float z = inPoints[i * 4 + 2];
        float w = inPoints[i * 4 + 3];
        
        outPoints[i * 4]     = x * m00 + y * m10 + z * m20 + w * m30;
        outPoints[i * 4 + 1] = x * m01 + y * m11 + z * m21 + w * m31;
        outPoints[i * 4 + 2] = x * m02 + y * m12 + z * m22 + w * m32;
        outPoints[i * 4 + 3] = x * m03 + y * m13 + z * m23 + w * m33;
        i++;
    }
}