# GLSL Preview

*GLSL Preview* is a [Qt](http://www.qt.io/)-based tool which helps
developing OpenGL Shaders. The original version (tag
`fh-project-release`) was developed as a student project at
[Fachhochschule Bingen](https://www.fh-bingen.de/).

## Project Setup

Clone the project and its submodules using the `--recursive` flag, or
run `git submodule update --init` after you cloned the repository.

Also make sure to install the
[FreeImage](http://freeimage.sourceforge.net/download.html) library
somewhere on your PATH (e.g. OSX: `brew install freeimage`). If you
install it somewhere else or for some reason Qt-Creator cannot find
the library you have to edit `glsl-preview-app.pro`.

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

## License

This project uses the [MIT License](./LICENSE), so you can do whatever
you want with it. Note that some of the dependencies use different
licenses.

* [Qt](http://www.qt.io/qt-licensing-terms/)
* [FreeImage](http://freeimage.sourceforge.net/license.html)
* [glm](https://github.com/g-truc/glm) (also MIT)
