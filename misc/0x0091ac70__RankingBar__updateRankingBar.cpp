// FUNC_NAME: RankingBar::updateRankingBar
// Address: 0x0091ac70
// __thiscall
// Reconstructed from Ghidra decompilation.
// Purpose: Updates a ranking bar display based on current rank value and animation parameters.

void __thiscall RankingBar::updateRankingBar(int this, uint updateMode, uint deltaValue)
{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;

  // +0xBC, +0xBD are byte flags, likely start/stop state
  *(undefined1 *)(this + 0xbc) = 0;
  *(undefined1 *)(this + 0xbd) = 0;

  if (deltaValue == 0)
  {
    // Reset: display current position without animation
    // +0xC0 = current position, +0xB4 = offset, +0xF0 = widget handle
    FUN_00918940(*(int *)(this + 0xc0) + *(int *)(this + 0xb4), *(undefined4 *)(this + 0xf0), 0x80);
    // Send Lua event "UpdateRankingText" with binding
    FUN_005a04a0("UpdateRankingText", 0, &DAT_00d8510c, 1, *(undefined4 *)(this + 0xf0));
    return;
  }

  // Non-zero delta means animated update
  FUN_0091a440(DAT_00e54d0c);   // Start animation sequence on manager
  uVar2 = DAT_00e54d24;         // some current max value?
  uVar1 = DAT_00e54d20;

  if ((char)updateMode == '\0')
  {
    // Simple incremental update (no forced animation)
    if (DAT_00e54d24 < DAT_00e54d2c)
    {
      *(int *)(this + 0xc0) = *(int *)(this + 0xc0) + deltaValue;
      DAT_00e54d2c = uVar2;    // store current max as previous max
    }
    if (DAT_00e54d28 < uVar1)
    {
      DAT_00e54d28 = uVar1;
    }
    return;
  }

  // Forced animation update
  iVar3 = FUN_00916c70(DAT_00e54d0c);   // get index from manager (sorted rank index?)
  // +0xA8 is pointer to array of ranking values
  uVar7 = *(uint *)(*(int *)(this + 0xa8) + iVar3 * 4);

  iVar3 = -1;
  if (DAT_00e54d1c == '\0')
  {
    // Normal mode: compute difference between current value and stored previous max
    iVar3 = uVar7 - DAT_00e54d2c;
LAB_0091ad0e:
    if (9 < iVar3)
    {
      // Large difference: animate with random offset
      iVar6 = FUN_009185a0();   // get random number (range size?)
      if (iVar3 < iVar6 + -10)
      {
        *(int *)(this + 0xc0) = iVar3 + -4;         // set start position slightly before target
        *(undefined4 *)(this + 0xb4) = 4;            // small offset
      }
      else
      {
        iVar6 = FUN_009185a0();
        *(int *)(this + 0xc0) = iVar6 + -10;         // random start position
        // Get random range for final offset
        uint local1 = 0;
        uint local2 = 0;
        FUN_00918600(&local1, &local2);
        if ((local2 < uVar7) || (uVar7 < local1))
        {
          *(undefined4 *)(this + 0xb4) = 9;          // clamp offset if out of random range
        }
        else
        {
          *(uint *)(this + 0xb4) = (uint)(iVar3 - (iVar6 + -10)) % 10;  // offset = difference mod 10
        }
      }
      goto LAB_0091adaa;
    }
  }
  else
  {
    // Special mode: use online/network data to adjust rank
    piVar4 = (int *)FUN_00ad8d40();   // get some global object
    if (piVar4 != (int *)0x0)
    {
      piVar4 = (int *)(**(code **)(*piVar4 + 0x48))();
      if (piVar4 != (int *)0x0)
      {
        piVar4 = (int *)(**(code **)(*piVar4 + 0x28))();
        uVar5 = (**(code **)(*piVar4 + 4))();
        iVar3 = FUN_00918700(uVar7, uVar5);   // compute adjusted rank difference
        goto LAB_0091ad0e;
      }
    }
  }

  // Fallback: no animation
  *(undefined4 *)(this + 0xc0) = 0;
  *(int *)(this + 0xb4) = iVar3;

LAB_0091adaa:
  uVar7 = FUN_009185a0();   // get another random value (possible limit)
  if (uVar7 == 0)
  {
    // Random zero => display current text only (no animation)
    FUN_005c4630(*(undefined4 *)(this + 0xf0), 0x80, &DAT_00e337ec);
    FUN_005a04a0("UpdateRankingText", 0, &DAT_00d8510c, 1, *(undefined4 *)(this + 0xf0));
    return;
  }
  iVar3 = *(int *)(this + 0xc0);
  if (uVar7 <= (uint)(*(int *)(this + 0xb4) + iVar3))
  {
    // Clamp offset so final position doesn't exceed random limit
    *(uint *)(this + 0xb4) = (uVar7 - iVar3) + -1;
  }
  // Set animated position and update display
  FUN_00919bb0(iVar3);   // animate from current start position
  FUN_00918940(*(int *)(this + 0xb4) + *(int *)(this + 0xc0), *(undefined4 *)(this + 0xf0), 0x80);
  // Send Lua event
  FUN_005a04a0("UpdateRankingText", 0, &DAT_00d8510c, 1, *(undefined4 *)(this + 0xf0));
  return;
}