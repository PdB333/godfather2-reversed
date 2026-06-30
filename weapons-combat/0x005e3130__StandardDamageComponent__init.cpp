// FUNC_NAME: StandardDamageComponent::init
void __thiscall StandardDamageComponent::init(StandardDamageComponent* this)
{
    // Global data pointers (likely default string constants)
    // DAT_00e2b04c -> gEmptyStringA
    // DAT_00e2b1a4 -> gDefaultName
    // DAT_00e2b050 -> gEmptyStringB
    unsigned int uVar1 = gEmptyStringA;   // DAT_00e2b04c
    unsigned int uVar2 = gDefaultName;    // DAT_00e2b1a4

    // +0x00: damageFlags (dword)
    this->damageFlags = 0;
    // +0x04: penetrationType (byte)
    *(unsigned char*)((int)&this->damageFlags + 4) = 0;
    // +0x05: hitFeedbackType (byte)
    *(unsigned char*)((int)&this->damageFlags + 5) = 0;

    // +0x5C: lastAttackerID (dword)
    this->lastAttackerID = 0;
    // +0x60: lastDamageTick (dword)
    this->lastDamageTick = 0;
    // +0x64: lastAttackerHandle (dword, -1 = none)
    this->lastAttackerHandle = -1;

    // +0x0C: baseDamage (dword)
    this->baseDamage = 0;
    // +0x10: damageMultiplier (dword)
    this->damageMultiplier = 0;
    // +0x08: armorPiercing (dword, 1 = yes)
    this->armorPiercing = 1;

    // +0x14: isExplosive (byte)
    *(unsigned char*)((int)&this->damageFlags + 0x14) = 0; // offset 20

    // +0x30: damageTypeString (pointer to string)
    this->damageTypeString = (const char*)uVar1;
    // +0x3C: damageSource (dword)
    this->damageSource = 0;
    // +0x28: damageElement (byte)
    *(unsigned char*)((int)&this->damageFlags + 0x28) = 0; // offset 40

    // +0x2C: weaponName (pointer to string)
    this->weaponName = (const char*)uVar2;
    // +0x29: damageChannel (byte)
    *(unsigned char*)((int)&this->damageFlags + 0x29) = 0; // offset 41

    // +0x34: statusEffectString (pointer to string)
    this->statusEffectString = (const char*)uVar1;
    // +0x38: statusEffectDuration (dword)
    this->statusEffectDuration = 0;

    // +0x40: knockbackForce (dword)
    this->knockbackForce = 0;
    // +0x44: knockbackAngle (dword)
    this->knockbackAngle = 0;

    // +0x48: impactEffectName (pointer to string)
    this->impactEffectName = (const char*)uVar2;
    // +0x4C: hitReactionName (pointer to string)
    this->hitReactionName = (const char*)uVar2;
    // +0x50: deathAnimationName (pointer to string)
    this->deathAnimationName = (const char*)uVar2;

    // +0x54: healthPercent (dword, 100 = max)
    this->healthPercent = 100;
    // +0x58: damageOverTime (dword)
    this->damageOverTime = 0;

    // +0x68: damageOverTimeDuration (dword)
    this->damageOverTimeDuration = 0;

    return;
}