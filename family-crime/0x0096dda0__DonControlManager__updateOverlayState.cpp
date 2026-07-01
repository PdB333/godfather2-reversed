// FUNC_NAME: DonControlManager::updateOverlayState
// Function address: 0x0096dda0
// Role: Handles the state machine for the Don Control overlay (phone call UI).
// Manages fade-in/fade-out transitions, timer, and rendering of action slots.
// Uses global interface at DAT_01223484 (likely GodfatherGameManager) and a
// presentation system for screen management.

undefined4 __fastcall DonControlManager::updateOverlayState(int this)
{
    int *piVar1;
    char cVar2;
    int iVar3;
    int *piVar4;
    uint uVar5;
    uint uVar6;
    int *piStack_10;
    int iStack_c;
    uint uStack_8;
    undefined4 uStack_4;

    iVar3 = FUN_00965110(); // getInterface() – returns some interface pointer
    piVar4 = DAT_01223484;  // global game manager (e.g. GodfatherGameManager)
    if (DAT_01223484 != (int *)0x0) {
        cVar2 = FUN_009650e0(); // isUIVisible() – checks if UI is active
        if (cVar2 != '\0') {
            // UI is visible – handle transition logic
            if (iVar3 != 0) {
                // If interface is valid, reset and abort
                FUN_00983120(0,0,0); // resetState()
                *(undefined1 *)(this + 0x704) = 0; // state = idle
                FUN_0096b880(iVar3); // cleanupInterface(iVar3)
                return 0;
            }
            if (*(char *)(this + 0x221) != '\0') {
                // Overlay is active (e.g. phone call screen)
                uVar6 = *(uint *)(this + 0x6f4); // state flags
                if ((uVar6 >> 0x12 & 1) == 0) {
                    // Bit 18 (0x40000) not set – not in fade-in transition
                    if ((uVar6 & 1) == 0) {
                        // Not active – start fade-in
                        *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) & 0xfffcffff; // clear bits 16,17,18
                        *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) | 0x40000;   // set bit 18 (fade-in)
                        FUN_0096d910(); // startFadeIn()
                        *(undefined1 *)(this + 0x704) = 1; // state = fading in
                        return 0;
                    }
                    // else active and bit 18 clear – already active, do nothing
                }
                else if (((uVar6 >> 0x11 & 1) != 0) && ((uVar6 >> 0x10 & 1) != 0)) {
                    // Bit 18 set AND bits 17 and 16 set (transition complete? both in and out?)
                    FUN_00982c90(); // startFadeOut()
                    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) & 0xfff8ffff; // clear bits 16,17,18
                    *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) | 1;           // set bit 0 (active)
                    (**(code **)(*piVar4 + 0x84))(); // call vtable+0x84 (e.g. updateGameManager?)
                }
                return 0;
            }
            // Overlay not active – force activate
            *(uint *)(this + 0x6f4) = *(uint *)(this + 0x6f4) | 1; // set active
            (**(code **)(*piVar4 + 0x84))(); // call vtable+0x84
            return 1;
        }
        // UI not visible – handle idle state
        if (*(char *)(this + 0x704) == '\0') {
            if (0.0 < *(float *)(this + 0x700)) {
                FUN_009697e0(); // resetTimer()
            }
            *(undefined1 *)(this + 0x704) = 1; // state = waiting
            DAT_00e574bc = '\0'; // global flag: overlay not ready
        }
        else if (DAT_00e574bc != '\0') {
            return 0; // already done
        }
        if (*(float *)(this + 0x700) <= 0.0) {
            // Timer expired – prepare overlay elements
            *(undefined4 *)(this + 0x700) = 0; // clear timer
            piVar4 = (int *)FUN_00ad8d40(); // getScreenManager()
            if ((piVar4 != (int *)0x0) && (iVar3 = (**(code **)(*piVar4 + 0x34))(), iVar3 != 0)) {
                // Get first screen from screen manager
                piVar4 = (int *)(**(code **)(*piVar4 + 0x34))(); // getActiveScreen()
                piVar4 = (int *)(**(code **)(*piVar4 + 0x3c))(); // getCanvas()
                if (piVar4 != (int *)0x0) {
                    // Iterate over action slots (array at this+0x338, count at this+0x33c)
                    uVar6 = 0;
                    iStack_c = 0;
                    uStack_8 = 0;
                    uStack_4 = 0;
                    if (*(int *)(this + 0x33c) != 0) {
                        do {
                            piVar1 = (int *)(*(int *)(this + 0x338) + uVar6 * 4); // slot pointer array
                            if ((*(char *)(*piVar1 + 0x59) != '\0') && // slot is active/visible
                                (piStack_10 = (int *)(**(code **)(*piVar4 + 0x14))(*(undefined4 *)(*piVar1 + 0x5c)), // getTexture? 
                                 piStack_10 != (int *)0x0)) {
                                FUN_0096aeb0(&piStack_10); // addToDrawList (stack grows)
                            }
                            uVar6 = uVar6 + 1;
                        } while (uVar6 < *(uint *)(this + 0x33c));
                    }
                    // Now iterate the collected draw list and clean up
                    uVar6 = uStack_8;
                    iVar3 = iStack_c;
                    uVar5 = 0;
                    if (uStack_8 != 0) {
                        do {
                            (**(code **)(**(int **)(iVar3 + uVar5 * 4) + 4))(0); // destructor? (vtable+4)
                            uVar5 = uVar5 + 1;
                        } while (uVar5 < uVar6);
                    }
                    DAT_00e574bc = '\x01'; // overlay ready flag
                    if (iVar3 != 0) {
                        FUN_009c8f10(iVar3); // freeList()
                    }
                }
            }
        }
    }
    return 0;
}