// FUNC_NAME: PlayerActionableInfo::deserializeFromBitStream
void __thiscall PlayerActionableInfo::deserializeFromBitStream(int this, undefined4 bitStream)
{
  char hasMoreData;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  undefined4 uVar5;
  
  FUN_0046f160(bitStream); // BitStream::readBegin
  FUN_0043aff0(bitStream,0x6f1d0554); // BitStream::readClassId
  hasMoreData = FUN_0043b120(); // BitStream::readBool (has more data?)
  while (hasMoreData == '\0') {
    FUN_0043b210(); // BitStream::readInt (field type?)
    uVar2 = FUN_0043ab70(); // BitStream::readEnum (action type?)
    switch(uVar2) {
    case 0: // ACTION_TYPE_0
      iVar4 = FUN_0043b210(); // BitStream::readInt
      *(undefined4 *)(this + 0x184) = *(undefined4 *)(iVar4 + 8); // +0x184 = some int field
      break;
    case 0xe: // ACTION_TYPE_14
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 400) = *(undefined4 *)(iVar4 + 8); // +0x190 = another int field
      break;
    case 0xf: // ACTION_TYPE_15
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x194) = *(undefined4 *)(iVar4 + 8); // +0x194 = int field
      break;
    case 0x11: // ACTION_TYPE_17
    case 0x12: // ACTION_TYPE_18
    case 0x13: // ACTION_TYPE_19
    case 0x14: // ACTION_TYPE_20
      FUN_0043b210(); // readInt (skip?)
      piVar3 = (int *)FUN_0043abc0(); // BitStream::readVec3
      if ((((*piVar3 != 0) || (piVar3[1] != 0)) || (piVar3[2] != 0)) || (piVar3[3] != 0)) {
        uVar2 = *(undefined4 *)(this + 0x1c); // +0x1c = some object pointer
        uVar5 = extraout_ECX;
        FUN_00401f40(piVar3); // Vector3::normalize?
        hasMoreData = FUN_006aee40(uVar2,uVar5); // some validation function
        if (hasMoreData == '\0') {
          uVar2 = FUN_0043ab10(); // BitStream::readFloat
          FUN_006b6c10(piVar3,uVar2); // apply force/velocity?
        }
      }
      break;
    case 0x15: // ACTION_TYPE_21
      FUN_0043b210();
      uVar2 = FUN_0043ab90(); // BitStream::readString
      FUN_004089b0(this + 0x244,uVar2); // +0x244 = String field
      break;
    case 0x16: // ACTION_TYPE_22
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x24c,uVar2); // +0x24c = String field
      break;
    case 0x17: // ACTION_TYPE_23
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x23c,uVar2); // +0x23c = String field
      break;
    case 0x18: // ACTION_TYPE_24
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x25c,uVar2); // +0x25c = String field
      break;
    case 0x19: // ACTION_TYPE_25
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x254,uVar2); // +0x254 = String field (different copy?)
      break;
    case 0x1a: // ACTION_TYPE_26
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x2ac,uVar2); // +0x2ac = String field
      break;
    case 0x1b: // ACTION_TYPE_27
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x26c,uVar2); // +0x26c = String field
      break;
    case 0x1c: // ACTION_TYPE_28
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x274,uVar2); // +0x274 = String field
      break;
    case 0x1d: // ACTION_TYPE_29
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x27c,uVar2); // +0x27c = String field
      break;
    case 0x1e: // ACTION_TYPE_30
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x284,uVar2); // +0x284 = String field
      break;
    case 0x1f: // ACTION_TYPE_31
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x28c,uVar2); // +0x28c = String field
      break;
    case 0x20: // ACTION_TYPE_32
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x294,uVar2); // +0x294 = String field
      break;
    case 0x21: // ACTION_TYPE_33
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x29c,uVar2); // +0x29c = String field
      break;
    case 0x22: // ACTION_TYPE_34
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x2a4,uVar2); // +0x2a4 = String field
      break;
    case 0x23: // ACTION_TYPE_35
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x264) = *(undefined4 *)(iVar4 + 8); // +0x264 = int field
      break;
    case 0x24: // ACTION_TYPE_36
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x268) = *(undefined4 *)(iVar4 + 8); // +0x268 = int field
      break;
    case 0x25: // ACTION_TYPE_37
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x1d8) = *(undefined4 *)(iVar4 + 8); // +0x1d8 = int field
      break;
    case 0x26: // ACTION_TYPE_38
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x1dc,uVar2); // +0x1dc = String field
    }
    FUN_0043b1a0(); // BitStream::readEnd
    hasMoreData = FUN_0043b120(); // BitStream::readBool
  }
  return;
}