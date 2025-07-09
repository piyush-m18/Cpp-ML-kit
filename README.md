# C++ ML kit
An library that can be included to implement ML algorithm in c++, giving you a boost up and low latency in running ml algorithms.

## File structure
```
c++ ML kit/
├── include/
│   └── mlkit/
│       └── knn.hpp            # Header-only implementation
├── examples/
│   ├── example_knn.cpp        # Small 6-point 
└── README.md
```

---

## Getting Started

### Compile & Run (Command Line)

```bash
g++ -std=c++17 examples/example_knn.cpp -Iinclude -o knn_large
./knn_large
```
## Implementation Highlights
Efficient use of STL: std::vector, std::pair, std::nth_element

No dependencies

Exception-safe (std::invalid_argument, std::runtime_error)

Extensible (can later add distance metric strategy, weights, etc.)

## Future Plans
To add other ML algo in mlkit like:

KMeans

Decision Tree

Linear Regression

Linear Regression

PCA

SVM

ANN, CNN

## Contributing
Contributions, ideas, and issues are welcome! You can