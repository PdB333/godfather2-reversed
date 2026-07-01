// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(undefined4 *thisObject)

{
  *thisObject = &PTR_FUN_00d8afc4;
  thisObject[3] = &PTR_LAB_00d8afc0;
  if ((*(byte *)(thisObject + 0x17) & 1) != 0) {
    FUN_004086d0(&DAT_012069c4);
    *(ushort *)(thisObject + 0x17) = *(ushort *)(thisObject + 0x17) & 0xfffe;
  }
  thisObject[4] = &PTR_FUN_00d8afb4;
  FUN_004de130();
  thisObject[3] = &PTR_LAB_00d8afbc;
  DAT_0112a67c = 0;
  FUN_004083d0();
  return;
}