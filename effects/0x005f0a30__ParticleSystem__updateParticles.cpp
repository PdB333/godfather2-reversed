//FUNC_NAME: ParticleSystem::updateParticles
uint __thiscall ParticleSystem::updateParticles(int* thisPtr)
{
    int* particleArray;
    int particleBase;
    int particleCount;
    int deltaX;
    int deltaY;
    int context;
    int index;
    int currentParticle;
    int newState;

    if (thisPtr == nullptr) {
        return 0; // return in_EAX & 0xffffff00 simplified
    }

    // +0x04: some context (e.g., renderer)
    // +0x38: number of particles
    context = *(int*)((int)thisPtr + 4);
    particleCount = *(int*)((int)thisPtr + 0x38);
    FUN_005dbc10(context, particleCount); // initial call with context and count

    if (particleCount != 0) {
        // +0x58: array of particle indices/offsets
        particleArray = (int*)((int)thisPtr + 0x58);
        // +0x50: base offset for particle data
        particleBase = *(int*)((int)thisPtr + 0x50);
        // +0x20: deltaX (velocity or gravity)
        deltaX = *(int*)((int)thisPtr + 0x20);
        // +0x28: deltaY
        deltaY = *(int*)((int)thisPtr + 0x28);

        index = 0;
        do {
            currentParticle = *particleArray + particleBase; // particle data pointer

            // +0x48: particle state (0xDEADBEEF = dead, -1 = unused)
            if (*(int*)(currentParticle + 0x48) != -0x21524111 && *(int*)(currentParticle + 0x48) != -1) {
                newState = FUN_005f0b20(); // allocate new state?
                *(int*)(currentParticle + 0x48) = newState;
            }

            if (*(int*)(currentParticle + 0x48) == 0) {
                *particleArray = 0; // clear index
            } else {
                // +0x4c: position X
                // +0x50: position Y
                *(int*)(currentParticle + 0x4c) += deltaX;
                *(int*)(currentParticle + 0x50) += deltaY;

                // Render call: first arg is texture/ID at +0x28, then color bytes at +0x21, +0x20, +0x23, +0x22
                FUN_005dbc10(
                    *(int*)(currentParticle + 0x28),   // texture or something
                    *(char*)(currentParticle + 0x21),  // color component (G?)
                    *(char*)(currentParticle + 0x20),  // color component (R?)
                    *(char*)(currentParticle + 0x23),  // color component (A?)
                    *(char*)(currentParticle + 0x22)   // color component (B?)
                );
                FUN_005f2490(); // post-render update

                *particleArray = currentParticle; // store updated pointer
            }

            particleArray++;
            index++;
        } while (index < particleCount);

        return 1; // success (CONCAT31((int3)(index >> 8), 1) simplified)
    }

    return 1;
}