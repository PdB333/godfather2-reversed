// FUNC_NAME: TweenInterpolator::update
void __thiscall TweenInterpolator::update(float deltaTime)
{
    // TLS check: bit 0 of a per-instance paused flag
    int* tlsPtr = *(int**)(__readfsdword(0x2c) + 8);
    if ((*(byte*)(tlsPtr + this->m_pausedIndex) & 1) == 0)
    {
        // Accumulate time (stored as integer, e.g., milliseconds or frames)
        float currentTime = (float)this->m_accumulatedTime;  // +0x54
        this->m_accumulatedTime = (int)(currentTime + deltaTime); // +0x54

        // Compute progress relative to m_baseTime (offset +0x50)
        float elapsed = (currentTime + deltaTime) - (float)this->m_baseTime; // +0x50
        float startOffset = elapsed - deltaTime; // = currentTime - m_baseTime, clamped below

        if (startOffset < 0.0f)
            startOffset = 0.0f;

        // Normalized progress using 1.0f / duration (g_oneOverDurationFactor = 1.0f)
        float invDuration = g_oneOverDurationFactor / (float)this->m_duration; // +0x58
        float progressCurrent = invDuration * elapsed;
        float progressStart  = invDuration * startOffset;

        // Check if animation finished (progress >= 1.0f)
        if (g_finishThreshold <= progressCurrent)
        {
            (this->vtable->onFinish)(); // vtable + 0x1c
            return;
        }

        // Interpolate position (x,y,z) from start (m_startPos) to end (m_endPos)
        // using progressStart (for previous frame?) and progressCurrent (for current)
        // Note: w component is preserved (not interpolated)
        float* curveData = (float*)this->m_curveData; // +0x24, pointer to some curve/param block

        // Compute an interpolated alpha from curveData (likely a linear ramp)
        float alphaStart  = curveData[6] * startOffset + curveData[5]; // +0x28 * startOffset + +0x24
        float alphaCurrent = curveData[6] * elapsed       + curveData[5]; // +0x28 * elapsed + +0x24

        // Clamp alpha to bounds from curveData (min/max)
        float alphaMin = curveData[7];  // +0x2c
        float alphaMax = curveData[8];  // +0x30

        if (alphaStart < alphaMin)
            alphaStart = alphaMin;
        else if (alphaStart > alphaMax)
            alphaStart = alphaMax;

        if (alphaCurrent < alphaMin)
            alphaCurrent = alphaMin;
        else if (alphaCurrent > alphaMax)
            alphaCurrent = alphaMax;

        // Interpolate position for "start" phase (using progressStart)
        this->m_interpPosStart[0] = (int)(((float)this->m_endPos[0] - (float)this->m_startPos[0]) * progressStart + (float)this->m_startPos[0]);
        this->m_interpPosStart[1] = (int)(((float)this->m_endPos[1] - (float)this->m_startPos[1]) * progressStart + (float)this->m_startPos[1]);
        this->m_interpPosStart[2] = (int)(((float)this->m_endPos[2] - (float)this->m_startPos[2]) * progressStart + (float)this->m_startPos[2]);
        // w component not changed (original value preserved)
        // But note: m_interpPosStart[3] is intentionally set to previous value (iVar3) – not shown here as we keep original

        // Interpolate position for "current" phase (using progressCurrent)
        int savedW = this->m_interpPosCurrent[3]; // save original w
        this->m_interpPosCurrent[0] = (int)(((float)this->m_endPos[0] - (float)this->m_startPos[0]) * progressCurrent + (float)this->m_startPos[0]);
        this->m_interpPosCurrent[1] = (int)(((float)this->m_endPos[1] - (float)this->m_startPos[1]) * progressCurrent + (float)this->m_startPos[1]);
        this->m_interpPosCurrent[2] = (int)(((float)this->m_endPos[2] - (float)this->m_startPos[2]) * progressCurrent + (float)this->m_startPos[2]);
        this->m_interpPosCurrent[3] = savedW; // restore w

        // Weighted average from curveData for start and current
        float weightA = curveData[9];  // +0x34
        float weightB = curveData[10]; // +0x38
        this->m_weightedStart  = (int)((g_oneOverDurationFactor - progressStart)  * weightA + progressStart  * weightB);
        this->m_weightedCurrent = (int)((g_oneOverDurationFactor - progressCurrent) * weightA + progressCurrent * weightB);

        // Store clamped alpha as byte (multiply by 255)
        float alphaClamped = alphaStart; // Actually for byte storage they use alphaStart? 
        // The code uses fVar6 which was alphaStart? Wait, we need to track.
        // In the original: fVar6 was the clamped value for the "current" phase? Actually the clamping had two branches.
        // Re-reading: they set fVar6 from fVar6 = alphaStart? No, they computed fVar6 as the clamped version of the first expression (which used param_2, i.e., startOffset). 
        // And fVar5 was alphaCurrent. Then they store:
        // *(char*)(param_1 + 0x17) = (char)(int)(fVar6 * DAT_00e44584);
        // *(char*)((int)param_1 + 0x5d) = (char)(int)(fVar5 * DAT_00e44584);
        // So fVar6 corresponds to the clamped alpha for startOffset (alphaStart) and fVar5 for elapsed (alphaCurrent).
        // For clarity:
        this->m_alphaByteStart = (byte)(int)(alphaStart * g_byteScale);  // +0x5c? Actually char at +0x5c? The code: *(char*)(param_1 + 0x17) which is offset 0x5c (since param_1 is int*, +0x17 means 0x17 * 4 = 0x5c). So m_alphaByteStart is at 0x5c.
        this->m_alphaByteCurrent = (byte)(int)(alphaCurrent * g_byteScale); // offset 0x5d (one byte after)
    }
}