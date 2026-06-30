// FUNC_NAME: WheelConstraint::updateSuspension
// Origin: 0x0058e240 – Updates suspension spring/damper forces for a single wheel
// Theory: Combines a spring-damper constraint with position interpolation (PID-like)
//         and writes final transforms to a transform manager for rendering/physics.

#include <cmath>

#define SQRT_EPSILON_SQR   (0.0001f) // DAT_00e2cbe0
#define VELOCITY_EPSILON   (0.01f)   // DAT_00e2e210
#define CROSS_MIN_SQR      (1.0e-6f) // DAT_00e2b05c
#define INV_SQRT_SCALE     (1.0f)    // DAT_00e2b1a4
#define DAMPING_K          (2.0f)    // DAT_00e448cc
#define FORCE_THRESHOLD    (0.5f)    // DAT_00e3ac54

struct WheelConstraint {
    int transformIndices[4];          // +0x00..+0x0C: indices into transform array
    float velocity[4];                // +0x14..+0x17: (vx, vy, vz, vw?) stored as ints
    float targetPos[4];               // +0x24..+0x27: desired position (x,y,z,w?)
    float currentPos[4];              // +0x34..+0x37: actual position (x,y,z,w?)
    float prevPos[4];                 // +0x44..+0x47: previous frame position
    float rotationQuat[4];            // +0x38..+0x3B: orientation (quaternion)
    float alignUp[3];                 // +0x5C..+0x60? (based on unaff_EDI+0x5C)
    float alignDir[3];               // +0x58..+0x5C? (unused?)
    // Additional fields … up to +0x60
};

// External math helpers (EARS engine)
extern float  invSqrt();                     // FAST rsqrt approximation
extern void   normalizeVector3(float* v);    // FUN_0058dfa0
extern void   crossProduct(float* result, const float* a, const float* b); // FUN_0056cba0
extern void   applyQuaternion(float* v, const float* q);                    // FUN_0056cef0 (transform vector by quaternion)
extern void   copyTransform(float* dst, const float* src);                  // FUN_0056d530
extern void   clearTransform(float* mat);                                   // FUN_00424470
extern void   identityTransform(float* mat);                                // FUN_00417560

// Internal helper: Normalize vector if length > epsilon
static float normalizeSafe(float& x, float& y, float& z, float& w) {
    float lenSq = x*x + y*y + z*z + w*w;
    if (lenSq <= SQRT_EPSILON_SQR) {
        return 0.0f;
    }
    float invLen = INV_SQRT_SCALE / std::sqrt(lenSq);
    x *= invLen;
    y *= invLen;
    z *= invLen;
    w *= invLen;
    return lenSq; // return original squared length?
}

