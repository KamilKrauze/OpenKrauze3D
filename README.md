# Open Krauze Engine - Stripped
This is the <b>stripped branch</b>, where everything but the basic renderer is stripped. This is a good starting point for anyone who may be new to OpenGL or graphics programming in general.

This is a 3D graphics engine hobby project using the OpenGL 4.6 API and GLFW.
The premise is to create a flexible and multi-platform graphics engine.

I will not provide built binaries and libraries used in this project for you, as I do not own or contribute those projects, please navigate to the [thirdparty folder](https://github.com/KamilKrauze/OpenKrauzeEngine/tree/main/thirdparty) for the list of libraries used.

For project generation please use [premake 5](https://premake.github.io/).


# Running the Executable
By default if ran normally via your IDE, command-line or desktop, the app will use 75% of available all threads for multi-processing. However, this can be overidden directly in the command-line.

| Flag      | Value Type     | Description                  | Notes                                         | Default              |
| --------- | -------------- | ---------------------------- | --------------------------------------------- | -------------------- |
| ```-t```  | `unsigned int` | Maximum thread override.     | Caps at MAX available and minimum of 2.       | $$\frac{3(MAX)}{4}$$ |
| ```-tR``` | `unsigned int` | The ratio of threads to use. | If the ratio is too small then it will use 2. | $$1$$                |

## Example 
> <br>
> 
> >  ### Windows
> > ```cmd
> > ./OpenKrauzeEngine.exe -t 10 -tR 5
> > ```
> > <br>
>
> >  ### Linux
> >  ```console
> >  ./OpenKrauzeEngine -t 10 -tR 5
> >  ```
> > <br>
> $$ 
> \frac{10}{5} = 2
> $$
> 
> 2 threads allocated for multi-processing.
> <br>
