// FUNC_NAME: NetConnection::handleNotification
void __fastcall NetConnection::handleNotification(void *thisPtr)
{
    // Structure at this+8: PacketDescriptor
    struct PacketDescriptor {
        short unknown; // +0x0? Actually +2 means offset 2 from start of this descriptor.
        int objectId; // +0x04
        int eventType; // +0x08
    };
    PacketDescriptor *desc = *(PacketDescriptor **)((int)thisPtr + 8);
    if (desc->unknown != 0x0c) {
        // Fatal error if descriptor type is invalid (expected 0x0C)
        ((void (*)())(*(int *)(*(int *)0x01205590 + 4)))();
    }
    int *piVar2 = (int *)FUN_00599b70(thisPtr, desc->objectId);
    if (piVar2 != 0) {
        switch (desc->eventType) {
        case 0:
            // Direct notification: call virtual function at vtable+0x10
            ((void (*)())(*piVar2 + 0x10))();
            return;
        case 1:
        {
            // Queue notification with type 2
            byte *count = (byte *)((int)thisPtr + 0x9b);
            if (*count > 0x1f) {
                ((void (*)())(*(int *)(*(int *)0x01205590 + 4)))(); // Error: overflow
            }
            int *typeArray = (int *)((int)thisPtr + 0xbc);
            int **objArray = (int **)((int)thisPtr + 0xc0);
            typeArray[(int)*count] = 2;
            objArray[(int)*count] = piVar2;
            (*count)++;
            break;
        }
        case 2:
        {
            // Queue notification with type 1
            byte *count = (byte *)((int)thisPtr + 0x9b);
            if (*count > 0x1f) {
                ((void (*)())(*(int *)(*(int *)0x01205590 + 4)))(); // Error: overflow
            }
            int *typeArray = (int *)((int)thisPtr + 0xbc);
            int **objArray = (int **)((int)thisPtr + 0xc0);
            typeArray[(int)*count] = 1;
            objArray[(int)*count] = piVar2;
            (*count)++;
            return;
        }
        case 3:
            // Direct notification: call virtual function at vtable+0x14
            ((void (*)())(*piVar2 + 0x14))();
            return;
        case 4:
            // Direct notification: call virtual function at vtable+0x18
            ((void (*)())(*piVar2 + 0x18))();
            return;
        }
        return;
    }
    // Object lookup failed – trigger fatal error
    ((void (*)())(*(int *)(*(int *)0x01205590 + 4)))();
}