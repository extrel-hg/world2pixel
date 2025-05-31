# world2pixel
<b>
Release date: 2025.05.31

EuVer version: 0.3.0
</b>

Small command-line utility to render maps in terminal. Requires a GOL object from Geodesk. Currently only works on windows, as the way I set colors on console is system-dependent. The goal however, is for the program to output to an image file and be system-independent.

## Usage

First, make sure you have a GOL object created using Geodesk for the part of the world you want to use. See: https://docs.geodesk.com/gol/build, https://www.geodesk.com/download.
Put the GOL file next to the exe. Then in the terminal you can use this command to run the program:

`./world2pixel.exe (latitude) (longitude) (tiles on one side) (length of one side, in meters) (name of xml settings file, default 1.xml) (name of gol object, default gol)`

Make sure you have a .xml settings file, and that you pointed to it in your command. Otherwise the program has no settings to load!

As of now there are no error-catching systems, so be cautious.

The latitude and longitude are the coordinates of the top left corner of your render.

As of now, the program (or, more specifically, 1.xml settings file) excels at renders with a high resolution (a lot of tiles) and small area. I have included examples of both a large-scale render (25kmx25km @ 200x200 tiles) and a smaller one (1.5kmx1.5km @ 250x250 tiles). This program has difficulties at very big renders (>75km) (especially if using a low tile amount). The resulting render in this case is very distorted. In the future I may alliviate this issue by using a different algorithm for selecting the tiles.

As the image is currently rendered in console, the way it appears will depend on your terminal application. The following screenshots are from the Terminal application from Microsoft Store. As they are screenshots, the quality may be lower than it would appear.

For now, you cannot properly use this program on higher amount of tiles, if you cannot scale the view in your terminal.

## Examples:

Examples as of now are outdated. They come from version 0.1.0.

### Small scale:

`.\world2pixel.exe 51.21654, 17.36196 250 1500 1.7 2`  renders the following map (assuming a file called gol.gol exists in current directory, and it contains data for Wroclaw):
![alt text](world2pixel.png)

Comparing it to the OSM render:

![alt text](osm.png)

### Large scale:

`.\world2pixel.exe 51.369433 17.463128 500 25000 10 40`

![alt text](world2pixel25km.png)

![alt text](osm25km.png)

# Credits

Big thanks to anyone behind RapidXML, Geodesk, Geos.

Made with love by Hubert Gonera.