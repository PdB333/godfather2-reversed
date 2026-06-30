// FUNC_NAME: PacketReader::readHeader
uint __thiscall PacketReader::readHeader(PacketReader *this)
{
  int *pHeader;
  int *pEnd;
  uint uRoundedValue;
  int iConvResult;
  float fClippedZ;
  float fZ;
  long long lTemp;
  float fY;
  float fX;
  float fZ2;

  // pEnd points to end of buffer (from this+0x8)
  pEnd = *(int **)(this + 8);
  // pHeader is the current header pointer (from this+0xc)
  pHeader = *(int **)(this + 0xc);

  // Validate first field of header
  if (pEnd <= pHeader || pHeader == (int *)0x0)
    return 0;
  if (*pHeader != 3 && *pHeader != 4) {
    iConvResult = FUN_00636850(&lTemp);
    if (iConvResult == 0)
      return 0;
  }

  // Validate second field (offset +8 from pHeader)
  pHeader = (int *)(*(int *)(this + 0xc) + 8);
  if (pEnd <= pHeader || pHeader == (int *)0x0)
    return 0;
  if (*pHeader != 3 && *pHeader != 4) {
    iConvResult = FUN_00636850(&lTemp);
    if (iConvResult == 0)
      return 0;
  }

  // Validate third field (offset +16 from pHeader)
  pHeader = (int *)(*(int *)(this + 0xc) + 0x10);
  if (pEnd <= pHeader || pHeader == (int *)0x0)
    return 0;
  if (*pHeader != 3 && *pHeader != 4) {
    iConvResult = FUN_00636850(&lTemp);
    if (iConvResult == 0)
      return 0;
  }

  // Read three float values via index (1,2,3)
  fX = (float)FUN_006259b0(this, 1);
  lTemp = (longlong)ROUND(fX);
  uRoundedValue = (uint)lTemp;

  fY = (float)FUN_006259b0(this, 2);   // stored as lower half of lTemp? Actually decompiled had CONCAT44, but simplified
  fZ = (float)FUN_006259b0(this, 3);

  // Clip z value to [0, DAT_00e2b050] if positive
  if ((float10)0.0 < (float10)fZ) {
    fClippedZ = DAT_00e2b050;
    if (fZ < DAT_00e2b050)
      fClippedZ = fZ;
  } else {
    fClippedZ = 0.0;
  }
  fZ2 = fClippedZ;

  // If rounded X is less than 2, trigger some action
  if (uRoundedValue < 2) {
    FUN_004584f0(uRoundedValue, fZ2);
  }
  return 0;
}