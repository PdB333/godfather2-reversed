// FUNC_NAME: InputDeviceManager::~InputDeviceManager

void __fastcall InputDeviceManager::~InputDeviceManager(undefined4 *this)
{
    int nextNode;
    int current;
    uint idx;

    // Set vtables
    *this = &PTR_FUN_00e39160;
    this[3] = &PTR_LAB_00e39170;

    // If string resource flag and pointer are set, free the string
    if ((*(char *)(this + 0x21b) != '\0') && (this[0x21a] != 0)) {
        FUN_009ea940(this + 0x1a, this[0x21a]); // likely string destructor
        this[0x21a] = 0;
    }

    // Destroy first linked list (e.g., active device list)
    nextNode = this[0x10];
    *(undefined1 *)(this + 0x21b) = 0;
    this[0x10] = 0;
    while (nextNode != 0) {
        current = *(int *)(nextNode + 0xb0); // next pointer at +0xB0
        FUN_009c8eb0(nextNode); // delete node
        nextNode = current;
    }

    // Destroy second linked list (e.g., device list by index)
    current = this[0x11];
    idx = 0;
    if (this[0x12] != 0) {
        do {
            nextNode = *(int *)(current + 4); // next pointer at +4
            FUN_009c8eb0(current);
            idx = idx + 1;
            current = nextNode;
        } while (idx < (uint)this[0x12]);
    }
    this[0x12] = 0;
    this[0x11] = 0;

    // Release mutex based on threading mode (bit1 of +0x17)
    FUN_004086d0(&DAT_01206770);
    FUN_004086d0(&DAT_0120679c);
    this[0x17] = this[0x17] & 0xfffffffe; // clear bit 0
    if ((*(byte *)(this + 0x17) & 2) == 0) {
        FUN_004086d0(&DAT_0121bf38);
        FUN_00408310(&DAT_0121bf38);       // lock/unlock? maybe reinitialize
    } else {
        FUN_004086d0(&DAT_012069c4);
        FUN_004086d0(&DAT_012069d4);
    }

    // Release interface object if present
    if ((undefined4 *)this[0x14] != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)this[0x14])(1); // virtual call with arg 1
    }
    this[0x14] = 0;

    // Global cleanup
    FUN_0053fb70();   // shutdownInputDevices()
    FUN_00ab50b0();   // cleanupOther()
    this[3] = &PTR_LAB_00e39174; // final vtable

    DAT_01223480 = 0; // global instance pointer
    FUN_004083d0();   // final heap cleanup
    return;
}