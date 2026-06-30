// FUNC_NAME: Constructor::initializeVTable
void __fastcall FUN_005963c0(undefined4 *this)
{
  *this = &PTR_FUN_00e3adf0; // Set vtable pointer to static table
  *(undefined1 *)(this + 1) = 0; // Initialize byte at +4 to 0 (likely a flag or counter)
  return;
}