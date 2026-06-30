// FUNC_NAME: MsgSystem::sendMessage
// Address: 0x004c40b0
// Builds a message structure and dispatches it via a virtual function.
// The structure contains a type (2), subtype (3), and optional extra fields (4 and 1) when flag bit 0 is set.
// vtable accessed at offset -4 from this pointer (unusual layout, possibly a compiler artifact or base class offset).

void __thiscall MsgSystem::sendMessage(int thisPtr, int targetObj, int unusedParam, byte flag, int data1, int data2)
{
    struct {
        int type;        // +0x00
        int arg1;        // +0x04  (data1)
        int subtype;     // +0x08
        int arg2;        // +0x0C  (data2)
        int flags;       // +0x10
        int extraType;   // +0x14  (only used if flag & 1)
        int extraFlag;   // +0x18  (only used if flag & 1)
    } msg;

    msg.type = 2;
    msg.arg1 = data1;
    msg.subtype = 3;
    msg.arg2 = data2;
    msg.flags = 0;

    if ((flag & 1) != 0) {
        msg.extraType = 4;
        msg.extraFlag = 1;
        // Virtual call: vtable pointer at (thisPtr - 4)
        (*(code (**)(void))**(int **)(thisPtr - 4))(targetObj, &msg.extraType);
    }
    else {
        (*(code (**)(void))**(int **)(thisPtr - 4))(targetObj, &msg.type);
    }
}