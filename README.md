# miniRT

*This project has been created as part of the 42 curriculum by aoperacz and yamohamm.*

## Description

**miniRT** is our first RayTracer, written in C using the MiniLibX graphics library. The goal of this project is to generate and render 3D computer-generated images using the Raytracing protocol. By simulating the physical behavior of light rays intersecting with mathematical primitives, this program renders a realistic representation of a scene configured via a simple `.rt` file.

This project challenged us to implement 3D mathematics, vector geometry, and a rendering architecture from scratch without relying on modern graphical engines. It includes a robust parsing engine, camera view calculations, and lighting computations to render scenes accurately.

### Capabilities (Mandatory)
- **Primitives**: Supports Planes, Spheres, and Cylinders.
- **Transformations**: Objects, lights, and cameras can be translated and rotated in 3D space.
- **Lighting & Shadows**: Implements Ambient and Diffuse lighting. Features hard shadow calculation for a single light source.
- **Window Management**: Smooth window management using MiniLibX.

## Instructions

### Compilation
To compile the project, run the provided Makefile from the root of the repository:
```bash
make
```
*(Note: This will automatically compile the required libft and link the MinilibX library using the -Wall -Wextra -Werror flags).*

### Execution
Run the executable by passing a valid scene configuration file (.rt extension) as the first argument:
```bash
./miniRT path/to/scene.rt
```

### Controls
- **Exit**: Press the ESC key or click the window's red cross to cleanly close the program and free all allocated memory.

## Resources

During the development of this project, the following resources were consulted to grasp the core mathematical and architectural concepts:

- **Ray Tracing in One Weekend** (Peter Shirley): Essential foundational knowledge for ray generation, vector math, and camera setup.
- **Scratchapixel**: Referenced for deriving the quadratic equations used in sphere and cylinder intersections.
- **MiniLibX Documentation**: Used for understanding window hooks, image buffer manipulation, and pixel pushing.

## AI Usage Declaration

AI tools (Large Language Models) were utilized during the development of this project in the following ways to assist with learning and debugging:

- Generating scene files
- Explaining certain concepts
- Troubleshooting
- General roadmap of the project

**Documentation**: Used to draft and format this README file according to the subject's required structure.

*No AI-generated code was included without full comprehension and manual peer review.*