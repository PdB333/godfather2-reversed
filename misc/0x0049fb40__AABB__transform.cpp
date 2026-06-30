// FUNC_NAME: AABB::transform
void __fastcall AABB::transform(Matrix4x4* matrix)
{
    // ECX is unused (possibly this pointer for a derived class)
    // ESI points to this->max (float[4])
    // EDI points to this->min (int[4] at offsets 0,4,8,12; the W component is set to global constant)
    // EDX is the 4x4 transformation matrix

    // Read min as integers (x,y,z) from EDI
    Vector3i minInt;
    minInt.x = *(int*)(EDI + 0);
    minInt.y = *(int*)(EDI + 4);
    minInt.z = *(int*)(EDI + 8);

    // Read max as floats from ESI
    Vector3f maxFloat;
    maxFloat.x = *(float*)(ESI + 0);
    maxFloat.y = *(float*)(ESI + 4);
    maxFloat.z = *(float*)(ESI + 8);

    // Global constant (likely 0.0f or 1.0f)
    const float constantW = *(float*)0x00e2b1a4;

    // Build the 8 corners of the AABB from min and max
    // Corner order: (max.x, min.y, min.z), (max.x, min.y, max.z), (max.x, max.y, min.z), (max.x, max.y, max.z),
    //               (min.x, min.y, min.z), (min.x, min.y, max.z), (min.x, max.y, min.z), (min.x, max.y, max.z)
    Vector4 corners[8];
    corners[0] = Vector4( maxFloat.x, (float)minInt.y, (float)minInt.z, constantW );
    corners[1] = Vector4( maxFloat.x, (float)minInt.y, maxFloat.z, constantW );
    corners[2] = Vector4( maxFloat.x, maxFloat.y, (float)minInt.z, constantW );
    corners[3] = Vector4( maxFloat.x, maxFloat.y, maxFloat.z, constantW );
    corners[4] = Vector4( (float)minInt.x, (float)minInt.y, (float)minInt.z, constantW );
    corners[5] = Vector4( (float)minInt.x, (float)minInt.y, maxFloat.z, constantW );
    corners[6] = Vector4( (float)minInt.x, maxFloat.y, (float)minInt.z, constantW );
    corners[7] = Vector4( (float)minInt.x, maxFloat.y, maxFloat.z, constantW );

    // Initialize transformed min and max with the first corner transformed
    Vector4 transformed = corners[0] * matrix; // matrix multiplication
    Vector4 min = transformed;
    Vector4 max = transformed;

    // Transform remaining 7 corners and update min/max
    for (int i = 1; i < 8; i++)
    {
        transformed = corners[i] * matrix;
        min = componentwiseMin(min, transformed);
        max = componentwiseMax(max, transformed);
    }

    // Write transformed min (as float now) and max back to structures
    *(Vector4*)EDI = min;
    *(Vector4*)ESI = max;
}