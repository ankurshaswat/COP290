# COP290
This repo contains all the work done under the Design Practices Course COP290


**Assignment 1:**
The software uses Qt libraries (tested on ver 5.10). Please make sure they are installed on your computer to run the software.

**Software description- **
The software has 2 modes- 
1) **3D to 2D**, which takes input 3D object description in an .obj file (can be created in many popular 3D modelling softwares (eg- Blender), and displays 3 orthographic projections of the object, with hidden lines shown in dotted form. It also offers sliders to rotate the object, as well as options to zoom in/out and change offset. Some examples (simple as well as complex) have been provided in the 'Examples' folder.
2) **2D to 3D**, where we have defined our own format for taking input the description of 2D orthographic views- we are taking edge information for 3 2D views and running our algorithm to first construct a wireframe, and then are forming potential face candidates from this wireframe. The 3D figure based on these faces is displayed in 3 orthographic views (with lines occluded from view hidden), and the isometric view of the wireframe is being displayed simultaneously.

https://ankurshaswat.github.io/COP290/
