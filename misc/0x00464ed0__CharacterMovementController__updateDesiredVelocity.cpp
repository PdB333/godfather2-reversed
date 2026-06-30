// FUNC_NAME: CharacterMovementController::updateDesiredVelocity
// Address: 0x00464ed0
// This function computes a desired velocity vector and an animation state based on input (dx, dy)
// and internal thresholds from a character component (entity).
// The state is stored in a MovementState struct (pointed to by statePtr).
// The input vector (dx, dy) is assumed to be in XMM4 and XMM5 (passed via registers).

struct MovementState {
    float velocityX;        // +0x00
    float velocityY;        // +0x04
    float turningSpeed;     // +0x08
    float speedMagnitude;   // +0x0C
    char moveState;         // +0x10 (animation state byte, e.g. 0x01=walk, 0x0A=run, etc.)
    char timerSlot;         // +0x11 (some timer index, always set to 0x21)
    char previousState;     // +0x12
    char flag;              // +0x13 (tested for zero to decide reset timer)
    char timer;             // +0x14 (byte at offset 5 floats = 20 bytes, timer decrement)
    // Probably padding/packed
};

// Constants (global DAT values with semantic names)
extern const float kMaxSpeed;           // DAT_00e2b1a4
extern const float kDeadZoneSq;         // DAT_00e2cbe0 (squared dead zone threshold)
extern const float kTurnRateMax;        // DAT_00e44594 (?)
extern const float kTurnRateMin;        // DAT_00e2af34 (?)
extern const float kSomeFactor;         // DAT_00e2cd54
extern const float kAngleThreshold1;    // DAT_00e448f0
extern const float kAngleThreshold2;    // DAT_00e448f4
extern const float kAngleThreshold3;    // DAT_00e448f8
extern const float kAngleThreshold4;    // DAT_00e44600
extern const float kAngleThreshold5;    // DAT_00e44720
extern const float kTimerMagic;         // DAT_00e44748 (multiplier for timer)
extern const float kSomeFlagFloat;      // PTR_FUN_00e4462c (cast to float)
extern const float kSomeBitmask;        // DAT_00e44680 (bitmask, reinterpreted as float)

