# 3D-file-conversion-utility
3D file conversion, unlimited sequence of transformations (scaling, rotation, translation), containment check for arbitrary vectors.
## Prerequisites:
*c++17 capable compiler on linux* (other platforms not yet tested), *Eigen3* linear argebra library, and *CMake* installed.
## Build and use:
In a linux terminal window:
```
---$ git clone https://github.com/venyige/showcase-with-3d-mesh-data.git 
---$ cd showcase-with-3d-mesh-data
---$ cmake .
---$ make
---$ ./tcmu
```
To show the welcome screen, but to achieve some result with the program, proper commandline parameters needed, at least with an input file name with full path, and either of -o output file, or -f format specifier, see below.

# Notes
## File converter:
Command line options:

Using ```getopt```.

### Reader:
Regardless of file format the common task is to read:
1. Vertices
2. Facet connections
3. Normal vectors (with options, see to do list)
4. Optionally edges (future)
### Note on [OBJ specification](http://paulbourke.net/dataformats/obj/):

At caption *"f"* there is nothing about negative (relative) vertex referencing, but an example is shown with it ```"3.Cube with negative reference numbers"```. As it is not a specification, and leaves more questions than answers (what about the ```vn``` and ```vt``` sections) I deliberately omitted. Also the ```fo``` notation is omitted, but for backward compatibility it might be a "todo".

### ```OBJ``` to ```STL``` file conversion:

In the assignment “The OBJ file support should be limited to v, vt, vn and f elements”. However this time there is nothing to do with the ```vt``` – texture coordinate elements, as ```ST```L can not handle this sort of data nor the transformations are affected by them. So skipped.

There is no time to implement a customizable reorder, so I get the given order of points from the ```OBJ``` file as the base of calculating the normals.

As for the inclusion problem there is a need for proper normal vectors for the ```GroupD``` triangles, I decided to replace the ones came from the ```OBJ``` file, moreover I omit to read them at all.

For binary ```STL``` serialization I assumed 32 bit little endian float type, because checking and testing needs more time than the given. For “real” production-ready software I would not make this assumption.

From the assignment the next one is a very important simplification „You can assume that these are always convex planar faces”, I decided to utilize it – in lack of time - because this way:
- messing with the winding can be omitted.
- triangulation can be done fan wise, because all points are co-planar.

## Determine if a point is inside a 3D body:

 Utilizing that arbitrary half-ray from the point of interest crosses the walls of the body:
- odd number of times if the point is inside the body, and
- even number of times (including zero) if outside of it.

The arbitrary half-ray will be the +Z direction from the point, for the sake of simplicity.

Implementation:
1. all triangles ```GroupA``` with ```Az<Pz and Bz<Pz and Cz<Pz``` to be excluded
2. all triangles, ```GroupB``` with  ```Az>Pz or Bz>Pz or Cz>Pz``` to be investigated for 2D inclusion in the plane ```Pz```.

*Reference:*
```
2D „pt in triangle” fiddle with multiplication-only solution:
```
[http://jsfiddle.net/PerroAZUL/zdaY8/1/](http://jsfiddle.net/PerroAZUL/zdaY8/1/)

3. ```GroupB``` includes ```GroupC``` with  ```Az>Pz and Bz>Pz and Cz>Pz``` needs no further checking
4. ```GroupD = GroupB-GroupC``` after inclusion check, calculate ```P’``` (impact point of the half-ray) then checking if

	```Pz’ > Pz.```
### Note on double inclusion check: 
If any transformation is given by the "-T" parameter, the inclusion check is performed twice, once before and once after the transformations.
	
### Tests:
```
./tcmu -f stl -p "10.8623 42.1901 10.8037" -T "tran,2.22;14.12;.2,3 rot,14;15.55;1.6,25 scal,1;1;1,3" /home/tve/Documents/shapr3d/tordef_py.obj
```
```
./tcmu -f stl -p "0.795495  -0.795496 -0.298591"  /home/tve/Documents/shapr3d/tordef.obj
```
### To do:
- Smart float4 (IEEE 754) serialization with size and endianness checking.
- Smart triangulation – in each polygon search for the max number of co-planar triangles, not to assume planarity for the polygons other than triangles.
- Customized (with ```getopt``` parameter) normal handling of facets. e.g.: a-as given, b-based on given winding order, c-uniform outward, d-uniform inward…
- Logging to file


### The "help" text of the program:
```Triangular Mesh Converter "tcmu" - Shapr3D Homework /GoDraw
Usage: tmcu [options] <input file with full path>
Options/Arguments:
   -h          Display this help text

   -f format   The destination file format. If not given, extracted from "-o".
               Formats, case insensitve: STL, OBJ, FBX, COLLADA, 3DS, IGES, STEP, X3D.

   -o fullpath    Write the output image to the file "fullpath". If not given,
               output file is deduced from input file + format ( "-f").

   -p pt3d     This parameter argument has to be put in between quotation marks!
               Point to investigate if included in the imported 3d body
               the coordinates are x y z, delimited with spaces, e.g. -p "2.43 .2 0".

   -T transforms    This parameter argument has to be put in between quotation marks!
               Transformations to be performed on the content of the input,
               before being written to the output file. To be given as space separated list
               of "," separated command lists, as follows:
               "cmd1,vec1,num1 cmd2,vec2,num2 ...etc.", where cmdN is either of:
               [scal, tran, rot] for two-part scaling, translation and rotation around
               given axis, vecN is a 3D vector given as a semicolon delimited list of 3 
               decimal number, numN is a decimal value. For "scal" the vector holds the
               factors of non-uniform scaling, and the scalar number is for uniform scaling.
               Warning: the product of the vector and scalar scale factors is to take effect.
               For "rot" the vector is the  axis of rotation, not necessary to be
               unit (normalized). The scalar value is for the rotation angle in degrees. 
               For "tran" translation the numN scalar value is omitted. Example:
               -T "tran,2.22;14.12;.2,3 rot,14;15.55;1.6,25 scal,1;1;1,3" 
	       ```


