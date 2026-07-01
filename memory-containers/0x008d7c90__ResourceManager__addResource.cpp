// FUNC_NAME: ResourceManager::addResource
void __thiscall ResourceManager::addResource(int this, int resourceType, int resourceIndex, float amount)
{
  int iVar1;
  float *pfVar2;
  
  // +0x44: resource array base, each resource entry is 0x14 bytes
  // Special type 0x637b907 (probably "invalid" or "none")
  if (resourceType != 0x637b907) {
    *(float *)(this + 0x44 + resourceIndex * 0x14) =
         *(float *)(this + 0x44 + resourceIndex * 0x14) + amount;
  }
  
  // Look up resource in a hash table or sorted list
  iVar1 = FUN_008d72e0(&resourceType);
  if ((iVar1 < 0) ||
     (pfVar2 = (float *)(*(int *)(this + 0x38) + 4 + iVar1 * 0x18), pfVar2 == (float *)0x0)) {
    // Not found, create new entry
    pfVar2 = (float *)FUN_008d77e0(&resourceType);
    FUN_008d5e80();
  }
  // Add amount to the resource entry value
  *pfVar2 = amount + *pfVar2;
  
  // +0x94: total resource accumulator
  *(float *)(this + 0x94) = *(float *)(this + 0x94) + amount;
  return;
}