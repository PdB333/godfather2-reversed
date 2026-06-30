// FUNC_NAME: InputDevice::initialize

/* Address: 0x0073b5b0
   Role: Initializes an input device (controller), sets up linked lists, detects capabilities, and configures flags */

void InputDevice::initialize(InputDevice *this, int deviceId, undefined4 param_3)
{
    int *piVar1;
    float fVar2;
    char cVar3;
    int *piVar4;
    int iVar5;
    undefined4 uVar6;
    int iVar7;
    
    // Call base class constructor
    FUN_0073e160(deviceId, param_3);
    
    // Set vtable and initialize fields
    *this = &PTR_LAB_00d63448; // vtable
    this->field_0x1c = 0; // offset +0x70
    this->field_0x1d = 0; // offset +0x74 (flags)
    this->field_0x1e = 0; // offset +0x78 (linked list node)
    this->field_0x1f = 0; // offset +0x7C
    this->field_0x26 = 0; // offset +0x98 (pointer)
    this->field_0x29 = 0; // offset +0xA4 (linked list node)
    this->field_0x2a = 0; // offset +0xA8
    this->field_0x2b = 0; // offset +0xAC
    this->field_0x2c = 0; // offset +0xB0
    this->field_0x2d = 0; // offset +0xB4
    this->field_0x20 = 0; // offset +0x80
    this->field_0x21 = 0; // offset +0x84
    
    // Get input device manager singleton
    if ((this->field_0x12 == 0) || (this->field_0x12 == 0x48)) {
        piVar4 = (int *)0x0;
    }
    else {
        piVar4 = (int *)FUN_0043b870(DAT_01131040);
    }
    
    // Prepare linked list node for field_0x1e based on manager's offset 0x30
    if (piVar4[0xc] == 0) {
        iVar5 = 0;
    }
    else {
        iVar5 = piVar4[0xc] + -0x48;
    }
    if (iVar5 != 0) {
        iVar7 = iVar5 + 0x48;
    }
    if (this->field_0x1e != iVar7) {
        if (this->field_0x1e != 0) {
            FUN_004daf90(this + 0x1e); // Remove from linked list
        }
        this->field_0x1e = iVar7;
        if (iVar7 != 0) {
            this->field_0x1f = *(undefined4 *)(iVar7 + 4);
            *(undefined4 **)(iVar7 + 4) = this + 0x1e;
        }
    }
    
    // Copy data from manager at offsets 0x4C-0x54 to this at 0x8C-0x94
    *(undefined8 *)(this + 0x23) = *(undefined8 *)(piVar4 + 0x13);
    this->field_0x25 = piVar4[0x15];
    
    // Manage linked list for field_0x26 (offset 0x98)
    if (this->field_0x26 != 0) {
        *(undefined4 *)(this->field_0x26 + 8) = 0;
        this->field_0x26 = 0;
    }
    iVar7 = piVar4[0x16];
    this->field_0x26 = iVar7;
    if (iVar7 != 0) {
        *(int **)(iVar7 + 8) = this + 0x26;
        piVar4[0x16] = 0;
    }
    
    // Prepare linked list node for field_0x29 from manager's offset 0x1C
    if (piVar4[7] == 0) {
        iVar7 = 0;
    }
    else {
        iVar7 = piVar4[7] + -0x48;
    }
    if (iVar7 == 0) {
        iVar7 = 0;
    }
    else {
        iVar7 = iVar7 + 0x48;
    }
    piVar1 = this + 0x29;
    if (this->field_0x29 != iVar7) {
        if (this->field_0x29 != 0) {
            FUN_004daf90(piVar1);
        }
        *piVar1 = iVar7;
        if (iVar7 != 0) {
            this->field_0x2a = *(undefined4 *)(iVar7 + 4);
            *(int **)(iVar7 + 4) = piVar1;
        }
    }
    
    // Get another singleton for field_0x28 and store manager pointer
    if ((*piVar1 == 0) || (*piVar1 == 0x48)) {
        uVar6 = 0;
    }
    else {
        uVar6 = FUN_0043b870(DAT_01130fb0);
    }
    this->field_0x28 = uVar6;
    this->field_0x27 = piVar4;
    
    // Detect device capabilities via virtual function call
    cVar3 = (**(code **)(*piVar4 + 0x1c))(4);
    if (cVar3 == '\0') {
        cVar3 = (**(code **)(*piVar4 + 0x1c))(0x1000);
        if (cVar3 != '\0') {
            this->field_0x1d |= 4;
            goto LAB_0073b776;
        }
        cVar3 = (**(code **)(*piVar4 + 0x1c))(0x2000);
        if (cVar3 != '\0') {
            this->field_0x1d |= 8;
            goto LAB_0073b776;
        }
        cVar3 = (**(code **)(*piVar4 + 0x1c))(8);
        if (cVar3 != '\0') {
            this->field_0x1d |= 2;
            goto LAB_0073b776;
        }
    }
    this->field_0x1d |= 1;
    
LAB_0073b776:
    // Process additional configuration if this device is valid
    if (((this->field_0x1e != 0) && (this->field_0x1e != 0x48)) &&
       (iVar7 = FUN_0043b870(DAT_0112af98), iVar7 != 0)) {
        this->field_0x1c = *(undefined4 *)(iVar7 + 0x10);
        FUN_00789f00(this->field_0x17);
        iVar5 = this->field_0x17;
        if ((*(byte *)(iVar7 + 0x34) & 1) != 0) {
            FUN_007f63e0(1);
            this->field_0x1d |= 0x200;
        }
        if (((*(byte *)(iVar7 + 0x34) & 0x20) != 0) && ((*(uint *)(iVar5 + 0x4a4) >> 6 & 1) != 0)) {
            this->field_0x1d |= 0x8000;
            (**(code **)(*(int *)this->field_0x14 + 0x290))(0,1);
        }
        fVar2 = *(float *)(iVar7 + 0x18);
        this->field_0x21 = fVar2;
        if (iVar5 != 0) {
            this->field_0x21 = *(float *)(iVar5 + 0x1db8) * fVar2;
        }
        if (((*(byte *)(this + 0x1d) & 2) != 0) && ((*(byte *)(iVar7 + 0x34) & 4) != 0)) {
            deviceId = 0;
            cVar3 = (**(code **)(**(int **)(iVar7 + 0xc) + 0x10))(0x36cac259, &deviceId);
            if ((cVar3 != '\0') && ((deviceId != 0 && (iVar7 = FUN_008b6ae0(), iVar7 != 0)))) {
                FUN_0079f100(0x33,0);
            }
        }
    }
    
    // More capability detection
    cVar3 = (**(code **)(*piVar4 + 0x1c))(0x10);
    if (cVar3 == '\0') {
        cVar3 = (**(code **)(*piVar4 + 0x1c))(0x40);
        if (cVar3 != '\0') {
            this->field_0x1d |= 0x100;
        }
    }
    else {
        this->field_0x1d |= 0x80;
    }
    
    // Ensure a certain flag is set and update another singleton
    if ((*(byte *)(this + 0x1d) & 0x10) == 0) {
        if ((this->field_0x17 != 0) && (iVar7 = FUN_0043b870(DAT_0113105c), iVar7 != 0)) {
            *(ushort *)(iVar7 + 0x78) &= 0xfffb;
        }
        this->field_0x1d |= 0x10;
    }
    
    // Final initialization
    if (this->field_0x12 != 0) {
        FUN_00461290();
        return;
    }
    FUN_00461290();
    return this;
}