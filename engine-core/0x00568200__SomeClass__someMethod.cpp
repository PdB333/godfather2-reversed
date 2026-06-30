// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int this, undefined4 param_2)
{
    // Call to some initialization or processing function with param_2
    FUN_004d3d90(param_2);
    
    // Check if a pointer at offset +0x8 is non-null
    if (*(int *)(this + 8) != 0) {
        // Call another helper function
        FUN_005684b0();
        
        // Call a virtual method (vtable index 25, since +100 = 25*4) on the object at this+8
        (**(code (***)(int))(**(int **)(this + 8) + 100))();
    }
    return;
}