// FUNC_NAME: DoubleBuffer::DoubleBuffer
void __thiscall DoubleBuffer::DoubleBuffer(DoubleBuffer *this)
{
  int iVar1;
  undefined4 uVar2;
  bool bInitialized;

  bInitialized = g_globalInitFlag == '\0'; // DAT_0120588f - global one-time init flag
  this->field0 = 0x11; // +0x00
  this->field1 = 0;    // +0x04
  this->field2 = 0;    // +0x08

  if (bInitialized) {
    g_globalInitFlag = '\x01'; // set flag
    initStaticPool(&g_staticPool); // FUN_00662100 on DAT_01203740
    initStaticPool2(&g_staticPool); // FUN_006622a0 on DAT_01203740
  }

  copyBlob(&this->bufferA, 8, &g_staticPool); // FUN_00662350(this+0x0C, 8, &g_staticPool)
  // copyBlob is likely memcpy or similar

  if (g_globalInitFlag == '\0') {
    g_globalInitFlag = '\x01';
    initStaticPool(&g_staticPool);
    initStaticPool2(&g_staticPool);
  }

  copyBlob(&this->bufferB, 8, &g_staticPool); // FUN_00662350(this+0x14, 8, &g_staticPool)

  iVar1 = allocateMemory(0x10); // FUN_009c8e50 - returns pointer or 0
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = createSubObject(); // FUN_0065c7c0 - constructor for sub-object
  }
  this->subObj1 = uVar2; // +0x1C

  iVar1 = allocateMemory(0x10);
  if (iVar1 != 0) {
    uVar2 = createSubObject();
    this->subObj2 = uVar2; // +0x20
    return;
  }
  this->subObj2 = 0; // +0x20
  return;
}