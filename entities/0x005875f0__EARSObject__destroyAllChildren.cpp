// FUNC_NAME: EARSObject::destroyAllChildren
void EARSObject::destroyAllChildren(void)
{
  int iVar1;
  int iVar2;
  undefined4 *this;
  
  iVar2 = this[5]; // +0x14: firstChild
  while (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0xc); // +0x0C: nextSibling
    (**(code **)(*(int *)*this + 4))(iVar2,0); // vtable[1] = destroy
    iVar2 = iVar1;
  }
  if (this[1] != 0) { // +0x04: nextSibling
    (**(code **)(*(int *)*this + 4))(this[1],0); // vtable[1] = destroy
  }
                    /* WARNING: Could not recover jumptable at 0x00587628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)*this + 0xc))(); // vtable[3] = onChildrenDestroyed
  return;
}