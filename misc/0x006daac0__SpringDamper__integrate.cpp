// FUNC_NAME: SpringDamper::integrate
// Address: 0x006daac0
// Role: Integrates a 4-component spring-damper system towards a target position.
// The spring state includes position (4 floats at +0x10), velocity (4 floats at +0x20),
// stiffness (+0x04), damping (+0x08), and a flag (+0x00) for angular wrapping.
// Uses sub-stepping based on global constants.

// Global constants (from data section)
extern float g_springTimeScale;      // _DAT_00d5f63c
extern float g_springDampingBase;    // _DAT_00d5780c

// External function: wraps a value (likely angle) into a range (e.g., [-pi, pi])
extern float wrapValue(float value); // FUN_004a1580

void __thiscall SpringDamper::integrate(char* thisPtr, float* targetAndOutput, float dt)
{
    // Compute number of sub-steps
    int subSteps = 1 - (int)(dt * g_springTimeScale);
    
    // Adjust time step per sub-step
    float subDt = (g_springDampingBase / (float)subSteps) * dt;
    
    // Compute damping factor for velocity decay per sub-step
    float dampingFactor = g_springDampingBase - 
                          (g_springDampingBase - *(float*)(thisPtr + 8)) * 
                          (g_springDampingBase / (float)subSteps);
    
    if (subSteps > 0) {
        do {
            // Compute delta from current position to target (input in targetAndOutput)
            float deltaX = *targetAndOutput - *(float*)(thisPtr + 0x10);
            float deltaY = targetAndOutput[1] - *(float*)(thisPtr + 0x14);
            float deltaZ = targetAndOutput[2] - *(float*)(thisPtr + 0x18);
            float deltaW = targetAndOutput[3] - *(float*)(thisPtr + 0x1c);
            
            // If angular wrapping flag is set, wrap each delta component
            if (*thisPtr != '\0') {
                deltaX = wrapValue(deltaX);
                deltaY = wrapValue(deltaY);
                deltaZ = wrapValue(deltaZ);
                deltaW = wrapValue(deltaW);
            }
            
            // Save current velocity[3] before overwriting (for later restoration)
            float savedVelocityW = *(float*)(thisPtr + 0x2c);
            
            // Update velocity: v += stiffness * subDt * delta
            float stiffness = *(float*)(thisPtr + 4);
            float velScale = stiffness * subDt;
            *(float*)(thisPtr + 0x20) += velScale * deltaX;
            *(float*)(thisPtr + 0x24) += velScale * deltaY;
            *(float*)(thisPtr + 0x28) += velScale * deltaZ;
            *(float*)(thisPtr + 0x2c)  = velScale * deltaW + *(float*)(thisPtr + 0x2c);
            // Restore velocity[3] (note: the assignment above is overwritten by the next line)
            *(float*)(thisPtr + 0x2c) = savedVelocityW;
            
            // Save current position[3] before overwriting
            float savedPosW = *(float*)(thisPtr + 0x1c);
            
            // Update position: p += v * subDt
            *(float*)(thisPtr + 0x10) += *(float*)(thisPtr + 0x20) * subDt;
            *(float*)(thisPtr + 0x14) += *(float*)(thisPtr + 0x24) * subDt;
            *(float*)(thisPtr + 0x18) += *(float*)(thisPtr + 0x28) * subDt;
            *(float*)(thisPtr + 0x1c)  = *(float*)(thisPtr + 0x2c) * subDt + *(float*)(thisPtr + 0x1c);
            // Restore position[3]
            *(float*)(thisPtr + 0x1c) = savedPosW;
            
            // If angular wrapping flag is set, wrap position components
            if (*thisPtr != '\0') {
                *(float*)(thisPtr + 0x10) = wrapValue(*(float*)(thisPtr + 0x10));
                *(float*)(thisPtr + 0x14) = wrapValue(*(float*)(thisPtr + 0x14));
                *(float*)(thisPtr + 0x18) = wrapValue(*(float*)(thisPtr + 0x18));
            }
            
            subSteps--;
            
            // Save current velocity[3] before damping
            float savedVelW2 = *(float*)(thisPtr + 0x2c);
            
            // Apply damping to velocity: v *= dampingFactor
            *(float*)(thisPtr + 0x20) *= dampingFactor;
            *(float*)(thisPtr + 0x24) *= dampingFactor;
            *(float*)(thisPtr + 0x28) *= dampingFactor;
            *(float*)(thisPtr + 0x2c)  = *(float*)(thisPtr + 0x2c) * dampingFactor;
            // Restore velocity[3]
            *(float*)(thisPtr + 0x2c) = savedVelW2;
            
        } while (subSteps != 0);
    }
    
    // Copy final position to output (targetAndOutput)
    float posX = *(float*)(thisPtr + 0x10);
    float posY = *(float*)(thisPtr + 0x14);
    float posZ = *(float*)(thisPtr + 0x18);
    float posW = *(float*)(thisPtr + 0x1c);
    *targetAndOutput = posX;
    targetAndOutput[1] = posY;
    targetAndOutput[2] = posZ;
    targetAndOutput[3] = posW;
}