// FUNC_NAME: PlayerSM::updateInputFlagsFromVehicle
void __fastcall PlayerSM::updateInputFlagsFromVehicle(int thisPtr)
{
  int iVar1;
  
  *(undefined1 *)(thisPtr + 0x5d) = 0;
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x19 & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x100;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x1a & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x200;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x1b & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x400;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x1b & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x400;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x1e & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x1000;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if (*(int *)(iVar1 + 0x1f5c) < 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x800;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x1c & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x2000;
  }
  if (*(int *)(thisPtr + 0x9c) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(thisPtr + 0x9c) + -0x48;
  }
  if ((*(uint *)(iVar1 + 0x1f5c) >> 0x1d & 1) != 0) {
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x8000;
  }
  return;
}