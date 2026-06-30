// FUNC_NAME: EARSObject::updateScaleFromMatrixMaxAxis

#include <cmath>

// Forward declarations
void __fastcall sub_56b480(const float* matrix, int dataPtr, float* outScale);
void __fastcall sub_4bd160(float* scaleParam);

// Class representing the object owning this method
struct EARSObject {
    // +0x00: vtable
    // +0x0C: pointer to a transform/matrix provider
    struct MatrixProvider {
        // +0x00: vtable
        // vtable offset 0x60: returns pointer to 4x4 matrix (row-major floats[16])
        const float* getMatrix() const;
    }* mMatrixProvider;  // offset 0x0C

    // +0x50: pointer to scale factor data
    struct ScaleData {
        // +0x0C: multiplier (float)
        float mScaleFactor;   // offset 0x0C
    }* mScaleData;           // offset 0x50
};

void __fastcall EARSObject::updateScaleFromMatrixMaxAxis(EARSObject* thisPtr)
{
    // Get matrix from the provider
    const float* matrix = thisPtr->mMatrixProvider->getMatrix();
    
    // Retrieve scale multiplier
    float multiplier = thisPtr->mScaleData->mScaleFactor;
    
    // Buffer for scale vector (3 components) and resulting uniform scale
    // Layout: scaleXYZ[0..2], uniformScale
    float scaleParam[4]; // 4 floats total
    
    // Extract scale from matrix into the first 3 components
    sub_56b480(matrix, thisPtr->mScaleData, scaleParam);
    
    // Compute squared lengths of the three matrix columns (row-major)
    // Assuming matrix is row-major, columns are at offsets 0,4,8 for the 3x3 part
    float sqLenX = matrix[0]*matrix[0] + matrix[1]*matrix[1] + matrix[2]*matrix[2];
    float sqLenY = matrix[4]*matrix[4] + matrix[5]*matrix[5] + matrix[6]*matrix[6];
    float sqLenZ = matrix[8]*matrix[8] + matrix[9]*matrix[9] + matrix[10]*matrix[10];
    
    // Find maximum squared length
    float maxSq = sqLenX;
    if (sqLenY > maxSq) maxSq = sqLenY;
    if (sqLenZ > maxSq) maxSq = sqLenZ;
    
    // Uniform scale = sqrt(maxSq) * multiplier
    scaleParam[3] = sqrtf(maxSq) * multiplier;
    
    // Apply computed scale (first 3 are from sub_56b480, last is uniform)
    sub_4bd160(scaleParam);
}