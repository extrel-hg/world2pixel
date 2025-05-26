# world2pixel

Small command-line utility to render maps in terminal. Requires a GOL object from Geodesk. Currently only tested for windows, but porting to linux should be really easy.

## Usage:
First, make sure you have a GOL object created using Geodesk for the part of the world you want to use. See: https://docs.geodesk.com/gol/build.
Put the GOL file next to the exe. Then in the terminal you can use this command to run the program:

`./world2pixel.exe (latitude) (longitude) (tiles on one side) (length of one side, in meters) (road scale factor) (rail scale factor) (name of gol object, default gol)`

### Example:

`.\world2pixel.exe 51.12788 16.99224 500 4000 1.5 4`  renders the following map (assuming a file called gol.gol exists in current directory, and it contains data for Wroclaw):
![Wroclaw](world2pixel.png)

Comparing it to the OSM render:

![alt text](osm.png)

Made with love by Hubert Gonera 2025.
Huge thanks for everyone who creates Geodesk!