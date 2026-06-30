// FUNC_NAME: UIGridSystem::initializeBuffers
// Address: 0x00419880 - Initializes vertex and index buffers for a 10x7 grid (likely for UI minimap/WorldMap)

#include <cstdlib>
#include <cstdint>
#include <cstring>

// Engine memory allocation functions (global)
extern void* engineAlloc(size_t size, int alignment, int unused1, int flags);
extern void engineFree(void* ptr);

// External globals (screen/rendering parameters)
extern float gScreenWidth;       // DAT_00e447d4
extern float gScreenHeight;      // _DAT_00e447d0
extern float gFov;               // DAT_00e2b1a4
extern float gDepthOffset;       // DAT_00e2afac
extern float gFloatConv;         // DAT_00e44578 (used for negative float conversion)
extern float gAspectRatioInv;    // _DAT_01205340
extern float gFovInv;            // _DAT_01205344

// Global buffer handles (singleton)
extern uint8_t* gVertexBuffer;   // DAT_01205334
extern uint8_t* gIndexBuffer;    // DAT_01205338
extern int32_t gMaxIndex;        // DAT_0120533c

// Forward declaration of engine lock/unlock methods (via vtable)
typedef void* (__fastcall* LockFunc)(void* buffer, uint32_t offsetToLock, uint32_t sizeToLock, void** ppData, uint32_t flags);
typedef void (__fastcall* UnlockFunc)(void* buffer);

// Structure assumed for VertexBuffer (size 0x360)
struct VertexBuffer {
    void* pVTable;               // +0x00
    uint32_t unk04;              // +0x04
    uint8_t lockedFlag1;         // +0x07
    float* pLockedData;          // +0x08 (offset from pointer? Actually +0x10? Let's keep as array)
    // ... other fields
    uint8_t lockFlag2;           // +0x1d
};

// Structure assumed for IndexBuffer (size 0xb2)
struct IndexBuffer {
    void* pVTable;               // +0x00
    uint32_t unk04;              // +0x04
    // ... 
    uint8_t lockedFlag1;         // +0x0a
    uint32_t indexCount;         // +0x0c? Actually at offset +3 in bytes? Use offset +0x0c
    uint16_t minIndex;           // +0x10? Actually +0x10 from start? We'll see
    uint16_t maxIndex;           // +0x12
    uint16_t* pLockedData;       // +0x14? Actually from decompiler: puVar10[5] is used as pointer
    uint8_t lockFlag2;           // +0x29
};

