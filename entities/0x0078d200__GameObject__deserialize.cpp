// FUNC_NAME: GameObject::deserialize
void __thiscall GameObject::deserialize(int thisPtr, int stream)
{
    char cVar1;
    int uVar2;
    int iVar3;

    // Begin stream reading (maybe initialize iterator)
    streamBeginRead(stream);
    // Read a version/integrity check (0x84bf4579 is likely a magic number)
    streamReadVersionOrMagic(stream, 0x84bf4579);
    cVar1 = streamEndReached(); // Check if stream is already at end

    do {
        if (cVar1 != '\0') {
            // If a global static buffer is available, copy large block into this+0x3c
            if (g_globalBuffer != 0) {
                memoryCopy(thisPtr + 0x3c, g_globalBuffer, 0x8000);
            }
            return;
        }

        // Advance to next element? (probably reads next type tag)
        streamAdvance();
        uVar2 = streamReadTypeCode(); // Get type identifier

        switch(uVar2) {
        case 1:
            iVar3 = streamReadObject(); // Read an object from stream
            *(int *)(thisPtr + 0x188) = *(int *)(iVar3 + 8); // Copy data member at +8
            break;
        case 2:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x170) = *(int *)(iVar3 + 8);
            break;
        case 3:
            streamReadObject();
            uVar2 = streamReadSomething(); // Additional data?
            streamAssignValue(thisPtr + 0x174, uVar2); // Write to +0x174
            break;
        case 4:
            iVar3 = thisPtr + 0x5c;
            goto LAB_0078d2aa;
        case 5:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x74) = *(int *)(iVar3 + 8);
            break;
        case 6:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x78) = *(int *)(iVar3 + 8);
            break;
        case 7:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x7c) = *(int *)(iVar3 + 8);
            break;
        case 8:
            iVar3 = thisPtr + 200;
            goto LAB_0078d2aa;
        case 9:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xe0) = *(int *)(iVar3 + 8);
            break;
        case 10:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xe4) = *(int *)(iVar3 + 8);
            break;
        case 0xb:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xe8) = *(int *)(iVar3 + 8);
            break;
        case 0xc:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xec) = *(int *)(iVar3 + 8);
            break;
        case 0xd:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xf0) = *(int *)(iVar3 + 8);
            break;
        case 0xe:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xf4) = *(int *)(iVar3 + 8);
            break;
        case 0xf:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xf8) = *(int *)(iVar3 + 8);
            break;
        case 0x10:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xfc) = *(int *)(iVar3 + 8);
            break;
        case 0x11:
            iVar3 = thisPtr + 0x80;
            goto LAB_0078d2aa;
        case 0x12:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x98) = *(int *)(iVar3 + 8);
            break;
        case 0x13:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x9c) = *(int *)(iVar3 + 8);
            break;
        case 0x14:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xa0) = *(int *)(iVar3 + 8);
            break;
        case 0x15:
            iVar3 = thisPtr + 0x100;
            goto LAB_0078d2aa;
        case 0x16:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x118) = *(int *)(iVar3 + 8);
            break;
        case 0x17:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x11c) = *(int *)(iVar3 + 8);
            break;
        case 0x18:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x120) = *(int *)(iVar3 + 8);
            break;
        case 0x19:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x124) = *(int *)(iVar3 + 8);
            break;
        case 0x1a:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x128) = *(int *)(iVar3 + 8);
            break;
        case 0x1b:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 300) = *(int *)(iVar3 + 8);
            break;
        case 0x1c:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x130) = *(int *)(iVar3 + 8);
            break;
        case 0x1d:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x134) = *(int *)(iVar3 + 8);
            break;
        case 0x1e:
            iVar3 = thisPtr + 0xa4;
            goto LAB_0078d2aa;
        case 0x1f:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xbc) = *(int *)(iVar3 + 8);
            break;
        case 0x20:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xc0) = *(int *)(iVar3 + 8);
            break;
        case 0x21:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0xc4) = *(int *)(iVar3 + 8);
            break;
        case 0x22:
            iVar3 = thisPtr + 0x138;
LAB_0078d2aa:
            streamReadObject(iVar3);  // Read data directly into member
            streamReadInto(iVar3);    // Possibly handle string/array
            break;
        case 0x23:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x150) = *(int *)(iVar3 + 8);
            break;
        case 0x24:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x154) = *(int *)(iVar3 + 8);
            break;
        case 0x25:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x158) = *(int *)(iVar3 + 8);
            break;
        case 0x26:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x15c) = *(int *)(iVar3 + 8);
            break;
        case 0x27:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x160) = *(int *)(iVar3 + 8);
            break;
        case 0x28:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x164) = *(int *)(iVar3 + 8);
            break;
        case 0x29:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x168) = *(int *)(iVar3 + 8);
            break;
        case 0x2a:
            iVar3 = streamReadObject();
            *(int *)(thisPtr + 0x16c) = *(int *)(iVar3 + 8);
        }
        streamEndElement(); // Move to next element
        cVar1 = streamEndReached();
    } while( true );
}