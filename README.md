# SnakeGame
Created a simple snake game in C++
https://www.youtube.com/watch?v=06_knpwTPLE
- Had 3 functions that would run inside a loop until game was over
- these 3 functions handled drawing the grid, updating the snake position and updating the snake direction
    - Global variables included snakeX, snakeY, candyX, candyY and snakeDirection
    - Elements of the grid, snake and candy are drawn if their positions were the same as column and row
    - Can control the speed of the game using the nanosleep function
    - If snake eats candy then tail grows by one
- There were some edge cases, such as what happens if the snake hits the side of the grid → I made it the same as the traditional snake game where it would appear on the other side.
- Game is over when snake eats its own tail
