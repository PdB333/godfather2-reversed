// FUNC_NAME: MaterialSwapListResource::constructor
void __fastcall MaterialSwapListResource::constructor(MaterialSwapListResource *this)
{
  this->vtable = &PTR_FUN_00d77720;
  this->field_0x08 = &PTR_LAB_00d7771c;
  FUN_0049c7f0("MaterialSwapListResource"); // base class constructor / resource type registration
  this->field_0x08 = &PTR_LAB_00d77718;
  DAT_01129998 = 0; // global flag or static counter
  FUN_0049c640(); // resource manager / reference counting init
  return;
}