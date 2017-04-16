# GS_CO_FirstOpenGLProject
This is a repository for an old college project in which I try to do something with OpenGL for the first time, don't be too harsh about it hehe. If you want to run it, the .exe inside the .zip in the releases tab in GitHub should work in Windows, please feel free to ask me if it doesn't.

## Gameplay
I implemented a very simple FPS with some frogs that hunt you down inside a box-like environment. The controlls used are:

- **WASD**: Movement, as always.
- **Mouse**: Shooting, as always.
- **R**: Reload, you guessed it.
- **P**: Pause and see the scene from the top of the map, this one was not that easy huh :P


## Some Notes

**Be careful with the sound**, It is pretty high by default.

The music used is from Charlie Parra del Riego making a version of the OST of Duke Nukem Forever: https://www.youtube.com/watch?v=NkHeLRds1k4

#### Technical notes
The things done gameplay-wise are not as much designed to be enjoyable but for me to learn how to do some game programming in terms of sound, graphics, collisions, physics, etc.

For example, there are boxes to learn how to do box collisions while the frogs have a sphere collider, everything collides with everything and the balls bounce with a gravity value (hence the astronaut frogs mode).

The shooting is done with raycasting and the whole camera movement is done with a pretty getto solution moving the pointer to the center of the screen is each frame and calculating how much should we move the camera based on its distance travelled.

The hud and the different types of light are there to learn how OpenGl works with that. As is pretty much every line of code.


## Some Images

This is the view of the whole map when paused.
![Paused](http://)

This is a capture of gameplay where you shoot the frogs (and you read those awesome bullet sounds).
![Gameplay](http://)

If the frogs hit you enough you might die.
![Dead](http://)