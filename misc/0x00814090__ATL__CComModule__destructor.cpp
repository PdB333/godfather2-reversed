// FUNC_NAME: ATL::CComModule::destructor
void __fastcall ATL_CComModule_destructor(undefined4 *this)

{
  *this = &PTR_FUN_00d730cc;
  this[1] = &PTR_LAB_00d730c8;
  ATL_CComModule_destructor_inner();
  ATL_ModuleUnregisterServer(0x964a0392);
  if (this[2] != 0) {
    ATL_ModuleUnlock(this[2]);
  }
  this[1] = &PTR_LAB_00d730c4;
  DAT_0112a688 = 0;
  *this = &PTR_LAB_00e30fe0;
  return;
}