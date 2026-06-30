// FUNC_NAME: Weapon::tryRegisterHit

// Assumed external functions: are they in the same module? Provide declarations.
bool isLineOfSightBlocked(float* targetPos, float* sourcePos); // 0x006a8560 – returns true if line of sight is blocked
void addHitRecord(uint hitData, float* targetPos); // 0x005f5c60 – records a hit on target

// Offset layout for this class (Weapon):
// +0x04 : float maxSqDistance  – squared maximum effective range
// +0x18c: int hitCount         – number of registered hits (capped at 32)

bool __thiscall Weapon::tryRegisterHit(uint hitData, Entity* hitTarget, float* impactPosition)
{
    bool canAdd;

    // Only allow up to 32 hits in a single burst
    if (this->hitCount < 32)
    {
        // hitTarget byte at +0x21: bit0 (alive flag) must be clear
        // hitTarget flags at +0x18: bits 14-15 must be clear (e.g., invulnerability)
        // The squared distance from hitTarget's position to impactPosition must be within maxSqDistance
        if (((*(&hitTarget->byteAt0x21) & 1) == 0) &&
            (((uint)hitTarget->flagsAt0x18 & 0xC000) == 0) &&
            ((hitTarget->position.z - impactPosition[2]) * (hitTarget->position.z - impactPosition[2]) +
             (hitTarget->position.y - impactPosition[1]) * (hitTarget->position.y - impactPosition[1]) +
             (hitTarget->position.x - impactPosition[0]) * (hitTarget->position.x - impactPosition[0]) < this->maxSqDistance))
        {
            // Check if line of sight is blocked; if not, register the hit
            if (!isLineOfSightBlocked((float*)hitTarget, impactPosition))
            {
                addHitRecord(hitData, (float*)hitTarget);
                this->hitCount++;
                return true;
            }
        }
        canAdd = (this->hitCount < 32);
    }
    return !canAdd;
}

// Note: The Entity struct layout based on offsets used:
// +0x00: float x, y, z (position)
// +0x18: uint32 flagsAt0x18 (mask 0xC000 for bits 14‑15)
// +0x21: byte byteAt0x21 (bit0 = alive/enabled)