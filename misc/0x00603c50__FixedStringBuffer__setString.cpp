// FUNC_NAME: FixedStringBuffer::setString

void __thiscall FixedStringBuffer::setString(char param_1) {
    char cVar1;
    char *pcVar2;
    int *piVar3;
    char *pcVar4;
    int *unaff_EDI; // this pointer
    undefined4 local_14;
    char *local_10;
    uint local_c;
    undefined4 local_8;
    code *local_4;

    local_10 = (char *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (code *)0x0;
    pcVar4 = (char *)0x0;

    // Check if internal string pointer (offset 0) is null or if source string retrieval fails
    if ((*unaff_EDI == 0) || 
        (cVar1 = getSourceString(*unaff_EDI, &local_14, &param_1), cVar1 == '\0')) {
LAB_00603cf4:
        // Use default string (global literal)
        pcVar2 = &defaultStringLiteral; // DAT_0120546e
    } else {
        // Retrieve string from source based on param_1
        if (param_1 == '\0') {
            freeString(local_14); // Release source string
        } else {
            copyAndAllocate(local_14, &local_10); // Allocate and copy
        }

        // Trim surrounding brackets if present
        if (((1 < local_c) && (*local_10 == '[')) && (local_10[local_c - 1] == ']')) {
            adjustLength(local_c - 1);
            adjustLength(0);
        }

        pcVar4 = local_10;
        if (0xb < local_c) {
            // String too long for fixed buffer; backup: set to space
            *(undefined2 *)(unaff_EDI + 1) = 0x20; // Write space + null at buffer start (+0x4)
            goto LAB_00603d16;
        }
        pcVar2 = local_10;
        if (local_10 == (char *)0x0) goto LAB_00603cf4; // Fallback to default
    }

    // Copy source string (pcVar2) into fixed buffer at offset +0x4
    piVar3 = unaff_EDI + 1; // Destination buffer
    do {
        cVar1 = *pcVar2;
        *(char *)piVar3 = cVar1;
        pcVar2 = pcVar2 + 1;
        piVar3 = (int *)((int)piVar3 + 1);
    } while (cVar1 != '\0');

LAB_00603d16:
    // Clean up allocated string if any
    if (pcVar4 != (char *)0x0) {
        (*local_4)(pcVar4); // Call deallocator stored in local_4 (likely a member function pointer)
    }
    return;
}