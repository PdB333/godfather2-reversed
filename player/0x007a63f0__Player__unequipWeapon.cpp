// FUNC_NAME: Player::unequipWeapon
void __fastcall Player::unequipWeapon(int *this) {
    int *vtablePtr;
    int iVar1;
    undefined4 uVar2;
    int *piVar3;

    // Clear the "has weapon equipped" flag (bit 13 of flags field at +0x928)
    this[0x928] = this[0x928] & 0xffffefff;
    
    // Check if there is a current weapon slot (at +0xc30) and it's not the "empty" slot (0x48)
    if ((this[0xc30] != 0) && (this[0xc30] != 0x48)) {
        // Set the flag indicating weapon was just unequipped (bit 13)
        this[0x928] = this[0x928] | 0x2000;
        
        // Get the weapon object pointer (subtract 0x48 to get base of weapon struct)
        if (this[0xc30] == 0) {
            piVar3 = (int *)0x0;
        } else {
            piVar3 = (int *)(this[0xc30] + -0x48);
        }
        
        // Call virtual function at vtable+0x84 to play "r_weapon" animation/effect
        (**(code **)(*piVar3 + 0x84))(this, "r_weapon", 0, 0, 0);
        
        // Call some cleanup function
        FUN_008b8880();
        
        // Get weapon object pointer again for further cleanup
        if (this[0xc30] == 0) {
            iVar1 = 0;
        } else {
            iVar1 = this[0xc30] + -0x48;
        }
        
        // Clear the current ammo count at +0x158
        *(undefined4 *)(iVar1 + 0x158) = 0;
        
        // Check for attached mesh/animation object at +0x130
        if (this[0xc30] == 0) {
            iVar1 = 0;
        } else {
            iVar1 = this[0xc30] + -0x48;
        }
        
        if (*(int **)(iVar1 + 0x130) != (int *)0x0) {
            iVar1 = **(int **)(iVar1 + 0x130);
            // Allocate some debug/event object (size 0x14, type 0x15)
            uVar2 = FUN_00540c60(0x14, 0x15, 0);
            // Call virtual function at +0x44 on the mesh object with a hash and the event
            (**(code **)(iVar1 + 0x44))(0xb49c1276, uVar2);
        }
        
        // Call virtual at +0x2a0 to destroy the weapon object
        if (this[0xc30] != 0) {
            (**(code **)(*this + 0x2a0))(this[0xc30] + -0x48);
            return;
        }
        (**(code **)(*this + 0x2a0))(0);
    }
}