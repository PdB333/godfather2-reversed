// FUNC_NAME: getFlagStatus

extern int DAT_0120588b; // constant from .rdata (address 0x0120588b)

int __fastcall getFlagStatus(int thisPtr)
{
    // reads field at offset +0xC, returns -1 AND'd with mask if non-zero
    int status = -(*(int*)(thisPtr + 0xC) != 0);
    return status & DAT_0120588b;
}