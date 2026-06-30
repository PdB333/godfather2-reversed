// FUNC_NAME: MaterialEffect::init(uint)
// Address: 0x00489470
// Role: Constructor/initializer for a material effect node, registers shader fragments and sets up scaling parameters.

undefined4 * __thiscall MaterialEffect::init(MaterialEffect *this, undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  byte *pbVar4;
  uint uVar5;
  float fVar6;
  undefined4 uStack_4;

  // Clear first field and set initial vtable
  this->field_4 = 0;
  this->vtable2 = &LAB_00e33808;                          // offset +8
  g_lastMaterialEffect = this;                             // global singleton/tracker
  this->vtable = &FUN_00e337f8;                            // primary vtable
  this->vtable2 = &LAB_00e33804;                           // overwrite, probably secondary vtable
  this->field_C = param_2;                                 // store parent/owner
  uVar3 = FUN_009c8e80(0x100);                            // allocate 256 bytes (maybe a buffer)
  uVar2 = DAT_00e2cd54;                                    // some global data
  fVar6 = DAT_00e2b1a4;                                    // global float (likely a scale factor)
  this->field_10 = uVar3;                                  // store allocated buffer
  this->field_14 = 0;
  this->field_18 = 0x40;                                   // constant (maybe buffer size or flag)
  this->field_1C = 0;
  this->field_20 = 0;
  this->field_28 = 0;
  this->field_2C = 0;
  this->field_30 = 0;
  this->field_34 = fVar6;
  this->field_38 = uVar2;
  this->field_3C = 0;
  this->field_40 = 0;
  this->field_44 = 0;
  this->field_48 = fVar6;
  this->field_4C = 0;
  this->field_50 = 0;

  // Call virtual method on parent object (offset 8 in its vtable)
  (**(code **)(*(int *)this->field_C + 8))();

  // Register two effect names
  FUN_0049c6e0(&PTR_LAB_00e337e0,1);                     // first name (label)
  FUN_0049c6e0("FFN-LR",1);                               // second name (shader fragment)

  // Compute scaling factors
  fVar6 = DAT_00e2b1a4 / (float)DAT_01205898;            // global float / screen height (or some dimension)
  this->field_28 = DAT_00e2b1a4 / (float)DAT_0120588c;   // global float / screen width
  this->field_2C = fVar6;

  uVar5 = 0;
  uStack_4 = CONCAT31(uStack_4._1_3_,0x80);              // build value with high byte 0x80

  // Check if any registered effect byte exceeds 0x80
  if (DAT_012224a8 != 0) {
    pbVar4 = &DAT_01222330;                                // start of registered effects array
    do {
      if (0x80 < *pbVar4) {                                // first byte of each entry
        FUN_00609bf0();                                    // error/exit handler
        return this;
      }
      uVar5 = uVar5 + 1;
      pbVar4 = pbVar4 + 0xc;                               // each entry is 12 bytes
    } while (uVar5 < DAT_012224a8);
  }

  // Register this effect if there is slot space
  if (DAT_012224a8 < 0x20) {
    iVar1 = DAT_012224a8 * 0xc;                            // offset into 12-byte array
    *(undefined8 *)(&DAT_01222328 + DAT_012224a8 * 3) = 0x48942000000000;  // store 8-byte value (function pointer?)
    *(undefined4 *)(&DAT_01222330 + iVar1) = uStack_4;    // store third 4-byte field
    DAT_012224a8 = DAT_012224a8 + 1;                       // increment count
  }

  return this;
}