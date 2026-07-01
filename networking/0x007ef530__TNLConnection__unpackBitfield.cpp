// FUNC_NAME: TNLConnection::unpackBitfield
void __thiscall TNLConnection::unpackBitfield(int this, ushort *bitfieldData)
{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  
  iVar3 = 0;
  if (*bitfieldData != 0) {
    iVar1 = *(int *)(this + 4); // +0x04: pointer to bitfield definitions or mask table
    puVar2 = bitfieldData + 0x16; // +0x2C: start of packed bitfield values after header
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)puVar2 = *(undefined4 *)((iVar1 - (int)bitfieldData) + (int)puVar2);
      puVar2 = puVar2 + 2;
    } while (iVar3 < (int)(uint)*bitfieldData);
  }
  return;
}