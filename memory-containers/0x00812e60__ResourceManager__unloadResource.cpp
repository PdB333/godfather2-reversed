// FUNC_NAME: ResourceManager::unloadResource
void __thiscall ResourceManager::unloadResource(int this, int resourceId)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  
  uVar4 = 0;
  if (*(int *)(this + 0x14) != 0) { // +0x14: resourceCount
    iVar6 = 0;
    do {
      piVar5 = (int *)(*(int *)(this + 0x10) + iVar6); // +0x10: resourceList (array of 0x10 byte entries)
      if (*piVar5 == resourceId) { // Check resource ID at offset 0x0 of entry
        iVar1 = ResourceEntry::hasReferences(piVar5[1]); // +0x4: referenceCount
        if (iVar1 == 0) {
          ResourceManager::destroyResource(uVar4); // Remove from internal tracking
          iVar6 = iVar6 + -0x10;
          uVar4 = uVar4 - 1;
          uVar2 = ResourceEntry::getResourceData(piVar5[3]); // +0xC: resourceData pointer
          uVar7 = 0;
          if (*(uint *)(this + 0x14) != 0) {
            piVar3 = (int *)(*(int *)(this + 0x10) + 0xc); // Check resource data pointers
            do {
              if (*piVar3 == piVar5[3]) goto LAB_00812eff; // Data still used elsewhere
              uVar7 = uVar7 + 1;
              piVar3 = piVar3 + 4;
            } while (uVar7 < *(uint *)(this + 0x14));
          }
          MemoryManager::deallocate(uVar2, 8, this); // Free the resource data
        }
        else {
          *piVar5 = 0; // Just invalidate the entry if still referenced
        }
      }
LAB_00812eff:
      uVar4 = uVar4 + 1;
      iVar6 = iVar6 + 0x10;
    } while (uVar4 < *(uint *)(this + 0x14));
  }
  return;
}