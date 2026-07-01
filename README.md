# The Godfather 2 - Reversed Source Code

Automated reverse engineering of **The Godfather 2** (2008, EA EARS engine, x86) using Ghidra exports + DeepSeek V4 Flash API.

## Status

- **~28,900 / 33,500 functions** reversed so far
- ~4,600 functions still remaining
- **747 functions have real, verified names** from the Xbox 360 debug build's PDB symbols, cross-matched to the PC binary via a global one-to-one string-reference matcher (no LLM involved in this step — see [Known issues](#known-issues) for methodology)
- The rest are **AI-guessed** and may be inaccurate — they are based on code structure analysis, not debug symbols
- Names that were obvious AI "I don't know" tells (`SomeClass`, `UnknownClass`, `emptyFunction`, etc.) have been demoted back to `FUN_<addr>` instead of kept as false-confidence names
- Empty stubs and very small functions may have generic names

## Structure

```
reversed-src/
  ai-npc/           - NPC AI, pathfinding, combat perception, cover system
  animation/         - Skeletal animation, state machines, blending
  audio/             - Audio managers, streaming, sound banks
  camera/            - Chase camera, collision camera, camera blending
  debug/             - Debug menus, gameplay logging
  effects/           - Particle emitters, decals, visual effects
  engine-core/       - EARS engine internals, base classes, utilities
  entities/          - Entity system, game objects, components
  family-crime/      - Family management, crime, buildings, missions, Don control
  input/             - Controller input, XInput, device management
  math/              - Vector/matrix math, quaternions, transforms
  memory-containers/ - Memory pools, allocators, hash tables, arrays, linked lists
  missions/          - Mission scripting, script VM, action manager
  networking/        - TNL networking, ghost replication, packets, BitStream
  online/            - Online services, XmlRpc
  physics/           - Havok physics integration
  player/            - Player state machines, actions, grapple, wall cover
  rendering/         - Shaders, textures, lighting, mob face system
  simulation/        - Sim manager, event scheduling, multiplayer scenarios
  streaming-io/      - Stream readers/writers, buffers
  ui/                - UI/HUD, minimap, Apt (Flash UI), fonts, dialog trees
  vehicles/          - Vehicle physics, AI driving, damage, traffic
  weapons-combat/    - Guns, throwables, damage, targeting, ragdoll
  misc/              - Uncategorized functions
  unidentified/      - Functions without identified class names
```

## How it was made

1. **Ghidra** exported 33,500 PC functions and 90,792 Xbox 360 functions as JSON (decompiled code, call graph, string/data refs), the Xbox side loaded with its original PDB
2. **DeepSeek V4 Flash** API reconstructed C++ with best-guess names (~$0.0009/function, 50 parallel workers) — these names are **unverified**
3. A separate, LLM-free matcher (`match_xbox_pc_v3.py`) cross-references PC and Xbox functions by shared string literals, using IDF-style rarity weighting, a function-size sanity ratio, and a **global one-to-one greedy assignment** (no PC/Xbox function can be claimed by more than one match) to produce verified real names from the Xbox PDB
4. Functions organized into categories by class name pattern matching

## Known issues

- **Most names are still AI-guessed and unverified** — only 747 functions currently carry a real name confirmed against the Xbox PDB (marked with a `// Xbox PDB: ...` comment at the top of the file). Everything else is a plausible-looking guess, not ground truth
- **~4,600 functions missing** — reversal pipeline is still running
- **Some duplicates exist** where the AI gave the same or different names to unrelated functions (e.g. many `SomeClass::constructor`-style collisions) — this is a known limitation of the unverified AI-guessed names, not of the Xbox-verified ones
- **misc/** and **unidentified/** contain functions that didn't fit any category or have no class name at all
- Code quality varies — large complex functions are better reconstructed than small stubs
- An earlier Xbox-matching pass (v2) used a flawed per-function independent best-match algorithm that produced wrong matches due to no global validation; it was reverted and replaced by the current v3 one-to-one matcher

## Tools

- [`batch_codex.py`](../batch_codex.py) — Batch RE pipeline (DeepSeek API, 50 parallel workers)
- [`xbox_symbol_matcher.py`](../xbox_symbol_matcher.py) — Offline Xbox .map symbol matcher
- [`build_symbol_dict.py`](../build_symbol_dict.py) — Xbox symbol dictionary builder
- [`organize_code.py`](../organize_code.py) — File organizer into gameplay categories

## Contributing

If you have access to more debug information, better symbol maps, or want to improve the function names, PRs are welcome. The pipeline can be re-run on any function by deleting its entry from the progress file.

## Credits

- Reversed using [DeepSeek](https://deepseek.com/) V4 Flash API
- Ghidra for decompilation
- Xbox debug .map symbols from the debug build
