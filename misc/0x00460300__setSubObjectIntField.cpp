// FUNC_NAME: setSubObjectIntField
void __thiscall setSubObjectIntField(void* thisPtr, int newValue)
{
    // this+0x218: pointer to a sub-object (e.g., a state controller or script object)
    int* subObject = *(int**)((char*)thisPtr + 0x218);
    if (subObject != nullptr)
    {
        // subObject+0x130: target field (e.g., a state variable or parameter)
        *(int*)((char*)subObject + 0x130) = newValue;
    }
}