// FUNC_NAME: SomeClass::shutdown
void __fastcall SomeClass::shutdown(undefined4 *this)
{
  *this = &PTR_FUN_00d5c958; // Set vtable pointer
  FUN_004086d0(&DAT_01130470); // Release resource
  FUN_004086d0(&DAT_01130368); // Release resource
  FUN_004086d0(&DAT_01130370); // Release resource
  FUN_004086d0(&DAT_01130248); // Release resource
  FUN_004086d0(&DAT_01130378); // Release resource
  FUN_004086d0(&DAT_01130218); // Release resource
  FUN_004086d0(&DAT_011303c8); // Release resource
  FUN_004086d0(&DAT_011304c8); // Release resource
  FUN_004086d0(&DAT_01130360); // Release resource
  FUN_004086d0(&DAT_011301b0); // Release resource
  FUN_004086d0(&DAT_012069fc); // Release resource
  FUN_004086d0(&DAT_01206a10); // Release resource
  FUN_004083d0(); // Final cleanup
  return;
}