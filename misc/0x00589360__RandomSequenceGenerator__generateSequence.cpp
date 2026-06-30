// FUNC_NAME: RandomSequenceGenerator::generateSequence
void __thiscall RandomSequenceGenerator::generateSequence(int *outputArray, int startIndex, int endIndex)
{
  int iVar2; // counter at this+0x0C
  uint uVar1; // random bits (2-bit)
  int *thisPtr = this; // unaff_ESI

  iVar2 = thisPtr[3]; // m_counter
  // fast-forward loop: advance state without generating output
  while (iVar2 < startIndex) {
    iVar2 = thisPtr[3];
    // extract 2 random bits from current 64-bit state (low at this[0], high at this[1])
    uVar1 = __aullshr(); // shift 64-bit state right by 62, mask 3
    if ((uVar1 & 3) - 1 < 3) {
      thisPtr[0] += 1; // m_stateLow
    } else {
      thisPtr[0] += 3; // m_stateLow
    }
    thisPtr[1] += 6; // m_stateHigh
    iVar2 = iVar2 + 1;
    thisPtr[3] = iVar2;
  }

  // main generation loop
  do {
    if (endIndex <= iVar2) {
      return;
    }
    uVar1 = __aullshr();
    uVar1 = uVar1 & 3;
    if (uVar1 == 1) {
      FUN_005925a0(thisPtr[0]); // generate type 1 using current stateLow
LAB_0058942d:
      thisPtr[0] += 1; // m_stateLow
    }
    else {
      if (uVar1 == 2) {
        FUN_00592480(thisPtr[0]); // generate type 2
        goto LAB_0058942d;
      }
      if (uVar1 == 3) {
        FUN_00592510(thisPtr[0]); // generate type 3
        goto LAB_0058942d;
      }
      // uVar1 == 0
      FUN_00592630(outputArray); // generate type 0 (uses outputArray pointer?)
      thisPtr[0] += 3; // m_stateLow
    }
    thisPtr[1] += 6; // m_stateHigh
    thisPtr[3] += 1; // m_counter
    outputArray += 4; // advance by 16 bytes (4 ints)
    iVar2 = thisPtr[3];
  } while( true );
}