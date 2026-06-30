// FUNC_NAME: Sentient::findExistingBodyPartOrCreate
int __fastcall Sentient::findExistingBodyPartOrCreate(undefined4 param_1, int bodyPartType)
{
  int iVar1;
  ushort existingPartIndex;
  int unaff_ESI;
  
  // +0x90: current body part count? +0x3c: max body parts? 
  // Calculate index of an existing body part of the same type
  existingPartIndex = (*(short *)(unaff_ESI + 0x90) - *(short *)(unaff_ESI + 0x3c)) + (short)bodyPartType;
  iVar1 = 0;
  
  // Check if index is valid (not -1) and slot is empty
  if ((existingPartIndex != 0xffff) && 
      (iVar1 = *(int *)(bodyPartType * 8 + *(int *)(unaff_ESI + 0x38)), iVar1 == 0))
  {
    // +0x8c: pointer to body part type index array
    iVar1 = FUN_005fafc0(*(undefined4 *)(*(int *)(unaff_ESI + 0x8c) + (uint)existingPartIndex * 4));
    if (iVar1 != 0) {
      FUN_005fa490(iVar1); // Casting or finalizing the new body part
    }
  }
  return iVar1;
}