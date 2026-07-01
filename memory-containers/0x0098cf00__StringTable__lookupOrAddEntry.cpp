// FUNC_NAME: StringTable::lookupOrAddEntry
void __thiscall StringTable::lookupOrAddEntry(int *this, byte *string)
{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  byte *pbVar6;
  int iVar7;
  undefined4 uVar8;
  byte *pbVar9;
  int *piVar10;
  bool bVar11;
  int aiStack_20 [3];
  code *pcStack_14;
  
  pbVar9 = (byte *)(this + 0x18); // +0x18: current string buffer
  pbVar6 = string;
  do {
    bVar1 = *pbVar6;
    bVar11 = bVar1 < *pbVar9;
    if (bVar1 != *pbVar9) {
LAB_0098cf36:
      iVar7 = (1 - (uint)bVar11) - (uint)(bVar11 != 0);
      goto LAB_0098cf3b;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar6[1];
    bVar11 = bVar1 < pbVar9[1];
    if (bVar1 != pbVar9[1]) goto LAB_0098cf36;
    pbVar6 = pbVar6 + 2;
    pbVar9 = pbVar9 + 2;
  } while (bVar1 != 0);
  iVar7 = 0;
LAB_0098cf3b:
  if (iVar7 != 0) {
    FUN_0098ce00(1); // lock mutex
    iVar7 = FUN_004dafd0(string); // hash string
    piVar10 = (int *)this[0x8c]; // +0x8c: hash table begin
    if (piVar10 != (int *)this[0x8d]) { // +0x8d: hash table end
      while (iVar2 = *piVar10, *(int *)(iVar2 + 0x30) != iVar7) { // +0x30: hash value
        piVar10 = piVar10 + 1;
        if (piVar10 == (int *)this[0x8d]) {
          return;
        }
      }
      if ((iVar2 != 0) && (*string != 0)) {
        (**(code **)*this)(); // vtable call
        (**(code **)(*this + 8))(); // vtable call
        _strncpy((char *)(this + 0x18),(char *)string,0xc0); // copy string to buffer
        iVar7 = FUN_004dafd0(this + 0x18); // hash new string
        this[0x48] = iVar7; // +0x48: hash value
        iVar7 = *(int *)(iVar2 + 0x24); // +0x24: some data
        iVar3 = *(int *)(iVar2 + 0x28); // +0x28: some data
        iVar4 = *(int *)(iVar2 + 0x2c); // +0x2c: some data
        this[0x4c] = *(int *)(iVar2 + 0x20); // +0x20: some data
        this[0x4d] = iVar7;
        this[0x4e] = iVar3;
        this[0x4f] = iVar4;
        __snprintf((char *)(this + 0x50),0xc0,"%s.text",string); // create .text filename
        iVar7 = FUN_009c8e50(0xa4); // allocate memory
        if (iVar7 == 0) {
          iVar7 = 0;
        }
        else {
          uVar8 = FUN_0098bc90(string); // get some ID
          iVar7 = FUN_0098a040(this + 0x18,*(undefined4 *)(iVar2 + 0x38),uVar8); // create object
        }
        this[0x17] = iVar7; // +0x17: store object pointer
        if (*(int *)(iVar2 + 0x3c) != 0) { // +0x3c: some data
          *(int *)(iVar7 + 0x3c) = *(int *)(iVar2 + 0x3c);
        }
        aiStack_20[0] = 0;
        aiStack_20[2] = 0;
        aiStack_20[1] = 0;
        cVar5 = FUN_0098b880(this[0x48],aiStack_20); // load resource
        if (cVar5 != '\0') {
          FUN_0098a150(aiStack_20); // process resource
        }
        if (aiStack_20[0] != 0) {
          (*pcStack_14)(aiStack_20[0]); // callback
        }
      }
    }
  }
  return;
}