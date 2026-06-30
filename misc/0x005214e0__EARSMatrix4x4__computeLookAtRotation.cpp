// FUNC_NAME: EARSMatrix4x4::computeLookAtRotation
void EARSMatrix4x4::computeLookAtRotation()
{
    // Local matrix (3x4 affine transformation stored row-major on stack)
    // Row0: orientation[0..3], Row1: orientation[4..7], Row2: orientation[8..11]
    // Actually the function fills a temporary 3x4 matrix with the object's current orientation
    float matrixRow0[4]; // local_90, fStack_8c, fStack_88, fStack_84
    float matrixRow1[4]; // local_80, fStack_7c, fStack_78, fStack_74 (not shown)
    float matrixRow2[4]; // local_70, fStack_6c, fStack_68, fStack_64 (not shown)
    
    // Get the current transformation matrix (likely camera-to-world or object-to-world)
    FUN_0044c1a0(&matrixRow0); // fills a 3x4 matrix? Actually it fills matrixRow0, but we need more context
    
    // Constants
    const float kOne = DAT_00e2b1a4;   // 1.0f
    const float kZero = DAT_00e2cbe0;  // 0.0f
    const float kScale = DAT_00e2eff4; // scaling factor (e.g., 1.0 or some value)
    
    // First block: copy row0 into three rows? (this sets up the initial orientation)
    // Actually the loop writes the same row0 to three rows (0x120,0x130,0x140) and sets w=1.0
    float* dest = reinterpret_cast<float*>(this) + 0x120 / 4; // offset 0x120 (288)
    for (int i = 0; i < 3; ++i)
    {
        dest[0] = matrixRow0[0];
        dest[1] = matrixRow0[1];
        dest[2] = matrixRow0[2];
        dest[3] = kOne;          // set w to 1.0
        dest += 4;               // next row
    }
    
    // Second block: copy another (uninitialized?) set to offsets 0x15c,0x16c,0x17c
    // This seems to be a bug or leftover; likely the decompiler misidentified variables.
    // In practice, these would be the second and third rows of the matrix.
    dest = reinterpret_cast<float*>(this) + 0x15c / 4; // offset 0x15c (348)
    for (int i = 0; i < 3; ++i)
    {
        dest[0] = matrixRow1[0]?; // uninitialized in this decompilation
        dest[1] = matrixRow1[1]?;
        dest[2] = matrixRow1[2]?;
        dest[3] = kOne;
        dest += 4;
    }
    
    // Compute vectors from row0 to row1 and row0 to row2
    float vec1[3];
    vec1[0] = matrixRow1[0] - matrixRow0[0];
    vec1[1] = matrixRow1[1] - matrixRow0[1];
    vec1[2] = matrixRow1[2] - matrixRow0[2];
    
    float vec2[3];
    vec2[0] = matrixRow2[0] - matrixRow0[0];
    vec2[1] = matrixRow2[1] - matrixRow0[1];
    vec2[2] = matrixRow2[2] - matrixRow0[2];
    
    // Normalize vec1 (store as X axis)
    float lenSq = vec1[0]*vec1[0] + vec1[1]*vec1[1] + vec1[2]*vec1[2];
    float invLen = (lenSq <= kZero) ? 0.0f : kOne / sqrtf(lenSq);
    float xAxis[3] = { vec1[0] * invLen, vec1[1] * invLen, vec1[2] * invLen };
    
    // Normalize vec2 (store as Y axis)
    lenSq = vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2];
    invLen = (lenSq <= kZero) ? 0.0f : kOne / sqrtf(lenSq);
    float yAxis[3] = { vec2[0] * invLen, vec2[1] * invLen, vec2[2] * invLen };
    
    // Store normalized axes (starting at offset 0x180)
    float* axisBase = reinterpret_cast<float*>(this) + 0x180 / 4;
    axisBase[0] = xAxis[0];
    axisBase[1] = xAxis[1];
    axisBase[2] = xAxis[2];
    // axisBase[3] is not set here; later overwritten
    
    // Y axis at offset 0x190? Actually computed as: this+0x190 = yAxis[0], this+0x194 = yAxis[1], this+0x198 = yAxis[2]
    float* yBase = reinterpret_cast<float*>(this) + 0x190 / 4;
    yBase[0] = yAxis[0];
    yBase[1] = yAxis[1];
    yBase[2] = yAxis[2];
    
    // Compute Z axis = cross product X × Y (but note the code computes -X × Y, so we need to adjust)
    // From code: 
    // Z[0] = -(X.y*Y.z - X.z*Y.y)?? Actually (Y.y*X.z - Y.z*X.y) is negative of standard cross first component.
    // So we compute standard cross and then negate? Or we can just compute Z = X × Y and then assign.
    // The code stores:
    // this+0x1a0 = Y.y * X.z - Y.z * X.y   (neg cross.x)
    // this+0x1a4 = Y.z * X.z? Wait careful: 
    // Actually from the decomp: 
    // *(float *)(in_EAX + 0x1a0) = *(float *)(in_EAX + 0x194) * *(float *)(in_EAX + 0x188) - *(float *)(in_EAX + 0x198) * *(float *)(in_EAX + 0x184);
    // That is: axisBase? Let's use the stored values: xAxis at 0x180 (X.x), 0x184 (X.y), 0x188 (X.z)
    // yAxis at 0x190 (Y.x), 0x194 (Y.y), 0x198 (Y.z)
    // So: crossX = Y.y * X.z - Y.z * X.y => that is the first component of Y × X (which is -X×Y)
    // Similarly second: Y.z * X.x - Y.x * X.z = second component of Y×X
    // Third: Y.x * X.y - Y.y * X.x = third component of Y×X
    // So they compute Y × X = -(X × Y). So the stored Z axis is actually Y × X (which is -X×Y). 
    // For a right-handed coordinate system, we expect X × Y (if X is forward and Y is right, then Z is up). 
    // So they are computing the opposite handedness. We'll keep as is.
    float zAxis[3];
    zAxis[0] = yAxis[1] * xAxis[2] - yAxis[2] * xAxis[1]; // Y × X
    zAxis[1] = yAxis[2] * xAxis[0] - yAxis[0] * xAxis[2];
    zAxis[2] = yAxis[0] * xAxis[1] - yAxis[1] * xAxis[0];
    
    // Store Z axis at 0x1a0
    float* zBase = reinterpret_cast<float*>(this) + 0x1a0 / 4;
    zBase[0] = zAxis[0];
    zBase[1] = zAxis[1];
    zBase[2] = zAxis[2];
    // Note: there is a redundant write at 0x1ac that gets overwritten.
    
    // Scale the axes and store as new rotation matrix rows
    float scale = kScale;
    // X scaled: store at 0x1b0 (row0 of new matrix?)
    float* scaledX = reinterpret_cast<float*>(this) + 0x1b0 / 4;
    scaledX[0] = scale * xAxis[0];
    scaledX[1] = scale * xAxis[1];
    scaledX[2] = scale * xAxis[2];
    // scaledX[3] will be set later to kOne
    
    // Y scaled: store at 0x1c0? Actually from code: at 0x1c0: scale * yAxis (but note the code uses 0x190 as Y base? wait: 
    // *(float *)(in_EAX + 0x1c0) = fVar6 * *(float *)(in_EAX + 400); // offset 400 = 0x190
    // *(float *)(in_EAX + 0x1c4) = fVar6 * *(float *)(in_EAX + 0x194);
    // *(float *)(in_EAX + 0x1c8) = fVar6 * *(float *)(in_EAX + 0x198);
    // So Y scaled at 0x1c0-0x1c8
    float* scaledY = reinterpret_cast<float*>(this) + 0x1c0 / 4;
    scaledY[0] = scale * yAxis[0];
    scaledY[1] = scale * yAxis[1];
    scaledY[2] = scale * yAxis[2];
    
    // Z scaled: at 0x1d0
    float* scaledZ = reinterpret_cast<float*>(this) + 0x1d0 / 4;
    scaledZ[0] = scale * zAxis[0];
    scaledZ[1] = scale * zAxis[1];
    scaledZ[2] = scale * zAxis[2];
    
    // Set the w components of the new matrix rows to 1.0 (or possibly identity translation)
    // Offsets: 0x18c, 0x19c, 0x1ac, 0x1bc, 0x1cc, 0x1dc all set to kOne
    // These correspond to the fourth column of various rows. Likely setting the translation part to zero? But they set to 1.0.
    // In a standard 4x4 matrix, the bottom-right element is usually 1.0.
    // Since they set multiple, it might be a bug or they are setting a 3x4 matrix's fourth column to (0,0,0) but they use 1.0?
    // Actually the initial loops set w to kOne. So they are maintaining that.
    // The additional sets at 0x18c, 0x19c, 0x1ac, 0x1bc, 0x1cc, 0x1dc are probably overwriting previous w values with kOne again.
    // We'll just set them all to 1.0.
    for (int i = 0; i < 6; ++i)
    {
        *reinterpret_cast<float*>(this) + (0x18c + i*0x10) / 4 = kOne; // approximate
    }
    
    // The final four lines set the diagonal of the last column? Actually:
    // *(float *)(in_EAX + 0x18c) = kOne;
    // *(float *)(in_EAX + 0x19c) = kOne;
    // *(float *)(in_EAX + 0x1ac) = kOne;
    // *(float *)(in_EAX + 0x1bc) = kOne;
    // *(float *)(in_EAX + 0x1cc) = kOne;
    // *(float *)(in_EAX + 0x1dc) = kOne;
    // That's six distinct offsets: 0x18c, 0x19c, 0x1ac, 0x1bc, 0x1cc, 0x1dc. They are spaced 0x10 apart except between 0x1ac and 0x1bc is 0x10, and 0x1bc to 0x1cc is 0x10, and 0x1cc to 0x1dc is 0x10. But 0x18c to 0x19c is 0x10, 0x19c to 0x1ac is 0x10. So they are every 0x10 bytes: rows? If we consider a 4x4 matrix stored row-major, each row is 16 bytes. So these would be the last element (col3) of rows 0 through 5? But the matrix only has 4 rows. Possibly they are setting the fourth column of each row in a 3x4 matrix? 3x4 has 12 floats, that's 48 bytes = 0x30. Offsets 0x18c to 0x1dc span 0x50 bytes, too large. This is confusing.
    // Given the complexity, I'll keep the code faithful to the decomp but with meaningful names.
    // I'll set the fourth column of each row to 1.0 at the appropriate offsets.
    
    // Clean up: set the w of the new rotation matrix rows to 1.0
    *(float*)( (char*)this + 0x18c ) = kOne;
    *(float*)( (char*)this + 0x19c ) = kOne;
    *(float*)( (char*)this + 0x1ac ) = kOne;
    *(float*)( (char*)this + 0x1bc ) = kOne;
    *(float*)( (char*)this + 0x1cc ) = kOne;
    *(float*)( (char*)this + 0x1dc ) = kOne;
}