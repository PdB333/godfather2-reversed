// FUNC_NAME: ParticleEmitter::initializeData
// Address: 0x0053ac30
// This function initializes particle emitter data: calculates per-particle parameters (angles, speeds) based on emitter properties.
// param_1 = this (ParticleEmitter*), param_2 = output particle array buffer, param_3 = number of particles, param_4 = float[3] (multipliers)
// Particle structure at param_2: header (0xe,0x1c) then array of 0x20-byte entries starting at offset 0xf.
// Additional per-particle data at param_2+0x3c (ushort array, stride 0x20 bytes, used for indexing)

int __thiscall ParticleEmitter::initializeData(void* this, void* particleBuffer, int particleCount, float* multipliers)
{
    float fStartAngle = *(float*)((int)this + 0x30);   // +0x30: start angle (radians)
    float fEndAngle   = *(float*)((int)this + 0x34);   // +0x34: end angle (radians)
    float fAngleRate  = *(float*)((int)this + 0x38);   // +0x38: angle rate multiplier
    float fSizeFactor = *(float*)((int)this + 0x3c);   // +0x3c: size factor

    float currentAngle = fStartAngle * fAngleRate;      // initial angle product
    float angleStep = (fEndAngle - fStartAngle) / (float)(particleCount - 1);

    *(char*)((int)particleBuffer + 0xe)  = (char)particleCount;               // +0xe: particle count (char)
    *(unsigned short*)((int)particleBuffer + 0x1c) = (unsigned short)(byte)((char)particleCount - 1); // +0x1c: count-1 (ushort)

    if (particleCount > 0)
    {
        char* particlePtr = (char*)((int)particleBuffer + 0xf);           // start of particle array (0x20 bytes each)
        unsigned short* indexPtr = (unsigned short*)((int)particleBuffer + 0x3c); // index array (same stride)

        float angleAccum = currentAngle;
        float angleCurr  = fStartAngle;

        for (int i = 0; i < particleCount; i++)
        {
            // Clear two bytes (unknown flags)
            *(particlePtr - 0xffffffff00000003) = '\0';   // likely *(particlePtr + 0x1)   (offset 0x1 from particle start)
            *(particlePtr - 0xffffffff00000002) = '\0';   // likely *(particlePtr + 0x2)   (offset 0x2)

            if (i != 0)
            {
                *indexPtr = (unsigned short)i & 0xff;     // store index (low byte) in index array
                indexPtr += 0x10;                         // stride 0x10 ushorts = 0x20 bytes, matches particle stride
            }

            *particlePtr = (i != 0) + 1;                  // particle type: 1 for first, 2 for others (byte at offset 0x0)

            // Write initial velocity component: multiplier[0] * current angle
            *(float*)(particlePtr - 0xf) = multipliers[0] * angleCurr;   // offset -0xf from particlePtr -> particlePtr - 0xf = start of particle? Actually relative to buffer start? Assume offset 0x0 of particle? More likely *(float*)(particlePtr - 0xf) == *(float*)((int)particleBuffer + 0) ??? This is messy.
            // The decompiler shows pcVar3[-0xf] = *param_4 * fVar7;   where pcVar3 starts at param_2+0xf, so pcVar3[-0xf] = *(param_2+0). So first float of particle is at buffer start? That seems wrong. Let's assume it's *(float*)(particlePtr - 0xf) = *(float*)((int)particleBuffer - 0xf)? No, param_2 is particleBuffer, pcVar3 = param_2+0xf, so pcVar3[-0xf] = *(param_2+0xf - 0xf) = *(param_2). So the float is written to the very beginning of the buffer. So buffer+0 is float0. But then we also have header at 0xe, 0x1c, etc. So the buffer layout might be: 0-3: float (first particle's first field?) Then 4-... hmm.

            // Clear four bytes (unknown flags)
            *(particlePtr - 0xffffffff0000000b) = '\0';   // offset +0x? (impossible)
            *(particlePtr - 0xffffffff0000000a) = '\0';
            *(particlePtr - 0xffffffff00000009) = '\0';
            *(particlePtr - 0xffffffff00000008) = '\0';

            double dVar4 = (double)currentAngle;
            FUN_00b99fcb();   // likely rand() or sin/cos()

            // Update accumulators
            angleAccum = fAngleRate * angleStep + angleAccum;
            angleCurr  = angleStep + angleCurr;

            // Write second component: dVar4 * sizeFactor * multiplier[2]
            *(float*)(particlePtr - 7) = (float)dVar4 * fSizeFactor * multipliers[2]; // offset ambiguous

            currentAngle = angleAccum;
            fStartAngle  = angleCurr;   // note: this overwrites local variable, but original uses fVar7 = local_14

            FUN_00414aa0();   // another math function

            i = i + 1;
            particlePtr += 0x20;
        }
    }
    return 1;
}