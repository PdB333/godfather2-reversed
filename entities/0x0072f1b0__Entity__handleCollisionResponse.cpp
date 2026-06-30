// FUNC_NAME: Entity::handleCollisionResponse

void __thiscall Entity::handleCollisionResponse(int* thisPtr, int unused, int* collisionInfo)
{
    int* objectPtr;
    bool flag;
    int localZero = 0;
    int* esiPtr;
    int* localVar;

    // Call base function with collision info and a flag (0)
    FUN_00892c50(thisPtr, collisionInfo, 0);

    // Check flags at offsets 0x862 and 0x863 (likely damage/state flags)
    // Bit tests: bit 4 of word at 0x862, bit 3 of word at 0x862,
    //           bit 24 of word at 0x863, bit 23 of word at 0x863
    if ((((thisPtr[0x862] >> 4) & 1) != 0) || (((thisPtr[0x862] >> 3) & 1) != 0) ||
        (((thisPtr[0x863] >> 0x18) & 1) != 0) || (((thisPtr[0x863] >> 0x17) & 1) != 0))
    {
        FUN_00892b40(thisPtr, 1);
    }

    // If collision info has a valid pointer at +0xc (e.g., a hit object handle)
    if ((*(int*)((int)collisionInfo + 0xc) != 0) &&
        (objectPtr = (int*)(*(int*)((int)collisionInfo + 0xc) - 0x48), objectPtr != (int*)0x0))
    {
        // Query the object for a specific interface (hash 0x383225a1)
        flag = ((code**)objectPtr[0])[4](0x383225a1, &localZero);
        if ((flag == false) || (localVar == 0))
        {
            // Query another interface (hash 0x369ac561)
            flag = ((code**)objectPtr[0])[4](0x369ac561, &localVar);
            if ((flag != false) && (esiPtr != (int*)0x0))
            {
                // If the esiPtr object reports being in some state (virtual func +0x1bc returns true)
                flag = ((code**)esiPtr[0])[0x6f](); // 0x1bc/4 = 0x6f
                if ((flag != false) && (thisPtr != esiPtr))
                {
                    FUN_00892b40(thisPtr, 1);
                }
            }
        }
    }
    return;
}