void FUN_00464ed0(void) {
    // INPUTS: in_XMM4_Da = dx, in_XMM5_Da = dy
    // ESI = statePtr (MovementState*)
    // EDI = entityPtr (some character component with fields at offsets 0x1694, 0x16a0, etc.)
    MovementState* state = reinterpret_cast<MovementState*>(unaff_ESI);
    EntityComponent* entity = reinterpret_cast<EntityComponent*>(unaff_EDI);

    float maxSpeed = kMaxSpeed;
    float deadZoneRadius = *(float*)(entity + 0x1694); // dead zone radius for this entity
    float inputSq = dx * dx + dy * dy;
    float inputMag = sqrtf(inputSq);

    float speedBasedForceX, speedBasedForceY;

    if (deadZoneRadius <= inputMag) {
        // Input exceeds dead zone -> compute force towards input direction
        float forceScale = (inputMag - deadZoneRadius) / (maxSpeed - deadZoneRadius);
        if (inputSq <= kDeadZoneSq) {
            inputMag = 0.0f;
        } else {
            inputMag = maxSpeed / inputMag; // normalize to max speed
        }
        speedBasedForceX = inputMag * dx * forceScale;
        speedBasedForceY = inputMag * dy * forceScale;
    } else {
        speedBasedForceX = 0.0f;
        speedBasedForceY = 0.0f;
    }

    state->velocityY = speedBasedForceY; // note: order reversed? actually unaff_ESI[1] first, then *unaff_ESI
    float speed = sqrtf(speedBasedForceY * speedBasedForceY + speedBasedForceX * speedBasedForceX);
    state->velocityX = speedBasedForceX;

    if (maxSpeed < speed) {
        // Clamp to max speed
        float scale = maxSpeed / speed;
        state->velocityX = scale * speedBasedForceX;
        state->velocityY = state->velocityY * scale;
        speed = maxSpeed;
    }

    float someFloat = reinterpret_cast<float&>(PTR_FUN_00e4462c); // questionable cast
    float turnRateMax = kTurnRateMax;
    float turnRateMin = kTurnRateMin;
    bool isSlowed = someFloat < speed; // some threshold test

    state->speedMagnitude = speed;

    if (isSlowed) {
        if (someFloat <= reinterpret_cast<float&>((uint32_t&)state->velocityY & (uint32_t&)kSomeBitmask)) {
            // Randomization path
            double dVar6 = (double)state->velocityX;
            FUN_00b9a9fa(); // likely a random number generator
            float randomFactor = (float)dVar6 * kTimerMagic;
            turnRateMin = kTurnRateMin;
            turnRateMax = kTurnRateMax;
            if (randomFactor < 0.0f) {
                randomFactor = randomFactor + kTurnRateMin; // wrap??
            }
            state->turningSpeed = randomFactor;
        } else {
            float turningSpeed = kAngleThreshold3;
            if (0.0f < state->velocityX) {
                turningSpeed = turnRateMax;
            }
            state->turningSpeed = turningSpeed;
        }
    } else {
        state->turningSpeed = 0.0f;
    }

    char animState;
    if (speed <= 0.0f) {
        animState = 0;
    } else {
        // Complex series of comparisons to determine animation state based on turning speed and speed thresholds
        float speedThreshold1 = *(float*)(entity + 0x16ac) * kSomeFactor;
        float speedThreshold2 = (turnRateMax - *(float*)(entity + 0x16ac)) * kSomeFactor;
        float turnSpeed = state->turningSpeed;

        if ((turnRateMin - speedThreshold1 < turnSpeed) || (turnSpeed < speedThreshold1)) {
            if (*(float*)(entity + 0x16a0) <= speed) {
                animState = 0x09; // '\t'
            } else {
                animState = 0x01;
            }
        } else if (turnSpeed <= kAngleThreshold4 - speedThreshold2) {
            if (turnSpeed <= kAngleThreshold3 - speedThreshold1) {
                if (turnSpeed <= kAngleThreshold1 - speedThreshold2) {
                    if (turnSpeed <= kAngleThreshold4 - speedThreshold1) {
                        if (turnSpeed <= kAngleThreshold5 - speedThreshold2) {
                            if (turnSpeed <= turnRateMax - speedThreshold1) {
                                if (*(float*)(entity + 0x16a0) <= speed) {
                                    animState = 0x0A; // '\n'
                                } else {
                                    animState = 0x02;
                                }
                            } else if (*(float*)(entity + 0x16a0) <= speed) {
                                animState = 0x0B; // '\v'
                            } else {
                                animState = 0x03;
                            }
                        } else if (*(float*)(entity + 0x16a0) <= speed) {
                            animState = 0x0C; // '\f'
                        } else {
                            animState = 0x04;
                        }
                    } else if (*(float*)(entity + 0x16a0) <= speed) {
                        animState = 0x0D; // '\r'
                    } else {
                        animState = 0x05;
                    }
                } else if (*(float*)(entity + 0x16a0) <= speed) {
                    animState = 0x0E;
                } else {
                    animState = 0x06;
                }
            } else if (*(float*)(entity + 0x16a0) <= speed) {
                animState = 0x0F;
            } else {
                animState = 0x07;
            }
        } else if (*(float*)(entity + 0x16a0) <= speed) {
            animState = 0x10;
        } else {
            animState = 0x08;
        }
    }

    // Timer management based on animState continuity
    if (animState == *(char*)((int)state + 0x12)) { // previousState
        float* pfVar1 = state + 5; // pointer to byte at offset 20 (timer)
        *(char*)pfVar1 = *(char*)pfVar1 - 1;
        if (*(char*)pfVar1 < 0) {
            *(char*)(state + 5) = 0;
        }
        if (*(char*)(state + 5) > 0x7E) {
            *(char*)(state + 5) = 0x7E;
        }
    } else if (*(char*)((int)state + 0x13) == 0) { // flag
        *(char*)(state + 5) = *(char*)(entity + 0x16a8); // timer reset value
    } else {
        *(char*)(state + 5) = *(char*)(entity + 0x16a4); // alternative timer reset
    }

    *(char*)((int)state + 0x11) = 0x21; // slot identifier
    *(char*)((int)state + 0x12) = animState; // previousState = current state

    if (*(char*)(state + 5) == 0) { // timer expired -> force immediate state
        *(char*)(state + 4) = animState; // moveState override
    }

    return;
}