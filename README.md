# 3D-file-conversion-utility
3D file conversion, unlimited sequence of transformations (scaling, rotation, translation), containment check for arbitrary vectors.
File converter:
Command line options:
Using getopt.

Reader:
Regardless of file format the common task is to read:
1. Vertices
2. Facet connections
3. Optionally edges (future)

OBJ to STL file conversion:

In the assignment “The OBJ file support should be limited to v, vt, vn and f elements”. However IMHO there is nothing to do with the vt – texture coordinate elements, as STL can not handle this sort of data nor the transformations are affected by them. So skipped.
There is no time to implement a customizable reorder, so I get the given order of points from the OBJ file as the base of calculating the normals. As for the inclusion problem there is a need for proper normal vectors for the GroupD triangles, I decided to replace the ones came from the OBJ file, moreover I omit to read them at all. 
For binary STL serialization I assumed 32 bit little endian float type, because checking and testing needs more time than the given. For “real” production-ready software I would not make this assumption.
From the assignment this is a very important simplification „You can assume that these are always convex planar faces”, I decided to utilize it – in lack of time - because this way:
- messing with the winding can be omitted.
- triangulation can be done fan wise, because all points are co-planar.

Determine if a point is inside a 3D body:

 Utilizing that arbitrary half-ray from the point of interest crosses the walls of the body:
- odd number of times if the point is inside the body, and
- even number of times (including zero) if outside of it.

The arbitrary half-ray will be the +Z direction from the point, for the sake of simplicity.


Implementation:
1. all triangles GroupA with Az<Pz and Bz<Pz and Cz<Pz to be excluded
2. all triangles, GroupB with  Az>Pz or Bz>Pz or Cz>Pz to be investigated for 2D inclusion in the plane Pz
	REF.:
	2D „pt in triangle” fiddle with multiplication-only solution:
	http://jsfiddle.net/PerroAZUL/zdaY8/1/
3. GroupB includes GroupC with  Az>Pz and Bz>Pz and Cz>Pz needs no further checking
4. GroupD = GroupB-GroupC after inclusion check, calculate P’ (impact point of the half-ray) then checking if 
	Pz’ > Pz.
Tests:
-f stl -p "0.795495  -0.795496 -0.298591" -T "scal,1;1;1,3;2.3,0 tran,2;2  rot,1;1;11.5,23.5" -o  /home/tve/Documents/shapr3d/torus_1.stl /home/tve/Documents/shapr3d/tordef.obj

-f stl -p "0.795495  -0.795496 -0.298591"  /home/tve/Documents/shapr3d/tordef.obj

To do:
In a pure file conversion program the riangulation step is to be put in the writing classes instead of the reading ones.
Smart float4 (IEEE 754) serialization with size and endianness checking.
Smart triangulation – in each polygon search for the max number of co-planar triangles, not to assume planarity for the polygons other than triangles.
Customized (with argp parameter) normal handling of facets. e.g.: a-as given, b-based on given winding order, c-uniform outward, d-uniform inward…
Logging to file

