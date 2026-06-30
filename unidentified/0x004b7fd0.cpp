// FUN_004b7fd0: StreamWriter::writeTypeWithValue
// Writes a type descriptor (constant pointer), a 4-byte value, and a byte flag to a buffer.
// The buffer pointer is at +0x00 in the object; the current write cursor is at +0x14 relative to the buffer.
// The constant pointer (PTR_LAB_011246a4) is likely a type identifier or vtable pointer.
void __thiscall StreamWriter::writeTypeWithValue(int *this, undefined4 value, byte flag)
{
    int *piVar1;
    int iVar2;
    
    // Get the buffer pointer stored in the first member of this (+0x00)
    iVar2 = *this;
    
    // Write the constant pointer to the current cursor location
    **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_011246a4; // write type descriptor
    piVar1 = (int *)(iVar2 + 0x14);
    *piVar1 = *piVar1 + 4; // advance cursor by 4
    
    // Re-fetch buffer pointer (though unchanged) and write the value
    iVar2 = *this;
    **(undefined4 **)(iVar2 + 0x14) = value; // write 4-byte value
    *(int *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 4; // advance cursor by 4
    
    // Write the byte flag and align cursor to 4-byte boundary
    **(undefined1 **)(iVar2 + 0x14) = flag; // write byte
    *(uint *)(iVar2 + 0x14) = *(int *)(iVar2 + 0x14) + 4U & 0xfffffffc; // align to next 4
    
    return;
}