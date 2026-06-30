// FUNC_NAME: Bignum::subSingleDigit
int Bignum::subSingleDigit(uint *thisBignum, uint singleDigit, uint *outBignum)
{
  int resultLen;
  uint *srcLimb;
  int i;
  uint *dstLimb;

  // +0x00: limbCount (number of 28-bit limbs)
  // +0x04: capacity (allocated limb count)
  // +0x08: flags (0 = positive/normal, 1 = negative? or special state)
  // +0x0C+: limbs[capacity] (each limb masked to 28 bits)

  // Ensure output has enough capacity (input limbCount + 1)
  if ((outBignum[1] < thisBignum[0] + 1) && (resultLen = bignumResize(outBignum, thisBignum[0] + 1), resultLen != 0)) {
    return resultLen;
  }

  // If thisBignum is in a "special" state (flags == 1), route through a different handler
  if (thisBignum[2] != 1) {
    int inLen = thisBignum[0];
    int outOrigLen = outBignum[0];

    srcLimb = (uint *)thisBignum[3];
    dstLimb = (uint *)outBignum[3];

    // Case: input is zero, or input is a single limb <= singleDigit
    if ((inLen == 1 && *srcLimb <= singleDigit) || (inLen == 0)) {
      if (inLen == 1) {
        singleDigit = singleDigit - *srcLimb;  // subtract first limb
      }
      *dstLimb = singleDigit;                 // store result
      i = 1;
      dstLimb = dstLimb + 1;
      outBignum[2] = 1;                        // mark result as normalized/single-digit
      outBignum[0] = 1;                        // result has 1 limb
    }
    else {
      // Case: input has limbs, first limb > singleDigit  →  subtract with borrow propagation
      outBignum[2] = 0;                        // clear normalization flag
      outBignum[0] = thisBignum[0];            // copy limb count from input
      singleDigit = *srcLimb - singleDigit;    // borrow from first limb
      *dstLimb = singleDigit & 0x0FFFFFFF;     // store masked 28-bit result
      i = 1;
      dstLimb = dstLimb + 1;

      // Propagate borrow across remaining limbs
      if (1 < thisBignum[0]) {
        do {
          srcLimb = srcLimb + 1;
          singleDigit = *srcLimb + ((int)singleDigit >> 0x1f);  // add sign-extended borrow
          *dstLimb = singleDigit & 0x0FFFFFFF;
          i = i + 1;
          dstLimb = dstLimb + 1;
        } while (i < thisBignum[0]);
      }
    }

    // Zero out any remaining higher limbs in the output
    if (i < outOrigLen) {
      for (int origLen = outOrigLen - i; origLen != 0; origLen = origLen - 1) {
        *dstLimb = 0;
        dstLimb = dstLimb + 1;
      }
    }

    bignumNormalize();
    return 0;
  }

  // Special case: thisBignum has flag == 1 (negative? or other representation)
  thisBignum[2] = 0;
  resultLen = bignumSubGeneric(thisBignum, singleDigit, outBignum);
  outBignum[2] = 1;
  thisBignum[2] = 1;
  return resultLen;
}