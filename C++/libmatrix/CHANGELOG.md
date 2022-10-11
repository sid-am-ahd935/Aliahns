### Changelog - Oct 11, 2022
#### Overloaded operator [ ]
```c++
matrix<int> m(5, 5);
m[2][3] = 11;
```

#### Constructor for 2D std::initializer_list
```c++
matrix<int> m2 {
    { 0, 2, 3, 4 },
    { 7, 1, 5, 6 },
    { 6, 5, 2, 7 },
    { 4, 3, 2, 3 }
};
```

#### Disabled default constructor
This is done to make sure a matrix always has its attributes (dimensions and data) defined.

This eliminates need to check a matrix for a nullptr attribute.
```c++
matrix<int> m;    // error
```

####  Excess features
1. Reference counter for smart memory management.
2. Overload `=` and add copy constructor.
3. Added 2 compiler flags to [library.md](library.md#compiler-flags)
