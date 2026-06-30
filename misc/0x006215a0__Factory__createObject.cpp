// FUNC_NAME: Factory::createObject
void __thiscall Factory::createObject(int thisPtr, int typeIndex, uint arg3, uint arg4)
{
    // Get the creator function pointer for the given type index
    // FUN_00621610 returns a pointer to a constructor/allocation function
    creatorFunc_t creator = (creatorFunc_t)FUN_00621610(typeIndex);
    
    // Call the creator with the provided arguments, returns pointer to new object
    int* newObject = creator(arg3, arg4);
    
    // Assign the next available ID from the factory's counter
    // Offset +0x2C in the new object holds the ID
    newObject[0x0B] = *(int*)(thisPtr + 8);  // 0x2C / 4 = 0x0B
    
    // Increment the factory's ID counter (stored at this+0x08)
    *(int*)(thisPtr + 8) = *(int*)(thisPtr + 8) + 1;
}