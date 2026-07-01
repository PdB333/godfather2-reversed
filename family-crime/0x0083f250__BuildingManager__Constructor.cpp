// FUNC_NAME: BuildingManager::Constructor
undefined4 * __thiscall BuildingManager::Constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)

{
  FUN_0083cbb0(param_2,param_3);
  this[0x52] = 0;                    // +0x148: some field initialized to 0
  *this = &PTR_FUN_00d74438;         // vtable pointer
  this[0xf] = &PTR_LAB_00d74428;     // +0x3C: vtable entry for BuildingManager method
  this[0x12] = &PTR_LAB_00d74424;    // +0x48: vtable entry for BuildingManager method
  this[0x53] = 0;                    // +0x14C: some field initialized to 0
  this[0x3f] = this[0x3f] | 0xc00;  // +0xFC: flags field, setting bits 0x400, 0x800
  this[0x54] = 0;                    // +0x150: some field initialized to 0
  this[0x55] = _DAT_00d5780c;        // +0x154: copy from global (likely a static pointer)
  return this;
}