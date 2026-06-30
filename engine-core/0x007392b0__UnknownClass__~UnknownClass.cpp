// FUNC_NAME: UnknownClass::~UnknownClass
void __fastcall UnknownClass::~UnknownClass(UnknownClass* this)
{
  // Set vtable pointer to base class vtable for destruction (safely call base destructor)
  this->vtable = (UnknownClassVTable*)&PTR_LAB_00d63090;

  // If the member at offset 0x68 (word index 0x1a) is non-null, destroy it
  // The function takes the address of the member, likely to delete and nullify
  if (this->field_0x68 != 0) {
    FUN_004daf90(&this->field_0x68);
  }

  // Perform global module cleanup / finalization
  FUN_0080ea60();
}