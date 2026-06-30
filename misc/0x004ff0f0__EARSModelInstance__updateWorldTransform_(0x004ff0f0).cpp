// FUNC_NAME: EARSModelInstance::updateWorldTransform (0x004ff0f0)

struct ModelData; // forward declare
struct RenderContext; // forward declare

class EARSModelInstance {
public:
    void updateWorldTransform(); // __thiscall

private:
    // offset +0x00: vtable or unknown
    // offset +0x04..+0x0F: unknown
    int m_instanceIndex;           // +0x10: index into global matrix buffer
    // offset +0x14..+0x23: unknown
    ModelData* m_pModelData;       // +0x24: pointer to model instance data
    void* m_pRenderable;          // +0x28: handle / pointer to renderable geometry
    // offset +0x2C..+0x3B: unknown
    uint m_flags;                  // +0x3C: flags (bit 3 = ?)
    // ... rest of class
};

struct ModelData {
    // offset +0x00: first 4 floats (used in transformation check)
    uint flags;                    // +0x10
    float translateX;              // +0x1C
    float translateY;              // +0x20
    float translateZ;              // +0x24
    // offset +0x28..+0x3F: unknown
    float colorParam;              // +0x40
    float colorR;                  // +0x44
    float colorG;                  // +0x48
    float colorB;                  // +0x4C
    // offset +0x50..+0x5F: unknown (used in matrix copy)
    float unknown[2];              // placeholder
    // offset +0x60..+0x67: used in FUN_004e9310 arguments
    float someParam;               // +0x68
    char typeCode;                 // +0x6C (3, 15, 16)
    // offset +0x70..+0x7B: unknown (part of 12-float block)
    // offset +0x7C..+0x83: unknown
    float param88;                 // +0x88
    float param8C;                 // +0x8C
    float param94;                 // +0x94
};

struct RenderContext {
    char pad[8];                   // +0x00..+0x07
    char* pMatrixBuffer;           // +0x08: base of per-instance matrix data
};

// Global context pointer accessed via FS:0x2C
static RenderContext* g_pRenderContext; // implementation details hidden

// External functions (assumed signatures)
extern int FUN_004e9310(int, int, int, int, int, int, int); // creates/get renderable
extern void FUN_004e9440(void* pRenderable, float* pMatrix4x4); // apply transform
extern void FUN_004fef50(); // alternate path for some flag
extern void FUN_004aab40(); // clear color buffer?
extern void FUN_004e94a0(float* pColor, float param); // set color
extern void FUN_004e9520(void* pRenderable, float, float, float); // set some parameters
extern int FUN_004e9270(); // checks model data first ints, returns -1 on failure

