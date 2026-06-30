//FUNC_NAME: VehicleController::updateSteering
void VehicleController::updateSteering(char param_1)
{
    float fVar1, fVar2, fVar3, fVar4;
    float *pfVar5, *pfVar8;
    uint uFlags;
    char cVar7;
    float fVar9, fVar10, fVar12, fVar13, fVar14, fVar15, fVar16;
    double dVar11;

    // If target or target position is null, acquire new target
    if ((m_pTarget == nullptr) || (m_pTargetPos == nullptr)) {
        acquireTarget(this, &m_targetPos, &m_pTarget, m_flags >> 0xd & 0xffffff01);
    }

    if ((m_pTarget != nullptr) && (pfVar5 = m_pTargetPos, pfVar5 != nullptr)) {
        // Get current position pointer
        if (m_bHasTarget == 0) {
            pfVar8 = nullptr;
        } else {
            pfVar8 = m_currentPos;
        }

        // Compute difference vector from current to target
        fVar1 = *pfVar5;          // target.x
        fVar2 = pfVar5[2];        // target.z (assuming y-up)
        fVar3 = *pfVar8;          // current.x
        fVar4 = pfVar8[2];        // current.z
        fVar9 = fVar1 - fVar3;    // dx
        fVar12 = pfVar5[1] - pfVar8[1]; // dy (vertical)
        fVar13 = fVar2 - fVar4;   // dz
        fVar10 = fVar12 * fVar12 + fVar9 * fVar9 + fVar13 * fVar13; // distance squared
        fVar14 = 0.0f;
        fVar13 = fVar14;

        // If distance squared > threshold, compute inverse distance
        if (kMinDistSq < fVar10) {
            fVar13 = sqrtf(fVar10); // actual distance
            fVar14 = kOneOverSomething / fVar13; // 1/distance
        }

        uFlags = m_flags;

        // Check if we should update target speed
        if ((((uFlags >> 7 & 1) == 0) || (m_pTarget != m_pSomething)) ||
            ((m_pTarget != nullptr && (m_pTargetPos != m_pSomethingElse)))) {
            // If current speed differs from target speed and not in a special state
            if ((m_currentSpeed != m_targetSpeed) && ((uFlags >> 6 & 1) == 0)) {
                m_currentSpeed = m_targetSpeed;
            }
            dVar11 = (double)(fVar14 * fVar9);
            FUN_00b9a9fa(); // likely a math utility (clamp/wrap)
            m_targetSpeed = (float)dVar11;
        }

        dVar11 = (double)(fVar14 * fVar12);
        FUN_00b9a9fa();
        fVar9 = kSomeConstant - (float)dVar11;
        m_verticalSpeed = fVar9;

        if ((uFlags >> 4 & 1) != 0) {
            m_derivative1 = 0;
            m_derivative2 = 0;
        }

        m_someFlag = 0;

        if (param_1 == '\0') {
            if ((uFlags >> 5 & 1) == 0) {
                m_steeringAngle = fVar9;
                m_steeringAnglePrev = fVar9;
            }
            if ((uFlags >> 6 & 1) == 0) {
                goto LAB_005fecbb;
            }
        } else {
            if ((uFlags >> 3 & 1) == 0) {
                // If special flag set and some condition holds
                if (((uFlags >> 7 & 1) != 0) && (cVar7 = FUN_005f5d30(m_pSomething), cVar7 != '\0')) {
                    m_steeringAngle = fVar9;
                    m_steeringAnglePrev = fVar9;
                    goto LAB_005fecbb;
                }

                // If target speed changed or steering angle changed
                if ((m_targetSpeed != m_previousTargetSpeed) ||
                    (((uFlags >> 5 & 1) == 0 && (fVar9 != m_steeringAngle)))) {
                    fVar10 = m_maxAcceleration;
                    fVar14 = fVar13;
                    if (fVar10 <= fVar13) {
                        fVar14 = fVar10;
                    }
                    if ((uFlags >> 9 & 1) == 0) {
                        fVar14 = fVar14 * kAccelScale;
                    }
                    fVar12 = fVar10 - m_minAcceleration;
                    if (fVar12 < fVar14) {
                        fVar14 = fVar12;
                    }
                    if (fVar14 < 0.0f) {
                        fVar14 = 0.0f;
                    }

                    // Compute angular difference and wrap
                    fVar12 = m_previousTargetSpeed - m_targetSpeed;
                    if (fVar12 <= kAngleThresholdPos) {
                        if (fVar12 < kAngleThresholdNeg) {
                            fVar12 = fVar12 + kTwoPi;
                        }
                    } else {
                        fVar12 = fVar12 - kTwoPi;
                    }

                    fVar15 = m_dampingFactor;
                    if (0.0f < fVar15) {
                        if (fVar12 < 0.0f) {
                            fVar15 = m_negativeDamping;
                        }
                        if (fVar15 < fVar14) {
                            fVar14 = fVar15;
                        }
                    }
                    m_acceleration = fVar14;
                    fVar15 = kSomeGlobal;
                    fVar16 = kAnotherGlobal;
                    if (0.0f < fVar14) {
                        fVar16 = kOneOverSomething / fVar14;
                    }
                    m_invAcceleration = fVar16;

                    if (((uFlags >> 4 & 1) != 0) && (m_targetSpeed != m_previousTargetSpeed)) {
                        m_derivative2 = fVar12 * fVar15;
                    }

                    fVar12 = (fVar14 / fVar10) * fVar15;
                    fVar10 = fVar12;
                    if (0.0f < fVar13) {
                        fVar10 = (fVar14 / fVar13) * fVar15;
                    }

                    // Compute lateral forces
                    m_forceX = (fVar1 - fVar3) * fVar10 - (fVar3 - m_prevPosX) * fVar12;
                    m_forceZ = (fVar2 - fVar4) * fVar10 - (fVar4 - m_prevPosZ) * fVar12;

                    if (((uFlags >> 5 & 1) == 0) && (fVar9 != m_steeringAngle)) {
                        m_steeringForce = (m_steeringAngle - fVar9) * fVar14 * fVar15;
                        return;
                    }
                    m_steeringForce = 0;
                }
            }
        }
        return;

LAB_005fecbb:
        m_previousTargetSpeed = m_targetSpeed;
        m_currentSpeed = m_targetSpeed;
    }
}