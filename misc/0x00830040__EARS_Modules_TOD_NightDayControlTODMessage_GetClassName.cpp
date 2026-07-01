// Xbox PDB: EARS_Modules_TOD_NightDayControlTODMessage_GetClassName
// FUNC_NAME: NightDayControlTODMessage::NightDayControlTODMessage
void __thiscall NightDayControlTODMessage::NightDayControlTODMessage(NightDayControlTODMessage *this)
{
  int local_10[3];
  code *local_4;
  undefined4 *allocPtr;
  undefined1 *puVar2;
  undefined4 uVar1;

  this->field_4 = 0;
  this->field_8 = 0;
  this->field_C = 0;
  this->field_10 = 0;
  this->field_14 = 0;
  this->field_18 = 0;
  this->field_1C = 0;
  *(undefined1 *)&this->field_20 = 1;
  this->vtable = &PTR_FUN_00d73868;  // vtable pointer
  this->field_24 = 1;
  FUN_008334a0();                    // global initialization
  this->field_30 = &PTR_LAB_00d73448; // another vtable or string
  this->field_7C = 0;
  this->field_80 = &PTR_FUN_00d73864; // vtable pointer
  this->field_84 = 0;
  allocPtr = (undefined4 *)FUN_009c8e80(0x40); // allocate 0x40 bytes
  this->field_88 = allocPtr;
  this->field_8C = 0;
  this->field_90 = 0x10;              // some size or count
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_4 = (code *)0x0;
  FUN_004d4ad0(local_10, &DAT_00e2f0b0, "NightDayControlTODMessage", "Sequence"); // register message handler
  FUN_004d3e20(local_10);            // process registration
  puVar2 = (undefined1 *)this->field_10; // field at +0x10
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;          // default string constant
  }
  uVar1 = FUN_004dafd0(puVar2);      // convert to ID or hash
  this->field_C = uVar1;             // store at +0x0C
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);         // cleanup callback
  }
  return;
}