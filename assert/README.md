# ASSERT Library
## Desciption
A generic ASSERT call for non-recovable events. The file and function name are printed to *stderr* and the program is exited.
## Defines
```C
#define ASSERT(x) ...
```
## Types
None
## APIs
None
## Required Libraries
None
## Tested Target
- x86
## Usage
```C
int someCall(int * alpha)
{
    ASSERT(alpha != NULL);
    return *alpha;
}
```
## Details
None