// FUNC_NAME: DialogLineData::getDialogLineHash
undefined4 __thiscall DialogLineData::getDialogLineHash(int this, undefined4 *outHash)
{
  int internalData;
  int dialogVariant;
  undefined4 resultHash;
  
  internalData = *(int *)(this + 0x18);
  resultHash = 0;
  dialogVariant = FUN_00800b60(); // Returns current dialog variant index (0-based after -1)
  if ((*(uint *)(*(int *)(this + 0x18) + 0x8e0) >> 1 & 1) == 0) { // Bit 1 of flag at +0x8e0: use alternate set?
    switch(dialogVariant + -1) {
    case 0:
      *outHash = *(undefined4 *)(internalData + 0x1dc0); // +0x1dc0: line 0 hash (primary)
      resultHash = 0x86b26309;
      dialogVariant = FUN_00800a90(); // Returns character context pointer
      if ((dialogVariant != 0) && (*(int *)(dialogVariant + 0x334) == 2)) { // Character type check
        *outHash = *(undefined4 *)(internalData + 0x1dd0); // +0x1dd0: special line hash for type 2
        return 0x98540b3d;
      }
      break;
    case 1:
      *outHash = *(undefined4 *)(internalData + 0x1dc8); // +0x1dc8: line 1 hash
      return 0xe66984f3;
    case 2:
      *outHash = *(undefined4 *)(internalData + 0x1dcc); // +0x1dcc: line 2 hash
      return 0x95f5ab4b;
    case 3:
      *outHash = *(undefined4 *)(internalData + 0x1dc4); // +0x1dc4: line 3 hash
      resultHash = 0xfac29dc9;
    }
  }
  else {
    switch(dialogVariant + -1) {
    case 0:
      *outHash = *(undefined4 *)(internalData + 0x1dc0);
      resultHash = 0xf7a12005;
      dialogVariant = FUN_00800a90();
      if ((dialogVariant != 0) && (*(int *)(dialogVariant + 0x334) == 2)) {
        *outHash = *(undefined4 *)(internalData + 0x1dd0);
        return 0x81bc0a39;
      }
      break;
    case 1:
      *outHash = *(undefined4 *)(internalData + 0x1dc8);
      return 0xe30fc8f7;
    case 2:
      *outHash = *(undefined4 *)(internalData + 0x1dcc);
      return 0x1db22d4f;
    case 3:
      *outHash = *(undefined4 *)(internalData + 0x1dc4);
      return 0xf768e1cd;
    }
  }
  return resultHash;
}