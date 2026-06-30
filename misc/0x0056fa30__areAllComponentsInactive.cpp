// FUNC_NAME: areAllComponentsInactive
bool __fastcall areAllComponentsInactive(int unused, void* obj)
{
    // obj points to an object with 5 consecutive component pointers at offsets 0x34, 0x38, 0x3C, 0x40, 0x44.
    // Each component (if non-null) has a byte at offset +0x08; 0 means inactive, non-zero means active.
    // Returns true only if all components are either null or inactive.
    bool result = true;
    
    int* comp0 = *(int**)((char*)obj + 0x34);
    if (comp0 != nullptr)
    {
        result = *(char*)(comp0 + 0x08 / sizeof(int)) == '\0';
    }
    
    int* comp1 = *(int**)((char*)obj + 0x38);
    if (comp1 != nullptr)
    {
        result = result && (*(char*)(comp1 + 0x08 / sizeof(int)) == '\0');
    }
    
    int* comp2 = *(int**)((char*)obj + 0x3C);
    if (comp2 != nullptr)
    {
        result = result && (*(char*)(comp2 + 0x08 / sizeof(int)) == '\0');
    }
    
    int* comp3 = *(int**)((char*)obj + 0x40);
    if (comp3 != nullptr)
    {
        result = result && (*(char*)(comp3 + 0x08 / sizeof(int)) == '\0');
    }
    
    int* comp4 = *(int**)((char*)obj + 0x44);
    if (comp4 != nullptr)
    {
        result = result && (*(char*)(comp4 + 0x08 / sizeof(int)) == '\0');
    }
    
    return result;
}