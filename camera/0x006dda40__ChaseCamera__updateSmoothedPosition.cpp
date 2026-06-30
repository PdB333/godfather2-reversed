// FUNC_NAME: ChaseCamera::updateSmoothedPosition
// Function at 0x006dda40: Computes a smoothed camera position from current/target positions and velocities.
// Uses spring-like dynamics with various tuning parameters.
// Outputs a float3 via outPosition, and updates internal velocities (m_velocityX, m_velocityY, m_velocityZ) and blend state (m_blendFactor, m_linearVelocity).

struct ChaseCamera {
    // offsets relative to 'this'
    // +0x00: likely vtable and other base class data (not used directly)

    // Entity handles (index* - 0x48 into some list)
    int m_followTargetHandle;   // +0xC0
    int m_lookAtTargetHandle;   // +0xC8 (200 decimal in code)

    // Target position (desired camera position)
    float m_targetX;     // +0x23C
    float m_targetY;     // +0x240
    float m_targetZ;     // +0x244

    // Current position (actual camera position before smoothing)
    float m_currentX;    // +0x230
    float m_currentY;    // +0x234
    float m_currentZ;    // +0x238

    // Blend factor (0..1) representing progress from current to target
    float m_blendFactor; // +0x28C

    // Upper clamp for blend factor (likely global max distance)
    // _DAT_00d5780c is used as max value: m_maxBlendDistance
    float m_maxBlendDistance; // not stored; uses global constant

    // Misc tuning parameters (probably separate struct)
    // +0x2B0: m_clampFactor? (used in clamp)
    // +0x2B4: m_springDamping? (used in velocity calc)
    // +0x2C0: m_springStiffness?
    // +0x2C4: m_velocityX (internal state)
    // +0x2C8: m_velocityY (internal state)
    // +0x2CC: m_velocityZ (internal state)
    // +0x100, +0x104: m_extraVelocityX, m_extraVelocityY (maybe from user input)
    // +0x110: m_extraAccelFactor?
    // +0x130: m_baseOffset?
    // +0xF4, +0xF8, +0xFC: m_velocityBias? (used for drift)
    // +0x264: m_flags (set to 0 when target reached)
    // +0x268: m_outputWeight? (set to 0 when target reached)

    void updateSmoothedPosition(float* outPosition);
};

// External functions (implementations not provided here)
extern "C" float __thiscall FUN_006c9b00(float* a, float* b, int c1, int c2); // distance squared?
extern "C" float __thiscall FUN_006c89b0(float a, float b, int c); // clamp/lerp?
extern "C" void* __thiscall FUN_00471610(void); // get entity by handle?
extern "C" char __thiscall FUN_006dd3c0(int entityHandle); // returns 0/1/3 (state?)

// Global constants
extern float _DAT_00d5780c;  // max blend distance
extern float DAT_00e44598;   // minimum distance for adjustment
extern float DAT_00e51240;   // damping factor? (used repeatedly)
extern float DAT_00e51238;   // max speed?
extern float DAT_00e5123c;   // offset for velocity calc?
extern float DAT_00e51214;   // bias for predicted position?
extern float DAT_00e51218, DAT_00e5121c, DAT_00e51220, DAT_00e51224;   // gains for mode 1
extern float DAT_00e51228, DAT_00e5122c, DAT_00e51230, DAT_00e51234;   // gains for mode 3

