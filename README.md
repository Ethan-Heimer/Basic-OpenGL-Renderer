# A Basic JSON-OpenGL Renderer

## Build

```
git clone https://github.com/Ethan-Heimer/Basic-OpenGL-Renderer ./Renderer
cd Renderer
mkdir build
cd build
cmake ..
make
```

## About 
This is a very simple renderer using OpenGL. It Reads data from `data.json` and displays it on screen.

## data.json
### structure
The structure is very simple. Each object to be renderered is stored in the `"objects"` array.
Each Object the contains the following data:
- `"vertex"` defines what vertex shader to use when rendering the object.
- `"fragment"` defines what fragment shader to use when rendering the object.
- `"verts"` defines the verticies of the object
- `"indicies"` defines the list of indicies the object will use
- `"colors"` defines the color at each vertex of the object

## Shaders
You can program and use your own shaders. Shaders must be placed into the `shaders/` directory.
The renderer defines the `frame` uniform for shaders to use, which is simply a float of the count of frames that have been rendered.
