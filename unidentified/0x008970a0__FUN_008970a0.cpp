// FUNC_NAME: BaseClass::virtualCall_7
void __thiscall virtualCall_7(void *this, undefined4 param2)
{
  // Calls the 8th virtual function (index 7) of the object pointed to by 'this'
  // The object's vtable is at the first field of the struct (offset 0x00)
  // The function pointer is at vtable[7] (offset +0x1C on 32-bit)
  (*(code *)this[7])(*this, param2);
  return;
}