// FUNC_NAME: Player::updateStaminaOrCooldown
void __fastcall Player::updateStaminaOrCooldown(int this)
{
  if (*(char *)(this + 0xa20) != '\0') {
    if ((*(int *)(this + 0xa1c) < 1) &&
       (*(undefined1 *)(this + 0xa20) = 0, (*(uint *)(this + 0xc88) >> 2 & 1) == 0)) {
      // +0xa20: active flag (bool), +0xa1c: timer/counter, +0xc88: bitfield flags
      // When timer expires and certain flag bit is not set, trigger cooldown reset
      FUN_00544ae0(2);  // likely setCooldown or resetAbility
      FUN_00544b90(1);  // likely playSound or showUI
    }
    *(int *)(this + 0xa1c) = *(int *)(this + 0xa1c) + -1;  // decrement timer
  }
  return;
}