# cc-trick
Collection of magic C macro and C++ template programming

## C++ template programming

- `random_input.cc`: apply a function with random inputs. 

```c++
auto foo = [](int a, int b, float c) -> float {
    return a + b + c;
};
std::cout << random_run(foo) << std::endl;
```

