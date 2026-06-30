// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass(int* this)
{
    *this = (int)&PTR_FUN_00e36f1c; // set vtable to destructor intermediate table
    if (*(int**)(this[1])) {
        (**(code**)(**(int**)(this[1]) + 0xc))(); // call virtual destructor on contained object at offset +0x4
    }
    *this = (int)&PTR_LAB_00e362b8; // restore vtable to base table
    return;
}