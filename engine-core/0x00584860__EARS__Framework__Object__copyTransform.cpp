// FUNC_NAME: EARS::Framework::Object::copyTransform
void __thiscall EARS::Framework::Object::copyTransform(undefined4 *this, undefined4 *source, undefined4 param_3)
{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 *in_EAX;
  
  cVar1 = *(char *)*source;
  if (*(char *)*this != '\x02') {
    if (cVar1 == '\x02') {
      puVar2 = (undefined4 *)this[1]; // +0x04: transform data pointer
      *(undefined1 *)*this = 2; // set type to 2 (matrix)
      puVar3 = (undefined4 *)source[1]; // +0x04: source transform data pointer
      uVar4 = puVar3[1];
      uVar5 = puVar3[2];
      uVar6 = puVar3[3];
      *puVar2 = *puVar3;
      puVar2[1] = uVar4;
      puVar2[2] = uVar5;
      puVar2[3] = uVar6;
      uVar4 = puVar3[5];
      uVar5 = puVar3[6];
      uVar6 = puVar3[7];
      puVar2[4] = puVar3[4];
      puVar2[5] = uVar4;
      puVar2[6] = uVar5;
      puVar2[7] = uVar6;
      return;
    }
    *(undefined1 *)*this = 0; // set type to 0 (identity)
    return;
  }
  puVar2 = (undefined4 *)this[1]; // +0x04: transform data pointer
  *(undefined1 *)*this = 2; // set type to 2 (matrix)
  if (cVar1 == '\x02') {
    FUN_005781f0(puVar2,param_3); // likely multiply matrices
    return;
  }
  puVar3 = (undefined4 *)source[1]; // +0x04: source transform data pointer
  uVar4 = puVar3[1];
  uVar5 = puVar3[2];
  uVar6 = puVar3[3];
  *puVar2 = *puVar3;
  puVar2[1] = uVar4;
  puVar2[2] = uVar5;
  puVar2[3] = uVar6;
  uVar4 = puVar3[5];
  uVar5 = puVar3[6];
  uVar6 = puVar3[7];
  puVar2[4] = puVar3[4];
  puVar2[5] = uVar4;
  puVar2[6] = uVar5;
  puVar2[7] = uVar6;
  return;
}