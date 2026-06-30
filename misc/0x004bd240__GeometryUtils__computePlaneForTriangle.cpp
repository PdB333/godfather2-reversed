// FUNC_NAME: GeometryUtils::computePlaneForTriangle
void __thiscall GeometryUtils::computePlaneForTriangle(int vertexIndexA, int vertexIndexB)
{
    // ESI holds the base address of a vertex array (each vertex is 16 bytes: x, y, z, w/padding)
    float* vertexArrayBase = reinterpret_cast<float*>(unaff_ESI);
    // EDI holds the output plane (4 floats: normal x, y, z, d)
    float* outputPlane = reinterpret_cast<float*>(unaff_EDI);
    // EAX holds the third vertex index
    int vertexIndexC = in_EAX;

    // Scaled stride = 0x10 = 16 floats? Actually 16 bytes, which is 4 floats (assuming float is 4 bytes)
    // Access vertices as float arrays
    float* vA = vertexArrayBase + (vertexIndexA * 4);   // +0x00 x, +0x04 y, +0x08 z, +0x0C w/unused
    float* vB = vertexArrayBase + (vertexIndexB * 4);
    float* vC = vertexArrayBase + (vertexIndexC * 4);

    float ex = vC[0] - vA[0];
    float ey = vC[1] - vA[1];
    float ez = vC[2] - vA[2];   // Edge C - A

    float fx = vA[0] - vB[0];
    float fy = vA[1] - vB[1];
    float fz = vA[2] - vB[2];   // Edge A - B

    // Normalize factor for first edge (f)
    float lenSqF = fx*fx + fy*fy + fz*fz;
    float normFactorF;
    // DAT_00e2cbe0 is a small epsilon (likely 0.0 or very small)
    if (lenSqF <= DAT_00e2cbe0) {
        normFactorF = 0.0f;
    } else {
        normFactorF = DAT_00e2b1a4 / sqrtf(lenSqF); // DAT_00e2b1a4 is likely 1.0f or a constant
    }

    // Normalize factor for second edge (e)
    float lenSqE = ex*ex + ey*ey + ez*ez;
    float normFactorE;
    if (lenSqE <= DAT_00e2cbe0) {
        normFactorE = 0.0f;
    } else {
        normFactorE = DAT_00e2b1a4 / sqrtf(lenSqE);
    }

    // Compute cross product: -(f x e) scaled by normFactorF * normFactorE
    // Actually the code produces -normFactorF*normFactorE * (f x e) in components:
    float nx = ey * normFactorE * normFactorF * fz - ez * normFactorE * normFactorF * fy; // -cross_x
    float ny = ez * normFactorE * fx * normFactorF - ex * normFactorE * fz * normFactorF; // -cross_y
    float nz = ex * normFactorE * fy * normFactorF - ey * normFactorE * fx * normFactorF; // -cross_z

    // Now normalize the cross product
    float lenSqN = nx*nx + ny*ny + nz*nz;
    float normFactorN;
    if (lenSqN <= DAT_00e2cbe0) {
        normFactorN = 0.0f;
    } else {
        normFactorN = DAT_00e2b1a4 / sqrtf(lenSqN);
    }

    // Store final plane normal
    outputPlane[0] = normFactorN * nx; // normal.x
    outputPlane[1] = normFactorN * ny; // normal.y
    outputPlane[2] = normFactorN * nz; // normal.z
    // Plane equation: normal·X + d = 0  => d = -normal·B (point B lies on plane)
    // DAT_00e44564 is a constant offset, likely 0.0f
    outputPlane[3] = DAT_00e44564 - (vB[0] * outputPlane[0] + vB[1] * outputPlane[1] + vB[2] * outputPlane[2]);
}