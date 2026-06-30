// FUNC_NAME: ParticleManager::spawnParticle
// Address: 0x0060db60
// Role: Creates a new particle entry in the particle data array, using a lookup table to determine subtype,
//        and initializes its position, size, and color.

void ParticleManager::spawnParticle(uint particleTypeIndex, float posScaleX, float posScaleY, float posScaleZ, float lifeScale)
{
    // Lookup particle subtype from a table indexed by particleTypeIndex (each entry is 2 bytes)
    ushort particleSubType = FUN_006066e0(*(undefined2*)(gParticleTypeTable + particleTypeIndex * 2));

    // Global default color for particles
    uint defaultColor = gParticleDefaultColor; // DAT_00e2b1a4

    // Calculate scaled life value
    int scaledLife = (int)((float)particleSubType * lifeScale);

    // Get current slot index (each slot is 0x18 bytes)
    int slotOffset = gParticleSlotIndex * 0x18; // DAT_012058b0

    // Set particle position (x, y, z) – note: position is scaled by the particle type index itself
    *(int*)(gParticleDataArray + slotOffset + 0x00) = (int)((float)(particleTypeIndex & 0xffff) * posScaleX);
    *(int*)(gParticleDataArray + slotOffset + 0x04) = (int)((float)particleSubType * posScaleY);
    *(int*)(gParticleDataArray + slotOffset + 0x08) = (int)((float)(particleTypeIndex & 0xffff) * posScaleZ);
    *(int*)(gParticleDataArray + slotOffset + 0x0c) = scaledLife; // life or size
    *(int*)(gParticleDataArray + slotOffset + 0x10) = 0;          // unused / zero
    *(uint*)(gParticleDataArray + slotOffset + 0x14) = defaultColor; // color

    // Initialize particle effect with scaled life and a fixed 1.0f factor
    FUN_00609500(scaledLife, 1.0f);
}

// Global variables referenced:
// - gParticleTypeTable (offset 0x011f38f4) – array of ushort (subtype per particle type)
// - gParticleDefaultColor (offset 0x00e2b1a4) – uint color value
// - gParticleSlotIndex (offset 0x012058b0) – int index into particle data array
// - gParticleDataArray (offset 0x011f3918) – array of structures (0x18 bytes each):
//   +0x00: int posX
//   +0x04: int posY
//   +0x08: int posZ
//   +0x0c: int life/size
//   +0x10: int reserved
//   +0x14: uint color