// FUNC_NAME: SimProjectile::~SimProjectile
void __fastcall SimProjectile::~SimProjectile(SimProjectile* this)
{
    float distanceSq;
    int targetEntity1;
    int targetEntity2;
    float dx;
    float dy;
    float dz;

    // Set vtable to base class (likely EARS::Framework::SimObject)
    *(int*)this = &PTR_LAB_00d63dc0;

    // If the projectile has a visual activation flag clear it
    if (*(char*)(this + 0x1e) != '\0') {
        setVisible(false);  // FUN_007f6300(0)
        *(undefined1*)(this + 0x1e) = 0;
    }

    // Get the projectile's physics component (pointer at +0x68) and its trigger radius at +0x50
    PhysicsComponent* physics = *(PhysicsComponent**)((char*)this + 0x68);
    distanceSq = *(float*)((char*)physics + 0x50);

    // Check if we have a target entity (pointer at +0x5C) and it's not a specific type (0x48)
    Entity* targetEntity = *(Entity**)((char*)this + 0x5C);
    if ((targetEntity != 0) && (targetEntity != (Entity*)0x48)) {
        // Get two entities (possibly the target and the projectile itself)
        targetEntity1 = getEntity();  // FUN_00471610
        targetEntity2 = getEntity();  // FUN_00471610
        // Compute vector between them
        dx = *(float*)(targetEntity1 + 0x30) - *(float*)(targetEntity2 + 0x30);
        dy = *(float*)(targetEntity1 + 0x34) - *(float*)(targetEntity2 + 0x34);
        dz = *(float*)(targetEntity1 + 0x38) - *(float*)(targetEntity2 + 0x38);
        if (dx*dx + dy*dy + dz*dz <= distanceSq * distanceSq) {
            // Target is within radius; snap physics position to the target's position
            targetEntity1 = getEntity();  // FUN_00471610
            PhysicsComponent* phys = *(PhysicsComponent**)((char*)this + 0x68);
            *(undefined8*)((char*)phys + 0x30) = *(undefined8*)(targetEntity1 + 0x30);
            *(undefined4*)((char*)phys + 0x38) = *(undefined4*)(targetEntity1 + 0x38);
            // Mark physics position as dirty (bit 0x20 at +0x78)
            *(unsigned short*)((char*)phys + 0x78) |= 0x20;
        }
    }

    // Play impact sound (sound ID 0x62)
    playSound(0x62);  // FUN_007f6420

    // If there's a damage source (pointer at +0x58) and the game is active, remove from simulation
    if ((*(int*)((char*)this + 0x58) != 0) && (isGameActive(DAT_01131038) != 0)) {
        removeFromSimulation();  // FUN_009b07a0(0)
    }

    // Release child objects (visual model at +0x70, target at +0x5C)
    if (*(int*)((char*)this + 0x70) != 0) {
        releaseObject(this + 0x70);  // FUN_004daf90(param_1 + 0x1c)
    }
    if (*(int*)((char*)this + 0x5C) != 0) {
        releaseObject(this + 0x5C);  // FUN_004daf90(param_1 + 0x17)
    }

    // Final cleanup (possibly freeing the object itself)
    cleanup();  // FUN_0080ea60()
}