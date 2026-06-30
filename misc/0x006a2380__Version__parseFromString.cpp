// FUNC_NAME: Version::parseFromString
int __thiscall Version::parseFromString(int* this, int str)
{
    int index = 0;
    int num1 = FUN_006a2310(str, &index);
    short ch = *(short*)(str + index * 2);
    if ((ch != 0x2e) && (ch != 0x2c)) {
        return 0;
    }
    index++;
    int num2 = FUN_006a2310(str, &index);
    ch = *(short*)(str + index * 2);
    if ((ch == 0x2e) || (ch == 0x2c)) {
        index++;
        int num3 = FUN_006a2310(str, &index);
        ch = *(short*)(str + index * 2);
        if ((ch == 0x2e) || (ch == 0x2c)) {
            index++;
            int num4 = FUN_006a2310(str, &index);
            if ((-1 < num1) && (((-1 < num2 && (-1 < num3)) && (-1 < num4)))) {
                this[2] = num3;
                *this = num1;
                this[3] = num4;
                this[1] = num2;
                return 1;
            }
        }
    }
    return 0;
}