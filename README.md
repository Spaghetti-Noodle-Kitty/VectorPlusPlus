# VectorPlusPlus
##### Attempts to implement a custom Vector datatype and draw vectors on bitmaps or console

## What is this?
> This is an attempt at implementing multiple things fairly badly
> * Creating an own datatype for vectors
> * Drawing those vectors to a bitmap
> * Drawing those vectors to std::cout

## The Vector-datatype
> The Vector is a class with only public values & methods consisting of:
> * The X and Y position of the vectors center
> * The Rotation of the Vector
> * The Force of the Vector
> * An initialization method for the Vector-datatype

## Initializing a new Vector
> Fairly simple, create a new Vector by the following:
> ``` Vector2D <Name> = Vector2D(X, Y, Rotation, Force); ```
> (The Rotation-value is clamped between 0f & 360f)
> An actual initialization might look like this:
> ``` Vector2D 45Deg = Vector2D(10f, 10f, 45f, 20f); ```

## A small closing statement
> * This thing is not intended to do much, it is just for me to learn about C++ and custom datatypes
> * Feel free to use any of the code in this mald if you want to
> * _(Please credit me if you actually use some of this code_ :point_right::point_left:_)_
