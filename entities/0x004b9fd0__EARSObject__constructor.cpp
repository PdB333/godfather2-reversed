// FUNC_NAME: EARSObject::constructor

void __fastcall EARSObject::constructor(uint32_t* thisObj) {
    // +0x00: Set the primary vtable pointer (class-specific virtual table)
    thisObj[0] = (uint32_t)&g_classVtable; // PTR_FUN_00e35990

    // +0x3C: Set secondary vtable / function pointer table
    thisObj[0xF] = (uint32_t)&g_vtable1; // PTR_LAB_00e35af0
    // +0x48:
    thisObj[0x12] = (uint32_t)&g_vtable2; // PTR_LAB_00e35b00
    // +0x50:
    thisObj[0x14] = (uint32_t)&g_vtable3; // PTR_LAB_00e35b04
    // +0x54:
    thisObj[0x15] = (uint32_t)&g_vtable4; // PTR_LAB_00e35b08
    // +0x58:
    thisObj[0x16] = (uint32_t)&g_vtable5; // PTR_LAB_00e35b68

    // Initialize a global engine subsystem (e.g., audio, rendering)
    initGlobalSubsystem(&g_globalStruct); // FUN_00408310(&DAT_01218038)

    // Check a flag at offset +0x19D (7 bytes after 0x196)
    if (*(char*)((int)thisObj + 0x19D) != 0 && g_someGlobalFlag != 0) {
        // Perform conditional action (e.g., start a coroutine)
        doConditionalAction(); // FUN_00478620
    }

    // +0x164: If a pointer (likely a list node or resource handle) is non-null
    if (thisObj[0x59] != 0) {
        // Insert this object into a global intrusive linked list
        uint32_t* listCursor = (uint32_t*)(g_memoryPool + 0x14); // pool head + offset
        // The following code builds a new node in the list's internal buffer
        *(uint32_t*)(*listCursor) = (uint32_t)&g_listLabel; // PTR_LAB_0110ba94
        *listCursor += 4;
        // Store pointer to the object's field at +0x54
        *(uint32_t*)(*listCursor) = (uint32_t)(thisObj + 0x15);
        *listCursor += 4;
        *(uint8_t*)(*listCursor) = 0; // null terminator
        // Align list cursor to next 4‑byte boundary
        *listCursor = (*listCursor + 4) & 0xFFFFFFFC;
    }

    // Release or finalize two global objects (possibly singletons)
    cleanupGlobalObject(&g_object1); // FUN_004086d0(&DAT_0120e944)
    cleanupGlobalObject(&g_object2); // FUN_004086d0(&DAT_0120e94c)

    // Finalize the construction sequence
    finalizeInitialization(); // FUN_0046ea20
}