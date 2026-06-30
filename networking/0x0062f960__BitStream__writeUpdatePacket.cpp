// FUNC_NAME: BitStream::writeUpdatePacket
void __thiscall BitStream::writeUpdatePacket(void) {
    int iVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    int *piVar4;
    
    // Check write buffer capacity using offset +0x10 which points to a buffer descriptor
    // bufferDescriptor->mWritePos (at +0x20) must be < bufferDescriptor->mCapacity (at +0x24)
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360(); // handle buffer overflow
    }
    puVar3 = *(undefined4 **)((int)this + 8); // get current write pointer from +0x8
    *puVar3 = 4; // write type tag 4 (int32)
    uVar2 = FUN_00638920(); // get some value (object ID or hash)
    puVar3[1] = uVar2; // write the value
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8; // advance write pointer by 8 bytes
    
    // Write two 4-byte fields from object at +0x40 and +0x44
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = *(undefined4 *)((int)this + 0x40);
    puVar3[1] = *(undefined4 *)((int)this + 0x44);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    FUN_00628260(0); // some initialization or state update
    
    // Another type 4 write
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = 4;
    uVar2 = FUN_00638920();
    puVar3[1] = uVar2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Another type 4 write (third)
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = 4;
    uVar2 = FUN_00638920();
    puVar3[1] = uVar2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Backpatch: rewind and overwrite the last written pair with something else
    iVar1 = *(int *)((int)this + 8);
    puVar3 = (undefined4 *)FUN_00638020(); // get some pointer (maybe to a table)
    *puVar3 = *(undefined4 *)(iVar1 + -8); // copy the pair that was just written (type+value)
    puVar3[1] = *(undefined4 *)(iVar1 + -4);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + -0x10; // move write pointer back 16 bytes (undo two writes)
    
    // Write type 4 again (fourth)
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = 4;
    uVar2 = FUN_00638920();
    puVar3[1] = uVar2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Write type 5 (string) with an object handle
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = 5; // type 5 = string
    uVar2 = FUN_00637c50(0, 0); // get string handle for (0,0)
    puVar3[1] = uVar2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Copy the string handle again (duplicate)
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = puVar3[-2]; // copy from two positions back
    puVar3[1] = puVar3[-1];
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Complex fixup: read the two most recently written items (type and value)
    iVar1 = *(int *)((int)this + 8);
    piVar4 = (int *)(iVar1 + -8);
    if (*piVar4 == 0) {
        // If type is 0, use a different target (the buffer descriptor's +0x34 field)
        piVar4 = (int *)(*(int *)((int)this + 0x10) + 0x34);
    }
    // If the type of the earlier pair (at iVar1-0x10) is 5 or 7, then set some object's field at +0x8
    if (*(int *)(iVar1 + -0x10) == 5) {
        *(int *)(*(int *)(iVar1 + -0xc) + 8) = piVar4[1]; // set target's +0x8 to the data value
    } else if (*(int *)(iVar1 + -0x10) == 7) {
        *(int *)(*(int *)(iVar1 + -0xc) + 8) = piVar4[1];
    }
    // Remove the last written pair (undo eight bytes)
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + -8;
    
    // Write type 4 again (fifth)
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = 4;
    uVar2 = FUN_00638920();
    puVar3[1] = uVar2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Write type 4 (sixth)
    if (*(uint *)(*(int *)((int)this + 0x10) + 0x20) <= *(uint *)(*(int *)((int)this + 0x10) + 0x24)) {
        FUN_00627360();
    }
    puVar3 = *(undefined4 **)((int)this + 8);
    *puVar3 = 4;
    uVar2 = FUN_00638920();
    puVar3[1] = uVar2;
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + 8;
    
    // Another backpatch: save the last written pair into a pointer from FUN_00638020()
    iVar1 = *(int *)((int)this + 8);
    puVar3 = (undefined4 *)FUN_00638020();
    *puVar3 = *(undefined4 *)(iVar1 + -8);
    puVar3[1] = *(undefined4 *)(iVar1 + -4);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + -0x10;
    
    FUN_00625d70(); // finalization or another write operation
    
    // Two more backpatches (saving the last written data)
    iVar1 = *(int *)((int)this + 8);
    puVar3 = (undefined4 *)FUN_00638020();
    *puVar3 = *(undefined4 *)(iVar1 + -8);
    puVar3[1] = *(undefined4 *)(iVar1 + -4);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + -0x10;
    
    iVar1 = *(int *)((int)this + 8);
    puVar3 = (undefined4 *)FUN_00638020();
    *puVar3 = *(undefined4 *)(iVar1 + -8);
    puVar3[1] = *(undefined4 *)(iVar1 + -4);
    *(int *)((int)this + 8) = *(int *)((int)this + 8) + -0x10;
    
    return;
}