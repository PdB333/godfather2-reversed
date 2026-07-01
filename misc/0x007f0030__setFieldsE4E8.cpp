// FUNC_NAME: setFieldsE4E8
void __thiscall setFieldsE4E8(void* this_, int valueA, int valueB)
{
    // +0xE4: field1
    *(int*)((char*)this_ + 0xE4) = valueA;
    // +0xE8: field2
    *(int*)((char*)this_ + 0xE8) = valueB;
}