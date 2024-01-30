## How to Run the Advanced C++ Assembly Line Simulator

Follow these steps to compile and execute the Assembly Line Simulator, which simulates a complex assembly line using C++ Object-Oriented Programming principles.

### Prerequisites

- Ensure you have a C++ compiler installed, such as `g++`.
- The project source files (`Utilities.h/cpp`, `Station.h/cpp`, `CustomerOrder.h/cpp`, `Workstation.h/cpp`, `LineManager.h/cpp`) must be present in your working directory.

### Compiling the Project

1. **Clone the Repository**: Clone the repository to your local machine using Git.
```
git clone https://github.com/yourusername/Advanced-Cpp-Assembly-Line-Simulator.git

```
2. **Navigate to the Project Directory**: Change to the directory containing the project files.
```
cd Advanced-Cpp-Assembly-Line-Simulator
```
3. **Compile the Source Code**: Compile the source files using the C++ compiler. You can use a `Makefile` if available or compile the files manually. For example:
```
g++ -o AssemblyLineSimulator Utilities.cpp Station.cpp CustomerOrder.cpp Workstation.cpp LineManager.cpp main.cpp
```


### Running the Project

After compiling the project, run the executable along with the necessary command line arguments as specified in `ms3_output.txt`.
```
./AssemblyLineSimulator Stations1.txt Stations2.txt CustomerOrders.txt AssemblyLine.txt
```

For specific command line arguments, refer to `ms3_output.txt` in the repository, which contains the necessary commands to start the application along with examples of expected output.

### Expected Output

The output will simulate an assembly line, displaying the processing of orders through various stages. For detailed descriptions and examples of expected output, please refer to the `ms3_output.txt` file.

