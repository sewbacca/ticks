
# Ticks

Ticks is an attempt for a [TickOaTTwo](https://www.youtube.com/watch?v=ePxrVU4M9uA) Engine.
Was created over night, born out of curiosity if the game is much more difficult than Tic Tac Toe or
if it is at the same level, or even worse.

Feel free to try it for yourself.
The commands are:
```
<number> -> put item on corresponding field (matching keyboard numpad layout)
undo / u -> undo last move
engine / e -> execute engine move
```

Building:
Requires CMake, run

`git clone https://github.com/sewbacca/ticks`

`cd ticks`

`cmake -Bbuild`

`cmake --build build`

Windows:
`.\build\ticks.exe`

Linux:
`./build/ticks` (?)