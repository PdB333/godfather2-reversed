// FUNC_NAME: Entity::handleMessage
void __thiscall Entity::handleMessage(void* thisPtr, int* message)
{
    int messageType = *message;
    int* thisInt = (int*)thisPtr;

    if (messageType == thisInt[0x39]) // +0xe4 (offset 0xE4/4 = 0x39)
    {
        FUN_00947510();
        return;
    }

    if (messageType == thisInt[0x3B]) // +0xec
    {
        int* dataPtr = (int*)message[1];
        if (dataPtr != 0)
        {
            int vtableMaybe = dataPtr[1];
            if (vtableMaybe != 0)
            {
                int derivedObj = vtableMaybe - 0x48; // adjust offset (cast to base?)
                if (derivedObj != 0)
                {
                    char checkResult = FUN_009467b0(derivedObj);
                    if (checkResult != 0)
                    {
                        FUN_00947510();
                        return;
                    }
                    int gameState = thisInt[0x6]; // +0x18
                    if (gameState == 5 || gameState == 6)
                    {
                        int hashed = FUN_006bc8d0(derivedObj, 0x369ac561);
                        if (hashed != 0)
                        {
                            int obj = FUN_007351c0();
                            if (obj != 0)
                            {
                                FUN_00947880(obj);
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (messageType == thisInt[0x3D]) // +0xf4
    {
        FUN_00946bb0();
        return;
    }
    else if (messageType == thisInt[0x3F]) // +0xfc
    {
        int result = FUN_00946c60(message);
        if (result != 0)
        {
            char check = FUN_00946c00(result);
            int gameState = thisInt[0x6]; // +0x18
            if (check == 0 && (gameState == 5 || gameState == 6))
            {
                int hashed = FUN_006bc8d0(result, 0x369ac561);
                if (hashed != 0)
                {
                    int obj = FUN_007351c0();
                    if (obj != 0)
                    {
                        FUN_00946c00(obj);
                        return;
                    }
                }
            }
        }
    }
    else if (messageType == thisInt[0x41]) // +0x104
    {
        int gameState = thisInt[0x6]; // +0x18
        if (gameState == 1)
        {
            FUN_00946c80(message);
            FUN_009478b0();
            return;
        }
        if (gameState == 5 || gameState == 6)
        {
            FUN_00946ca0(message);
            FUN_00947950();
            return;
        }
    }
    else if (messageType == DAT_0120e93c) // sentinel/global constant
    {
        // Check global structures
        if (*(int*)(DAT_01223484 + 0xC) == 0 || *(int*)(DAT_01223484 + 8) != 0)
        {
            FUN_00947510();
        }
        FUN_004086d0(&DAT_0120e93c);
    }
    return;
}