void EARSModelInstance::updateWorldTransform() {
    ModelData* pModelData = m_pModelData; // this+0x24
    int iVar3 = *(int*)__readfsdword(0x2C); // TIB slot -> global pointer
    RenderContext* pRenderContext = *(RenderContext**)iVar3;

    // Create or acquire the renderable from model data attributes
    int renderableHandle = FUN_004e9310(
        (&g_unknownArray)[*(byte*)(pModelData + 0x6C)], // based on typeCode
        *(int*)(pModelData + 0x18),
        *(int*)(pModelData + 0x60),
        *(int*)(pModelData + 0x64), // +100 decimal
        *(int*)(pModelData + 0x68),
        *(int*)(pModelData + 0x7C),
        *(int*)(pModelData + 0x80)
    );
    m_pRenderable = (void*)renderableHandle; // store at this+0x28

    if (m_pRenderable == nullptr) {
        return; // early exit if renderable creation failed
    }

    // Fetch 4 floats (a 4-component vector, likely translation or quaternion)
    float* pSrc = (float*)(pRenderContext->pMatrixBuffer + 0x80 + m_instanceIndex);
    float vecX = pSrc[0];
    float vecY = pSrc[1];
    float vecZ = pSrc[2];
    float vecW = pSrc[3];

    // Second base pointer for matrix copy
    int matrixBase = (int)(pRenderContext->pMatrixBuffer) + m_instanceIndex;
    ModelData* pModelData2 = m_pModelData; // same as above, but reused

    // Add translation offset if flags indicate no local translation?
    if ((pModelData2->flags & 6) == 0) {
        vecX += pModelData2->translateX;
        vecY += pModelData2->translateY;
        vecZ += pModelData2->translateZ;
    }

    // Handle transform application based on typeCode
    if (pModelData2->typeCode == 0) {
        // Simple path: apply transform directly
        float transform[4] = { vecX, vecY, vecZ, vecW };
        FUN_004e9440(m_pRenderable, transform);
    } else {
        // Build a 4x4 matrix from model data (12 floats from +0x50..+0x7C)
        float matrix[16]; // local_50..uStack_24 + the 4 from above
        if ((pModelData2->flags & 0x2000) == 0) {
            // Copy 12 floats starting at +0x50
            memcpy(&matrix[0], (float*)(matrixBase + 0x50), 12 * sizeof(float));
        } else {
            FUN_004fef50(); // alternate path (likely fills matrix differently)
        }

        if (m_pRenderable != nullptr) {
            // Write the matrix into the renderable's buffer
            float* pDest = (float*)(*(int*)((char*)m_pRenderable + 0x18) + (int)pRenderContext->pMatrixBuffer);
            memcpy(pDest, matrix, 12 * sizeof(float));
            // Append the 4 floats as last row/column
            pDest[12] = vecX;
            pDest[13] = vecY;
            pDest[14] = vecZ;
            pDest[15] = vecW;
        }
    }

    // Handle color / ambient component based on flags
    if ((m_flags & 8) == 0) {
        float color[4];
        color[0] = pModelData2->colorR;
        color[1] = pModelData2->colorG;
        color[2] = pModelData2->colorB;
        color[3] = g_someConstant; // DAT_00e2b1a4 likely 1.0f or 0.0f
        FUN_004e94a0(color, pModelData2->colorParam);
    } else {
        // Clear color buffer
        m_flags &= ~8;
        float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; // local_60..uStack_54 = 0
        // Write zeros to renderable's color storage
        float* pColorDest = (float*)(*(int*)((char*)m_pRenderable + 0x18) + 0x40 + (int)pRenderContext->pMatrixBuffer);
        pColorDest[0] = 0.0f;
        pColorDest[1] = 0.0f;
        pColorDest[2] = 0.0f;
        pColorDest[3] = 0.0f;
        FUN_004aab40();
        // Set some other parameter to zero
        *(int*)(*(int*)((char*)m_pRenderable + 0x18) + 0x88 + (int)pRenderContext->pMatrixBuffer) = 0;
    }

    // Apply further parameters (e.g., blend weights)
    FUN_004e9520(
        m_pRenderable,
        pModelData2->param88,
        pModelData2->param8C,
        pModelData2->param94
    );

    // If model type code indicates special model (3, 15, 16), check bone parent
    ModelData* pMD = m_pModelData;
    char type = pMD->typeCode;
    if (type == 3 || type == 15 || type == 16) {
        // Check if the first 4 floats of model data are not all zero
        if (pMD->v[0] != 0.0f || pMD->v[1] != 0.0f || pMD->v[2] != 0.0f || pMD->v[3] != 0.0f) {
            int parentResult = FUN_004e9270();
            if (parentResult == -1) {
                parentResult = 0; // fallback
            }
            // Store parent index in renderable's data at offset +0x94
            *(int*)(*(int*)((char*)m_pRenderable + 0x18) + 0x94 + (int)pRenderContext->pMatrixBuffer) = parentResult;
        }
    }
}

// Note: g_someConstant is the undefined4 constant 0x00e2b1a4, likely 1.0f or similar.
// FUN_004e9270 checks if the model instance has a valid parent (bone index) and returns it; -1 if not applicable.
// The matrix copy (12 floats) is likely a 3x4 transform (rotation+scale+translation) without the homogeneous row.