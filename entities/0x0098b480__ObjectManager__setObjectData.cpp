// FUNC_NAME: ObjectManager::setObjectData
void __thiscall ObjectManager::setObjectData(int param_2, undefined4 param_3)
{
    // Access the object container: begin pointer at +0x230, end pointer at +0x234
    int **begin = *(int ***)(this + 0x230);
    int **end = *(int ***)(this + 0x234);
    
    if (begin != end)
    {
        // Iterate over array of pointers to objects
        while (**begin + 0x30 != param_2) // Compare object's ID field at +0x30
        {
            ++begin;
            if (begin == end)
            {
                return; // ID not found
            }
        }
        // Found object; set field at +0x3C to param_3
        *(undefined4 *)(**begin + 0x3c) = param_3;
    }
}