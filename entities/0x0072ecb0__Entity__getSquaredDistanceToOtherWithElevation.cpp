// FUNC_NAME: Entity::getSquaredDistanceToOtherWithElevation
float Entity::getSquaredDistanceToOtherWithElevation(const PackedPosition& other) const
{
    // other.xy is a 64-bit integer containing two floats: low 32 bits = x, high 32 bits = y
    // other.z at offset 8
    float otherX = *reinterpret_cast<const float*>(&other.xy); // low 32 bits as float (x)
    uint32_t yBits = static_cast<uint32_t>(other.xy >> 32);   // high 32 bits
    float otherY = *reinterpret_cast<const float*>(&yBits);   // reinterpret bits as float (y)
    float otherZ = other.z;

    // Apply world‑space Y offset (e.g. elevation adjustment)
    otherY += kYOffset; // DAT_00e518a4 – constant elevation offset

    // Get own world position via internal storage function
    PackedPosition selfStorage; // local_c – 12‑byte temporary
    PackedPosition* self = reinterpret_cast<PackedPosition*>(
        getWorldPositionInternal(&selfStorage, 0) // FUN_00424fb0 – returns pointer to position
    );

    float selfX = *reinterpret_cast<const float*>(&self->xy);
    uint32_t selfYBits = static_cast<uint32_t>(self->xy >> 32);
    float selfY = *reinterpret_cast<const float*>(&selfYBits);
    float selfZ = self->z;

    float dx = otherX - selfX;
    float dy = otherY - selfY;
    float dz = otherZ - selfZ;

    return (dx * dx) + (dy * dy) + (dz * dz); // squared distance
}