// FUNC_NAME: RagdollComponent::updateRagdollPose

// Function address: 0x006db310
// Role: Updates the ragdoll pose for a character. Retrieves a embedded component pointer (at +0xe8),
// uses it to calculate the parent controller (offset -0x48), then calls virtual functions for
// pose application. Finally, stores the resulting transform and additional data.

class RagdollComponent {
public:
    // Offset +0x10: World transform matrix (4x4, 16 floats)
    Matrix4x4 m_worldTransform;

    // Offset +0xe8: Pointer to an embedded component (e.g., HavokRagdoll sub-object)
    HavokRagdollComponent* m_pComponent;

    // Offset +0xf0: Bitfield flags (only lowest bit kept)
    uint32_t m_flags;

    // Offset +0x190: Pointer to the world transform (set to &m_worldTransform)
    Matrix4x4* m_pTransformPointer;

    // Offsets +0x194, +0x198, +0x19c: Additional rotation/quaternion data
    // (likely derived from the Havok finalizePose call)
    float m_rotationX;
    float m_rotationY;
    float m_rotationZ;

    // Virtual method table offsets for the parent controller class:
    // 0x94: setTransform(Flags*, Matrix4x4*)
    // 0x9c: canApplyPose() -> bool
    // 0xa4: finalizePose(Matrix4x4*, Flags*)

    void __fastcall updateRagdollPose() {
        // Derive the parent controller from the embedded component pointer
        HavokRagdollController* controller = nullptr;
        if (m_pComponent != nullptr) {
            // The component is embedded at offset 0x48 in its parent (controller)
            controller = (HavokRagdollController*)((char*)m_pComponent - 0x48);
        }

        // Keep only the lowest bit (possibly a dirty or enabled flag)
        m_flags = m_flags & 1;

        if (controller != nullptr) {
            // Check if the controller is ready to apply the pose
            if (controller->canApplyPose()) {
                // Prepare transform data and finalize pose via virtual calls
                controller->setTransform(&m_flags, &m_worldTransform);

                // The finalizePose virtual takes a local temporary matrix and flags.
                // The local matrix is allocated on the stack (address &stack0xffffffe8 in disassembly).
                Matrix4x4 localMatrix;
                controller->finalizePose(&localMatrix, &m_flags);

                // Store the resulting transform pointer and additional rotation data.
                // The rotation values come from caller's registers (unaff_EBP, unaff_EDI) and a global.
                m_pTransformPointer = &m_worldTransform;
                m_rotationX = /* unaff_EBP */;   // Unknown value from caller context
                m_rotationY = /* unaff_EDI */;   // Unknown value from caller context
                m_rotationZ = _DAT_00d5780c;     // Global constant
            }
        }
    }
};