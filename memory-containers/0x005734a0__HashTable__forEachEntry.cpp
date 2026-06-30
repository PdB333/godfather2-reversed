// FUNC_NAME: HashTable::forEachEntry
// Address: 0x005734a0
// Iterates all entries in a chained hash table, calling callback(key, value, extraArg) for each.
// Returns index of entry where callback returned true (bit 0 set), or -1 if no match found.
// Structure at this+0x30: pointer to bucket array header:
//   +0x00: pointer to array of bucket heads (each is pointer to first node in chain)
//   +0x04: number of buckets (uint)
// Each node layout:
//   +0x00: key (first callback argument)
//   +0x04: value (second callback argument)
//   +0x08: padding/unused?
//   +0x0C: next pointer (next node in chain)

__declspec(naked) int HashTable::forEachEntry(void* this, HashTableCallback callback, uint extraArg) {
    _asm {
        push ebp
        mov ebp, esp
        push ecx
        push ebx
        push esi
        push edi
        
        // Get bucket array header pointer from this+0x30
        mov eax, dword ptr [ecx + 0x30]
        mov [ebp-8], eax          // store bucketHeader pointer
        
        call threadResetState     // FUN_00573aa0 - reset iteration state
        
        xor edi, edi              // iVar3 = 0 (entry index counter)
        
        // local_4 (current node) - assume starts with first entry
        // For clarity: this is an iterator state that may have been set by threadResetState
        cmp dword ptr [ebp-4], 0
        je done_empty
        
    main_loop:
        jmp check_node_loop
        
    process_entry:
        // Call callback(key, value, extraArg)
        push dword ptr [ebp+0x0C]   // extraArg (param_2)
        push dword ptr [esi+4]      // node[1] = value
        push dword ptr [esi]        // node[0] = key
        call dword ptr [ebp+0x08]   // callback (param_1)
        add esp, 12
        
        test al, 1
        jnz found_and_return
        
        // Advance to next node in chain
        mov esi, dword ptr [esi+0x0C]  // node[3] = next
        inc edi                         // iVar3++
        
    check_node_loop:
        cmp esi, 0                 // if current node is null
        jne process_entry
        
        // Check if we have a bucket array to scan
        cmp dword ptr [ebp-8], 0
        je check_outer_end
        
        // Scan for next non-empty bucket
        mov ebx, dword ptr [ebp-0x0C]  // local_8 = bucket index
    scan_buckets:
        mov edx, dword ptr [ebp-8]
        mov eax, dword ptr [edx+4]     // bucketHeader[1] = bucket count
        cmp ebx, eax
        jae bucket_scan_done
        
        mov eax, dword ptr [edx]       // bucketHeader[0] = bucket array pointer
        mov esi, dword ptr [eax + ebx*4]  // load head pointer for this bucket
        inc ebx
        
        cmp esi, 0
        je scan_buckets                 // skip empty buckets
        
        mov dword ptr [ebp-0x0C], ebx    // save updated bucket index
        jmp process_entry               // process first entry from this bucket
        
    bucket_scan_done:
    check_outer_end:
        cmp esi, 0
        jne main_loop
        
    done_empty:
        mov eax, -1
        jmp exit
        
    found_and_return:
        mov eax, edi
        
    exit:
        pop edi
        pop esi
        pop ebx
        pop ecx
        pop ebp
        ret 8
    }
}

// Note: Due to x86 __thiscall convention and the decompiled code's use of in_EAX,
// actual implementation is assembly; the C++ signature is provided for documentation.
// Parameters:
//   - callback: function pointer called as (*callback)(key, value, extraArg)
//   - extraArg: custom data passed through to callback
// Returns:
//   - Index (from 0) of entry where callback returned odd, or -1 if none matched
// Structure details are reverse-engineered approximations.