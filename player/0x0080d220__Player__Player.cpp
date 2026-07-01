// FUNC_NAME: Player::Player
// Function address: 0x0080d220
// Role: Constructor for Player class. Initializes member fields, sets vtable, checks game state flags and plays initialization sounds.

undefined4 * __thiscall Player::Player(undefined4 *this, undefined4 arg1, undefined4 arg2) {
    char cVar1;
    undefined4 uVar2;
    // unaff_retaddr appears to be a global game state pointer from register (e.g., EAX)
    int *pGlobalState = reinterpret_cast<int *>(unaff_retaddr);

    // Call base class constructor (likely EARSObject or SimObject)
    BaseClass::BaseClass(arg1, arg2);

    // Set vtable pointer for Player class
    *this = &PTR_LAB_00d72c30;  // VTable for Player

    // Initialize various fields to zero
    this[0x16] = 0;  // +0x58: unknown
    this[0x17] = 0;  // +0x5C
    this[0x18] = 0;  // +0x60
    this[0x19] = 0;  // +0x64
    this[0x25] = 0;  // +0x94: flags/state bitfield
    this[0x1d] = 0;  // +0x74
    this[0x1c] = 0;  // +0x70
    this[0x1b] = 0;  // +0x6C
    this[0x20] = 0;  // +0x80
    this[0x1f] = 0;  // +0x7C
    this[0x1e] = 0;  // +0x78

    // Static initialization call (sets up some global)
    SomeStaticInit(0);

    this[0x27] = 0;  // +0x9C

    // Reset arg2 to 0 (possibly used as output parameter)
    arg2 = 0;

    // Get the game object pointer from this[0x14] (+0x50)
    if (this[0x14] != 0) {
        // Call virtual function at offset 0x10 on the game object,
        // with a hash and a pointer to arg2.
        // This likely checks a specific flag or component.
        cVar1 = (**(code **)(*(int *)this[0x14] + 0x10))(0x383225a1, &arg2);
        if ((cVar1) && (pGlobalState != 0) && ((*(byte *)(pGlobalState + 0x894) & 1) == 0) &&
            ((*(uint *)(pGlobalState + 0x894) >> 3 & 1) == 0)) {
            // Set bit 0 of flags at +0x94
            this[0x25] = this[0x25] | 1;
            uVar2 = GetSomeManager();    // Likely AudioManager or UIManager
            SomeManagerMethod(uVar2);     // Perform manager action
        }
    }

    // Check if the game state byte at offset 0x6e3 from the game object equals 4 (likely "in-game" mode)
    if ((char)((int *)this[0x14])[0x6e3] == '\x04') {
        // Call virtual function at offset 0x234 on game object (set state/mode)
        (**(code **)(*(int *)this[0x14] + 0x234))(0, 0);
        this[0x25] = this[0x25] | 2;    // Set bit 1 of flags
    }

    // Play initialization sound event (ID 0x5c)
    PlaySoundEvent(0x5c);
    StopSoundEvent();

    // Store a pointer from the game object's offset +0x4a8 into +0x98
    this[0x26] = *(undefined4 *)(this[0x14] + 0x4a8);

    if (this[0x14] != 0) {
        // Get singleton manager and store result
        uVar2 = GetGameManager(DAT_01130950);  // Global singleton handle
        this[0x1a] = uVar2;  // +0x68
        return this;
    }

    this[0x1a] = 0;
    return this;
}