// FUNC_NAME: ComponentManager::applyFunctionToAll
void ComponentManager::applyFunctionToAll(void* param_2)
{
    short elementCount = *(short*)(this + 0x80); // Number of elements in the array
    void** elementPtrArray = (void**)(this + 0xF4); // Base of array of structs (stride 20 bytes)
    
    for (int i = 0; i < elementCount; i++)
    {
        void* element = elementPtrArray[i * 5]; // Each element is 20 bytes (5 ints), first field is pointer
        if (element != 0)
        {
            // Call virtual function at vtable offset 0x34 (probably onUpdate or onEvent)
            (*(void (**)(void*))(*(int*)element + 0x34))(param_2);
        }
    }
}