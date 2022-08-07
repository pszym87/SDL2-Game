## Introduction

PacMario is a 2D game inspired by the popular retro games: Pacman and Mario. General logic of the game is derived from the first one whereas graphics are borrowed from the Mario Game. Project is **coded in the C programming language**. Uses the SDL graphic library. Opponent’s moves are generated by finding the **shortest path between nodes in a graph**.

![mario](https://user-images.githubusercontent.com/106841261/181225128-b5755c44-77e2-403f-ad82-f4cd91a61136.gif)

## Code structure

Graphical module was separated from the logic in the code. As a result code gained substantial flexibility (e.g. implementing a new graphical engine would be a fairly easy task). 

Graphics and logics are glued back together in the control module. It performs as an intermediate layer whose main responsibilities are: initialization of modules, keyboard events handling, communication between logic and graphics, and lastly final clean up. 

**Module division per file**

1. graphics: ‘gfx.c’
2. logics: ‘logic.c’ ‘adj.c’
3. control: ‘main.c’ ‘ctrl.c’

## Move generation

Two of the three computer players are “dummies” - their moves are generated by random function. The function creates *linked list* of permissible moves for the current figure position. The next move is drawn from this list.  

The logic behind the third player’s moves is a bit more advanced. Its moves are optimal in any given situation due to the implementation of the **Dijkstra Algorithm**. To achieve this a few transformations were needed. 

### Game map transformations

The map of the game is coded as a *two-dimensional matrix*. In the first transformation it is converted to the *undirected graph* with edges of equal cost. In the memory, the graph is stored as an *adjacency matrix*. A generated move is first stored as a graph node and then converted back to the index position of the two-dimensional matrix. 

**Example (4x4 map)**

The picture below subsequently shows: visual representation, two-dimensional matrix, undirected graph

![przeksztalcenia](https://user-images.githubusercontent.com/106841261/181225276-f597e357-9eca-4d4b-bff2-bbd0e0c18e1b.png)

## Dijkstra algorithm implementation

A slight modification of Dijkstra’s Algorithm was needed to find an **optimal move** for the third player. The original Dijkstra only holds information about the distance of the shortest path, not the nodes of the path itself. An *auxiliary array* was added to store predecessors for each node included in the shortest path in the graph.

## Configuration and compilation

The Game uses SDL2 graphical library. 

SDL2 project website: [https://www.libsdl.org/](https://www.libsdl.org/)

**Library sources**

Installation of the following libraries is required to compile and run the game:

- SDL2 ([https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php))

- SDL2 Image ([https://github.com/libsdl-org/SDL_image](https://github.com/libsdl-org/SDL_image))

- SDL2 TTF ([https://github.com/libsdl-org/SDL_ttf](https://github.com/libsdl-org/SDL_ttf))

### Compilation

Linking libraries in the linker is needed for SDL2, SDL2 Image, SDL2 TTF. Depending on the user’s operating system, it may be necessary to change paths in the #include declarations: SDL.h → SDL/SDL.h and SDL_image.h → SDL/SDL_image.h)

