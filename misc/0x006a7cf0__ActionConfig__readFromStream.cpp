// FUNC_NAME: ActionConfig::readFromStream
void __thiscall ActionConfig::readFromStream(ActionConfig* this, Stream* stream)
{
  int iVar1;
  bool hasMoreData;
  int actionType;
  int* slotPtr;
  int actionArray[26];
  
  stream = stream;
  FUN_0043b540(stream);
  FUN_0043aff0(stream, 0xc5bdda89);
  
  hasMoreData = FUN_0043b120();
  while (hasMoreData == false) {
    FUN_0043b210();
    actionType = FUN_0043ab70();
    switch(actionType) {
    case 0:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar4 + 8);
      break;
    case 1:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(iVar4 + 8);
      break;
    case 2:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x74) = *(undefined4 *)(iVar4 + 8);
      break;
    case 3:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x54) = *(undefined4 *)(iVar4 + 8);
      break;
    case 4:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x78) = *(undefined4 *)(iVar4 + 8);
      break;
    case 5:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x58) = *(undefined4 *)(iVar4 + 8);
      break;
    case 6:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x7c) = *(undefined4 *)(iVar4 + 8);
      break;
    case 7:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x5c) = *(undefined4 *)(iVar4 + 8);
      break;
    case 8:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar4 + 8);
      break;
    case 9:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x60) = *(undefined4 *)(iVar4 + 8);
      break;
    case 10:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x84) = *(undefined4 *)(iVar4 + 8);
      break;
    case 0xb:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x64) = *(undefined4 *)(iVar4 + 8);
      break;
    case 0xc:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x88) = *(undefined4 *)(iVar4 + 8);
      break;
    case 0xd:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x68) = *(undefined4 *)(iVar4 + 8);
      break;
    case 0xe:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x8c) = *(undefined4 *)(iVar4 + 8);
      break;
    case 0xf:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x6c) = *(undefined4 *)(iVar4 + 8);
    }
    FUN_0043b1a0();
    hasMoreData = FUN_0043b120();
  }
  
  // Now process the 8 slot assignments
  // Pair each "binding" at +0x70..+0x8c with its "actionID" at +0x50..+0x6c
  slotPtr = (int*)(this + 0x70);  // start of bindings array
  iVar4 = 8;
  do {
    int binding = *slotPtr;
    if (binding != 0) {
      int actionID = slotPtr[-8];  // slotPtr[-8] corresponds to +0x50, +0x54, etc.
      FUN_006a78f0(actionArray, &binding);
      *(int*)(actionArray[0] + 4) = actionID;
    }
    slotPtr = slotPtr + 1;
    iVar4 = iVar4 - 1;
  } while (iVar4 != 0);
  
  return;
}