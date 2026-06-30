// FUNC_NAME: ParticleEffectSystem::spawnParticle
int __thiscall ParticleEffectSystem::spawnParticle(EffectContext* context, int extraParam) {
    ParticleData* data = *(ParticleData**)(this + 0x60); // +0x60: particle definition pointer
    if (data == 0) {
        return 0;
    }

    *(char*)(this + 0x30) = 0; // +0x30: clear some flag
    *(ParticleEffectSystem**)(context + 0x7c) = this; // +0x7c: back pointer to emitter

    byte typeByte = data->type; // first byte of data: particle type
    int savedParam = *(int*)(this + 0x20); // +0x20: parameter passed to creation

    if ((typeByte & 0x3f) < 0x23) {
        // Jump table for particle type creation at DAT_0103afc0, index = (typeByte & 0x3f)
        int (*createFunc)(EffectContext*, byte*, int, int, int, int, float) =
            (int (*)(EffectContext*, byte*, int, int, int, int, float))DAT_0103afc0[(typeByte & 0x3f)];
        Particle* newParticle = (Particle*)createFunc(
            context,
            (byte*)data,
            *(int*)(this + 100), // +0x64: some parameter (e.g., lifetime scale)
            *(int*)(this + 0x1c), // +0x1c: another parameter
            savedParam,
            extraParam,
            1.0f // 0x3f800000
        );
        if (newParticle != 0) {
            // FUN_0056cba0: likely vector operation (copy/add velocity)
            // call(newParticle + 0x10, this + 0x40, newParticle + 0x10)
            VectorOperation(newParticle + 0x10, this + 0x40); 

            // Add emitter position offset to particle position (Vector4)
            newParticle->posX += *(float*)(this + 0x50); // +0x50: emitter X
            newParticle->posY += *(float*)(this + 0x54); // +0x54: emitter Y
            newParticle->posZ += *(float*)(this + 0x58); // +0x58: emitter Z
            newParticle->posW = *(float*)&DAT_00e2b1a4; // +0x2c: set W to constant
        }
    } else {
        newParticle = 0;
    }

    *(ParticleEffectSystem**)(context + 0x7c) = this; // restore context reference
    FUN_00591160(); // probably update emitter state

    *(int*)(this + 0x24) = savedParam; // +0x24: store back saved parameter

    if (*(int*)(this + 0x68) != 0) {
        // Free allocated data associated with particle definition
        FUN_00591ab0(context, *(int*)(this + 0x60), *(int*)(this + 100));
        *(int*)(this + 0x68) = 0; // clear pointer
    }

    // Clear bit 5 (0x20) of flags at +0x10
    *(int*)(this + 0x10) &= 0xffffffdf;

    return (int)newParticle;
}