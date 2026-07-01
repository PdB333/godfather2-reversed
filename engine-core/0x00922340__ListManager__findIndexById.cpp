// FUNC_NAME: ListManager::findIndexById
// Function at 0x00922340: Searches a list for an item with a given ID, returns its index or 0xFFFFFFFF if not found.
// Uses a lock/iterator pattern: getListInfo() returns count and pointer to buffer,
// getNextListItemHandle() returns the handle of each item in sequence, releaseList() unlocks.
__declspec(naked) uint __cdecl ListManager::findIndexById(int targetHandle) {
    // This is a reconstructed C++ representation of the decompiled assembly.
    // The actual implementation uses inline assembly to access internal state.
    _asm {
        push ebp
        mov ebp, esp
        sub esp, 0x10

        // local variables:
        // [ebp-0x10] local_10 = 0xFFFFFFFF (not-found sentinel)
        // [ebp-0xC]  local_c  = pointer to list buffer
        // [ebp-8]    local_8  = count of items
        // [ebp-4]    local_4  = unused (maybe padding)

        mov dword ptr [ebp-0x10], 0xFFFFFFFF   // local_10 = -1
        mov dword ptr [ebp-0xC], 0             // local_c = 0
        mov dword ptr [ebp-8], 0               // local_8 = 0
        mov dword ptr [ebp-4], 0               // local_4 = 0

        // Call getListInfo(&local_c) - expects pointer to struct { pointer, count }?
        lea eax, [ebp-0xC]                     // address of local_c
        push eax
        call FUN_009217e0                      // getListInfo (acquire lock and get list data)
        add esp, 4

        mov edx, [ebp-8]                       // uVar2 = count
        mov ecx, [ebp-0xC]                     // iVar1 = pointer
        xor eax, eax                           // uVar4 = 0 (index)
        mov edi, [ebp-0x10]                    // uVar5 = -1 (default not-found)

        test edx, edx                          // if count == 0
        jz end_loop                            // skip loop

    loop_start:
        // Call getNextListItemHandle()
        call FUN_00891980                      // returns handle in eax
        test eax, eax                          // if handle != 0
        jz skip_check
        cmp eax, dword ptr [ebp+8]             // compare with targetHandle (param_1)
        jne skip_check
        mov edi, eax                           // found: set uVar5 = current index (uVar4)
        jmp end_loop
    skip_check:
        inc eax                                // uVar4++
        cmp eax, edx                           // compare with count
        jb loop_start                          // continue if not done

    end_loop:
        test ecx, ecx                          // if pointer (local_c) != 0
        jz skip_free
        push ecx
        call FUN_009c8f10                      // releaseList (unlock)
        add esp, 4
    skip_free:
        mov eax, edi                           // return uVar5 (index or -1)
        mov esp, ebp
        pop ebp
        ret 4                                  // __cdecl, clean one parameter
    }
}