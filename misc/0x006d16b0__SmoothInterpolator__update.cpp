// FUNC_NAME: SmoothInterpolator::update

#include <cmath>

// External globals (likely constants or timestep-related)
extern float g_interpolationConstant;       // _DAT_00d5780c (likely 1.0f)
extern float g_yScaleFactor;                // _DAT_00e51138
extern float g_lerpFactorDefault;           // _DAT_00e51160
extern float g_lerpFactorAlt;               // _DAT_00e511a0

// External check (likely a global state, e.g., isMenuOpen or useSmoothPath)
extern bool __cdecl isUsingAltMode();        // FUN_00410eb0

void __thiscall SmoothInterpolator::update(
    float deltaTime,
    float* targetPos,        // param_3: at least 3 floats (4th used if use4D true)
    float* targetOrient,     // param_4: at least 3 floats
    bool use4D               // param_6: if false uses 3-component pos, else 4-component
)
{
    // Current state (this offsets)
    // +0x10: current position (x,y,z,w if applicable)
    // +0x40: current velocity (x,y,z,w)
    // +0x8c: interpolation factor (0..1)
    // +0x90: max acceleration magnitude
    // +0x20: orientation (x,y,z,w) - only y is smoothly blended

    float lerpFactor = *(float*)(this + 0x8c);           // blending factor
    float maxAccel   = *(float*)(this + 0x90);           // maximum acceleration magnitude

    // Interpolated target position (linear blend)
    float interpX, interpY, interpZ, interpW;
    float* curPos = (float*)(this + 0x10);
    float* curVel = (float*)(this + 0x40);

    if (!use4D && !isUsingAltMode()) {
        // 3D position with y scaled
        interpX = (targetPos[0] - curPos[0]) * lerpFactor + curPos[0];
        interpY = (targetPos[1] - curPos[1]) * lerpFactor * g_yScaleFactor + curPos[1];
        interpZ = (targetPos[2] - curPos[2]) * lerpFactor + curPos[2];
        interpW = curPos[3]; // keep w unchanged (may be unused)
    } else {
        // 4D position (no extra scaling)
        interpX = (targetPos[0] - curPos[0]) * lerpFactor + curPos[0];
        interpY = (targetPos[1] - curPos[1]) * lerpFactor + curPos[1];
        interpZ = (targetPos[2] - curPos[2]) * lerpFactor + curPos[2];
        interpW = (targetPos[3] - curPos[3]) * lerpFactor + curPos[3];
    }

    // Compute displacement from interpolated to current
    float dx = interpX - curPos[0];
    float dy = interpY - curPos[1];
    float dz = interpZ - curPos[2];
    float dw = interpW - curPos[3];

    // Rate factor (inverse of some constant over deltaTime)
    float rate = g_interpolationConstant / deltaTime;

    // Desired velocities
    float desiredVx = rate * dx;
    float desiredVy = rate * dy;
    float desiredVz = rate * dz;
    float desiredVw = rate * dw;

    // Acceleration (difference between desired and current velocity, scaled by rate)
    float ax = (desiredVx - curVel[0]) * rate;
    float ay = (desiredVy - curVel[1]) * rate;
    float az = (desiredVz - curVel[2]) * rate;
    // Note: w velocity is not used in acceleration clamping

    // Clamp acceleration magnitude if needed
    float accelMag = sqrtf(ax * ax + ay * ay + az * az);
    if (!use4D && (maxAccel < accelMag)) {
        float scale = maxAccel / accelMag;
        // Clamp desired velocities (blend towards clamped acceleration)
        float newVx = scale * ax * deltaTime + curVel[0];
        float newVy = scale * ay * deltaTime + curVel[1];
        float newVz = scale * az * deltaTime + curVel[2];
        float newVw = scale * (desiredVw - curVel[3]) * rate * deltaTime + curVel[3];

        // Update displacement using clamped velocity * time
        dx = deltaTime * newVx;
        dy = deltaTime * newVy;
        dz = deltaTime * newVz;
        dw = deltaTime * newVw;

        // Set new velocity to clamped version
        curVel[0] = newVx;
        curVel[1] = newVy;
        curVel[2] = newVz;
        curVel[3] = newVw;
    } else {
        // No clamping: use the original displacement directly and set velocities
        curVel[0] = desiredVx;
        curVel[1] = desiredVy;
        curVel[2] = desiredVz;
        curVel[3] = desiredVw;
    }

    // Update position
    curPos[0] += dx;
    curPos[1] += dy;
    curPos[2] += dz;
    curPos[3] += dw;

    // Update orientation (smooth blend for one component)
    float orientLerpFactor;
    if (isUsingAltMode()) {
        orientLerpFactor = g_lerpFactorAlt;
    } else {
        orientLerpFactor = g_lerpFactorDefault;
    }

    float* curOrient = (float*)(this + 0x20);
    // Set x and z directly (instantaneous)
    curOrient[0] = targetOrient[0];
    curOrient[2] = targetOrient[2];
    // Smooth blend for y component
    curOrient[1] = (g_interpolationConstant - orientLerpFactor) * curOrient[1] +
                   targetOrient[1] * orientLerpFactor;
    // Set w to constant (maybe 1.0 for quaternion)
    curOrient[3] = g_interpolationConstant;
}