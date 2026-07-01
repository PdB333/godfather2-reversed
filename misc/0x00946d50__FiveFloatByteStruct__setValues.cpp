// FUNC_NAME: FiveFloatByteStruct::setValues
class FiveFloatByteStruct {
public:
    // +0x08: float data[5] (20 bytes)
    // +0x1c: char flag

    void __thiscall setValues(const float* fiveFloats, char flag) {
        this->data[0] = fiveFloats[0];
        this->data[1] = fiveFloats[1];
        this->data[2] = fiveFloats[2];
        this->data[3] = fiveFloats[3];
        this->data[4] = fiveFloats[4];
        this->flag = flag;
    }

private:
    float data[5];  // offset 0x08
    char flag;      // offset 0x1c
};