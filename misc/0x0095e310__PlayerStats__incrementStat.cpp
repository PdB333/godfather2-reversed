// FUNC_NAME: PlayerStats::incrementStat
undefined1 __thiscall PlayerStats::incrementStat(uint *this, undefined4 statIndex, undefined1 *param_3)
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  
  uVar4 = 0;
  switch(statIndex) {
  case 0: // Kills
    if (this[0] + 1 < DAT_011307ec) { // +0x00 killCount
      this[0] = this[0] + 1;
      return 1;
    }
    break;
  case 1: // Deaths
    if (this[0x1c] + 1 < DAT_01130820) { // +0x70 deathCount
      this[0x1c] = this[0x1c] + 1;
      *param_3 = 1;
      FUN_0095cf50(); // likely onDeath()
      return 1;
    }
    break;
  case 2: // Money earned
    if (this[2] + 1 < DAT_011307fc) { // +0x08 moneyEarned
      this[2] = this[2] + 1;
      uVar1 = FUN_0095c9f0(); // likely getCurrentMoney()
      this[0xd] = uVar1; // +0x34 currentMoney
      return 1;
    }
    break;
  case 3: // Money spent
    iVar2 = FUN_0095ca40(); // likely getMoneySpent()
    uVar1 = this[0xd]; // +0x34 currentMoney
    uVar3 = FUN_0095ca80(); // likely getMaxMoney()
    if (iVar2 + uVar1 <= uVar3) {
      this[0xd] = iVar2 + uVar1; // +0x34 currentMoney
      return 1;
    }
    break;
  case 4: // Missions completed
    if (this[9] + 1 < DAT_01130850) { // +0x24 missionsCompleted
      this[9] = this[9] + 1;
      return 1;
    }
    break;
  case 5: // Side missions completed
    if (this[10] + 1 < DAT_0113082c) { // +0x28 sideMissionsCompleted
      this[10] = this[10] + 1;
      return 1;
    }
    break;
  case 6: // Favor points
    if (this[5] + 1 < DAT_01130808) { // +0x14 favorPoints
      this[5] = this[5] + 1;
      return 1;
    }
    break;
  case 7: // Respect points
    if (this[8] + 1 < DAT_01130814) { // +0x20 respectPoints
      this[8] = this[8] + 1;
      return 1;
    }
    break;
  case 8: // Reset stat
    uVar4 = *(undefined1 *)((int)this + 0x7a); // +0x7A someFlag
    *(undefined1 *)((int)this + 0x7a) = 0;
    break;
  case 9: // Property count
    if (this[7] + 1 < DAT_01130844) { // +0x1C propertyCount
      this[7] = this[7] + 1;
      return 1;
    }
  }
  return uVar4;
}