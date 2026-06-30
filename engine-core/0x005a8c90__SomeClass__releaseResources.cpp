// FUNC_NAME: SomeClass::releaseResources
void SomeClass::releaseResources(void)
{
  uint *puVar1;
  undefined *puVar2;
  
  // Release resource at offset +0x10
  puVar1 = *(uint **)(this + 0x10);
  if (puVar1 != (uint *)0x0) {
    (**(code **)(&DAT_0103aee0 + (*puVar1 & 0x7fff) * 4))(puVar1);
  }
  
  // Release resource at offset +0x18
  puVar1 = *(uint **)(this + 0x18);
  if (puVar1 != (uint *)0x0) {
    (**(code **)(&DAT_0103aee0 + (*puVar1 & 0x7fff) * 4))(puVar1);
  }
  
  // Release resource at offset +0x20
  puVar1 = *(uint **)(this + 0x20);
  if (puVar1 != (uint *)0x0) {
    (**(code **)(&DAT_0103aee0 + (*puVar1 & 0x7fff) * 4))(puVar1);
  }
  
  // Release resource at offset +0x1c
  puVar1 = *(uint **)(this + 0x1c);
  if (puVar1 != (uint *)0x0) {
    (**(code **)(&DAT_0103aee0 + (*puVar1 & 0x7fff) * 4))(puVar1);
  }
  
  // Save pointer at +0x14 before clearing
  puVar2 = *(undefined **)(this + 0x14);
  
  // Clear all resource pointers
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  
  // Release the special resource at +0x14 if it's not null and not a sentinel
  if ((puVar2 != (undefined *)0x0) && (puVar2 != &DAT_0103ae68)) {
    (*DAT_0119cb3c)(puVar2);  // Call destructor/free function
    *(undefined4 *)(this + 0x14) = 0;
  }
  
  // Call base class cleanup
  FUN_005a43a0(this);
  return;
}