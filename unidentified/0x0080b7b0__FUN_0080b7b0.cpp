// FUNC_NAME: UnknownClass::Constructor
void __fastcall UnknownClass::constructor(UnknownClass *this)
{
  // +0x00: vtable pointer
  this->vtable = (void *)&gVtable_00d724cc;
  // +0x3C: pointer to some global data
  this->field_3C = (void *)&gData_00d724bc;
  // +0x48: pointer to another global data
  this->field_48 = (void *)&gData_00d724b8;

  // Initialize embedded subobject at offset 0x50 (0x14 * 4)
  EmbeddedSubObject::constructor(&this->subObject);
  // Additional setup for the embedded subobject
  EmbeddedSubObject::postInit(&this->subObject);

  // Global initialization call
  SomeGlobalInit();
}