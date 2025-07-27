# MLKit - C++ Machine Learning Library

Overview
--------
This library provides templated machine learning algorithms in C++ as part of the `mlkit` namespace. Currently includes k-Nearest Neighbors (k-NN) classification and K-means clustering algorithms with support for generic data types.

## Algorithms

### 1. K-Nearest Neighbors (KNN)

**File:** `include/mlkit/knn.hpp`

**Features:**
- Templated for feature type `T` (e.g., float, double) and label type `Label` (e.g., int, std::string).
- Implements the classic k-NN algorithm using Euclidean distance.
- Supports fitting on training data and predicting labels for new samples.
- Batch prediction for multiple samples.
- Throws exceptions for invalid usage (e.g., unfitted classifier, invalid k).

**Usage:**
```cpp
#include "mlkit/knn.hpp"

// Create an instance
mlkit::KNNClassifier<double, int> knn(3); // 3-NN, double features, int labels

// Fit the classifier
std::vector<std::vector<double>> X_train = { ... };
std::vector<int> y_train = { ... };
knn.fit(X_train, y_train);

// Predict a single sample
std::vector<double> x = { ... };
int label = knn.predict(x);

// Predict multiple samples
std::vector<std::vector<double>> X_test = { ... };
std::vector<int> labels = knn.predict(X_test);
```

**API Reference:**
- `KNNClassifier(int k)` - Constructor with number of neighbors
- `void fit(const std::vector<std::vector<T>>& X, const std::vector<Label>& y)` - Train on data
- `Label predict(const std::vector<T>& x) const` - Predict single sample  
- `std::vector<Label> predict(const std::vector<std::vector<T>>& X) const` - Batch prediction

**Implementation Details:**
- Uses Euclidean distance for neighbor search.
- Majority voting for label prediction.
- Throws std::invalid_argument and std::runtime_error for error handling.

---

### 2. K-Means Clustering

**File:** `include/mlkit/kmeans.hpp`

**Features:**
- Templated for feature type `T` (e.g., float, double).
- Implements the classic K-means clustering algorithm with Lloyd's algorithm.
- Supports configurable maximum iterations and convergence tolerance.
- Provides cluster quality metrics (inertia/WCSS).
- Multi-dimensional data support.
- Convergence detection for efficient computation.

**Usage:**
```cpp
#include "mlkit/kmeans.hpp"

// Create an instance
mlkit::ClusteringAlgorithm<double> kmeans(3); // 3 clusters, default params

// With custom parameters
mlkit::ClusteringAlgorithm<double> kmeans(5, 200, 1e-6); // 5 clusters, 200 max iter, 1e-6 tolerance

// Fit the model
std::vector<std::vector<double>> X_train = { ... };
kmeans.fit(X_train);

// Get cluster assignments
auto labels = kmeans.get_labels();
auto centroids = kmeans.get_centroids();
double inertia = kmeans.get_inertia();

// Predict cluster for new data
std::vector<std::vector<double>> X_test = { ... };
auto predictions = kmeans.predict(X_test);

// Convenience method: fit and predict in one call
auto cluster_labels = kmeans.fit_predict(X_train);
```

**API Reference:**
- `ClusteringAlgorithm(int k, int max_iterations = 100, T tolerance = 1e-4)` - Constructor
- `void fit(const std::vector<std::vector<T>>& X)` - Train clustering model
- `std::vector<int> predict(const std::vector<std::vector<T>>& X) const` - Predict clusters
- `std::vector<int> fit_predict(const std::vector<std::vector<T>>& X)` - Fit and predict
- `std::vector<std::vector<T>> get_centroids() const` - Get cluster centers
- `std::vector<int> get_labels() const` - Get training data cluster assignments
- `T get_inertia() const` - Get within-cluster sum of squares (WCSS)
- `int get_k() const` - Get number of clusters
- `int get_max_iterations() const` - Get maximum iterations setting
- `T get_tolerance() const` - Get convergence tolerance setting

**Implementation Details:**
- Uses Lloyd's algorithm with random centroid initialization.
- Iterative centroid updates until convergence or max iterations reached.
- Euclidean distance for cluster assignment.
- Convergence detection based on centroid movement tolerance.
- Calculates inertia (WCSS) for cluster quality assessment.
- Throws std::invalid_argument and std::runtime_error for error handling.

---

## Getting Started

**Include all algorithms:**
```cpp
#include "mlkit/core.hpp"  // Includes all algorithms
```

**Or include individually:**
```cpp
#include "mlkit/knn.hpp"     // Only KNN
#include "mlkit/kmeans.hpp"  // Only K-means
```

## Examples

See the `examples/` directory for complete working examples:
- `example_knn.cpp` - K-Nearest Neighbors classification example
- `example_kmeans.cpp` - K-means clustering example

## Compilation

Compile with C++17 or later:
```bash
g++ -std=c++17 -I./include your_code.cpp -o your_program
```

License
-------
This code is provided as-is for educational and research purposes.

Author
------
supremeashu