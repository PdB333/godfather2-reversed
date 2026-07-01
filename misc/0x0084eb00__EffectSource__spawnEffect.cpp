// FUNC_NAME: EffectSource::spawnEffect
// Function at 0x0084eb00: Spawns a new effect/particle instance from an effect source
void EffectSource::spawnEffect(int *source, Vector3 *position, Vector3 *velocity, float lifetime, float scale, int unknownRef1, int unknownRef2)
{
    if (source != nullptr) {
        // Check if the source is active via virtual function at vtable+0x78
        bool isActive = (**(code **)(*source + 0x78))();
        if (isActive) {
            // Allocate a new effect instance (size 0x48 = 72 bytes)
            int *newEffect = (int *)FUN_009c8e50(0x48);
            if (newEffect != nullptr) {
                newEffect = FUN_0084dd20(); // Constructor call (returns the same pointer)
            }

            // Release references to unknown objects
            FUN_0044b210(unknownRef2);
            FUN_0044b210(unknownRef1);

            // Copy position into newEffect structure (stored twice? possibly local and world position)
            Vector3 posCopy;
            posCopy.x = position->x;
            posCopy.y = position->y;
            posCopy.z = position->z;
            *(Vector3 *)(newEffect + 0x20) = posCopy;  // +0x20: world position
            *(Vector3 *)(newEffect + 0x14) = posCopy;  // +0x14: local position (or initial)

            // Set velocity/direction
            *(float *)(newEffect + 0x30) = scale;      // +0x30: scale
            *(float *)(newEffect + 0x2C) = lifetime;   // +0x2C: lifetime

            // Set a global constant (e.g., particle lifespan)
            *(int *)(newEffect + 0x40) = DAT_01205224; // +0x40: some global timer/limit

            // Randomize a scalar factor using rand()
            int r = _rand();
            float randomFloat = (float)r * DAT_00e44590 * DAT_00d5f18c + DAT_00d5efb8;

            // Register the effect with the manager (global singleton DAT_0112dd94)
            // source + 0xf is likely a tag or name offset within the source struct
            FUN_00440590(&DAT_0112dd94, (char *)(source + 0xf), randomFloat, newEffect, 0);
        }
    }
}