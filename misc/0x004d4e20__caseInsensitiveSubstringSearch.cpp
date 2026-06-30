// FUNC_NAME: caseInsensitiveSubstringSearch
char* __thiscall caseInsensitiveSubstringSearch(char* subStr, char* str)
{
    char cVar1;
    char* pcVar2;
    int iVar3;
    int iVar4;
    int iVar5;

    if (*str != '\0') {
        iVar5 = (int)str - (int)subStr;
        cVar1 = *subStr;
        pcVar2 = subStr;
joined_r0x004d4e3e:
        do {
            if (cVar1 != '\0') {
                iVar3 = (int)pcVar2[iVar5];
                if (iVar3 - 0x41U < 0x1a) {
                    iVar3 = iVar3 + 0x20;
                }
                iVar4 = (int)cVar1;
                if (iVar4 - 0x41U < 0x1a) {
                    iVar4 = iVar4 + 0x20;
                }
                if (iVar3 == iVar4) {
                    if (pcVar2[1] == '\0') {
                        return str;
                    }
                    cVar1 = pcVar2[1];
                    pcVar2 = pcVar2 + 1;
                    goto joined_r0x004d4e3e;
                }
            }
            str = str + 1;
            iVar5 = iVar5 + 1;
            cVar1 = *subStr;
            pcVar2 = subStr;
        } while (*str != '\0');
    }
    return (char *)0x0;
}