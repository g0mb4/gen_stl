# gen_stl

Simple surface generator. Written for LIGGGHTS.

## Compilation

```bash
make
```

# Usage

```bash
gen_stl <shape> <params>
```

## cube

Generates a cube centered at (0, 0, 0).

 + l - length of a side
 + mask - sides to generate

## box

Generates a box centered at (0, 0, 0).

 + lx - length of the X side
 + ly - length of the Y side
 + lz - length of the Z side
 + mask - sides to generate

## cylinder

Generates a cylinder centered at (0, 0, 0).

 + r - radius
 + h - height
 + N - number of segments
 + mask - sides to generate

## Examples

Creating a unit cube.
```bash
gen_stl cube 1 63 > cube.stl
```
