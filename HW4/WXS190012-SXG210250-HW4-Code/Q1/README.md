# Q1 — Type Compatibility Lab

This folder contains small test programs (C, C++, C#, Java) used to observe
type compatibility and conversion behavior for common compilers.

Files:
- `test_c.c` — C tests (implicit widening, explicit narrowing, void* behavior)
- `test_cpp.cpp` — C++ tests (pointer cast rules, narrowing rules)
- `test_cs.cs` — C# tests (widening/narrowing, boxing/unboxing, generics notes)
- `TestJava.java` — Java tests (primitive conversions, array covariance, generics)
- `type_compatibility_report.txt` — Summary of findings

How to run (PowerShell examples):

1) C (GCC):
```powershell
gcc -Wall "Q1\test_c.c" -o "Q1\test_c.exe"
.\Q1\test_c.exe
```

Expected output (example run):
```
int i = 42 -> double d = 42.000000
double e = 3.140000 -> int j = 3 (after cast)
assign -1 to unsigned -> ui = 4294967295
arr[0] via int* from void* = 1
```

2) C++ (g++):
```powershell
g++ -Wall "Q1\test_cpp.cpp" -o "Q1\test_cpp.exe"
.\Q1\test_cpp.exe
```

Expected output (example run):
```
int i = 42 -> double d = 42
double e = 3.1415 -> int j = 3 (after cast)
arr[0] via int* from void* (with cast) = 1
```

3) C# (Microsoft C# compiler `csc`) — if installed:
```powershell
csc "Q1\test_cs.cs"
.\test_cs.exe
```

Note: On this machine `csc` was not found on PATH. If you don't have a C# toolchain you can install the .NET SDK
(recommended) or use Visual Studio Build Tools. After installing the .NET SDK you can use the `dotnet` CLI to run the test.

Install (recommended)
- Using Windows Package Manager (winget):
```powershell
winget install --id Microsoft.DotNet.SDK.7 -e --source winget
```
- Or download and install from Microsoft: https://dotnet.microsoft.com/download

Verify installation:
```powershell
dotnet --info
dotnet --list-sdks
```

Run `test_cs.cs` with `dotnet` (no separate `csc` required):
```powershell
Push-Location "Q1"
dotnet new console -n TempCSRun -o TempCSRun -f net7.0
Copy-Item "test_cs.cs" -Destination "TempCSRun\Program.cs" -Force
Push-Location TempCSRun
dotnet run
Pop-Location
Pop-Location
```

Notes:
- The commands above create a temporary project `Q1\TempCSRun`, replace the generated `Program.cs` with `test_cs.cs`, then build and run it.
- Remove the temporary project after running: `Remove-Item -Recurse -Force Q1\TempCSRun`.
- If you prefer `csc` (Roslyn) instead of `dotnet`, install Visual Studio Build Tools or the .NET SDK that includes the compiler; `csc` may require additional PATH setup.

4) Java:
```powershell
javac "Q1\TestJava.java"
java -cp Q1 TestJava
```

Expected output (example run):
```
int 42 -> double 42.0
double 3.14 -> int 3 (after cast)
ArrayStoreException observed when storing Base into Derived[] via Base[] reference
```

Notes:
- Many disallowed conversions in each language are present as commented lines in the test files.
- To observe compiler diagnostics, uncomment one commented example at a time and recompile.
- Compiler flags such as `-std=c11` or `-std=c++17` and `-Wall` can affect whether certain conversions produce warnings or errors.
