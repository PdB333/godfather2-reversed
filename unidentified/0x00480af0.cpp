// FUN_00480af0: PropertyStream::deserialize(ObjectPropertySet* pPropertySet)
void __thiscall PropertyStream::deserialize(int thisPtr, void* pStreamData)
{
    char local_64;
    int local_60;
    undefined4* local_5c;
    uint local_58;
    uint local_54;
    undefined4* local_50;
    short local_4c;
    undefined4 local_48;
    undefined4** local_8;
    
    // Initialize stream reader with hash identifiers
    FUN_0043aff0(pStreamData, 0xb390b11a);       // likely readUint32 for block begin
    FUN_0043af00(1);                              // set stream depth or flag
    FUN_0043aff0(pStreamData, 0x7b6c269);        // another block hash
    
    // Begin iteration over stream tokens
    ppuVar3 = local_8;
    do {
        // Check if stream end condition or iteration limit
        if (local_64 == '\0') {
            bVar6 = *ppuVar3 == (undefined4 *)0x0;
        }
        else {
            bVar6 = local_58 == local_54;
        }
        
        if (bVar6) {
            // Check if any properties are dirty and frame update needed
            if (((((*(int*)(thisPtr + 100) != 0) || (*(int*)(thisPtr + 0x68) != 0)) ||
                 (*(int*)(thisPtr + 0x6c) != 0)) || (*(int*)(thisPtr + 0x70) != 0)) &&
               ((*(byte*)(thisPtr + 0x74) & 1) != 0)) {
                FUN_00480d90();          // update or notify observers
            }
            return;
        }
        
        // Determine current token pointer based on iteration mode
        ppuVar4 = &local_50;
        if (local_64 == '\0') {
            ppuVar4 = ppuVar3;
        }
        
        // Extract token type from item
        if (*(short*)((int)ppuVar4 + 6) == 0x25e3) {
            puVar1 = (undefined4*)(uint)*(ushort*)(ppuVar4 + 1);
        }
        else {
            puVar1 = ppuVar4[1];
        }
        
        // Process token based on type
        switch((int)puVar1) {
        case 0: // Token type 0: set current property pointer
            ppuVar4 = &local_50;
            if (local_64 == '\0') {
                ppuVar4 = ppuVar3;
            }
            *(undefined4**)(thisPtr + 0x74) = ppuVar4[2]; // mCurrentProperty = token data
            break;
            
        case 1: // Token type 1: read string property into slot at +0x54
            ppuVar4 = &local_50;
            if (local_64 == '\0') {
                ppuVar4 = ppuVar3;
            }
            if (*(short*)((int)ppuVar4 + 6) == 0x25e3) {
                if (*ppuVar4 == (undefined4 *)0x0) {
                    ppuVar4 = (undefined4**)&DAT_00e2a89b;
                }
                else {
                    ppuVar4 = (undefined4**)((int)ppuVar4[2] + (int)*ppuVar4);
                }
            }
            else {
                ppuVar4 = ppuVar4 + 2;
            }
            piVar5 = (int*)(thisPtr + 0x54); // mStringPropertyA
            goto LAB_00480bba;
            
        case 2: // Token type 2: read string property into slot at +0x5c
            ppuVar4 = &local_50;
            if (local_64 == '\0') {
                ppuVar4 = ppuVar3;
            }
            if (*(short*)((int)ppuVar4 + 6) == 0x25e3) {
                if (*ppuVar4 == (undefined4 *)0x0) {
                    ppuVar4 = (undefined4**)&DAT_00e2a89b;
                    piVar5 = (int*)(thisPtr + 0x5c);
                }
                else {
                    ppuVar4 = (undefined4**)((int)ppuVar4[2] + (int)*ppuVar4);
                    piVar5 = (int*)(thisPtr + 0x5c);
                }
            }
            else {
                ppuVar4 = ppuVar4 + 2;
                piVar5 = (int*)(thisPtr + 0x5c); // mStringPropertyB
            }
            
LAB_00480bba:
            // Clear and initialize string property
            FUN_004086d0(piVar5);  // string destructor / clear
            FUN_00408310(piVar5);  // string constructor / init
            if ((ppuVar4 != (undefined4**)0x0) && (*(char*)ppuVar4 != '\0')) {
                uVar2 = FUN_004dafd0(ppuVar4); // string convert / read
                FUN_00408260(piVar5, uVar2);   // string assign
                if (*piVar5 != 0) {
                    FUN_00407e60(thisPtr + 0x3c, piVar5); // add to property list
                }
            }
            break;
            
        case 3: // Token type 3: handle extra pointer property
            FUN_0043ad10(thisPtr + 100); // clear or process extra data
            ppuVar3 = local_8;            // reset iterator
        }
        
        // Advance iterator based on mode
        if (local_64 == '\0') {
            if ((int)local_58 < 0) {
                local_8 = (undefined4**)((int)ppuVar3 + (int)*ppuVar3);
                FUN_0043b140();          // skip to next block
                ppuVar3 = local_8;
            }
            else if ((int)local_58 < (int)(local_54 - 1)) {
                local_58 = local_58 + 1;
                local_8 = (undefined4**)((int)ppuVar3 + (int)*ppuVar3);
                ppuVar3 = (undefined4**)((int)ppuVar3 + (int)*ppuVar3);
            }
            else {
                local_8 = (undefined4**)&DAT_01163cf8; // end marker
                ppuVar3 = (undefined4**)&DAT_01163cf8;
            }
        }
        else {
            local_58 = local_58 + 1;
            if (local_58 != local_54) {
                local_4c = (short)local_58;
                if ((*(byte*)((local_58 >> 3) + local_60) & (byte)(1 << ((byte)local_58 & 7))) == 0) {
                    local_48 = *local_5c;
                    local_50 = local_5c;
                    local_5c = local_5c + 1;
                }
                else {
                    local_50 = (undefined4 *)0x0;
                    local_48 = 0;
                }
            }
        }
    } while( true );
}