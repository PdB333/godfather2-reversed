// FUNC_NAME: EARS::Framework::LinkedListNode::init
void __thiscall LinkedListNode::init()
{
    // +0x00: first data block (5 ints)
    this->dataBlock0.data0 = 0;   // +0x00
    this->dataBlock0.data1 = 0;   // +0x04
    this->dataBlock0.data2 = 0;   // +0x08
    this->dataBlock0.data3 = 0;   // +0x0C
    this->dataBlock0.data4 = 0;   // +0x10
    // +0x14: first self-referencing next pointer
    this->next0 = this;

    // +0x18: second data block (4 ints)
    this->dataBlock1.data5 = 0;   // +0x18
    this->dataBlock1.data6 = 0;   // +0x1C
    this->dataBlock1.data7 = 0;   // +0x20
    this->dataBlock1.data8 = 0;   // +0x24
    // +0x28: second self-referencing next pointer
    this->next1 = this;

    // +0x2C: third data block (4 ints)
    this->dataBlock2.data9 = 0;   // +0x2C
    this->dataBlock2.data10 = 0;  // +0x30
    this->dataBlock2.data11 = 0;  // +0x34
    this->dataBlock2.data12 = 0;  // +0x38
    // +0x3C: third self-referencing next pointer
    this->next2 = this;

    // +0x40: fourth data block (4 ints)
    this->dataBlock3.data13 = 0;  // +0x40
    this->dataBlock3.data14 = 0;  // +0x44
    this->dataBlock3.data15 = 0;  // +0x48
    this->dataBlock3.data16 = 0;  // +0x4C
    // +0x50: fourth self-referencing next pointer
    this->next3 = this;

    // +0x54: final data (1 int)
    this->data17 = 0;             // +0x54
}