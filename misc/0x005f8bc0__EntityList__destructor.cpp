// FUNC_NAME: EntityList::destructor
void __fastcall EntityList::~EntityList(EntityList *this)

{
  int iVar1;
  Entity **ppEntity;
  int iVar2;
  Entity **ppEntity_00;
  Entity **ppEntity_01;
  void **ppvVar2;
  void **ppvVar3;
  
  this->vftable = (VFTABLE *)&PTR_FUN_00e407e4;
  EntityList::sub_FUN_005f8c90();
  iVar1 = this->field_0x30; // +0x30: number of entities
  if (0 < iVar1) {
    while (iVar1 = iVar1 + -1, -1 < iVar1) {
      ppEntity = *(Entity ***)(this->field_0x2c + iVar1 * 4); // +0x2c: entity pointer array
      if (ppEntity != (Entity **)0x0) {
        iVar2 = *ppEntity;
        if (iVar2 != 0) {
          ppEntity_00 = *(Entity ***)(iVar2 + 4); // next pointer in linked list
          if (ppEntity_00 == ppEntity) {
            *(Entity **)(iVar2 + 4) = ppEntity[1]; // unlink head
          }
          else {
            ppEntity_01 = (Entity **)ppEntity_00[1];
            while (ppEntity_01 != ppEntity) {
              ppEntity_00 = (Entity **)ppEntity_00[1];
              ppEntity_01 = (Entity **)ppEntity_00[1];
            }
            ppEntity_00[1] = ppEntity[1]; // unlink from middle
          }
        }
        operatorDelete(ppEntity); // delete entity
      }
    }
  }
  if (this->field_0x2c != 0) {
    operatorDeleteArray(this->field_0x2c); // free array
  }
  iVar1 = this->field_0x24; // +0x24: linked list pointer
  if (iVar1 != 0) {
    ppvVar2 = *(void ***)(iVar1 + 4); // first node
    if (ppvVar2 == this + 0x24) { // check if self-referencing
      *(void **)(iVar1 + 4) = this->field_0x28; // skip self
    }
    else {
      ppvVar3 = (void **)ppvVar2[1];
      while (ppvVar3 != this + 0x24) {
        ppvVar2 = (void **)ppvVar2[1];
        ppvVar3 = (void **)ppvVar2[1];
      }
      ppvVar2[1] = this->field_0x28; // unlink from list
    }
  }
  this->vftable = (VFTABLE *)&PTR_FUN_00e32808; // base vftable
  ppvVar2 = this->field_0x04; // +0x04: array of pointers
  while (ppvVar2 != (void **)0x0) {
    ppvVar3 = (void **)ppvVar2[1]; // next pointer
    ppvVar2[1] = 0; // clear next
    *ppvVar2 = 0; // clear data
    ppvVar2 = ppvVar3;
  }
  return;
}