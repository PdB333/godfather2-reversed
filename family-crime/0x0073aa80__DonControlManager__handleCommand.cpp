// FUNC_NAME: DonControlManager::handleCommand
undefined1 __thiscall DonControlManager::handleCommand(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int commandId, undefined4 param_6)
{
    int *playerOrDonControl;
    char result;
    int tmpInt;
    undefined4 tmpVal;
    undefined1 retVal;

    // Get player/don control pointer at offset 0x5C (0x17 * 4)
    playerOrDonControl = (int *)this[0x17];
    retVal = 1; // default return = true

    switch(commandId - 0x23) {
        case 0: // command 0x23
            tmpInt = FUN_006bc8b0(playerOrDonControl); // likely getDonControlGadget
            if ((tmpInt != 0) && (result = FUN_006eb940(), result != '\0')) { // likely isDonControlActive
                FUN_009b1320(0,0); // show help message?
                return 1;
            }
            break;

        case 1: // command 0x24
            FUN_006bc8b0(playerOrDonControl);
            FUN_009b1410(); // hide help message?
            return 1;

        case 2: // command 0x25
            FUN_0072cf00(0); // set camera state?
            return 1;

        case 3: // command 0x26
            // Check bit 23 of playerOrDonControl[0x7D6] (offset 0x1F58)
            if (((uint)playerOrDonControl[0x7d6] >> 0x17 & 1) != 0) {
                (**(code **)(*playerOrDonControl + 0x318))(); // virtual call on player
                return 1;
            }
            break;

        case 4: // command 0x27
            FUN_00939860(playerOrDonControl,1); // set focus target (maybe marker 1)
            return 1;

        case 5: // command 0x28
            FUN_00939860(playerOrDonControl,2);
            return 1;

        case 6: // command 0x29
            FUN_00939860(playerOrDonControl,0);
            return 1;

        case 7: // command 0x2A
            FUN_00719260(); // some global action
            return 1;

        case 8: // command 0x2B
            FUN_007f63e0(0xb); // show screen? (0xB = maybe "donControlUI")
            tmpVal = 0;
            *(undefined1 *)(playerOrDonControl + 0x184) = 0; // clear flags at offset 0x610, 0x612, etc.
            *(undefined1 *)((int)playerOrDonControl + 0x612) = 0;
            playerOrDonControl[0x84a] = 0; // offset 0x2128
            tmpVal = FUN_006fbc40(0,0); // get hud or something
            FUN_007f96a0(0xc7bf0ee2,0,tmpVal,tmpVal); // play UI sound
            FUN_006fbc70(); // cleanup
            result = 0;
            (**(code **)(*this + 0x2c))(0xa039288f,1,1,0,0x3f800000,0x3f800000); // virtual call on this (play animation?)
            return result;

        case 9: // command 0x2C
            FUN_007f6420(0xb); // hide screen 0xB
            FUN_007f6420(0xf); // hide screen 0xF
            return 1;

        case 10: // command 0x2D
            this[0x1c] = this[0x1c] | 2; // set flag bit 1 (offset 0x70)
            return 1;

        case 11: // command 0x2E
            this[0x1c] = this[0x1c] & 0xfffffffd; // clear flag bit 1
            FUN_0073a930(); // some state update
            return 1;

        case 12: // command 0x2F
            tmpInt = FUN_006bea40(this[0x14]); // get something at offset 0x50
            if (tmpInt != 0) {
                FUN_009aef10(); // trigger action
                return 1;
            }
            break;

        case 13: // command 0x30
            tmpInt = FUN_006bc8b0(playerOrDonControl);
            *(uint *)(tmpInt + 0x48) = *(uint *)(tmpInt + 0x48) & 0xffff7fff; // clear bit 15
            return 1;

        case 0xF: // command 0x32
            FUN_0073a930();
            return 1;

        default:
            // Delegate to a base handler (FUN_0073e610) likely from a parent class
            retVal = FUN_0073e610(param_2,param_3,param_4,commandId,param_6);
            break;
    }
    return retVal;
}