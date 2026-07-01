// FUNC_NAME: PS3TextureResourceFile::readChunkData
void __thiscall readChunkData(int this, undefined4 param_2) // this = PS3TextureResourceFile, param_2 = archiveFile maybe
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  // Start chunk reading with magic
  FUN_0043aff0(param_2, 0xb390b11a); // startChunk
  FUN_0043af00(1); // setEndian(1) - big endian
  cVar1 = FUN_0043b120(); // isChunkEmpty
  if (cVar1 == '\0') {
    iVar3 = this + 0x60; // +0x60: headerSize
    FUN_0043b210(iVar3); // readBasicType
    FUN_0043ad90(iVar3); // swapEndian
  }
  // End chunk
  FUN_0043aff0(param_2, 0x30aa423a); // endChunk
  cVar1 = FUN_0043b120(); // isChunkEmpty
  do {
    if (cVar1 != '\0') {
      // Texture dimension check - if not already set, save dimensions from this
      if ((((*(int *)(this + 0x50) == 2) && (DAT_0112dacc == 0)) && (DAT_0112dad0 == 0)) &&
         ((DAT_0112dad4 == 0 && (DAT_0112dad8 == 0)))) {
        DAT_0112dacc = *(int *)(this + 0x20); // +0x20: width
        DAT_0112dad0 = *(int *)(this + 0x24); // +0x24: height
        DAT_0112dad4 = *(int *)(this + 0x28); // +0x28: depth
        DAT_0112dad8 = *(int *)(this + 0x2c); // +0x2c: mipmaps
      }
      // If dimensions match, copy data
      if (((DAT_0112dacc == *(int *)(this + 0x20)) && (DAT_0112dad0 == *(int *)(this + 0x24)))
         && ((DAT_0112dad4 == *(int *)(this + 0x28) &&
             ((DAT_0112dad8 == *(int *)(this + 0x2c) && (DAT_0120e93c != 0)))))) {
        FUN_00408900(this + 0x3c, &DAT_0120e93c, 0x8000); // copyTextureData
      }
      return;
    }
    FUN_0043b210(); // readChunkType
    uVar2 = FUN_0043ab70(); // getChunkType
    switch(uVar2) {
    case 0: // HEADER chunk
      iVar3 = FUN_0043b210(); // readChunkType
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(iVar3 + 8); // +0x50: format
      break;
    case 1: // DATA chunk
      FUN_0043b210(); // readChunkType
      uVar2 = FUN_0043ab90(); // getChunkSize
      FUN_00408980(this + 0xa0, uVar2); // allocateTextureData
      break;
    case 2: // MIP chunk
      iVar3 = FUN_0043b210(); // readChunkType
      *(undefined4 *)(this + 0xa8) = *(undefined4 *)(iVar3 + 8); // +0xa8: mipCount
      break;
    case 3: // PALETTE chunk
      iVar3 = this + 0xb0; // +0xb0: paletteData
      goto LAB_00811680;
    case 4: // UNKNOWN chunk 4
      iVar3 = this + 0xc0; // +0xc0: extraData1
      FUN_0043b210(iVar3); // readChunkType
      FUN_0043ad10(iVar3); // swapEndian
      break;
    case 5: // UNKNOWN chunk 5
      iVar3 = this + 0xd0; // +0xd0: extraData2
      FUN_0043b210(iVar3); // readChunkType
      FUN_0043ad10(iVar3); // swapEndian
      break;
    case 6: // PALETTE/EXTRA chunk
      iVar3 = this + 0xe0; // +0xe0: moreExtraData
LAB_00811680:
      FUN_0043b210(iVar3); // readChunkType
      FUN_0043ad10(iVar3); // swapEndian
      break;
    case 7: // FLAGS chunk
      iVar3 = FUN_0043b210(); // readChunkType
      *(uint *)(this + 0xac) = *(uint *)(this + 0xac) | *(uint *)(iVar3 + 8); // +0xac: flags OR combine
    }
    FUN_0043b1a0(); // nextChunk
    cVar1 = FUN_0043b120(); // isChunkEmpty
  } while( true );
}