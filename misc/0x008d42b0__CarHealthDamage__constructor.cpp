// FUNC_NAME: CarHealthDamage::constructor
undefined4 * CarHealthDamage::constructor(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  if ((param_1 != 0) && (puVar1 = (undefined4 *)FUN_009c8e50(0x88), puVar1 != (undefined4 *)0x0)) {
    FUN_008d3ec0();
    puVar1[7] = param_2;         // +0x1C: damage value
    puVar1[0x12] = param_1;     // +0x48: target object pointer
    *puVar1 = &PTR_FUN_00d7d5b4; // +0x00: vtable pointer for CarHealthDamage
    puVar1[0x13] = &PTR_LAB_00d7d5a4; // +0x4C: reference to static data (e.g., damage type ID)
    return puVar1;
  }
  return (undefined4 *)0x0;
}