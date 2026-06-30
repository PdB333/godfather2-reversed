// FUNC_NAME: GameObject::GameObject
// Function address: 0x00416a70
// Constructor for a game object (likely player/entity with vtable)
// - Sets up vtable pointer, initializes member fields
// - Calls base class constructor (FUN_004a7560) with two parameters
// - Retrieves possibly a scene manager and links object to it
// - Calls a virtual function after construction

undefined4 * __thiscall GameObject::GameObject(undefined4 *this, undefined4 param2, undefined4 param3)
{
    undefined4 uVar1;
    char cVar2;
    int *piVar3;
    int iVar4;

    // Call base class constructor (param2, param3 likely parent parameters)
    BaseClassConstructor(param2, param3);  // FUN_004a7560

    // Fetch a global constant (probably a sentinel value like -1)
    uVar1 = g_DefaultValue;  // DAT_0110ac04

    // Clear bits 0 and 2 of flags at offset 0x62
    *(byte *)((int)this + 0x62) = *(byte *)((int)this + 0x62) & 0xfa;

    // Initialize two fields to the default value
    this[0x16] = uVar1;  // +0x58? Actually index 0x16 = offset 0x58
    this[0x17] = uVar1;  // +0x5C

    // Set vtable pointer
    *this = &s_VTable;  // PTR_FUN_00e2f858

    // Clear linking fields
    this[0x14] = 0;  // +0x50
    this[0x15] = 0;  // +0x54

    // Initialize byte at offset 0x60 to 0xFF, and at 0x61 to 0
    *(byte *)(this + 0x18) = 0xff;  // careful: this+0x18 is pointer arithmetic, but cast to byte writes at +0x60
    *(byte *)((int)this + 0x61) = 0;

    // Get a pointer from the base's vtable? This is convoluted: 
    // this[2] is at offset 8, dereferenced twice to get a vtable, then call slot 0x20
    piVar3 = (int *)(**(code **)(**(int **)(this[2] + 8) + 0x20))();
    // This calls a function that returns an int* likely a singleton manager

    // Call virtual function at slot 0x48 on that returned object
    cVar2 = (**(code **)(*piVar3 + 0x48))();

    // Load another constant
    uVar1 = g_AnotherDefault;  // DAT_00e2b1a4

    // Set bit 1 of flags at 0x62 based on cVar2 (multiplied by 2)
    *(byte *)((int)this + 0x62) =
        *(byte *)((int)this + 0x62) ^ (cVar2 * 2 ^ *(byte *)((int)this + 0x62)) & 2;

    // Initialize matrix or transform fields (groups of 4 floats? each set with default and three zeros)
    this[4] = uVar1;   // +0x10
    this[5] = 0;
    this[6] = 0;
    this[7] = 0;
    this[8] = 0;       // +0x20
    this[9] = uVar1;   // +0x24
    this[10] = 0;
    this[11] = 0;
    this[12] = 0;      // +0x30
    this[13] = 0;
    this[14] = uVar1;  // +0x38
    this[15] = 0;      // +0x3C
    this[0x10] = 0;    // +0x40
    this[0x11] = 0;    // +0x44
    this[0x12] = 0;    // +0x48
    this[0x13] = uVar1;// +0x4C

    // Get some system reference (like ObjectManager)
    iVar4 = GetObjectManager();  // FUN_004168f0
    if ((iVar4 != 0) && (iVar4 = *(int *)(iVar4 + 0x14), iVar4 != 0))
    {
        // Link this object to that system: store pointers at offsets 0x50 and 0x54
        this[0x14] = iVar4 + 0x10;
        this[0x15] = iVar4;
    }

    // Additional initialization
    DoPostInit();  // FUN_00416b50

    // Call virtual function at slot 0x50 on the base's vtable (likely scene or network marker)
    (**(code **)(**(int **)(this[2] + 8) + 0x50))();

    return this;
}