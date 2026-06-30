# The Godfather 2 - Reversed Source Code

Automated reverse engineering of **The Godfather 2** (2008, EA EARS engine, x86) using Ghidra exports + DeepSeek V4 Flash API.

## Status

- **~19,600 / 33,500 functions** reversed so far
- ~14,000 functions still remaining
- Function/class names are **AI-guessed** and may be inaccurate — they are based on code structure analysis, not debug symbols
- Some functions matched against Xbox debug symbols (.map file with 127k real C++ names), but most names are approximations
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

1. **Ghidra** exported 33,500 functions as JSON (decompiled code, call graph, data refs)
2. **DeepSeek V4 Flash** API reconstructed C++ with meaningful names (~$0.0009/function, 50 parallel workers)
3. **Xbox debug .map** file (127k symbols) provided real class names injected into the AI prompt
4. Functions organized into categories by class name pattern matching

## Known issues

- **Names are not accurate** — most function and class names are guesses by the AI based on code patterns. Real names from the Xbox debug build were used as hints but could not be directly matched to PC addresses (different architectures)
- **~14,000 functions missing** — API budget ran out before completing all functions
- **Some duplicates** may exist where the AI gave different names to related functions
- **misc/** contains ~8,700 files from classes that didn't fit any category
- Code quality varies — large complex functions are better reconstructed than small stubs

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
