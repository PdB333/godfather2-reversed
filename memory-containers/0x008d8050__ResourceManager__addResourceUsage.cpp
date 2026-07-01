// FUNC_NAME: ResourceManager::addResourceUsage
void __thiscall ResourceManager::addResourceUsage(int thisPtr, int resourceId, int usageSlot)
{
  float fVar1;
  int *piVar2;
  int iVar3;
  float *pfVar4;
  
  iVar3 = resourceId;
  piVar2 = (int *)FUN_008d7dc0(resourceId,1);  // getResourceData(resourceId, 1)
  *piVar2 = *piVar2 + 1;  // increment reference count
  fVar1 = (float)piVar2[4];  // get resource size (float at +0x10)
  
  if (iVar3 != 0x637b907) {  // special resource ID check (probably "null" or "empty")
    // Add to per-slot usage at thisPtr + 0x44 + usageSlot * 0x14
    *(float *)(thisPtr + 0x44 + usageSlot * 0x14) =
         *(float *)(thisPtr + 0x44 + usageSlot * 0x14) + fVar1;
  }
  
  resourceId = iVar3;
  iVar3 = FUN_008d72e0(&resourceId);  // findResourceInTable(&resourceId)
  
  if ((iVar3 < 0) ||
     (pfVar4 = (float *)(*(int *)(thisPtr + 0x38) + 4 + iVar3 * 0x18), pfVar4 == (float *)0x0)) {
    // Resource not found in table, allocate new entry
    pfVar4 = (float *)FUN_008d77e0(&resourceId);  // allocateResourceEntry(&resourceId)
    FUN_008d5e80();  // initializeResourceEntry()
  }
  
  *pfVar4 = *pfVar4 + fVar1;  // add to total resource usage in table entry
  *(float *)(thisPtr + 0x94) = *(float *)(thisPtr + 0x94) + fVar1;  // add to total resource usage (thisPtr + 0x94)
  return;
}