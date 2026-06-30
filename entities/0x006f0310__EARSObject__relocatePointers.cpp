// FUNC_NAME: EARSObject::relocatePointers
// Address: 0x006f0310
// This function relocates relative offsets within a binary resource blob.
// It fixes up multiple arrays of objects and pointers stored as offsets
// relative to the container or to themselves. After relocation, it calls
// a virtual fixup function on each sub-object.

void __fastcall EARSObject::relocatePointers()
{
    // First array: array of objects each 0x14 bytes (20 bytes)
    // Offsets relative to this:
    // +0x08: count1 (number of elements)
    // +0x0c: base1 (relative offset to first element)
    int count1 = *(int *)(this + 0x08);
    int base1; // absolute base for first array
    if (*(int *)(this + 0x0c) == 0) {
        base1 = 0;
    } else {
        base1 = *(int *)(this + 0x0c) + (int)this;
    }
    *(int *)(this + 0x0c) = base1; // fix base pointer

    int i1 = 0;
    if (count1 > 0) {
        int offset = 0; // byte offset into first array
        do {
            int *elem = (int *)(offset + base1); // absolute pointer to current element

            // Type ID is at elem[1] (offset +4)
            int typeId = elem[1];
            if (typeId == 1) {
                if (elem != (int *)0x0) {
                    *elem = (int)&PTR_LAB_00d5fee8; // set vtable for type 1
                }
            } else if (typeId == 0x22) {
                if (elem != (int *)0x0) {
                    *elem = (int)&PTR_LAB_00d5ff10; // set vtable for type 34
                }
            } else if (typeId == 0x23) {
                if (elem != (int *)0x0) {
                    *elem = (int)&PTR_LAB_00d5ff34; // set vtable for type 35
                }
            } else {
                FUN_006eff10(elem, typeId); // handle unknown types
                elem = extraout_ECX; // likely function returns updated pointer
            }

            // Sub-array inside each element: at elem[3] (offset +12)
            // and the number of sub-elements at elem[2] (offset +8)
            int subArrayOffset = elem[3];
            int subCount = elem[2];
            if (subArrayOffset == 0) {
                subArrayOffset = 0;
            } else {
                subArrayOffset = subArrayOffset + (int)elem; // relative to element
            }
            elem[3] = subArrayOffset; // fix sub-array pointer

            // Fix up sub-elements: each is a pointer (4 bytes) stored as
            // an offset relative to the sub-array base.
            int j = 0;
            if (subCount > 0) {
                do {
                    int *subElemPtr = (int *)(subArrayOffset + j * 4);
                    int val = *subElemPtr;
                    if (val == 0) {
                        val = 0;
                    } else {
                        val = val + (int)elem; // offset relative to element
                    }
                    *subElemPtr = val;
                    j++;
                } while (j < subCount);
            }

            // Call virtual function at vtable+4 (second entry)
            // This likely performs further fixup or initialization
            (**(code **)(*elem + 4))();

            i1++;
            offset += 0x14; // each element is 20 bytes
        } while (i1 < count1);
    }

    // Second array: array of 8-byte entries (two ints), each a pointer
    // stored as offset relative to its own address.
    // Offsets relative to this:
    // +0x14: count2
    // +0x18: base2 (relative offset to start of array)
    int count2 = *(int *)(this + 0x14);
    int base2;
    if (*(int *)(this + 0x18) == 0) {
        base2 = 0;
    } else {
        base2 = *(int *)(this + 0x18) + 0x14 + (int)this; // note: +0x14? Actually they added 0x14 after? Check: original code had base2 = *(this+0x18) + 0x14 + this; This seems to account for the array being packed with an extra offset? Wait, re-examine: In decompiled, they set *(param_1+0x18) = iVar2; where iVar2 computed as *(param_1+0x18) + 0x14 + param_1. That is weird: why +0x14? Possibly a misalignment? Actually the decompiled line: "iVar2 = *(int *)(param_1 + 0x18) + 0x14 + param_1;" That would mean the base is stored as offset from the start of the structure plus 0x14? That seems odd. Let's re-read the decompiled code carefully for the second array:
    //   iVar2 = *(int *)(param_1 + 0x18) + 0x14 + param_1;
    // So base2 = *(this+0x18) + 0x14 + this. This is not a relative offset from the start, but rather an offset from the start plus an additional 0x14. Possibly the base2 field is not a simple relative offset but an index into a larger buffer? Or maybe Ghidra misinterpreted the expression. It could be that the original code is: base2 = *(this+0x18) + this; and later they add 0x14? But the decompiler wrote it as a single line. I'll assume the calculation is as given for correctness, but it's strange. To match the binary exactly, I'll keep it.
    // Actually, looking at the first array, they did: base1 = *(this+0xc) + this; (no extra 0x14).
    // So for second array, there is an extra +0x14. That might be because the second array is located immediately after the first array? Possibly a layout constant. I'll implement as decompiled.
    }

    *(int *)(this + 0x18) = base2;

    int i2 = 0;
    if (count2 > 0) {
        do {
            // Each entry is 8 bytes, but they only use the first 4 bytes as an offset.
            int *entryPtr = (int *)(base2 + i2 * 8);
            int val = *entryPtr;
            if (val == 0) {
                val = 0;
            } else {
                val = val + (int)entryPtr; // offset relative to its own address
            }
            *entryPtr = val;
            i2++;
        } while (i2 < count2);
    }

    // Fix up arrays of pointers stored as offsets relative to this.
    // Each offset in these arrays is null-terminated.
    // Offsets: +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30
    // For each, if the stored offset is non-zero, it points to an array
    // of relative offsets (int) terminated by a zero.

    // Helper macro-like pattern:
    // int *ptrArray = (int *)(*(this + offset) + this);
    // *(this + offset) = (int)ptrArray;
    // int cur = *ptrArray;
    // while (cur != 0) {
    //     if (*ptrArray == 0) cur = 0;
    //     else cur = *ptrArray + this;
    //     *ptrArray = cur;
    //     ptrArray++;
    //     cur = *ptrArray;
    // }

    // Offset 0x1c
    if (*(int *)(this + 0x1c) != 0) {
        int *list = (int *)(*(int *)(this + 0x1c) + (int)this);
        *(int **)(this + 0x1c) = list;
        int cur = *list;
        while (cur != 0) {
            if (*list == 0) {
                cur = 0;
            } else {
                cur = *list + (int)this;
            }
            *list = cur;
            list++;
            cur = *list;
        }
    }

    // Offset 0x20
    if (*(int *)(this + 0x20) != 0) {
        int *list = (int *)(*(int *)(this + 0x20) + (int)this);
        *(int **)(this + 0x20) = list;
        int cur = *list;
        while (cur != 0) {
            if (*list == 0) {
                cur = 0;
            } else {
                cur = *list + (int)this;
            }
            *list = cur;
            list++;
            cur = *list;
        }
    }

    // Offset 0x24
    if (*(int *)(this + 0x24) != 0) {
        int *list = (int *)(*(int *)(this + 0x24) + (int)this);
        *(int **)(this + 0x24) = list;
        int cur = *list;
        while (cur != 0) {
            if (*list == 0) {
                cur = 0;
            } else {
                cur = *list + (int)this;
            }
            *list = cur;
            list++;
            cur = *list;
        }
    }

    // Offset 0x28
    if (*(int *)(this + 0x28) != 0) {
        int *list = (int *)(*(int *)(this + 0x28) + (int)this);
        *(int **)(this + 0x28) = list;
        int cur = *list;
        while (cur != 0) {
            if (*list == 0) {
                cur = 0;
            } else {
                cur = *list + (int)this;
            }
            *list = cur;
            list++;
            cur = *list;
        }
    }

    // Offset 0x2c
    if (*(int *)(this + 0x2c) != 0) {
        int *list = (int *)(*(int *)(this + 0x2c) + (int)this);
        *(int **)(this + 0x2c) = list;
        int cur = *list;
        while (cur != 0) {
            if (*list == 0) {
                cur = 0;
            } else {
                cur = *list + (int)this;
            }
            *list = cur;
            list++;
            cur = *list;
        }
    }

    // Offset 0x30
    if (*(int *)(this + 0x30) != 0) {
        int *list = (int *)(*(int *)(this + 0x30) + (int)this);
        *(int **)(this + 0x30) = list;
        int cur = *list;
        while (cur != 0) {
            if (*list == 0) {
                cur = 0;
            } else {
                cur = *list + (int)this;
            }
            *list = cur;
            list++;
            cur = *list;
        }
    }
}