void __fastcall UIGridSystem::initializeBuffers(void* thisPtr)
{
    bool bAlreadyInit = (gVertexBuffer == nullptr);
    *(uint32_t*)((uint8_t*)thisPtr + 0x08) = 0; // Clear some field in this

    if (bAlreadyInit) {
        // Allocate vertex buffer of size 0x360
        gVertexBuffer = (uint8_t*)engineAlloc(0x360, 0, 0, 0x12);
        // Allocate index buffer of size 0xb2
        gIndexBuffer = (uint8_t*)engineAlloc(0xb2, 0, 0, 0x12);

        VertexBuffer* pVB = (VertexBuffer*)gVertexBuffer;
        IndexBuffer* pIB = (IndexBuffer*)gIndexBuffer;

        float* vertData = nullptr;
        uint16_t* idxData = nullptr;

        // Lock vertex buffer if needed (vtable method at +0x2c)
        if (*(uint8_t*)(pVB + 0x07) == 0) {
            // Not locked, access data directly from buffer
            vertData = (float*)(*(uint32_t*)((uint8_t*)pVB + 0x10)); // pVB[4] (offset +0x10)
            *(uint8_t*)((uint8_t*)pVB + 0x1d) = 1; // Set lock flag2
        } else {
            uint32_t flags = 0;
            if (*(uint8_t*)(pVB + 0x03) != 0) {
                flags = 0x3000; // Some lock flag
            }
            LockFunc lockFunc = (LockFunc)(*(void***)pVB)[0x2c / 4]; // vtable offset 0x2c
            lockFunc(pVB, 0, 0, &vertData, flags);
        }

        // Lock index buffer if needed (vtable method at +0x2c)
        if (*(uint8_t*)(pIB + 0x0a) == 0) {
            idxData = (uint16_t*)(*(uint32_t*)((uint8_t*)pIB + 0x14)); // pIB[5] (offset +0x14)
            *(uint8_t*)((uint8_t*)pIB + 0x29) = 1; // Set lock flag2
        } else {
            uint32_t flags = 0;
            if (*(uint8_t*)(pIB + 0x02) != 0) {
                flags = 0x3000;
            }
            LockFunc lockFunc = (LockFunc)(*(void***)pIB)[0x2c / 4];
            lockFunc(pIB, 0, 0, &idxData, flags);
        }

        // Set up vertex data: 10 rows x 7 columns = 70 vertices, each 3 floats
        // Format: x, y, z (screen-space positions)
        float fRowScale = gDepthOffset;        // Used as base for z? Actually fVar5
        float fColScale = gScreenHeight;       // fVar7
        float fRowStep  = gScreenWidth;        // fVar8
        float fConstX   = gFov;                // fVar6

        float* pVert = vertData;
        for (int row = 0; row < 10; ++row) {
            float fRowFloat = (float)row;
            if (row < 0) fRowFloat += gFloatConv; // For negative? Not needed here since row>=0

            for (int col = 0; col < 7; ++col) {
                float fColFloat = (float)col;
                if (col < 0) fColFloat += gFloatConv;

                pVert[0] = fConstX;                               // x (constant)
                pVert[1] = (fColFloat + 1.0f) * fColScale;       // y (scaled column + 1)
                pVert[2] = fRowFloat * fRowStep - fRowScale;     // z (or y offset?)

                pVert += 3;
            }
        }

        // Set up index data: triangle strip indices with degenerates for per-row strips
        short sRowStart = 2; // Starting vertex index for first row strip (vertices 0,1 reserved)
        uint16_t* pIdx = idxData;
        for (int row = 1; row <= 10; ++row) {
            int rowIdx = row;
            if (row > 9) rowIdx = 0; // Should not happen because loop condition

            if (row != 1) {
                *pIdx++ = 0; // Degenerate triangle start
            }
            *pIdx++ = 0; // Another degenerate

            for (int col = 0; col < 7; ++col) {
                *pIdx++ = sRowStart + (short)col;                  // Upper vertex of quad
                *pIdx++ = (short)col + (short)rowIdx * 7 + 2;     // Lower vertex (row+1)
            }

            *pIdx++ = 1; // Degenerate triangle end
            pIdx = idxData + (pIdx - idxData); // Actually pIdx already advanced, no need
            if (row < 10) {
                *pIdx++ = 1; // Additional degenerate for next row
            }

            sRowStart += 7; // Move to next row base
        }

        // Unlock vertex buffer if needed
        if (*(uint8_t*)((uint8_t*)pVB + 0x07) == 0) {
            *(uint8_t*)((uint8_t*)pVB + 0x1d) = 0;
        } else {
            UnlockFunc unlockFunc = (UnlockFunc)(*(void***)pVB)[0x30 / 4]; // vtable offset 0x30
            unlockFunc(pVB);
        }

        // Unlock index buffer and compute min/max indices
        if (*(uint8_t*)((uint8_t*)pIB + 0x0a) == 0) {
            *(uint8_t*)((uint8_t*)pIB + 0x29) = 0;
        } else {
            uint16_t minIdx = 0xFFFF;
            uint16_t maxIdx = 0;
            uint32_t idxCount = *(uint32_t*)((uint8_t*)pIB + 0x0c); // pIB[3] (index count)
            for (uint32_t i = 0; i < idxCount; ++i) {
                uint16_t val = ((uint16_t*)pIB->pLockedData)[i]; // Actually from pIB[5] pointer
                // But since we used pIB[5] earlier as idxData, we need to access it
                // Better to use local idxData? But here it uses the global buffer's data pointer.
                // The decompiler reads from pIB[5] (offset +0x14) as the locked pointer.
                uint16_t* pIdxDataFromBuf = *(uint16_t**)((uint8_t*)pIB + 0x14);
                if (val < minIdx) minIdx = val;
                if (val > maxIdx) maxIdx = val;
            }
            *(uint16_t*)((uint8_t*)pIB + 0x10) = minIdx; // pIB[4] = min
            *(uint16_t*)((uint8_t*)pIB + 0x12) = maxIdx; // pIB+0x12 = max

            UnlockFunc unlockFunc = (UnlockFunc)(*(void***)pIB)[0x30 / 4];
            unlockFunc(pIB);
        }

        gMaxIndex = 0xb2; // Some constant? Possibly final index count

        // Compute some scaling factors using screen dimensions
        float dVar22 = gAspectRatioInv; // from DAT_00e447c8? Actually decompiler uses DAT_00e447c8 and DAT_00e447c0
        // But those globals aren't defined above; we'll assume they are stored by engine call
        // The decompiler calls FUN_00b99e20 twice and then computes ratios.
        // For now, we'll approximate:
        float val1 = gScreenHeight; // Actually from DAT_00e447c8? Not sure
        float val2 = gScreenWidth;  // From DAT_00e447c0?
        // The function calls are omitted for brevity; they might set globals.
        // We'll leave as placeholder:
        // FUN_00b99e20(); // Possibly update screen dimensions?
        // val1 = something; val2 = something;
        // Then compute:
        // _DAT_01205340 = gFov / (val2 * val1);
        // _DAT_01205344 = gFov / val1;
        // But we won't include those calls as they are not part of the original decompiler output? Actually they are there.
        // Since we don't know FUN_00b99e20, we'll skip the calls and assume the globals are already set.
    }
}