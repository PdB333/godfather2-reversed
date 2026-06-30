// FUNC_NAME: Version::parseVersionString
bool __thiscall Version::parseVersionString(int *this, short *data)
{
    int index = 0;
    int num1 = parseNextInt(data, &index);
    short currentChar = *(short *)(data + index * 2);
    if ((currentChar != 0x2e) && (currentChar != 0x2c)) {
        return false;
    }
    index++;
    int num2 = parseNextInt(data, &index);
    currentChar = *(short *)(data + index * 2);
    if ((currentChar == 0x2e) || (currentChar == 0x2c)) {
        index++;
        int num3 = parseNextInt(data, &index);
        currentChar = *(short *)(data + index * 2);
        if ((currentChar == 0x2e) || (currentChar == 0x2c)) {
            index++;
            int num4 = parseNextInt(data, &index);
            if ((num1 >= 0) && (num2 >= 0) && (num3 >= 0) && (num4 >= 0)) {
                // Store parsed version numbers into this struct
                this[2] = num3;  // +8
                this[0] = num1;  // +0
                this[3] = num4;  // +12
                this[1] = num2;  // +4
                return true;
            }
        }
    }
    return false;
}