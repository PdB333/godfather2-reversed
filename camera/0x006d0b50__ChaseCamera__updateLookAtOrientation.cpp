// FUNC_NAME: ChaseCamera::updateLookAtOrientation

#include <cmath>

// Globals (from data references)
extern float g_horizontalSpringConstant;        // 0x00e51128
extern float g_desiredHorizontalOffset;          // 0x00e44564
extern float g_minDistanceSqForAdjustment;       // 0x00d5f2b4
extern float g_one;                               // 0x00d5780c (often 1.0f)
extern float g_verticalAdjustmentFactor;         // 0x00e51124
extern char g_previousFlag;                       // 0x0112a860
extern float g_timeAccum;                         // 0x00e510d0
extern float g_timeTotal;                         // 0x00e510cc
extern float g_timeConstant;                      // 0x00d5eee4
extern float g_dampingNormal;                     // 0x00e446a0
extern float g_dampingTransition;                 // 0x00d5f00c
extern float g_rotationSmoothFactor;              // 0x00d5c458
extern float g_minBlendDistance;                  // 0x00e51170
extern float g_maxBlendDistance;                  // 0x00e51178

// External helper (likely updates frame time globals)
void updateFrameTime();                            // 0x00b99fcb

void __thiscall ChaseCamera::updateLookAtOrientation(float *outputQuat, float *inputQuat, char isTransitioning)
{
    float *cameraPos;       // pfVar11 - from vtable[0x14]
    float *targetPos;       // pfVar12 - from vtable[0x10]
    float fVar1, fVar2, fVar3, fVar4;            // copies of inputQuat
    float fVar5, fVar6, fVar7, fVar8;            // inputQuat used for distance
    float fVar9, fVar10, fVar13, fVar14;
    float fVar16, fVar17, fVar18;
    float horizontalOffset, verticalDiff, distSq;
    double dVar15;
    
    // Get positions from derived class
    cameraPos = this->getCameraPosition();        // vtable+0x14
    targetPos = this->getTargetPosition();        // vtable+0x10
    
    fVar9 = g_horizontalSpringConstant;
    
    // Compute horizontal offset in the x-z plane? Actually uses z as vertical, x as horizontal with desired offset
    verticalDiff = targetPos[2] - cameraPos[2];
    horizontalOffset = g_desiredHorizontalOffset - (targetPos[0] - cameraPos[0]);
    
    distSq = horizontalOffset * horizontalOffset + verticalDiff * verticalDiff;
    
    // If distance is small, no adjustment; otherwise compute scaling
    if (distSq <= g_minDistanceSqForAdjustment) {
        fVar13 = 0.0f;
    } else {
        fVar13 = g_one / sqrtf(distSq);
    }
    
    // Apply vertical/horizontal scaling factors
    fVar17 = g_verticalAdjustmentFactor * fVar13 * verticalDiff;
    fVar13 = g_verticalAdjustmentFactor * fVar13 * horizontalOffset;
    
    // Track previous flag state to detect transition
    if (isTransitioning != g_previousFlag) {
        g_timeAccum = g_timeTotal - g_timeAccum;  // reset accumulator on state change
    }
    
    // Choose damping factor based on transition flag
    if (isTransitioning != 0) {
        fVar18 = g_dampingTransition;
    } else {
        fVar18 = g_dampingNormal;
    }
    
    // Update time and compute damping progress
    dVar15 = (double)(((g_timeAccum / g_timeTotal) * g_timeConstant - g_one) * fVar18);
    updateFrameTime();
    
    // Compute orientation adjustment amount for this frame
    fVar18 = ((float)dVar15 + g_one) * g_rotationSmoothFactor;
    
    if (isTransitioning == 0) {
        // Normal mode: lerp from full adjustment to zero
        fVar18 = g_one - fVar18;
        fVar16 = (0.0f - 0.0f) * fVar18;    // still 0
        fVar17 = (0.0f - fVar17) * fVar18 + fVar17;
        fVar13 = (0.0f - fVar13) * fVar18 + fVar13;
    } else {
        // Transitioning mode: lerp from zero to full adjustment
        fVar16 = (0.0f - 0.0f) * fVar18;    // still 0
        fVar17 = (fVar17 - 0.0f) * fVar18 + 0.0f;
        fVar13 = (fVar13 - 0.0f) * fVar18 + 0.0f;
    }
    
    // Copy input orientation for blending
    fVar1 = inputQuat[0];
    fVar2 = inputQuat[1];
    fVar3 = inputQuat[2];
    fVar4 = inputQuat[3];
    
    // Get camera position again for distance-based blend factor
    cameraPos = this->getCameraPosition();        // vtable+0x10 (redundant call)
    
    fVar5 = inputQuat[0];
    fVar6 = inputQuat[1];
    fVar7 = inputQuat[2];
    fVar8 = inputQuat[3];
    
    // Compute normalized distance from input (treated as world position) to camera
    fVar14 = (sqrtf((fVar6 - cameraPos[1]) * (fVar6 - cameraPos[1]) +
                    (fVar7 - cameraPos[2]) * (fVar7 - cameraPos[2]) +
                    (fVar5 - cameraPos[0]) * (fVar5 - cameraPos[0])) - g_minBlendDistance) /
             (g_maxBlendDistance - g_minBlendDistance);
    
    // Clamp to [0,1]
    fVar10 = 0.0f;
    if ((fVar14 <= 0.0f) || (fVar10 = g_one, g_one <= fVar14)) {
        fVar14 = fVar10;
    }
    
    // Blend: output = inputOrientation * (1 - blend) + (inputOrientation + adjustment) * blend
    outputQuat[0] = ((fVar1 + fVar17) - fVar5) * fVar14 + fVar5;
    outputQuat[1] = ((fVar2 + fVar16 + fVar9) - fVar6) * fVar14 + fVar6;
    outputQuat[2] = ((fVar3 + fVar13) - fVar7) * fVar14 + fVar7;
    outputQuat[3] = ((fVar4 + fVar18 * 0.0f + 0.0f) - fVar8) * fVar14 + fVar8;
    
    // Save current flag for next frame
    g_previousFlag = isTransitioning;
}