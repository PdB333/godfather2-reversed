// FUNC_NAME: NameChecksum::xorChecksum

byte __thiscall NameChecksum::xorChecksum(int extraInput) {
    char firstChar;
    byte result = 0;
    int i = 0;

    if (this->count > 0) {
        do {
            firstChar = this->namePointers[i][0]; // first character of each string
            byte xorVal;
            if (firstChar < '\n') {
                // Use function table indexed by character (0-9 only)
                xorVal = (*(code*)PTR_FUN_0103af90[firstChar])(extraInput);
            } else {
                xorVal = 0;
            }
            result ^= xorVal;
            i++;
        } while (i < this->count);
    }
    return result;
}