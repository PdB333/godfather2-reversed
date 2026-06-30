// FUNC_NAME: Accumulator::applyUpdates
// Function at 0x00626fd0: Repeatedly applies a delta amount to an accumulated value, controlled by a count field.
// Uses esi as 'this', typical __thiscall member function.
// Fields:
//   this+0x10: pointer to Data struct with:
//     +0x04: m_value (int)
//     +0x08: m_count (int)

class Accumulator {
public:
    void applyUpdates() {
        Data* data = reinterpret_cast<Data*>(this->m_pData); // offset 0x10
        int count = data->m_count;                          // +0x08
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                int delta = getDelta();                     // call to FUN_00626f80
                data->m_value -= delta;                     // +0x04
            }
        }
    }

private:
    // Other fields omitted; m_pData is at offset 0x10
    void* m_pData;                                          // +0x10

    struct Data {
        int m_value;                                        // +0x04
        int m_count;                                        // +0x08
    };

    // Static helper function (corresponds to FUN_00626f80)
    static int getDelta();
};
// Note: The actual implementation of getDelta() is separate (at 0x00626f80) and returns a constant or computed value.