# Open Krauze Engine
 
This is a 3D graphics engine hobby project using the OpenGL 4.5 API and GLFW.
The premise is to create a flexible and multi-platform graphics engine.

I will not provide built binaries and libraries used for you, as I do not own or contribute those projects, please navigate to the [thirdparty folder](https://github.com/KamilKrauze/OpenKrauzeEngine/tree/main/thirdparty) for the list of libraries used.

For project generation please use [premake 5](https://premake.github.io/).


# Running the Executable
By default if ran normally via your IDE, command-line or desktop, the app will use 75% of available all threads for multi-processing. However, this can be overidden directly in the command-line.

| Flag      | Value Type     | Description                  | Notes                                         | Default              |
| --------- | -------------- | ---------------------------- | --------------------------------------------- | -------------------- |
| ```-t```  | `unsigned int` | Maximum thread override.     | Caps at MAX available and minimum of 2.       | $$\frac{3(MAX)}{4}$$ |
| ```-tR``` | `unsigned int` | The ratio of threads to use. | If the ratio is too small then it will use 2. | $$1$$                |

## Example 
> ### Windows
> ```cmd
> C:\Users\foo>./OpenKrauzeEngine.exe -t 10 -tR 5
> ```
> $$ 
> \frac{10}{5} = 2
> $$
> 
> ``2 threads used for multi-processing.``
> <br>
