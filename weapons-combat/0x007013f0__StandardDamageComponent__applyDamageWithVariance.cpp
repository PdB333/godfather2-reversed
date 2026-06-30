// FUNC_NAME: StandardDamageComponent::applyDamageWithVariance

// Function address: 0x007013f0
// Applies damage with random variance if the component is in a vulnerable state.
// The vulnerability state is stored at +0x2DC, and if it is 3 or 4, the incoming damage
// is multiplied by a random factor (1–4). The resulting damage is stored at +0x384,
// and then, if a flag at +0x2D0 is set, a damage notification callback is triggered
// using the delegate stored at +0x334.

void __thiscall StandardDamageComponent::applyDamageWithVariance(int incomingDamage)
{
  uint randomFactor;
  int finalDamage;

  // Check if vulnerability state indicates weak/vulnerable (state 3 or 4)
  if ((this->vulnerabilityState - 3) < 2) {
    randomFactor = rand() & 3;       // random 0–3
    incomingDamage *= (randomFactor + 1);  // multiply by 1–4
  }

  // Store the final damage value (offset 0x384)
  this->damageValue = incomingDamage;

  // If there are listeners registered, notify them
  if (this->hasListeners != 0) {
    this->notifyDamageListeners(this->eventDelegate, 0);
  }
}