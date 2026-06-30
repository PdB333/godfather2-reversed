// FUNC_NAME: AudioDataManager::processAudioData
// Address: 0x0057e300
// This function processes audio data, converting between different sample rates and formats.
// It appears to handle audio resampling and channel conversion (mono/stereo).
// The function takes a pointer to a structure containing audio processing parameters.

int AudioDataManager::processAudioData(int *params)
{
    bool bIsResampling;
    int iSampleCount;
    char *pInputData;
    float *pOutputBuffer;
    float *pTempBuffer;
    int iChannelCount;
    float10 fAccumulator;
    float fSampleValue;
    float fFractionalPart;
    float fIntegerPart;
    float fInputSample;
    float fOutputSample;
    
    // Get audio format info from params
    iSampleCount = params[1];  // +0x04: sample count
    fInputSample = (float)params[2];  // +0x08: input sample rate
    
    // Determine audio format based on channel count
    if ((*(uint *)(iSampleCount + 4) & 0xff) < 10) {
        fOutputSample = *(float *)(iSampleCount + 0x24);  // +0x24: output sample rate (mono)
    }
    else {
        fOutputSample = *(float *)(iSampleCount + 0x2c);  // +0x2c: output sample rate (stereo)
    }
    
    // Calculate resampling ratio
    fIntegerPart = (float)(int)fInputSample;
    fFractionalPart = fInputSample - fIntegerPart;
    fSampleValue = 1.0f - fFractionalPart;  // DAT_00e2b1a4 = 1.0f
    
    // Determine if we need to resample up or down
    if (0.5f < fFractionalPart) {  // DAT_00e2e780 = 0.5f
        if (0.5f < fSampleValue) {
            bIsResampling = true;
            fOutputSample = fSampleValue;
        }
        else {
            fInputSample = (float)((int)fInputSample + 1);
            fSampleValue = 0.0f;
            fFractionalPart = 0.0f;
            fOutputSample = 1.0f;
            bIsResampling = false;
        }
    }
    else {
        fSampleValue = 0.0f;
        fFractionalPart = 0.0f;
        fOutputSample = 1.0f;
        bIsResampling = false;
        fInputSample = fIntegerPart;
    }
    
    // Get or create audio processing buffers
    iSampleCount = *(int *)(*params + 0x38);  // +0x38: audio buffer pointer
    iChannelCount = params[3];  // +0x0c: channel count
    fSampleValue = 1.0f;
    
    if (iSampleCount == 0) {
        iSampleCount = FUN_0056ef10(iChannelCount);  // Allocate audio buffer
        fSampleValue = 1.0f;
        *(int *)(*params + 0x38) = iSampleCount;
    }
    
    pOutputBuffer = (float *)(iSampleCount + 0x10);  // +0x10: output buffer
    iSampleCount = params[1];  // +0x04: sample count
    pInputData = (char *)(*(int *)(*params + 0x34) + 0x14);  // +0x34: input data pointer
    
    // Get audio format flags
    if ((*(uint *)(iSampleCount + 4) & 0xff) < 10) {
        iSampleCount = *(int *)(iSampleCount + 0x20);  // +0x20: mono format flag
    }
    else {
        iSampleCount = *(int *)(iSampleCount + 0x28);  // +0x28: stereo format flag
    }
    
    // Process audio data based on resampling direction
    if (iSampleCount < 0) {
        // Downsampling
        fAccumulator = (float10)fInputSample;
        if (bIsResampling) {
            // Resample up
            for (; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                if (*pInputData == '\x02') {  // Audio data present
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    *pOutputBuffer = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[1] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[2] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[3] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[4] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[5] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[6] = fSampleValue;
                    pOutputBuffer[7] = fSampleValue;
                }
                else if (*pInputData != '\0') {
                    // Skip audio data
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                pInputData = pInputData + 1;
                pOutputBuffer = pOutputBuffer + 8;
            }
            
            // Process remaining samples
            iSampleCount = params[5];  // +0x14: remaining sample count
            if (0 < iSampleCount) {
                for (iChannelCount = params[4] - params[3]; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                
                iChannelCount = *(int *)(*params + 0x40);  // +0x40: temp buffer
                if (iChannelCount == 0) {
                    iChannelCount = FUN_00580b40(iSampleCount);  // Allocate temp buffer
                    fAccumulator = (float10)fInputSample;
                    *(int *)(*params + 0x40) = iChannelCount;
                }
                
                pOutputBuffer = (float *)(iChannelCount + 0x10);
                if (0 < iSampleCount) {
                    do {
                        fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                        *pOutputBuffer = fSampleValue;
                        iSampleCount = iSampleCount + -1;
                        pOutputBuffer = pOutputBuffer + 1;
                    } while (0 < iSampleCount);
                    return 1;
                }
            }
        }
        else {
            // Resample down
            for (; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                if (*pInputData == '\x02') {
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    *pOutputBuffer = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[1] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[2] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[3] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[4] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[5] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[6] = fSampleValue;
                    pOutputBuffer[7] = fSampleValue;
                }
                else if (*pInputData != '\0') {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                pInputData = pInputData + 1;
                pOutputBuffer = pOutputBuffer + 8;
            }
            
            iSampleCount = params[5];
            if (0 < iSampleCount) {
                for (iChannelCount = params[4] - params[3]; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                
                iChannelCount = *(int *)(*params + 0x40);
                if (iChannelCount == 0) {
                    iChannelCount = FUN_00580b40(iSampleCount);
                    fAccumulator = (float10)fInputSample;
                    *(int *)(*params + 0x40) = iChannelCount;
                }
                
                pOutputBuffer = (float *)(iChannelCount + 0x10);
                if (0 < iSampleCount) {
                    do {
                        fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                        *pOutputBuffer = fSampleValue;
                        iSampleCount = iSampleCount + -1;
                        pOutputBuffer = pOutputBuffer + 1;
                    } while (0 < iSampleCount);
                    return 1;
                }
            }
        }
    }
    else {
        // Upsampling
        iSampleCount = *(int *)(*params + 0x3c);  // +0x3c: upsampling buffer
        if (iSampleCount == 0) {
            iSampleCount = FUN_005807d0(iChannelCount);  // Allocate upsampling buffer
            fSampleValue = 1.0f;
            *(int *)(*params + 0x3c) = iSampleCount;
        }
        
        fAccumulator = (float10)fInputSample;
        pTempBuffer = (float *)(iSampleCount + 0x10);
        
        if (bIsResampling) {
            // Resample up with stereo output
            for (; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                if (*pInputData == '\x02') {
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    *pOutputBuffer = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[1] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[2] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[3] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[4] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[5] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[6] = fSampleValue;
                    pOutputBuffer[7] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    *pTempBuffer = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pTempBuffer[1] = fSampleValue;
                    fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                    pTempBuffer[2] = fSampleValue;
                    pTempBuffer[3] = fSampleValue;
                }
                else if (*pInputData != '\0') {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                pInputData = pInputData + 1;
                pOutputBuffer = pOutputBuffer + 8;
                pTempBuffer = pTempBuffer + 4;
            }
            
            iSampleCount = params[5];
            if (0 < iSampleCount) {
                for (iChannelCount = params[4] - params[3]; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                
                iChannelCount = *(int *)(*params + 0x40);
                if (iChannelCount == 0) {
                    iChannelCount = FUN_00580b40(iSampleCount);
                    fAccumulator = (float10)fInputSample;
                    *(int *)(*params + 0x40) = iChannelCount;
                }
                
                pOutputBuffer = (float *)(iChannelCount + 0x10);
                if (0 < iSampleCount) {
                    do {
                        fAccumulator = (float10)FUN_0057d4e0(&fOutputSample, (float)fAccumulator);
                        *pOutputBuffer = fSampleValue;
                        iSampleCount = iSampleCount + -1;
                        pOutputBuffer = pOutputBuffer + 1;
                    } while (0 < iSampleCount);
                    return 1;
                }
            }
        }
        else {
            // Resample down with stereo output
            for (; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                if (*pInputData == '\x02') {
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    *pOutputBuffer = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[1] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[2] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[3] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[4] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[5] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pOutputBuffer[6] = fSampleValue;
                    pOutputBuffer[7] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    *pTempBuffer = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pTempBuffer[1] = fSampleValue;
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    pTempBuffer[2] = fSampleValue;
                    pTempBuffer[3] = fSampleValue;
                }
                else if (*pInputData != '\0') {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                pInputData = pInputData + 1;
                pOutputBuffer = pOutputBuffer + 8;
                pTempBuffer = pTempBuffer + 4;
            }
            
            iSampleCount = params[5];
            if (0 < iSampleCount) {
                for (iChannelCount = params[4] - params[3]; 0 < iChannelCount; iChannelCount = iChannelCount + -1) {
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    FUN_0057d3a0(&fOutputSample);
                    fAccumulator = (float10)FUN_0057d3a0(&fOutputSample);
                }
                
                iChannelCount = *(int *)(*params + 0x40);
                if (iChannelCount == 0) {
                    iChannelCount = FUN_00580b40(iSampleCount);
                    fAccumulator = (float10)fInputSample;
                    *(int *)(*params + 0x40) = iChannelCount;
                }
                
                pOutputBuffer = (float *)(iChannelCount + 0x10);
                for (; 0 < iSampleCount; iSampleCount = iSampleCount + -1) {
                    fAccumulator = (float10)FUN_0057dc70(&fOutputSample, (float)fAccumulator);
                    *pOutputBuffer = fSampleValue;
                    pOutputBuffer = pOutputBuffer + 1;
                }
            }
        }
    }
    return 1;
}