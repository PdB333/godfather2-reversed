// FUNC_NAME: NetSession::initializeConnection
void __fastcall NetSession::initializeConnection(int *thisPtr)
{
    float fVar1;
    int iVar3;
    undefined4 uVar4;
    undefined4 *puVar5;
    uint uVar6;
    uint uVar7;
    float local_44[4]; // 16-byte vector from virtual call

    // Call virtual function to get a direction vector (likely from a component)
    (**(code **)(*(int *)(thisPtr[0xba] + 0xd0) + 0x14))(local_44);
    fVar1 = *(float *)(thisPtr[0xba] + 0x19c); // scale factor

    // Set velocity or impulse on some object (thisPtr[0xda] is likely a physics body)
    *(float *)(thisPtr[0xda] + 0x7c) = local_44[0] * fVar1;
    *(float *)(thisPtr[0xda] + 0x74) = local_44[1] * fVar1;
    *(float *)(thisPtr[0xda] + 0x78) = local_44[2] * fVar1;

    FUN_009e6ff0(thisPtr[0xba], 1); // enable something on component

    // Allocate a 0x170-byte reliable packet window structure
    TlsGetValue(DAT_01139810); // thread-local storage (unused result)
    iVar3 = FUN_00aa2680(0x170, 0xb); // allocation with tag 0xb
    *(undefined2 *)(iVar3 + 4) = 0x170; // set size field
    iVar3 = FUN_0055d510(); // construct the packet window
    thisPtr[0xd8] = iVar3; // store pointer

    // Initialize fields of the packet window from this object's data
    *(int *)(iVar3 + 0x1c) = thisPtr[0xda];          // physics body pointer
    *(int *)(iVar3 + 0x20) = thisPtr[0xde];          // some other object
    *(int *)(iVar3 + 0x24) = thisPtr[0xe0];          // ...
    *(int *)(iVar3 + 0x28) = thisPtr[0xdd];          // ...
    *(int *)(iVar3 + 0x2c) = thisPtr[0xdf];          // ...
    *(int *)(iVar3 + 0x30) = thisPtr[0xe1];          // ...
    uVar4 = (**(code **)(*thisPtr + 0x234))();       // get a unique ID (virtual)
    *(undefined4 *)(iVar3 + 0x34) = uVar4;           // store ID
    *(int *)(iVar3 + 0x38) = thisPtr[0xe2];          // another field
    *(int *)(iVar3 + 0x44) = thisPtr[0xe3];          // ...

    // Allocate a 0x30-byte event manager / window state structure
    TlsGetValue(DAT_01139810);
    puVar5 = (undefined4 *)FUN_00aa2680(0x30, 0xb);
    *(undefined2 *)(puVar5 + 1) = 0x30; // set size
    FUN_00bed040(); // construct event manager
    *puVar5 = &PTR_LAB_00e39b6c; // set vtable
    puVar5[9] = 0;   // offset 0x24
    puVar5[10] = 0;  // offset 0x28
    puVar5[0xb] = 0x80000000; // offset 0x2C - negative one?
    thisPtr[0xdb] = (int)puVar5;

    // Link event manager to packet window
    *(int *)(thisPtr[0xd8] + 0x3c) = thisPtr[0xdb]; // packet window points to event manager

    // Compute initial sequence mask for event manager
    uVar6 = (**(code **)(*thisPtr + 0x22c))(); // virtual function, probably getSessionID()
    *(uint *)(thisPtr[0xdb] + 0xc) = (uVar6 & 0x1f) << 5 | 7; // window slot mask

    // Copy a timestamp or sequence from another object
    *(undefined4 *)(thisPtr[0xd8] + 0x9c) = *(undefined4 *)(thisPtr[0xde] + 0x18);

    FUN_009f3d60(thisPtr[0xdc]); // initialize some component
    (**(code **)(*(int *)thisPtr[0xd8] + 0x20))(); // virtual: start packet window
    FUN_009e7450(*(undefined4 *)(*(int *)(thisPtr[0xd8] + 0x3c) + 0x10)); // release old resource?

    // Remove from a list
    FUN_009f1f90(thisPtr + 0xb8);

    // Get new IDs for packet sender
    uVar6 = FUN_0043b490(); // generates a session ID component
    uVar7 = (**(code **)(*thisPtr + 0x22c))(); // get another ID

    // Allocate a 0x160-byte packet sender object
    TlsGetValue(DAT_01139810);
    iVar3 = FUN_00aa2680(0x160, 0x31);
    *(undefined2 *)(iVar3 + 4) = 0x160;
    iVar3 = FUN_009f7230(*(undefined4 *)(thisPtr[0xba] + 0x10), // some component
                         thisPtr[0xba] + 0xe0, // address of a buffer
                         (uVar6 & 0xfff) << 0x10 | (uVar7 & 0x1f) << 5 | 6); // packet ID
    thisPtr[0xd9] = iVar3; // store sender pointer

    // Generate another token (maybe for ack)
    FUN_0043b490();

    // Register a message handler (type 0x2001) with this object as context
    FUN_009f01f0(0x2001, thisPtr, 0);

    // Finalize the packet sender
    FUN_009e7450(thisPtr[0xd9]);
    return;
}