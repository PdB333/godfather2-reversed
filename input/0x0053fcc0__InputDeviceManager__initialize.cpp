// FUNC_NAME: InputDeviceManager::initialize
// Function address: 0x0053fcc0
// Initializes the input device manager, setting up input bindings and allocating internal objects.

void InputDeviceManager::initialize(void)
{
    int iVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    LPVOID pvVar4;
    char local_e0[16]; // buffer for resource name or ID
    undefined4 local_d0;
    undefined4 local_cc;
    undefined4 local_c8;
    undefined4 local_c4;
    undefined1 local_b8;
    undefined4 local_34;
    char local_23;

    // Base initialization
    FUN_00bf49c0();
    FUN_00bf4b30(_DAT_0103b26c);

    // Determine initialization mode based on flag at this+0x28
    // If flag is non-zero, mode = 3, else mode = 2
    local_23 = (*(char *)(this + 0x28) != '\0') + 2;

    // Initialize local variables (possibly for a structure)
    local_d0 = 0;
    local_cc = DAT_00e4499c;
    local_c8 = 0;
    local_c4 = 0;
    local_34 = 0;
    local_b8 = 1;

    // Get thread-local storage for allocator
    TlsGetValue(DAT_01139810);

    // Allocate main input state buffer (0x310 bytes, tag 0x2f)
    iVar1 = FUN_00aa2680(0x310, 0x2f);
    *(undefined2 *)(iVar1 + 4) = 0x310; // store size at offset 4

    // Create a resource/object and store at this+0x24
    uVar2 = FUN_009e8a60(local_e0, 0xc544);
    *(undefined4 *)(this + 0x24) = uVar2;

    // Allocate a small object (0x30 bytes, tag 0xd) for vtable setup
    TlsGetValue(DAT_01139810);
    puVar3 = (undefined4 *)FUN_00aa2680(0x30, 0xd);
    *(undefined2 *)(puVar3 + 1) = 0x30; // store size at offset 4

    // Initialize the resource with flag 1
    FUN_00a0ebb0(*(undefined4 *)(this + 0x24), 1);

    // Set up vtable for the small object
    *puVar3 = &PTR_FUN_00e3918c;
    puVar3[2] = &PTR_LAB_00e391a0;
    puVar3[3] = &PTR_LAB_00e391a8;

    // Reference counting / cleanup check
    if ((*(short *)(puVar3 + 1) != 0) &&
        (*(short *)((int)puVar3 + 6) = *(short *)((int)puVar3 + 6) + -1,
         *(short *)((int)puVar3 + 6) == 0))
    {
        (**(code **)*puVar3)(1);
    }

    // If flag at this+0x28 is set, allocate an additional sub-object
    if (*(char *)(this + 0x28) != '\0')
    {
        pvVar4 = TlsGetValue(DAT_01139810);
        puVar3 = *(undefined4 **)((int)pvVar4 + 0x98);
        if (puVar3 == (undefined4 *)0x0)
        {
            puVar3 = (undefined4 *)FUN_00aa2150(0xc, 0xd);
        }
        else
        {
            *(int *)((int)pvVar4 + 0x9c) = *(int *)((int)pvVar4 + 0x9c) + -1;
            *(undefined4 *)((int)pvVar4 + 0x98) = *puVar3;
        }
        if (puVar3 == (undefined4 *)0x0)
        {
            uVar2 = 0;
        }
        else
        {
            uVar2 = FUN_00561790();
        }
        *(undefined4 *)(this + 0x2c) = uVar2;
    }

    // Initialize sub-object at this+0x24 (offset 0x74)
    FUN_00c07180(*(undefined4 *)(*(int *)(this + 0x24) + 0x74));

    // Additional initialization
    FUN_00559ba0();

    // Allocate input binding configuration (0x100 bytes, tag 0x27)
    TlsGetValue(DAT_01139810);
    puVar3 = (undefined4 *)FUN_00aa2680(0x100, 0x27);
    *(undefined2 *)(puVar3 + 1) = 0x100;

    // Initialize input system
    FUN_00a67a10();

    // Set up vtable for input binding object
    *puVar3 = &PTR_FUN_00e39128;
    puVar3[2] = &PTR_LAB_00e39138;
    puVar3[3] = &PTR_LAB_00e39140;
    puVar3[4] = &PTR_LAB_00e39150;
    puVar3[5] = &PTR_LAB_00e39158;

    // Register input bindings (action, key/button pairs)
    // Format: FUN_00a67930(actionFlag, inputFlag)
    FUN_00a67930(0xfffffffe, 0xfffffffe);
    FUN_00a67930(4, 4);
    FUN_00a67930(4, 8);
    FUN_00a67930(4, 2);
    FUN_00a67930(4, 0x10);
    FUN_00a67930(4, 0x20);
    FUN_00a67930(4, 0x100);
    FUN_00a67930(4, 0x200);
    FUN_00a67930(4, 0x40000);
    FUN_00a67930(4, 0x20000);
    FUN_00a67930(4, 0x400);
    FUN_00a67930(0x8000, 4);
    FUN_00a67930(0x8000, 2);
    FUN_00a67930(0x8000, 0x10);
    FUN_00a67930(0x8000, 0x20);
    FUN_00a67930(0x8000, 0x100);
    FUN_00a67930(0x8000, 0x200);
    FUN_00a67930(0x8000, 0x40000);
    FUN_00a67930(0x8000, 0x400);
    FUN_00a67930(0x10, 0x10);
    FUN_00a67930(0x10, 2);
    FUN_00a67930(0x10, 0x20);
    FUN_00a67930(0x10, 0x20000);
    FUN_00a67930(0x10, 0x100);
    FUN_00a67930(0x10, 0x200);
    FUN_00a67930(0x10, 0x40000);
    FUN_00a67930(0x10, 8);
    FUN_00a67930(0x20, 0x20);
    FUN_00a67930(0x20, 2);
    FUN_00a67930(0x20, 8);
    FUN_00a67930(0x20, 0x100);
    FUN_00a67930(0x20, 0x200);
    FUN_00a67930(0x20, 0x40000);
    FUN_00a67930(0x20, 0x20000);
    FUN_00a67930(0x40, 8);
    FUN_00a67930(0x80, 2);
    FUN_00a67930(0x80, 0x100);
    FUN_00a67930(0x80, 0x20000);
    FUN_00a67930(0x100, 0x100);
    FUN_00a67930(0x100, 0x200);
    FUN_00a67930(0x100, 0x40000);
    FUN_00a67930(0x100, 0x20000);
    FUN_00a67930(0x100, 2);
    FUN_00a67930(0x200, 0x200);
    FUN_00a67930(0x200, 0x100);
    FUN_00a67930(0x200, 0x1000);
    FUN_00a67930(0x200, 0x40000);
    FUN_00a67930(0x200, 0x20000);
    FUN_00a67930(0x200, 2);
    FUN_00a67930(0x20000, 0x40000);
    FUN_00a67930(0x20000, 0x100);
    FUN_00a67930(0x20000, 2);
    FUN_00a67930(0x40000, 0x40000);
    FUN_00a67930(0x40000, 0x100);
    FUN_00a67930(0x40000, 2);
    FUN_00a67930(0x800, 4);
    FUN_00a67930(0x800, 0x10);
    FUN_00a67930(0x800, 0x20);
    FUN_00a67930(0x800, 0x100);
    FUN_00a67930(0x800, 0x40000);
    FUN_00a67930(0x800, 0x20000);
    FUN_00a67930(0x800, 0x200);
    FUN_00a67930(0x1000, 2);
    FUN_00a67930(0x1000, 0x100);
    FUN_00a67930(0x1000, 0x200);
    FUN_00a67930(0x1000, 0x40000);
    FUN_00a67930(0x1000, 0x20000);
    FUN_00a67930(0x1000, 0x20);
    FUN_00a67930(0x2000, 8);
    FUN_00a67930(0x4000, 2);
    FUN_00a67930(0x4000, 0x4000);
    FUN_00a67930(0x10000, 4);
    FUN_00a67930(0x10000, 2);
    FUN_00a67930(0x10000, 0x20);
    FUN_00a67930(0x10000, 0x200);
    FUN_00a67930(0x10000, 0x40000);

    // Store the input binding object at this+0x54
    *(undefined4 **)(this + 0x54) = puVar3;

    // Finalize initialization
    FUN_009ec340(puVar3, 1, 0, 1);

    return;
}