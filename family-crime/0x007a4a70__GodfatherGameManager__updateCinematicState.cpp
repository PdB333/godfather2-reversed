// FUNC_NAME: GodfatherGameManager::updateCinematicState
void __fastcall GodfatherGameManager::updateCinematicState(int *this)
{
    // Offset +0x91c: m_bCinematicActive (flag)
    // Offset +0x93c: m_bPendingCinematic (flag)
    // Global DAT_01205a20: g_bEnableCinematicMode ?
    // Offset +0x7ae: m_iCinematicMode (int)
    // Global DAT_01205224: g_iDesiredCinematicMode ?
    if (((*(char*)(this + 0x91c) != '\0') || (DAT_01205a20 == 0)) &&
        ((*(char*)(this + 0x93c) != '\0') || (this[0x7ae] != DAT_01205224)))
    {
        // Not satisfying condition; proceed to update
    }
    else
    {
        return;
    }

    // Update display/input
    FUN_00806de0(); // Likely DisplayManager::update()
    FUN_0079dad0(); // Likely InputManager::update()

    // Call virtual method at vtable offset 0x28c (index 0xA3) - e.g., onCinematicStateChanged
    code *virtualFn = *(code**)(*this + 0x28c);
    *(undefined1*)(this + 0x93c) = 0; // Clear pending flag
    char result = virtualFn(); // call virtual

    if ((result != '\0') && (this[0x7ba] != 0))
    {
        // +0x7ba likely m_pCinematicEntity (pointer)
        int entity = this[0x7ba];
        int entityResult = FUN_006b07e0(entity); // Maybe get entity validity
        if (entityResult != 0)
        {
            FUN_006ad5c0(); // Destroy or stop entity
        }
    }

    // Query some global state
    undefined4 uStack_c = DAT_0112b18c;
    undefined4 uStack_8 = 0;
    undefined1 uStack_4 = 0;
    FUN_00408a00(&uStack_c, 0); // Pass as output buffer

    uStack_c = DAT_0112b29c;
    uStack_8 = 0;
    uStack_4 = 0;
    FUN_00408a00(&uStack_c, 0);

    // +0x71e m_pCinematicTarget (pointer to some object)
    if ((this[0x71e] != 0) && (this[0x71e] != 0x48))
    {
        int basePtr;
        if (this[0x71e] == 0)
        {
            basePtr = 0;
        }
        else
        {
            basePtr = this[0x71e] - 0x48; // Adjust pointer to base of containing structure
        }
        int* piBase = (int*)basePtr;

        int local10 = 0;
        // Call virtual at offset 0x10 from basePtr (vtable index 4)
        char vResult = (*(code**)(*piBase + 0x10))(0x55859efa, &local10);

        int someValue = local10;
        // Compare magic IDs: 0x55859efa and 0x637b907
        if ((vResult != '\0') && (local10 != 0))
        {
            int check = FUN_00806440(); // maybe check game state
            if ((check != 0) && (*(int*)(someValue + 0x1ed4) != 0x637b907))
            {
                int param = this[0x7b5]; // +0x7b5 m_iCinematicParam
                undefined4 uVar5 = FUN_00806440(1);
                undefined4 uVar7 = 1;
                FUN_008d7d90(param, uVar5, uVar7); // Configure something
            }
        }
    }

    // Check network condition
    char cVar2 = FUN_00481620(); // NetConnection::isConnected?
    if ((cVar2 != '\0') && (FUN_00800a90() != 0)) // Game paused or something
    {
        FUN_007fff40(this + 0xc07); // Update sub-object at offset 0xc07
    }
}