# cub3d - A Raycasting Game Engine

*This project was developed as part of the Ecole 42 curriculum in collaboration with [Joonatan Aurasmaa](https://github.com/Jaurasma).*

## Overview

`cub3d` is a project at Ecole 42 inspired by the iconic Wolfenstein 3D. This project focuses on creating a game engine that will utilize raycasting to create a 3D maze in a 2D environment. The player is then able to navigate within this area.

<img src="imgs/irssi.png" width="80%" align="center">

## Description

The `cub3d` project is a challenging graphics programming exercise. The main lessons learned from the projects:

- **Graphics Programming in C**: Utilizing only a very barebones graphics library (opening a window and coloring pixels).
- **Texture Rendering**: Reading texture files that are then rendered to make the game more immersive.
- **Raycasting Algorithms**: Creating a fast running algorithm to update graphics information.
- **Game Engine Development**: Creating a simple, smooth and robust engine to handle the parsing, algoritms, rendering and gameplay loop.
- **Soft Skills and Teamwork**: Breaking the subjest into smaller tasks, dividing them, communicating and merging code.
- **Error Handling**: Figuring out all the edge cases and making the program as foolproof as possible.

## Screenshots

A few screenshots of the game running.


### How it works


<img src="imgs/server_client_setup.png" width="80%" align="center">
<img src="imgs/polling_loop.png" width="80%" align="center">
<img src="imgs/message_forwarding.png" width="80%" align="center">

## Prerequisites

To run `cub3d`, you are going to need the `Minilibx` library.

If you are a 42 student, this should already be on your Mac. If not, please download the library and add the path to Makefile & cub3d.h.

## Installation

```bash
git clone https://github.com/tikanoja/cub3D cub3d && cd cub3d && make
```

## Usage

Cd to the installation location and execute with the path to the .cub file as an argument.

```bash
./cub3d maps/classic42.cub
```

## Helpful Resources

If you wish to start a similar project, I would highly recommend [Lode's Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html), [3DSage's video series](https://www.youtube.com/watch?v=gYRrGTC7GtA&t=880s), [javidx9's tutorial on DDA](https://www.youtube.com/watch?v=NbSee-XM7WA&t=371s), and to get familiar with MLX: [MLX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
