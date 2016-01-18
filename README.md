# GLSL Preview

GLSL Preview is a tool which helps developing OpenGL Shaders.

## Project Setup

Clone the project and its submodules using `git clone --recursive
git@bitbucket.org:j-bieser/glsl-preview.git`. If you already cloned the
repository you can use `git submodule update --init` to get the submodule.

Also make sure to install the
[FreeImage](http://freeimage.sourceforge.net/download.html) library somewhere on
your PATH (e.g. OSX: `brew install freeimage`). If you install it somewhere else
or for some reason Qt-Creator cannot find the library you have to edit
`glsl-preview-app.pro`.

```
# Add Include Path
INCLUDEPATH += /path/to/freeimage/include

# Add Library Directory
LIBS += -L/path/to/freeimage/lib
```

This project uses FreeImage version 3.17.0.

## Compile & Run

1. [Download and install Qt](http://www.qt.io/download-open-source/) including
Qt-Creator.
2. Open `glsl-preview-app.pro` inside of Qt-Creator
3. Click 'Run'
