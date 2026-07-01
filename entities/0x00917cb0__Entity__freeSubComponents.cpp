// FUNC_NAME: Entity::freeSubComponents
void __fastcall Entity::freeSubComponents(int thisPtr)

{
  if (*(int *)(thisPtr + 0x70) != 0) {
    FUN_009c8f10(*(int *)(thisPtr + 0x70)); // likely Component::release or delete
  }
  if (*(int *)(thisPtr + 0x64) != 0) { // originally 100 decimal, correct to 0x64
    FUN_009c8f10(*(int *)(thisPtr + 0x64));
  }
  if (*(int *)(thisPtr + 0x58) != 0) {
    FUN_009c8f10(*(int *)(thisPtr + 0x58));
  }
  if (*(int *)(thisPtr + 0x4c) != 0) {
    FUN_009c8f10(*(int *)(thisPtr + 0x4c));
  }
  FUN_005c16e0(); // likely Entity::clearComponentList or similar base cleanup
  return;
}