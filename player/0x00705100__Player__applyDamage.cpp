// FUNC_NAME: Player::applyDamage
void __thiscall Player::applyDamage(Player *this, DamageInfo *damageInfo, Entity *target, HitResult *hitResult)
{
    DamageComponent *damageComponent;
    int healthState;
    
    if ((((target != (Entity *)0x0) && (damageInfo != (DamageInfo *)0x0)) && (hitResult != (HitResult *)0x0)) && 
        (damageComponent = this->m_pDamageComponent, damageComponent != (DamageComponent *)0x0)) {
        healthState = damageComponent->field_0x74c; // +0x74c: current health or state
        if (((healthState != 0) && (healthState != 0x48)) && ((healthState - 0x48) == (int)damageInfo)) {
            // If health state is between 0x48 and something, call virtual function on damage component
            (damageComponent->vtable[150])(target); // vtable offset 600 bytes = index 150, likely OnReceiveDamage
        }
        damageInfo->flags &= 0xfffffffd; // Clear bit 1 (maybe "isCritical" flag)
        damageInfo->applyDamageToHealth(); // FUN_004088c0(damageInfo + 0x3c)
        target->takeDamageEffect(damageInfo); // FUN_00704ca0(target)
        if (hitResult->someCount < 2) { // hitResult +0x10
            hitResult->outcome = hitResult->someCount; // +0xc
        }
        else {
            hitResult->outcome = 1;
        }
        target->playHitAnimation(damageInfo); // FUN_00704590(target)
        // Condition to call cleanup: if healthState is 0 or 0x48, or target mismatch, or bit test fails
        if (((healthState == 0) || (healthState == 0x48)) ||
           (((healthState - 0x48) != (int)target) || ((damageComponent->field_0x8e0 >> 10 & 1) == 0))) {
            FUN_00707610();
        }
        FUN_00707ea0();
    }
    return;
}