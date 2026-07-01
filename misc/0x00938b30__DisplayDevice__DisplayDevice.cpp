// FUNC_NAME: DisplayDevice::DisplayDevice
undefined4* __fastcall DisplayDevice::DisplayDevice(undefined4* this)
{
    undefined4 uVar1;
    int iVar2;

    // Set vtable pointer at offset 0
    *this = &PTR_FUN_00d8a52c;
    // Set vtable pointer at offset 4 (first assignment, possibly for base class)
    this[1] = &PTR_LAB_00d8a524;
    // Overwrite offset 4 with another vtable pointer (likely derived class or second base)
    this[1] = &PTR_LAB_00d8a528;

    // Store global reference to this object
    DAT_011305b8 = this;

    // Get system info handle
    uVar1 = getSystemInfo();
    // Retrieve display mode structure from handle
    iVar2 = getDisplayMode(uVar1);
    // Read width and height as unsigned shorts from offsets +2 and +4, convert to float
    this[2] = (float)*(ushort *)(iVar2 + 2);  // +0x08: width
    this[3] = (float)*(ushort *)(iVar2 + 4);  // +0x0C: height

    // Register a callback (0 = unknown, &LAB_00938af0 = function, 0x80 = parameter/ID)
    registerCallback(0, &LAB_00938af0, 0x80);

    return this;
}