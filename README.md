# Endeavor

<p> Endeavor is a <strong> very </strong> simple game framework. Endeavor provides window management, input handling, and 2D rendering via geometry batching.

## Dependencies

- OpenGL 3.3 or greater
- CMake 3.25.1 or greater

## Usage

- Add the repository <strong> recursively </strong> as a submodule to your game project. Endeavor depends on submodules included in /endeavor/vendor

- Add the new subdirectory to your project through CMake.

- Link with the generated static library through CMake.

I recommend viewing [endeavor-pong](https://github.com/lukeburton00/endeavor-pong) to see the majority of Endeavor's features in a basic working example.