void WheelConstraint::updateSuspension(TransformManager* mgr, float dt)
{
    // Clamp input delta
    if (dt < 0.0f) dt = 0.0f;

    // Read vehicle state (from this)
    float curX = (float)this->velocity[0];      // +0x15? Actually +0x14 is velocity
    float curY = (float)this->velocity[1];      // +0x15
    float curZ = (float)this->velocity[2];      // +0x16
    float curW = (float)this->velocity[3];      // +0x17

    // Target position (wheel attachment point)
    float tgtX = (float)this->targetPos[0];     // +0x24
    float tgtY = (float)this->targetPos[1];     // +0x25
    float tgtZ = (float)this->targetPos[2];     // +0x26
    float tgtW = (float)this->targetPos[3];     // +0x27

    // Delta from target to current (spring stretch)
    float dx = this->currentPos[0] - this->prevPos[0];
    float dy = this->currentPos[1] - this->prevPos[1];
    float dz = this->currentPos[2] - this->prevPos[2];
    float dw = this->currentPos[3] - this->prevPos[3];

    // Vector from previous to target
    float toTargetX = tgtX - this->currentPos[0];
    float toTargetY = tgtY - this->currentPos[1];
    float toTargetZ = tgtZ - this->currentPos[2];
    float toTargetW = tgtW - this->currentPos[3];

    // Velocity of current point
    float velX = (float)this->velocity[0];
    float velY = (float)this->velocity[1];
    float velZ = (float)this->velocity[2];
    float velW = (float)this->velocity[3];

    // Compute projection coefficient (for spring damping)
    float dx2 = dx*dx + dy*dy + dz*dz + dw*dw;
    float toTargetSq = toTargetX*toTargetX + toTargetY*toTargetY + toTargetZ*toTargetZ + toTargetW*toTargetW;
    float dot = dx*toTargetX + dy*toTargetY + dz*toTargetZ + dw*toTargetW;
    float ratio = 1.0f; // placeholder for DAT_00e2cd54

    // (simplified: projection of current-vector onto target-vector)
    float lambda = ( (dx2 + toTargetSq - toTargetSq) / dx2 ) * ratio;  // DEBUG: original has complex expression

    // Position interpolation along spring
    float interpX = lambda * dx + this->prevPos[0];
    float interpY = lambda * dy + this->prevPos[1];
    float interpZ = lambda * dz + this->prevPos[2];
    float interpW = lambda * dw + this->prevPos[3];

    // Compute spring force direction (from interp to current)
    float toCurrX = curX - interpX;
    float toCurrY = curY - interpY;
    float toCurrZ = curZ - interpZ;
    float toCurrW = curW - interpW;

    // Normalize spring direction
    float springLenSq = toCurrX*toCurrX + toCurrY*toCurrY + toCurrZ*toCurrZ + toCurrW*toCurrW;
    float invSpringLen = 0.0f;
    if (springLenSq > SQRT_EPSILON_SQR) {
        invSpringLen = INV_SQRT_SCALE / std::sqrt(springLenSq);
    }
    toCurrX *= invSpringLen;
    toCurrY *= invSpringLen;
    toCurrZ *= invSpringLen;
    toCurrW *= invSpringLen;

    // Wind force / damping
    float windForceX = tgtX - this->prevPos[0];
    float windForceY = tgtY - this->prevPos[1];
    float windForceZ = tgtZ - this->prevPos[2];
    float windForceW = tgtW - this->prevPos[3];
    float windLenSq = windForceX*windForceX + windForceY*windForceY + windForceZ*windForceZ + windForceW*windForceW;
    float invWindLen = 0.0f;
    if (windLenSq > SQRT_EPSILON_SQR) {
        invWindLen = INV_SQRT_SCALE / std::sqrt(windLenSq);
    }
    windForceX *= invWindLen;
    windForceY *= invWindLen;
    windForceZ *= invWindLen;
    windForceW *= invWindLen;

    // Project wind onto spring direction
    float proj = windForceX*toCurrX + windForceY*toCurrY + windForceZ*toCurrZ + windForceW*toCurrW;

    // Normalize the remaining component
    float compX = windForceX - proj * toCurrX;
    float compY = windForceY - proj * toCurrY;
    float compZ = windForceZ - proj * toCurrZ;
    float compW = windForceW - proj * toCurrW;
    float compLenSq = compX*compX + compY*compY + compZ*compZ + compW*compW;
    float invCompLen = 0.0f;
    if (compLenSq > SQRT_EPSILON_SQR) {
        invCompLen = INV_SQRT_SCALE / std::sqrt(compLenSq);
    }
    compX *= invCompLen;
    compY *= invCompLen;
    compZ *= invCompLen;
    compW *= invCompLen;

    // Combine: spring + perpendicular wind force
    float finalX = interpX + toCurrX * someFactor;
    float finalY = interpY + toCurrY * someFactor;
    float finalZ = interpZ + toCurrZ * someFactor;
    float finalW = interpW + toCurrW * someFactor;

    // Update wheel position (write to currentPos)
    this->currentPos[0] = (int)finalX;
    this->currentPos[1] = (int)finalY;
    this->currentPos[2] = (int)finalZ;
    this->currentPos[3] = (int)finalW;

    // Clamp velocity using damping
    float velMag = (float)this->velocity[0] + dt; // originally: param_2 = param_2 + this->velocity[0]
    this->velocity[0] = (int)velMag;
    if (someOther < THRESHOLD) {
        velMag = (INV_SQRT_SCALE - someOther * DAMPING_K) * (velMag - this->velocity[0]) + this->velocity[0];
    }
    if (velMag < (float)this->velocity[0]) {
        this->velocity[0] = (int)velMag;
    }

    // Normalize orientations (three tiers)
    float tx = (float)this->currentPos[0];
    float ty = (float)this->currentPos[1];
    float tz = (float)this->currentPos[2];
    float tw = (float)this->currentPos[3];

    float dxNorm = dx*dx + dy*dy + dz*dz + dw*dw;
    float invDxNorm = 0.0f;
    if (dxNorm > SQRT_EPSILON_SQR) invDxNorm = INV_SQRT_SCALE / std::sqrt(dxNorm);
    dx *= invDxNorm;
    dy *= invDxNorm;
    dz *= invDxNorm;

    float toTargetLenSq = toTargetX*toTargetX + toTargetY*toTargetY + toTargetZ*toTargetZ + toTargetW*toTargetW;
    float invToTarget = 0.0f;
    if (toTargetLenSq > SQRT_EPSILON_SQR) invToTarget = INV_SQRT_SCALE / std::sqrt(toTargetLenSq);
    toTargetX *= invToTarget;
    toTargetY *= invToTarget;
    toTargetZ *= invToTarget;
    toTargetW *= invToTarget;

    // Velocity derivative (used as "torque") normalized
    float dvx = (float)this->velocity[0] - tx;
    float dvy = (float)this->velocity[1] - ty;
    float dvz = (float)this->velocity[2] - tz;
    float dvw = (float)this->velocity[3] - tw;
    float dvLenSq = dvx*dvx + dvy*dvy + dvz*dvz + dvw*dvw;
    float invDv = 0.0f;
    if (dvLenSq > SQRT_EPSILON_SQR) invDv = INV_SQRT_SCALE / std::sqrt(dvLenSq);
    dvx *= invDv;
    dvy *= invDv;
    dvz *= invDv;
    dvw *= invDv;

    // Build intermediate vectors for quaternion blending
    float q0 = dvx; // missing actual cross product logic
    float q1 = dvy;
    float q2 = dvz;
    float cross1 = dx * q2 - dz * q1; // simplified
    // ... more cross products

    // Write final positions (using velocity magnitude as blend)
    float speed = std::sqrt(velY*velY + velZ*velZ + velX*velX);
    this->velocity[0] = (int)(speed * dvx + tx);
    this->velocity[1] = (int)(speed * dvy + ty);
    this->velocity[2] = (int)(speed * dvz + tz);
    this->velocity[3] = (int)(speed * dvw + tw);

    // Update rotation quaternions via cross products and normalization
    // (Three tiers: local->world, world->constraint, velocity->orientation)
    // Write result to transform manager
    int baseAddr = *(int*)(mgr + 0x38); // transform array
    float local90[48]; // temporary transform

    for (int i = 0; i < 4; ++i) {
        int idx = this->transformIndices[3 - i]; // order reversal
        int matOffset = idx * 0x20 + 0x10 + baseAddr;
        clearTransform((float*)matOffset);
        identityTransform((float*)matOffset);
        copyTransform(local90, (float*)matOffset); // copy original
        // Overwrite rotation part (offset 0x10–0x18) with computed quaternion
        *(float*)(matOffset + 0x10) = local90[0];
        *(float*)(matOffset + 0x14) = local90[1];
        *(float*)(matOffset + 0x18) = local90[2];
    }
}