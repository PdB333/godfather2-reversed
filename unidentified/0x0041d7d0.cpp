// FUN_NAME: AudioVisualizer::updateSpectrum
void AudioVisualizer::updateSpectrum(uint channelIndex) // channelIndex from EAX
{
    uint uVar3;
    uint *puVar4;
    float *pfVar5;
    int iVar6;
    uint uVar7;
    float fVar9, fVar10, fVar11, fVar13, fVar14, fVar15;
    double dVar12;
    byte bVar1;

    // Check if the sound channel represented by channelIndex is active and not stopped
    uVar3 = gSoundChannelList[channelIndex]; // DAT_01206af0[channelIndex]
    if (((uVar3 < 0x1000) && (gSoundChannelData[uVar3] != nullptr)) && // DAT_011a0f28 + uVar3*0x38
        ((bVar1 = gSoundChannelState[uVar3], 1 < bVar1) && (bVar1 != 5 && bVar1 != 4)))
    {
        // Stop the sound channel
        SoundSystem::stopChannel(uVar3, 0); // FUN_006064b0(uVar3,0)
    }

    uint globalParam = gAudioGlobalParam; // DAT_01206b00
    gAudioSpectrumAccum = 0; // DAT_01162388
    gAudioSpectrumBuffer = 0; // DAT_01162588

    // Compute base value for decay
    fVar9 = gAudioDecayFactor * gAudioScaleFactor; // DAT_01206a94 * DAT_00e446f0

    // Initialize decay buffer (size 0x80 floats) to base value
    float* decayBuf = gAudioDecayBuffer; // DAT_0116238c
    for (iVar6 = 0x7f; iVar6 != 0; iVar6--)
    {
        *decayBuf = fVar9;
        decayBuf++;
    }

    // Retrieve audio data from controller/input system
    // This fills a buffer with audio samples (2 shorts per sample)
    AudioInputData audioData; // local_50 structure
    AudioSystem::getAudioInput(globalParam, 1, 0, &audioData); // FUN_00606fd0

    fVar11 = gAudioTimeDelta; // DAT_00e2b1a4
    uint sampleCount = audioData.sampleCount; // local_4c

    if (sampleCount != 0)
    {
        do
        {
            if (audioData.channelCount != 0) // local_4e (channels per sample)
            {
                // Process samples: extract 7-bit index from each sample and accumulate into histogram
                int samplesPerBlock = (audioData.channelCount - 1 >> 3) + 1;
                puVar4 = audioData.samples; // local_c points to sample array
                do
                {
                    uVar7 = *puVar4 >> 1 & 0x7f; // Extract bin index from sample
                    gAudioHistogram[uVar7] += fVar11; // DAT_01162388

                    uVar7 = puVar4[1] >> 1 & 0x7f;
                    gAudioHistogram[uVar7] += fVar11;

                    uVar7 = puVar4[2] >> 1 & 0x7f;
                    gAudioHistogram[uVar7] += fVar11;

                    uVar7 = puVar4[3] >> 1 & 0x7f;
                    gAudioHistogram[uVar7] += fVar11;

                    uVar7 = puVar4[4] >> 1 & 0x7f;
                    gAudioHistogram[uVar7] += fVar11;

                    uVar7 = puVar4[5] >> 1 & 0x7f;
                    gAudioHistogram[uVar7] += fVar11;

                    uVar7 = puVar4[6] >> 1 & 0x7f;
                    gAudioHistogram[uVar7] += fVar11;

                    uVar7 = puVar4[7] >> 1 & 0x7f;
                    puVar4 += 8;
                    samplesPerBlock--;
                    gAudioHistogram[uVar7] += fVar11;
                } while (samplesPerBlock != 0);
            }
            // Move to next block of samples
            audioData.samples = (uint*)((int)audioData.samples + audioData.blockStride); // local_28 stride?
            sampleCount--;
        } while (sampleCount != 0);
    }

    AudioSystem::releaseAudioInput(&audioData); // FUN_006071a0

    fVar15 = gAudioTimeDelta; // DAT_00e2b1a4
    fVar11 = gAudioFrequencyScale; // DAT_00e2af44
    fVar9 = fVar9 * gOverallScaleFactor; // _DAT_00e44920 (maybe global audio level)
    fVar14 = gAudioTimeDelta - gAudioDecayRate; // _DAT_01206a98 - decay rate

    // Apply decay and threshold to histogram
    uVar3 = 0x7f;
    do
    {
        float freqIndex = (float)(int)uVar3;
        if ((int)uVar3 < 0)
        {
            freqIndex += 0x10000; // DAT_00e44578 (2^16)
        }
        fVar10 = gAudioDecayBuffer[uVar3] * fVar14; // decay buffer * (timeDelta - decayRate)
        fVar9 = freqIndex * fVar11 * gAudioHistogram[uVar3] + fVar9; // accumulate energy
        if (gAudioHistogram[uVar3] < fVar10)
        {
            gAudioHistogram[uVar3] = fVar10;
        }
        uVar3--;
    } while (uVar3 < 0x80);

    fVar11 = 0.0f;
    fVar9 = fVar9 * gAudioNormalizationFactor; // DAT_00e2af48
    gAudioEnergy = fVar9; // DAT_01206a7c

    if (fVar9 > 0.0f)
    {
        // Apply scaling to histogram and decay buffer
        uVar3 = 4;
        do
        {
            fVar13 = *(float*)((int)gAudioHistogram + uVar3) * fVar14;
            if (*(float*)((int)gAudioDecayBuffer + uVar3) <= fVar13 &&
                fVar13 != *(float*)((int)gAudioDecayBuffer + uVar3))
            {
                *(float*)((int)gAudioDecayBuffer + uVar3) = fVar13;
            }
            *(float*)((int)gAudioHistogram + uVar3) =
                *(float*)((int)gAudioDecayBuffer + uVar3 - 4) + *(float*)((int)gAudioHistogram + uVar3);
            uVar3 += 4;
        } while (uVar3 < 0x200);

        fVar14 = (gAudioMaxVolume / gAudioAverageVolume) * gAudioVolumeScaleFactor; // DAT_01206aa0 / DAT_01162584 * _DAT_00e44670
        fVar13 = fVar15 - gAudioMaxVolume; // timeDelta - maxVolume

        uVar3 = 1;
        do
        {
            float* pf = (float*)(&gAudioHistogram + uVar3);
            float fIndex = (float)(int)uVar3;
            if ((int)uVar3 < 0)
            {
                fIndex += 0x10000;
            }
            uVar3++;
            *(float*)((int)&gAudioDecayBuffer + uVar3 * 4) = (*pf * fVar14) / fIndex + fVar13;
        } while (uVar3 < 0x7f);

        gAudioHistogram[0] = gAudioDecayBuffer[0];
        gAudioAverageVolume = fVar15;

        // Determine threshold for energy interpolation
        float* pfThresholdHigh = &gAudioThresholdHigh; // DAT_01206ac4
        float* pfThresholdLow = &gAudioThresholdLow;   // DAT_01206ab0

        if (fVar9 > gAudioThresholdLow) // DAT_01206ab0
        {
            if (fVar9 > gAudioThresholdMid) // DAT_01206ac4
            {
                pfThresholdHigh = &gAudioThresholdHigh; // DAT_01206ad8? Wait logic is messy
                if (fVar9 > gAudioThresholdHigh)
                {
                    pfThresholdHigh = &gAudioThresholdHigh; // actually DAT_01206ad8? Let's fix below
                }
            }
            else
            {
                pfThresholdHigh = &gAudioThresholdLow;
            }
        }
        else
        {
            pfThresholdHigh = &gAudioThresholdLow;
        }

        if (fVar9 < gAudioThresholdHigh) // DAT_01206ad8
        {
            if (fVar9 < gAudioThresholdMid) // DAT_01206ac4
            {
                pfThresholdLow = &gAudioThresholdMid;
                if (fVar9 < gAudioThresholdLow) // DAT_01206ab0
                {
                    pfThresholdLow = &gAudioThresholdLow;
                }
            }
            else
            {
                pfThresholdLow = &gAudioThresholdHigh; // DAT_01206ad8
            }
        }
        else
        {
            pfThresholdLow = &gAudioThresholdHigh;
        }

        fVar14 = *pfThresholdHigh;
        if (fVar14 < *pfThresholdLow)
        {
            fVar11 = (fVar9 - fVar14) / (*pfThresholdLow - fVar14);
        }

        fVar15 = fVar15 - fVar11;

        // Interpolate output color/values based on thresholds
        gAudioOutputColorR = pfThresholdHigh[1] * fVar15 + pfThresholdLow[1] * fVar11; // DAT_012233c8
        gAudioOutputColorG = pfThresholdHigh[2] * fVar15 + pfThresholdLow[2] * fVar11; // DAT_012233d0
        gAudioOutputColorB = pfThresholdHigh[3] * fVar15 + pfThresholdLow[3] * fVar11; // DAT_012233d4
        gAudioOutputColorA = pfThresholdHigh[4] * fVar15 + pfThresholdLow[4] * fVar11; // DAT_012233d8
        float* pfHist = (float*)&gAudioHistogram;
        uVar3 = 0;
        gAudioOutputBaseColor = gAudioOutputColorR; // DAT_012233cc
        gAudioOutputBaseAlpha = gAudioOutputColorA; // DAT_012233dc

        // Apply random noise to histogram bins (flicker effect)
        do
        {
            dVar12 = RandomFloat(); // FUN_00b9af10 returns double
            *pfHist = (float)dVar12 * *pfHist;
            uVar3 += 0x18;
            pfHist++;
        } while (uVar3 < 0xC00);
    }
}