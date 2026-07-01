// FUNC_NAME: WeaponBase::spawnProjectile
// Function address: 0x0084eec0
// Reconstructed C++ for EA EARS engine, Godfather 2
void __thiscall WeaponBase::spawnProjectile(WeaponBase* this, Entity* pSpawner, uint extraParam)
{
    // Check spawner validity and ability to spawn
    if (pSpawner != nullptr) {
        bool canSpawn = pSpawner->vtable->canSpawn();  // virtual at vtable+0x78
        if (canSpawn) {
            // Allocate projectile object (size 0x48 = 72 bytes)
            Projectile* pProj = (Projectile*)EA::Memory::alloc(0x48);
            if (pProj == nullptr) {
                pProj = nullptr;
            } else {
                // Call constructor for projectile
                Projectile::constructor(pProj);
            }

            // Release references to components currently held by this weapon
            // +0x30 and +0x2c are likely pointers to shared components (e.g., weapon model, sound)
            EA::ReleaseRef(*(IUnknown**)(this + 0x30));  // FUN_0044b210
            EA::ReleaseRef(*(IUnknown**)(this + 0x2c));

            // Copy spawn position from this weapon to projectile
            // this offsets: +0x10 = m_spawnPos.x, +0x14 = m_spawnPos.y, +0x18 = m_spawnPos.z
            pProj->m_positionX = *(float*)(this + 0x10);  // +0x20
            pProj->m_positionY = *(float*)(this + 0x14);  // +0x24
            pProj->m_positionZ = *(float*)(this + 0x18);  // +0x28

            // If weapon has a secondary component (e.g., bone transform?), copy its transform
            if (*(int*)(this + 0x30) != 0) {
                // FUN_00471610 likely returns a transform struct pointer (e.g., Matrix43)
                void* pTransform = GetTransformComponent();  // return iVar5
                // Copy 8 bytes at +0x30 (two floats or a Vec3?) and 4 bytes at +0x38
                pProj->m_transformOffset0 = *(uint64*)(pTransform + 0x30);  // +0x14
                pProj->m_transformOffset1 = *(uint32*)(pTransform + 0x38);  // +0x1c
            }

            // Set projectile's extra parameters
            pProj->m_extraParam = *(uint32*)(this + 0x34);   // +0x30 = from weapon's field
            pProj->m_spawnerParam = extraParam;              // +0x2c = passed in param_3

            // Set global flag (e.g., projectile ID or type)
            pProj->m_globalFlag = DAT_01205224;              // +0x40

            // Generate random value for initial velocity/offset
            int randVal = rand();
            float randomFloat = (float)randVal * DAT_00e44590 * DAT_00d5f18c + DAT_00d5efb8;

            // Register projectile with global manager
            // DAT_0112dd94 is likely g_projectileManager
            // pSpawner + 0xf is an offset into the spawner's data (e.g., weapon slot)
            ProjectileManager::addProjectile(g_projectileManager, pSpawner + 0xf, randomFloat, pProj, 0);
        }
    }
}