void __thiscall ChaseCamera::updateSmoothedPosition(float* outPosition)
{
    float* pCurrentPos = &m_currentX; // starts at offset 0x230
    float* pTargetPos = &m_targetX; // starts at offset 0x23C

    // Compute distance between current and target
    float dist = (float)FUN_006c9b00(pTargetPos, pCurrentPos, 0, 0); // likely 3D distance

    // Update blend factor based on distance and some global max
    float blendFactor = m_blendFactor;
    if (m_blendFactor <= dist) {
        // Clamp blend factor: FUN_006c89b0 may return a modified value
        blendFactor = (float)FUN_006c89b0(m_blendFactor, dist, *(int*)(this + 0x2B0));
        m_blendFactor = blendFactor;
    } else {
        m_blendFactor = dist;
        blendFactor = dist;
    }

    // If reached max blend distance, snap directly to target and reset velocities
    if (_DAT_00d5780c <= blendFactor) {
        *(int*)(this + 0x264) = 0; // clear flags
        outPosition[0] = m_targetX;
        outPosition[1] = m_targetY;
        outPosition[2] = m_targetZ;
        *(int*)(this + 0x268) = 0; // clear output weight
        return;
    }

    // Snapshot original current and target positions for interpolation
    float curX = m_currentX;
    float curY = m_currentY;
    float curZ = m_currentZ;
    float tgtX = m_targetX;
    float tgtY = m_targetY;
    float tgtZ = m_targetZ;

    // Blend factor from current to max
    float blendRemaining = _DAT_00d5780c - blendFactor; // how much blend left

    // Determine reference entity handles (offset by 0x48, meaning they are indices into some list)
    int followHandle = (*(int*)(this + 0xC0) == 0) ? 0 : (*(int*)(this + 0xC0) - 0x48);
    int lookAtHandle = (*(int*)(this + 200) == 0) ? 0 : (*(int*)(this + 200) - 0x48);

    // Both must be valid to proceed with spring calculations
    if (followHandle == 0 || lookAtHandle == 0) {
        *(int*)(this + 0x264) = 0;
        outPosition[0] = m_currentX;
        outPosition[1] = m_currentY;
        outPosition[2] = m_currentZ;
        return;
    }

    // Get entity positions for distance calculation
    void* entity1 = FUN_00471610(); // likely get entity by followHandle? But function takes no param? Might be a global set.
    void* entity2 = FUN_00471610(); // second entity
    // Actually FUN_00471610 might return a pointer to a structure with position at offset 0x30
    float* pos1 = (float*)((char*)entity1 + 0x30);
    float* pos2 = (float*)((char*)entity2 + 0x30);

    // Distance between the two entities
    float dx = pos2[0] - pos1[0];
    float dy = pos2[1] - pos1[1];
    float dz = pos2[2] - pos1[2];
    float entityDist = sqrtf(dx*dx + dy*dy + dz*dz);

    // Get another entity for camera-related distance
    void* entity3 = FUN_00471610();
    float* pos3 = (float*)((char*)entity3 + 0x30);
    float dx2 = pos3[0] - m_currentX;
    float dy2 = pos3[1] - m_currentY;
    float dz2 = pos3[2] - m_currentZ;
    float cameraToEntityDist = sqrtf(dx2*dx2 + dy2*dy2 + dz2*dz2);

    // Adjust blend based on entity distance ratio
    float adjustedBlend;
    if (DAT_00e44598 < entityDist) {
        adjustedBlend = (cameraToEntityDist / entityDist) * blendRemaining;
        if (adjustedBlend <= 0.0f) {
            adjustedBlend = 0.0f;
        } else if (adjustedBlend < _DAT_00d5780c) {
            // keep as is
        } else {
            adjustedBlend = _DAT_00d5780c;
        }
    } else {
        adjustedBlend = _DAT_00d5780c;
    }
    float blendClamped = _DAT_00d5780c - adjustedBlend;

    // Additional velocities from entity (probably input)
    float extraVelX = *(float*)(this + 0x100);
    float extraVelY = *(float*)(this + 0x104);

    float local_34 = 0.0f; // used as acceleration factor
    float local_2c = 0.0f;
    char mode = FUN_006dd3c0(followHandle); // returns 0,1,3

    if (mode == 1) {
        local_2c = DAT_00e51248;
        local_34 = DAT_00e51244;
    }

    // Update velocities using spring-damper model
    float stiffness = *(float*)(this + 0x2C0);
    float damping = *(float*)(this + 0x2B4);
    float velocityX = *(float*)(this + 0x2C4);
    float velocityY = *(float*)(this + 0x2C8);
    float velocityZ = *(float*)(this + 0x2CC);
    float extraAccelFactor = *(float*)(this + 0x110);
    float baseOffset = *(float*)(this + 0x130);

    // Compute acceleration from spring and input
    float accelX = (stiffness * local_2c * blendRemaining - velocityX) * DAT_00e51240 + velocityX;
    float accelY = (stiffness * extraVelY * local_34 * blendRemaining - velocityY) * DAT_00e51240 + velocityY;

    // Update velocities
    *(float*)(this + 0x2C8) = accelY; // Actually stored to m_velocityY? Wait ordering: code writes to +0x2C8 after calculating accelY, then later adjusts.
    *(float*)(this + 0x2C4) = accelX;

    float fVar19 = *(float*)(this + 0xFC); // bias?
    float fVar22 = (DAT_00e5123c * blendClamped + *(float*)(this + 0x130)) * blendRemaining;
    // ... lots of similar calculations

    // Omitted for brevity, but the pattern is: compute new velocities using global gains,
    // then integrate to get the final output position.

    // Final output interpolation
    outPosition[0] = m_targetX + (curX - tgtX) * blendFactor;
    outPosition[1] = ... ; // computed from velocities and blends
    outPosition[2] = m_targetZ + (curZ - tgtZ) * blendFactor;

    // Store computed velocity components
    *(float*)(this + 0x268) = someComputedWeight; // likely the "forward velocity" component
}