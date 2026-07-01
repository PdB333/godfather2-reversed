// FUNC_NAME: Entity::initFromTemplate
void __thiscall Entity::initFromTemplate(undefined4 *this, int templateEntity, byte flags)
{
  int *vtable;
  int somePtr;
  undefined4 templateData;
  
  if (templateEntity == 0) {
    vtable = (int *)0x0;
  }
  else {
    vtable = (int *)FUN_0043b870(DAT_01131018); // Get entity manager singleton
  }
  
  // Store flags in the object's flag field (offset +0x10)
  *(byte *)(this + 4) = *(byte *)(this + 4) | flags;
  
  // Copy template data from offset +0xB90 (likely template data pointer)
  *this = *(undefined4 *)(templateEntity + 0xb90);
  
  // Initialize some counter/index to 0 (offset +0x0C)
  this[3] = 0;
  
  // Call virtual function at vtable+0x34 to get some global state
  somePtr = (**(code **)(*vtable + 0x34))();
  
  // Store value from offset +0x30 of that state (offset +0x08)
  this[2] = *(undefined4 *)(somePtr + 0x30);
  
  // Check if bit 0 of flags is not set, then try to set it
  if ((*(byte *)(this + 4) & 1) == 0) {
    somePtr = FUN_0084daa0(templateEntity, 0x383225a1); // Check if entity has specific component
    if (somePtr != 0) {
      *(byte *)(this + 4) = *(byte *)(this + 4) | 1; // Set bit 0
    }
  }
  
  // Get some data from template and store it (offset +0x04)
  templateData = FUN_0084dba0(templateEntity);
  this[1] = templateData;
  
  return;
}