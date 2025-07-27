# C++ ML Kit

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Header Only](https://img.shields.io/badge/Header%20Only-Yes-green.svg)]()
[![Platform](https://img.shields.io/badge/Platform-Cross--Platform-lightgrey.svg)]()

A lightweight, header-only C++ machine learning library that provides fast implementations of common ML algorithms with minimal dependencies. Designed for high performance and ease of integration.

## Features

✅ **K-Nearest Neighbors (KNN)** - Classification algorithm  
✅ **K-Means Clustering** - Unsupervised clustering algorithm  
🚧 **More algorithms coming soon!**

## File Structure
```
c++ ML kit/
├── include/
│   └── mlkit/
│       ├── core.hpp           # Includes all algorithms
│       ├── knn.hpp            # KNN classifier implementation
│       ├── kmeans.hpp         # K-means clustering implementation
│       └── README.md          # Detailed API documentation
├── examples/
│   ├── example_knn.cpp        # KNN classification example
│   └── example_kmeans.cpp     # K-means clustering example
└── README.md
```

## Quick Start

### Include the Library
```cpp
#include "mlkit/core.hpp"  // All algorithms
// OR include individually:
// #include "mlkit/knn.hpp"
// #include "mlkit/kmeans.hpp"
```

### KNN Classification Example
```cpp
mlkit::KNNClassifier<double, int> knn(5);
knn.fit(X_train, y_train);
auto predictions = knn.predict(X_test);
```

### K-Means Clustering Example
```cpp
mlkit::ClusteringAlgorithm<double> kmeans(3);
kmeans.fit(X_train);
auto labels = kmeans.get_labels();
auto centroids = kmeans.get_centroids();
```

## Compilation

Compile with C++17 or later:
```bash
# Compile KNN example
g++ -std=c++17 examples/example_knn.cpp -Iinclude -o knn_example

# Compile K-means example  
g++ -std=c++17 examples/example_kmeans.cpp -Iinclude -o kmeans_example

# Run examples
./knn_example
./kmeans_example
```

## Key Features

### Performance
- **Header-only**: No separate compilation required
- **Template-based**: Compile-time optimizations
- **STL-optimized**: Efficient use of std::vector, std::algorithms
- **Low memory footprint**: Minimal overhead

### Reliability
- **Exception-safe**: Proper error handling with std::invalid_argument, std::runtime_error
- **Input validation**: Comprehensive parameter checking
- **Convergence detection**: Automatic stopping for iterative algorithms

### Flexibility
- **Generic types**: Support for float, double, and custom numeric types
- **Multi-dimensional**: Works with data of any dimensionality
- **Configurable**: Adjustable parameters for different use cases

## Algorithms

### 1. K-Nearest Neighbors (KNN)
- **Type**: Supervised Classification
- **Features**: Multi-class support, batch prediction, configurable k
- **Use cases**: Pattern recognition, recommendation systems, anomaly detection

### 2. K-Means Clustering  
- **Type**: Unsupervised Clustering
- **Features**: Configurable clusters, convergence detection, quality metrics
- **Use cases**: Customer segmentation, image compression, data exploration

## Future Roadmap

🚧 **Planned Algorithms:**
- Decision Trees
- Linear Regression  
- Principal Component Analysis (PCA)
- Support Vector Machines (SVM)
- Neural Networks (ANN/CNN)

## Documentation

For detailed API documentation, usage examples, and implementation details, see:
- [`include/mlkit/README.md`](include/mlkit/README.md) - Complete API reference
- [`examples/`](examples/) - Working code examples

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to contribute to this project.

## Acknowledgments

- Inspired by scikit-learn's API design
- Built with modern C++ best practices
- Community-driven development

---

**⭐ Star this repository if you find it useful!**

## Contributing
Contributions, ideas, and issues are welcome! You can