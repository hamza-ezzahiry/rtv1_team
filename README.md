# RTv1


[![All Contributors](https://img.shields.io/badge/all_contributors-4-blue.svg?style=flat-square)](#contributors-)


<p align="center">
  <a href="https://docs.microsoft.com/en-us/learn/paths/azure-fundamentals/ "Azure fundamentals">
    <img alt="Gatsby" src="https://i.imgur.com/qB1BnfQ.png" width="500" />
  </a>
</p>
<h1 align="center">
  Ray Tracing Version 1.0 (RTv1)
</h1>


## About 
**RTv1** is a project i made it during my student years at 1337 School khouribga (one of 42 network), This project is the first step to create a Raytracing program, for you to finally be able to render computer-generated images.

## Project Contents :

- [x] 01. Libft : C library regrouping usual functions that we’ll be allowed to use in all your other projects.
- [x] 02. minilibx
- [x] 03. Ray Tracing files + Parsing
- [x] 03. scenes


## ID of evey Shape (for parsing) :

| id | Shape |
| ------ | ------ |
| 1 | sphere |
| 2 | plane |
| 3 | cylinder |
| 4 | cone |

## Parsing file format 

```sh
camera -50,0,20 0,0,0 70
light -40,0,30 0.7 255,255,255
sphere 0,0,20 20 255,0,0
plane 0,0,0 255,0,225
cylinder 50.0,0.0,20.6 14.2 21.42 10,0,255
cone 0,0,0 20 255,0,0
```


**Camere**

```sh
camera <position> <look at> <field of view>
```

**light**

```sh
light <position> <intensity> <color>
```
**Sphere**

```sh
sphere <origin> <raduis> <color>
```

**Plane**

```sh
plane <origin> <color>
```
**Cylinder**

```sh
cylinder <centre> <raduis> <height> <color> 
```

**Cone**

```sh
cone <origin> <raduis> <color> 
```

## Resources :  

- **[KhanAcademy - Vectors & Spaces](https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces)**
- **[Ray Tracing in One Weekend - PDF](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf)** 
- **[Ray Tracing in One Weekend - Website](https://raytracing.github.io/books/RayTracingInOneWeekend.html)**
- **[All about Ray Tracing - YouTube](https://youtu.be/Ahp6LDQnK4Y)**
- **[Images in minilibx](https://github.com/keuhdall/images_example)**
- **[Ray tracing Cone - Maths behind](http://www.illusioncatalyst.com/notes_files/mathematics/line_cone_intersection.php)**



## Getting Started

### Compiling

Run the following commands:

* To compile
	- `make`
* To remove objects:
	- `make clean`
* To remove objects and binary file (program):
	- `make fclean`
* To re-compile:
	- `make re`

### Executing

To run the program:

`./rtv1 [scene]`

## Screenshots

<img src="https://i.imgur.com/1OHon4g.png" width="1000" />

## keys keyboards (Minilibx)

<img src="https://i.imgur.com/VIuTiO9.png" width="700" />

## I want to contribute to the project! But how?

 - Fork this repository
 - Clone your repository forked
 - Contribute
 - Push
 - Create a pull request in this repository
 - Wait the merged !
 - Be happy :)


