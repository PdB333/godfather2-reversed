// FUNC_NAME: releaseResources
void __fastcall releaseResources(int thisObject)
{
  // +0xA04, +0xA08, +0xA0C: first array of resource pointers (size 3)
  if (*(int *)(thisObject + 0xa04) != 0) {
    FUN_004df710();
  }
  if (*(int *)(thisObject + 0xa08) != 0) {
    FUN_004df710();
  }
  if (*(int *)(thisObject + 0xa0c) != 0) {
    FUN_004df710();
  }
  // +0xB6C, +0xB70, +0xB74, +0xB78: second array of resource pointers (size 4)
  if (*(int *)(thisObject + 0xb6c) != 0) {
    FUN_004df710();
  }
  if (*(int *)(thisObject + 0xb70) != 0) {
    FUN_004df710();
  }
  if (*(int *)(thisObject + 0xb74) != 0) {
    FUN_004df710();
  }
  if (*(int *)(thisObject + 0xb78) != 0) {
    FUN_004df710();
  }
  return;
}