// FUNC_NAME: NetReflectable::getNetFlags
undefined4 __fastcall NetReflectable::getNetFlags(int this)
{
  return *(undefined4 *)(this + 0x2e8); // +0x2e8: mNetFlags
}