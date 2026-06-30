// FUNC_NAME: MovementController::UpdateSteering
// Function at 0x006d14b0 - Updates object's velocity towards a target with smoothing and speed clamping.
// TODO: Identify actual class (likely part of NPC/Vehicle movement). 
// Param_1 (this) has fields:
//   +0x14 float m_forwardX? (used in dot product)
//   +0x16 float m_forwardZ? (used in dot product)
//   +0x18 int m_velocityX (stored as int but treated as float)
//   +0x19 int m_velocityY
//   +0x1a int m_velocityZ
//   +0x1b int m_velocityW? (vertical? not used in normalization)
//   +0x20 float m_speedThreshold (if >0, forces update even if disabled)
//   +0x22 float m_desiredSpeed (magnitude to clamp velocity to)
//   +0x23 float m_smoothingFactor (for exponential interpolation)
//   +0x25 float m_overrideSpeed (if non-zero and game not paused, skips speed normalization)
// Param_2 (char) bForceTurn? (implies bVar5 true only if set and not paused)
// Param_3 (undefined4) unused
// Param_4 (TargetState*) target object with:
//   +0x20 float targetVelocityX
//   +0x28 float targetVelocityZ
//   +0x30 float targetPosX
//   +0x34 float targetPosY
//   +0x38 float targetPosZ
//   +0x3c float targetPosW? (constant subtracted by _DAT_00d5780c)
// Param_5 (float[3]) currentPosition (x,y,z)
// Param_6 (char) bEnable? (if 0, always runs; if non-zero, conditionally runs)
// Param_7 (char*) outFlags - set to 1 if moving towards target (dot product > 0)

#include <math.h> // for sqrt

// External globals (constants / parameters)
extern float g_speedScaleTime;          // DAT_00e51178
extern float g_yOffset;                // _DAT_00e5112c (added to current Y)
extern float g_distanceThresholdScale;  // DAT_0112a864
extern float g_speedThresholdScale;     // DAT_00e51184
extern float g_angleDeadZone;          // DAT_00e44564
extern float g_unknownSubtract;        // _DAT_00d5780c (subtracted from targetPosW)

// External function: likely checks if game is paused
extern char IsGamePaused(); // FUN_00410eb0

void __thiscall MovementController::UpdateSteering(
    MovementController* this,
    char bForceTurn,
    int unused_param,
    const TargetState* target,
    const float* currentPos,
    char bEnable,
    char* outFlags)
{
    char bVar5;
    char paused;
    float smoothingFactor;
    float dx, dz, magnitude;
    float targetDeltaX, targetDeltaZ, targetDeltaW;
    float dotProduct;
    float scaledDist;
    float desiredSpeed;
    
    *outFlags = 0;
    
    // Determine bVar5: true only if bForceTurn is set and game is not paused
    if ((bForceTurn == 0) || (paused = IsGamePaused(), paused != 0)) {
        bVar5 = 0;
    } else {
        bVar5 = 1;
    }
    
    // Condition to proceed with velocity calculation
    // If bEnable==0, always proceed; else need m_speedThreshold>0 or bVar5
    if ((bEnable == 0) || (0.0f < this->m_speedThreshold) || (bVar5 != 0)) {
        float currX = currentPos[0];
        float currY = currentPos[1];
        float currZ = currentPos[2];
        
        // Target velocity components scaled
        float targetVelX = target->velocityX * g_speedScaleTime;
        float targetVelZ = target->velocityZ * g_speedScaleTime;
        
        // Current Y with offset
        float currYOffset = currY + g_yOffset;
        
        // Target position (from matrix translation)
        float targetX = target->posX;
        float targetY = target->posY;
        float targetZ = target->posZ;
        float targetW = target->posW - g_unknownSubtract;
        
        // Get this object's position (via virtual function at vtable+0x10)
        float* thisPos = (float*)(this->vtable->GetPosition)(this); // struct with x,z at [0],[2]
        
        // Distance from this object to target (only x and z used)
        dx = targetX - thisPos[0];
        dz = targetZ - thisPos[2];
        float dist = sqrt(dx*dx + dz*dz);
        
        float scaledDist1 = g_distanceThresholdScale * dist;
        float scaledDist2 = g_speedThresholdScale * dist;
        
        // Dot product of (this->forwardX, this->forwardZ) with (dx, dz)
        dotProduct = (float)this->m_forwardX * dx + (float)this->m_forwardZ * dz;
        
        if (dotProduct > 0.0f) {
            *outFlags = 1; // Moving towards target
        }
        
        // Check if dotProduct exceeds dead zone relative to distance
        if ((g_angleDeadZone - scaledDist1 < dotProduct) && 
            ((bForceTurn != 0) || (dotProduct < scaledDist2))) {
            // Exponential smoothing towards target position with velocity prediction
            smoothingFactor = (float)this->m_smoothingFactor;
            
            // Target for X: targetX - (currX - targetVelX) = (targetX - currX) + targetVelX
            float targetVelXForX = targetX - (currX - targetVelX);
            this->m_velocityX = (int)(((targetVelXForX - (float)this->m_velocityX) * smoothingFactor) + (float)this->m_velocityX);
            
            float targetVelY = targetY - currYOffset; // note: using currYOffset (currY + g_yOffset)
            this->m_velocityY = (int)(((targetVelY - (float)this->m_velocityY) * smoothingFactor) + (float)this->m_velocityY);
            
            float targetVelForZ = targetZ - (currZ - targetVelZ);
            this->m_velocityZ = (int)(((targetVelForZ - (float)this->m_velocityZ) * smoothingFactor) + (float)this->m_velocityZ);
            
            float targetVelW = targetW; // no velocity component for W? likely vertical
            this->m_velocityW = (int)(((targetVelW - (float)this->m_velocityW) * smoothingFactor) + (float)this->m_velocityW);
        }
    }
    
    // Normalize velocity vector to desired speed if necessary
    magnitude = sqrt((float)this->m_velocityX * (float)this->m_velocityX +
                     (float)this->m_velocityY * (float)this->m_velocityY +
                     (float)this->m_velocityZ * (float)this->m_velocityZ);
    
    if ((magnitude > 0.0f) && 
        ((this->m_overrideSpeed == 0.0f) || (paused = IsGamePaused(), paused != 0))) {
        desiredSpeed = this->m_desiredSpeed / magnitude;
        this->m_velocityX = (int)(desiredSpeed * (float)this->m_velocityX);
        this->m_velocityY = (int)(desiredSpeed * (float)this->m_velocityY);
        this->m_velocityZ = (int)(desiredSpeed * (float)this->m_velocityZ);
        this->m_velocityW = (int)(desiredSpeed * (float)this->m_velocityW);
    }
}