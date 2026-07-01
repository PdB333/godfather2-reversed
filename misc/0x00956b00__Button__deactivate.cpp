// FUNC_NAME: Button::deactivate
// Address: 0x00956b00
// Sets the button's active flag to false and calls engine function to deactivate the button UI element.

class Button {
public:
    void deactivate(); // __thiscall

private:
    // +0x7c: bool m_isActive; // 0 = inactive, 1 = active
};

// Global engine function to deactivate a button (likely from UI system)
// Parameters: name string, unknown int, some data pointer, count, pointer to button ID
void deactivateButton(const char* name, int arg2, void* data, int count, uint32_t* buttonId);

void Button::deactivate() {
    // Set active flag to false
    *(uint8_t*)(this + 0x7c) = 0;

    // Construct button ID from high 16 bits of this pointer and 0x30 (ASCII '0')
    uint32_t buttonId = ((uint32_t)this >> 16) << 16 | 0x30;

    // Call engine function to deactivate the button
    deactivateButton("DeactivateButton", 0, (void*)0x00d8c174, 1, &buttonId);
}