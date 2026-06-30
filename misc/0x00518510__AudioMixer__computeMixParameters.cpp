// FUNC_NAME: AudioMixer::computeMixParameters
// Function address: 0x00518510
// Role: Computes audio mix coefficients (gain, pan, etc.) for a sound channel.
// Uses global flags and thread-local storage for current audio context.

// Note: Custom calling convention: EAX = output1 (float*), ESI = output2 (float*, optional)
// ECX = param1 (unused?), EDX = param2 (pointer to sound channel structure)

void __fastcall AudioMixer::computeMixParameters(
    uint32_t unusedParam1,       // ECX - not used in body
    SoundChannel* channel       // EDX - structure at param2
)
{
    float fVar1;
    int iVar2;
    uint8_t bFlags;
    float* output1 = *reinterpret_cast<float**>(&EAX); // in_EAX from decompiler
    float* output2 = *reinterpret_cast<float**>(&ESI); // unaff_ESI (optional)
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;

    // Get base frequency/volume from global (DAT_012192d0)
    fVar4 = sAudioMasterFrequency; // DAT_012192d0

    // If flag 0x4 is set, use interpolated value from table
    if (sAudioFlags & 0x4) { // DAT_012192f4 & 4
        fVar4 = _fRam01218e18 * _sAudioParamA + 
                _fRam01218e08 * _sAudioParamB +
                _fRam01218e28 * _sAudioParamC +
                _fRam01218e38 * _sAudioParamD +
                sAudioMasterFrequency; // DAT_012192d0
    }

    // Read channel parameters at offsets +0x144 and +0x148
    fVar6 = channel->field_0x144; // Likely a frequency or rate
    fVar1 = channel->field_0x148; // Another parameter (e.g., duration)

    // Compute first output based on flag 0x2
    if ((sAudioFlags & 2) == 0) { // DAT_012192f4 & 2
        fVar5 = 0.0f;
    } else {
        fVar5 = sAudioOffset1 - _sAudioOffset2; // DAT_00e44564 - _DAT_012192e8
    }
    output1[0] = fVar5; // First coefficient

    // Compute second output based on flag 0x1
    bFlags = sAudioFlags & 1;
    fVar5 = sAudioDefaultValue; // DAT_012192ec
    if (bFlags == 0) {
        fVar5 = 0.0f;
    }
    output1[1] = fVar5;

    // Access thread-local storage for current thread's audio context
    // FS:0x2C points to thread data block
    iVar2 = *(int*)(**(int**)(__readfsdword(0x2C) + 0x2C) + 0x34); 
    // Select index based on iVar2 non-zero
    iVar2 = *(int*)(&sAudioIndexTable[0] + (uint)(iVar2 != 0) * 4); // DAT_011f6be8 / DAT_011f6bec

    fVar7 = sAudioFactor * fVar1; // DAT_012192d4 * fVar1

    // Compute third coefficient with complex formula
    output1[2] = (( (fVar1 / fVar4) * fVar6 - fVar6) / (fVar1 - fVar6)) * fVar5 - fVar5;

    // Store temporary third, then override
    output1[3] = fVar5;

    // Adjust third coefficient using another global table
    fVar4 = sAudioBaseGain; // DAT_00e2b1a4
    fVar6 = fVar4;
    if (iVar2 != -1) {
        fVar6 = gAudioFloatTable[iVar2 * 3]; // DAT_011f6bbc
    }
    output1[3] = (fVar4 / fVar6) * fVar5;

    // If second output pointer is provided, set stereo pan/position
    if (output2 != nullptr) {
        output2[0] = sAudioPanScaleX * _sAudioPanFactor;   // DAT_01218e44 * _DAT_012192d8
        output2[1] = sAudioPanScaleY * _sAudioPanFactor;   // DAT_01218e48 * _DAT_012192d8
        output2[2] = 0.0f;
        output2[3] = 0.0f;
    }
}