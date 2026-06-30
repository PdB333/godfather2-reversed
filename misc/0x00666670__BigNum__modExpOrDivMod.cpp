// FUNC_NAME: BigNum::modExpOrDivMod
int BigNum::modExpOrDivMod(int *this, uint divisor, int quotientOut, uint *remainderOut)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  undefined8 uVar6;
  int bitIndex;
  int quotient;
  int remainder;
  int local_4;
  
  if (divisor == 0) {
    return -3;
  }
  if ((divisor == 1) || (*this == 0)) {
    if (remainderOut != (uint *)0x0) {
      *remainderOut = 0;
    }
    if (quotientOut != 0) {
      iVar1 = FUN_00665ce0(); // copyBigNum
      return iVar1;
    }
  }
  else {
    iVar1 = FUN_00666640(&bitIndex); // getHighestBitIndex
    if (iVar1 == 1) {
      if (remainderOut != (uint *)0x0) {
        *remainderOut = (1 << ((byte)bitIndex & 0x1f)) - 1U & *(uint *)this[3]; // mask remainder
      }
      if (quotientOut != 0) {
        iVar1 = FUN_00666300(this,bitIndex,quotientOut,0); // shiftRight
        return iVar1;
      }
    }
    else {
      if (divisor == 3) {
        iVar1 = FUN_006664b0(this,quotientOut,remainderOut); // divBy3
        return iVar1;
      }
      iVar1 = FUN_006678c0(); // checkSmallDivisor
      if (iVar1 != 0) {
        return iVar1;
      }
      quotient = *this; // number of limbs
      remainder = this[2]; // remainder accumulator
      uVar4 = 0;
      iVar1 = 0;
      bitIndex = quotient;
      while (bitIndex = bitIndex + -1, -1 < bitIndex) {
        uVar3 = iVar1 << 0x1c | uVar4 >> 4;
        uVar4 = *(uint *)(this[3] + bitIndex * 4) | uVar4 << 0x1c;
        if ((uVar3 == 0) && (uVar4 < divisor)) {
          uVar2 = 0;
          iVar1 = 0;
        }
        else {
          uVar2 = __aulldiv(uVar4,uVar3,divisor,0);
          uVar6 = __allmul(uVar2,0,divisor,0);
          bVar5 = uVar4 < (uint)uVar6;
          uVar4 = uVar4 - (uint)uVar6;
          iVar1 = (uVar3 - (int)((ulonglong)uVar6 >> 0x20)) - (uint)bVar5;
        }
        *(undefined4 *)(local_4 + bitIndex * 4) = uVar2;
      }
      if (remainderOut != (uint *)0x0) {
        *remainderOut = uVar4;
      }
      if (quotientOut != 0) {
        FUN_00665b10(); // normalizeQuotient
        FUN_00666970(); // copyQuotient
      }
      FUN_00665b40(); // freeTemp
    }
  }
  return 0;
}