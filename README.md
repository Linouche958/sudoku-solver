# Sudoku Solver


```sh
cc -O3 -o sudoku main.c sudoku_gui.c sudoku_reader.c sudoku_solver.c \
  $(pkg-config --cflags --libs sdl2 SDL2_ttf)
```


