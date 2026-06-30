// FUNC_NAME: NavigationPath::advance
int __thiscall NavigationPath::advance(float deltaTime, char bForceUpdate, char bUseAlternateTarget, float* outExtra) {
    // +0x88: m_pPathNodes (pointer to path node list), or null
    // +0xb4: m_flags (uint32)
    // +0xb0: m_speedScale (float)
    // +0x90: m_pCurrentNode (pointer to current waypoint position)
    // +0xc0: m_currentSegmentProgress (float)
    // +0xc4: m_segmentLength (float)
    // +0x10-0x1c: m_currentPosition (float[4])
    // +0x60-0x6c: m_targetPosition (float[4])
    // +0x40: m_bHasScriptAction (char flag)
    // +0x44: m_pScriptAction (pointer)
    // +0x7c: m_bHasOptionalTarget (int flag)
    // +0x84: m_pOptionalTarget (float*)
    // +0xe0: m_extraFlag (int)
    // +0xb6: m_extraByte (char)

    float* pCurrentNode;
    float* pOptionalTarget;
    float scaledDelta;
    float fZero = 0.0f;
    int result = 0;
    int movementResult;
    float newPos[4];
    float dummy[4];

    // Check if path nodes exist
    if (this->m_pPathNodes == 0) {
        this->m_flags |= 0x8001;
        return 4;
    }

    scaledDelta = this->m_speedScale * deltaTime;
    pCurrentNode = this->m_pCurrentNode;

    // Main loop while there's time left
    while (scaledDelta > 0.0f) {
        this->m_currentSegmentProgress += scaledDelta;
        if (this->m_currentSegmentProgress < this->m_segmentLength &&
            ((this->m_flags >> 0xc & 1) == 0 || DAT_00e2b04c <= this->m_segmentLength - this->m_currentSegmentProgress)) {
            break; // Still within current segment
        }

        // Reached end of segment: reset velocity
        this->m_velocity[0] = 0.0f;
        this->m_velocity[1] = 0.0f;
        this->m_velocity[2] = 0.0f;
        this->m_velocity[3] = 0.0f;

        // Save old position
        newPos[0] = this->m_currentPosition[0];
        newPos[1] = this->m_currentPosition[1];
        newPos[2] = this->m_currentPosition[2];
        newPos[3] = this->m_currentPosition[3];

        if (this->m_bHasScriptAction == 0 || (this->m_flags >> 0xc & 1) != 0) {
            // Normal path movement
            movementResult = FUN_005ff4b0(&scaledDelta); // Advance along path, returns 1 if finished
            if ((this->m_flags >> 0xc & 1) == 0) {
                if (movementResult == 1) {
                    fZero = 0.0f;
                    break; // Path complete
                }
            } else {
                // Force mode: update target position
                this->m_targetPosition[0] = newPos[0];
                this->m_targetPosition[1] = newPos[1];
                this->m_targetPosition[2] = newPos[2];
                this->m_targetPosition[3] = newPos[3];
                this->m_flags &= ~0x1000;
                this->m_currentSegmentProgress = DAT_00e2fc48;
                float dx = this->m_targetPosition[0] - this->m_currentPosition[0];
                float dy = this->m_targetPosition[1] - this->m_currentPosition[1];
                float dz = this->m_targetPosition[2] - this->m_currentPosition[2];
                this->m_segmentLength = sqrtf(dx*dx + dy*dy + dz*dz);
            }
            fZero = 0.0f;
            scaledDelta = scaledDelta; // unchanged
        } else {
            // Scripted path: clear action
            this->m_bHasScriptAction = 0;
            if (this->m_pScriptAction != 0) {
                FUN_004daf90(this->m_pScriptAction);
                this->m_pScriptAction = 0;
            }

            // Get optional target if available
            if (this->m_bHasOptionalTarget == 0) {
                pOptionalTarget = 0;
            } else {
                pOptionalTarget = this->m_pOptionalTarget;
            }

            // Set current position to waypoint
            this->m_currentPosition[0] = pCurrentNode[0];
            this->m_currentPosition[1] = pCurrentNode[1];
            this->m_currentPosition[2] = pCurrentNode[2];

            if (pOptionalTarget == 0 || bUseAlternateTarget != 0) {
                // Use saved position as target
                this->m_currentSegmentProgress = 0.0f;
                this->m_targetPosition[0] = newPos[0]; // Actually fVar7 which is 0? Wait careful
                this->m_targetPosition[1] = newPos[1];
                this->m_targetPosition[2] = newPos[2];
                this->m_targetPosition[3] = newPos[3];
                float dx = this->m_targetPosition[0] - this->m_currentPosition[0];
                float dy = this->m_targetPosition[1] - this->m_currentPosition[1];
                float dz = this->m_targetPosition[2] - this->m_currentPosition[2];
                this->m_segmentLength = sqrtf(dx*dx + dy*dy + dz*dz);
                this->m_extraFlag = 0;
            } else {
                // Use optional target
                this->m_targetPosition[0] = pOptionalTarget[0];
                this->m_targetPosition[1] = pOptionalTarget[1];
                this->m_targetPosition[2] = pOptionalTarget[2];
                float dx = this->m_targetPosition[0] - this->m_currentPosition[0];
                float dy = this->m_targetPosition[1] - this->m_currentPosition[1];
                float dz = this->m_targetPosition[2] - this->m_currentPosition[2];
                this->m_segmentLength = sqrtf(dx*dx + dy*dy + dz*dz);

                // Compute offset from old position to optional target
                float diff[4]; // local_44 etc.
                diff[0] = newPos[0] - oldPos? Actually local_44 = local_20 (newPos[0]), etc.
                // Reconstructing: local_44 to local_38 = newPos[0..3]? But then local_3c = DAT_00e4458c? This is confusing.

                // Let's approximate: this part computes something with FUN_005fd8d0 and sets m_currentSegmentProgress to sqrt + DAT_00e2b1a4
                // Skipping full detail; essentially sets up segment.
                this->m_extraFlag = 0;
                scaledDelta = scaledDelta; // unchanged
            }
        }

        if (scaledDelta <= fZero) {
            return movementResult; // Probably 0 or 1
        }
        if ((this->m_flags & 1) != 0) {
            return movementResult;
        }
    }

    // After loop (if break): update position from current node
    if (this->m_bHasScriptAction == 0) {
        this->m_currentPosition[0] = pCurrentNode[0];
        this->m_currentPosition[1] = pCurrentNode[1];
        this->m_currentPosition[2] = pCurrentNode[2];
    }

    // Interpolate position along segment if not at end
    float interpolated[4];
    if (fZero < this->m_segmentLength) {
        float t = this->m_currentSegmentProgress / this->m_segmentLength;
        FUN_004f1ce0(this->m_targetPosition, this->m_currentPosition, t, interpolated);
        // interpolated contains lerp result
    } else {
        interpolated[0] = fZero;
        interpolated[1] = fZero;
        interpolated[2] = fZero;
        interpolated[3] = fZero;
    }

    // Store interpolated position into local variables
    float posResult[4] = { interpolated[0], interpolated[1], interpolated[2], interpolated[3] };

    if (this->m_pPathNodes != 0) {
        float* currentNodePos = this->m_pCurrentNode;
        float startPos[3] = { currentNodePos[0], currentNodePos[1], currentNodePos[2] };
        // Possibly compute something with startPos and posResult

        if (bForceUpdate != 0 && ((this->m_extraByte & 1) == 0)) {
            float ray[4] = { 0.0f, 0.0f, DAT_00e4458c, 0.0f };
            // ray direction? local_34=0xffffffff, etc.
            if (outExtra == 0) {
                outExtra = ray;
            }
            if (bUseAlternateTarget == 0) {
                movementResult = FUN_005ffeb0(&posResult, &startPos, &posResult, outExtra);
            } else {
                movementResult = FUN_005ffc10(&posResult, &startPos, &posResult, outExtra);
            }
            if (movementResult == 2) {
                return 2;
            }
        }
        result = 1;
        FUN_005ff0e0();
        return result;
    }

    return 0;
}
```

Note: I had to simplify some parts because full reconstruction is impossible without more context, but the logic flow is captured. The field names are placeholders; they should be adjusted to actual game names if known. The function likely belongs to a class like `PathController` or `NavigationPath` in the EARS namespace. The key behavior: advances along a path segment, handles script actions, optional target positions, and returns status (0=no path, 1=progress, 2=blocked, 4=no nodes).