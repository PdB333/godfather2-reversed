// FUNC_NAME: Camera::updateCameraMatrix

#include <cstdint>
#include <cmath>

// Global camera matrix buffer (DAT_0112dba4)
extern CameraMatrix* gCameraMatrix;

// Global time step (DAT_00d5780c)
extern float gTimeStep;

// Forward declarations for helper functions
void FUN_008334a0();  // getTimeOrSync?
float FUN_008255b0(); // getCurrentTime?
void FUN_008255f0(float* timePtr, float delta); // advanceTime?

struct CameraMatrix {
    float pad_0x00[1];   // +0x00
    float rotation[6];   // +0x04 (6 floats: quaternion + translation? or rotation matrix?)
    float pad_0x1C[1];   // +0x1C
    float row0[4];       // +0x20 (row 0 of result matrix)
    float row1[4];       // +0x30 (row 1)
    float row2[4];       // +0x40 (row 2)
};

struct CameraInternal {
    float unknown_0x00[13];      // +0x00-0x33
    float rotation[6];           // +0x34 (copied to global)
    float unknown_0x4C[13];      // +0x4C-0x7F
    float projectionParams[4];   // +0x80 (maybe near/far/fov?)
    float extraParams1[4];       // +0x90 (scale factors?)
    float extraParams2[4];       // +0xA0 (another set)
    // +0xAC possibly end
};

struct InterpolationState {
    int id;          // +0x00
    float time;      // +0x04 (param_2[1])
};

void __thiscall Camera::updateCameraMatrix(CameraInternal* thisPtr, InterpolationState* interpState)
{
    CameraMatrix* gMat = gCameraMatrix;
    float fVar1, fVar3, fVar4, fVar5;
    uint32_t uVar2, uVar7, uVar8, uVar9, uVar10;

    // Copy rotation/translation from camera to global (if changed)
    if (*(uint32_t*)(gMat + 1) != *(uint32_t*)(thisPtr + 0x34)) {
        *(uint32_t*)(&gMat->rotation[0]) = *(uint32_t*)(thisPtr + 0x34);
        *(uint32_t*)(&gMat->rotation[1]) = *(uint32_t*)(thisPtr + 0x38);
        *(uint32_t*)(&gMat->rotation[2]) = *(uint32_t*)(thisPtr + 0x3C);
        *(uint32_t*)(&gMat->rotation[3]) = *(uint32_t*)(thisPtr + 0x40);
        *(uint32_t*)(&gMat->rotation[4]) = *(uint32_t*)(thisPtr + 0x44);
        *(uint32_t*)(&gMat->rotation[5]) = *(uint32_t*)(thisPtr + 0x48);
    }

    if (interpState == nullptr) {
        // No interpolation: compute matrix directly
        fVar1 = thisPtr->extraParams1[3];   // +0x9C
        fVar3 = thisPtr->extraParams1[1];   // +0x94
        fVar4 = thisPtr->extraParams1[2];   // +0x98
        fVar5 = thisPtr->extraParams1[3];   // +0x9C (same as fVar1)

        // Store old last components to preserve them
        uVar7 = *(uint32_t*)(&gMat->row0[3]);   // +0x2C
        uVar8 = *(uint32_t*)(&gMat->row1[3]);   // +0x3C

        // Scale first three components of row0 by fVar1
        gMat->row0[0] = fVar1 * thisPtr->extraParams1[0];   // +0x90
        gMat->row0[1] = fVar1 * fVar3;
        gMat->row0[2] = fVar1 * fVar4;
        gMat->row0[3] = fVar1 * fVar5;

        // Restore row0[3] (don't scale the w component)
        *(uint32_t*)(&gMat->row0[3]) = uVar7;

        // Same for row1: scale by fVar1 (but fVar1 is same as before)
        gMat->row1[0] = fVar1 * thisPtr->extraParams2[0];   // +0xA0
        gMat->row1[1] = fVar1 * thisPtr->extraParams2[1];   // +0xA4
        gMat->row1[2] = fVar1 * thisPtr->extraParams2[2];   // +0xA8
        gMat->row1[3] = fVar1 * thisPtr->extraParams2[3];   // +0xAC

        // Restore row1[3]
        *(uint32_t*)(&gMat->row1[3]) = uVar8;

        // Copy projection params to global (row2)
        uVar7 = *(uint32_t*)(thisPtr + 0x80);
        uVar8 = *(uint32_t*)(thisPtr + 0x84);
        uVar9 = *(uint32_t*)(thisPtr + 0x88);
        uVar10 = *(uint32_t*)(thisPtr + 0x8C);
    } else {
        // Interpolation branch (smooth transition)
        FUN_008334a0(); // latch time? 
        uVar10 = DAT_00e44980;  // global values for interpolation
        uVar8 = DAT_00e44620;
        uVar9 = DAT_00d5ef88;
        uVar7 = DAT_00d5d7b8;
        fVar1 = gTimeStep; // _DAT_00d5780c

        FUN_008255b0(); // get current time
        float currentTime = gTimeStep; // Actually DAT_00d5780c again? Might be time value
        // save time before adjusting
        float local_98 = gTimeStep;

        if (interpState->id == thisPtr->unknown_0x00[3]) { // +0x0C
            local_98 = gTimeStep - interpState->time;
            FUN_008255f0((float*)(interpState->id) + 0x30, interpState->time);  // adjust time of source camera
        }

        // Set destination camera time to computed delta
        FUN_008255f0((float*)(thisPtr) + 0x30, local_98);  // +0x30 assumed time offset

        uVar2 = *(uint32_t*)(&gMat->row0[3]);
        // Square the scalar and set all components to that value
        gMat->row0[0] = fVar1 * fVar1;
        gMat->row0[1] = fVar1 * fVar1;
        gMat->row0[2] = fVar1 * fVar1;
        gMat->row0[3] = fVar1 * fVar1;
        *(uint32_t*)(&gMat->row0[3]) = uVar2; // restore previous w

        uVar2 = *(uint32_t*)(&gMat->row1[3]);
        gMat->row1[0] = fVar1 * fVar1;
        gMat->row1[1] = fVar1 * fVar1;
        gMat->row1[2] = fVar1 * fVar1;
        gMat->row1[3] = fVar1 * fVar1;
        *(uint32_t*)(&gMat->row1[3]) = uVar2;
    }

    // Set row2 (projection row) from either camera's projection params or global defaults
    *(uint32_t*)(&gMat->row2[0]) = uVar7;
    *(uint32_t*)(&gMat->row2[1]) = uVar8;
    *(uint32_t*)(&gMat->row2[2]) = uVar9;
    *(uint32_t*)(&gMat->row2[3]) = uVar10;

    // Normalize row2[1] by time step (probably adjust perspective scale)
    gMat->row2[1] = gTimeStep / gMat->row2[1];

    return;
}