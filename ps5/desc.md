# Interactive Ball and Walls Program

## How to use the program:

1. Run the program to open a window with colored walls and a moving ball.
2. Use the arrow keys to move the ball:
   - Up arrow: Move the ball up
   - Down arrow: Move the ball down
   - Left arrow: Move the ball left
   - Right arrow: Move the ball right
3. The ball changes color when it hits a wall, taking on the color of that wall.
4. When the ball hits a corner, it blends the colors of the two walls that form that corner.
5. Press the ESC key to exit the program.

## Features used to satisfy requirements:

1. **OpenGL animation using double-buffering:**
   - The program uses `FsSwapBuffers()` for smooth animation.

2. **Animation loop:**
   - The main game loop runs continuously until the ESC key is pressed.

3. **Interactive program:**
   - The user can control the ball's movement using arrow keys.

4. **OpenGL feature - Color gradation:**
   - The ball displays a solid color when it hits a wall.
   - When the ball hits a corner, it shows a smooth color gradient between the colors of the two walls that form that corner.
   - This is achieved using `glShadeModel(GL_SMOOTH)` and varying colors in `GL_TRIANGLE_FAN`.

5. **Multiple OpenGL primitives:**
   - `GL_QUADS`: Used to draw the walls.
   - `GL_TRIANGLE_FAN`: Used to draw the ball with color gradation.

6. **Math library function:**
   - The program uses `cos()` and `sin()` functions from the math library to draw the circular ball.
