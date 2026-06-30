// FUNC_NAME: ParticleEmitter::generateRandomDirection
void ParticleEmitter::generateRandomDirection(Vector4& outVelocity, undefined4 param_2) // param_2 may be a pointer to emitter data
{
    float randomDirection[3]; // local_30, local_2c, local_28
    randomDirection[0] = 0.0f;
    randomDirection[1] = 0.0f;
    randomDirection[2] = 0.0f;
    float randomValue = getRandomFloat(); // FUN_0055a980, returns [0,1)
    if (randomValue > gProbabilityThreshold) // DAT_00e446c8
    {
        fillRandomDirection(randomDirection); // FUN_0055aa00, fills with random unit vector
        float scale = getRandomFloat(); // another random for speed
        randomDirection[0] *= scale;
        randomDirection[1] *= scale;
        randomDirection[2] *= scale;
    }
    // Copy to output
    outVelocity.x = randomDirection[0];
    outVelocity.y = randomDirection[1];
    outVelocity.z = randomDirection[2];
    outVelocity.w = gSomeExtraData; // DAT_00e2b1a4, maybe lifetime or color
    emitParticle(&outVelocity, param_2); // FUN_0056d1f0
}