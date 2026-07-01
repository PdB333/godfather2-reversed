// FUNC_NAME: Player::~Player
void __fastcall Player::~Player(Player *this)
{
    int *pEntity; // piVar1 - pointer to entity object at this+0x58
    int *pSomeManager; // piVar4
    int iVar2;
    char cVar3;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // Set vtable to current class vtable (destructor start)
    this->vtable = &PTR_LAB_00d6bfa8;

    // Release string resources if certain flags are set
    if (*(char *)((int)this + 0x184) < 0) {
        local_c = DAT_0112b9f4; // some string or resource
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c, 0); // releaseString
    }
    if ((*(byte *)((int)this + 0x185) & 1) != 0) {
        local_c = DAT_0112b9fc;
        local_8 = 0;
        local_4 = 0;
        FUN_00408a00(&local_c, 0);
    }

    // Release static objects
    FUN_00408310(&DAT_0112b9e8);
    FUN_00408310(&DAT_0112b9f4);
    FUN_00408310(&DAT_0112b9e0);
    FUN_00408310(&DAT_0112b9fc);

    pEntity = (int *)this->field_0x58; // this[0x16] -> offset 0x58
    if (pEntity != (int *)0x0) {
        pSomeManager = (int *)FUN_007abe90(); // getInputManager or similar
        if ((pSomeManager != (int *)0x0) && ((*(ushort *)((int)this + 0x184) >> 9 & 1) != 0)) {
            // Call virtual function at vtable+0x70 on manager (e.g., disableInput)
            (**(code **)(*pSomeManager + 0x70))();
            *(ushort *)((int)this + 0x184) &= 0xfdff; // clear bit 9
        }

        // Stop various sounds
        FUN_007f6420(0xc); // stopSound(12)
        FUN_007f6420(0xd); // stopSound(13)
        FUN_007f6420(0x3a); // stopSound(58)
        FUN_007f6420(0x3b); // stopSound(59)

        // Clear flags in entity object
        pEntity[0x928] &= 0xfffffffd; // clear bit 1 at offset 0x24A0
        pEntity[0x927] &= 0xdfffffff; // clear bit 29 at offset 0x249C
        pEntity[0x928] &= 0xbfffbfdf; // clear multiple bits
        *(undefined1 *)(pEntity + 0x7b1) = 0xff; // set byte at offset 0x1EC4 to 0xFF
        pEntity[0x929] &= 0xfffffffd; // clear bit 1 at offset 0x24A4
        pEntity[0x929] &= 0xfffffffb; // clear bit 2

        if ((pEntity[0x6e5] & 0x300U) != 0) {
            FUN_007faca0(); // stopAllSounds?
        }
        FUN_007f6420(0x67); // stopSound(103)

        // Release managers
        pSomeManager = (int *)FUN_007ab130(); // getSomeManager
        (**(code **)(*pSomeManager + 4))(this->field_0x1b4); // release object at offset 0x1B4
        pSomeManager = (int *)FUN_007ab150(); // getAnotherManager
        (**(code **)(*pSomeManager + 4))(this->field_0x1b8); // release object at offset 0x1B8

        cVar3 = FUN_00481660(); // isGamePaused?
        if ((cVar3 != '\0') || (cVar3 = FUN_00481640(), cVar3 != '\0')) {
            FUN_00472130(1); // setPauseState(1)
        }

        // Handle additional flags
        if ((*(byte *)((int)this + 0x184) >> 4 & 1) != 0) {
            FUN_0079f100(3, 0); // setPlayerState(3, 0)
        }
        if ((*(byte *)((int)this + 0x184) >> 5 & 1) != 0) {
            FUN_0043b870(DAT_01131018); // getDialogManager
            FUN_009ae900(0); // resetDialog(0)
        }

        // Clear flag in entity
        if ((~*(byte *)(pEntity + 0x129) & 1) == 0) {
            pEntity[0x129] &= 0xfffffffe;
        }

        pEntity[0x928] |= 0x10; // set bit 4
        FUN_00799c20(); // updateSomething
        pEntity[0x928] |= 0x8000; // set bit 15
        pEntity[0xc45] = 5; // set some state to 5 at offset 0x3114

        iVar2 = pEntity[0x3fc]; // offset 0xFF0
        if (iVar2 == 0) {
            pSomeManager = (int *)0x0;
        }
        else {
            pSomeManager = (int *)(iVar2 - 0x48); // adjust pointer to base object
            if (pSomeManager != (int *)0x0) {
                if (((*(ushort *)((int)this + 0x184) >> 10 & 1) != 0) &&
                   (iVar2 = FUN_0043b870(DAT_01131018), iVar2 != 0)) {
                    *(undefined4 *)(iVar2 + 0x50) = this->field_0x1c0; // offset 0x1C0
                    *(ushort *)((int)this + 0x184) &= 0xfbff; // clear bit 10
                }
                if ((*(uint *)(iVar2 + 0x1b4c) & 0x300) != 0) {
                    FUN_007faca0(); // stopAllSounds?
                }
                FUN_007f6420(0x67); // stopSound(103)
                FUN_007f7e40(); // stopAllSounds?
                FUN_007f6420(6); // stopSound(6)
                FUN_007fd670(); // clearEffects?
                FUN_007fc9f0(); // clearParticles?
                (**(code **)(*pSomeManager + 0x198))(); // virtual method on base object
                if ((~*(byte *)(iVar2 + 0x45c) & 1) == 0) {
                    *(uint *)(iVar2 + 0x45c) &= 0xfffffffe;
                }
                cVar3 = (**(code **)(*pSomeManager + 0x1bc))(); // virtual method
                if (cVar3 != '\0') {
                    FUN_007f7cf0(); // resumeSounds?
                }
            }
        }

        // More cleanup on entity
        FUN_007fd670(); // clearEffects?
        FUN_007fc9f0(); // clearParticles?
        (**(code **)(*pEntity + 0x198))(); // virtual method on entity
        FUN_007f6420(6); // stopSound(6)
        FUN_007f6420(0x31); // stopSound(49)
        FUN_007f6420(0x32); // stopSound(50)
        FUN_007f7e40(); // stopAllSounds?
        FUN_00550c30(); // clearInput?
        pEntity[0x927] &= 0xffffe7ff; // clear bits 11-12

        cVar3 = FUN_00481660(); // isGamePaused?
        if ((cVar3 != '\0') || (cVar3 = FUN_00481640(), cVar3 != '\0')) {
            *(undefined1 *)(pEntity + 0x91c) = 1; // set byte at offset 0x2470 to 1
        }

        if ((pSomeManager != (int *)0x0) && (((uint)pSomeManager[0x6e5] >> 6 & 1) != 0)) {
            (**(code **)(*pEntity + 0x2a0))(pSomeManager); // virtual method on entity
            (**(code **)(*pSomeManager + 0x2a0))(pEntity); // virtual method on base
        }
    }

    // Release additional object
    if (this->field_0x19c != 0) {
        FUN_009c8f10(this->field_0x19c); // releaseObject
    }

    FUN_007affe0(); // cleanupSomething

    // Set vtable to deleted vtable (destructor end)
    this->vtable = &PTR_LAB_00d6b95c;
    FUN_0080ea60(); // freeMemory or final cleanup
    return;
}