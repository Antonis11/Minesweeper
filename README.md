## 🎮 Start of the Game

At the beginning of the game, the user selects:
- The **board dimensions**
- The **difficulty level**

---

## 🧩 Board Representation

The board uses the following symbols:

| Symbol | Meaning                           |
|--------|-----------------------------------|
| `@`    | Mine                              |
| `#`    | Closed square                      |
| `1-8`  | Number of adjacent mines          |
| `.`    | Open empty square  |

This representation helps the player navigate the board and avoid the mines.

## 🎮 Playing the Game

Players interact with the game using the following commands:

- `open(x,y)`  
  Opens the square at row `x`, column `y`.  
  - If the square is already open, an error message is shown.
  - If the square contains a mine, the game ends.
  - If the square is safe, it is revealed —  
    **if it's empty (no adjacent mines), recursive opening occurs**  
    *(see [🔁 Recursive Opening](#-recursive-opening))*.
  - The **first opened square is always safe** (no mine).

- `mark(x,y)`  
  Marks the square at `(x,y)` as a suspected mine.  
  - Uses the `@` symbol.
  - Has no effect on the actual game logic (just for player reference).
  - Marking an already open square triggers an error.

- `cheat(x,y)`  
  Reveals the content of the square at `(x,y)` without opening it:  
  - Mine, number of adjacent mines, or empty.

- `exit`  
  Ends the game.

> ⚠️ Invalid commands or incorrect formats show an error and prompt the player to try again.

## 🔁 Recursive Opening

If a player opens a square with no adjacent mines (i.e. it's empty), the game **automatically reveals all neighboring squares**.  
This continues recursively until all connected empty squares and their borders (with numbers) are uncovered.

This improves gameplay and avoids unnecessary manual input.

## 🗺️ Levels & Board Reset

When the player successfully opens all non-mine squares, the game automatically advances to the **next level** with:

- The **same difficulty**,  
- A board enlarged by **+5 rows and +5 columns**,  
- Mines recalculated based on the new size and difficulty.

If the player reaches the **maximum board size**, the game ends — a tribute to their veteran Minesweeper skills. 😄

