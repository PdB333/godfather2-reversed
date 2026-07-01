// FUNC_NAME: SimulationObject::initializeFromDefinition
undefined4 __thiscall SimulationObject::initializeFromDefinition(int *this, int *definition, int param_3)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  cVar3 = (**(code **)(*this + 0x14))(definition);
  if (cVar3 == '\0') {
    return 0;
  }
  bVar2 = true;
  piVar4 = (int *)SimulationObject::findOrCreateType(definition); // FUN_0082dbf0
  if (piVar4 == (int *)0x0) {
    bVar2 = false;
    puVar5 = (undefined4 *)Engine::getAllocator(); // FUN_009c8f80
    piVar4 = (int *)(**(code **)*puVar5)(0x60,&stack0xfffffff0);
    if (piVar4 == (int *)0x0) {
      return 0;
    }
    SimulationObjectType::constructor(); // FUN_008334a0
    *piVar4 = (int)&SimulationObjectType_vtable; // VTable at 0x00d73688
    SimulationObjectType::registerType(); // FUN_009d3650
  }
  piVar4[7] = *definition;           // +0x1C - typeId
  piVar4[8] = definition[1];         // +0x20 - field_1
  piVar4[9] = definition[2];         // +0x24 - field_2
  piVar4[10] = definition[3];        // +0x28 - field_3
  iVar1 = this[2];                    // +0x08 - some pointer
  if (iVar1 != 0) {
    piVar4[0xf] = *(int *)(iVar1 + 0x24);  // +0x3C - copy from source object
    piVar4[0x10] = *(int *)(iVar1 + 0x28); // +0x40
    piVar4[0x11] = *(int *)(iVar1 + 0x2c); // +0x44
    piVar4[0x12] = *(int *)(iVar1 + 0x30); // +0x48
  }
  if (param_3 != 0) {
    (**(code **)(*piVar4 + 4))(param_3);  // vtable+0x04 - setOwner?
  }
  if (!bVar2) {
    SimulationObjectType::registerWithManager(piVar4); // FUN_008321e0
  }
  return 1;
}