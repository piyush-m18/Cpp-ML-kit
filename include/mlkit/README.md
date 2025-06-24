# KNN 
Overview
--------
This header defines a templated k-Nearest Neighbors (k-NN) classifier in C++ as part of the `mlkit` namespace. The classifier supports generic feature and label types, and provides basic fit and predict functionality for supervised classification tasks.

File: include/mlkit/knn.hpp

Features
--------
- Templated for feature type `T` (e.g., float, double) and label type `Label` (e.g., int, std::string).
- Implements the classic k-NN algorithm using Euclidean distance.
- Supports fitting on training data and predicting labels for new samples.
- Batch prediction for multiple samples.
- Throws exceptions for invalid usage (e.g., unfitted classifier, invalid k).

Usage
-----
1. Include the header:
    #include "mlkit/knn.hpp"

2. Create an instance:
    mlkit::KNNClassifier<double, int> knn(3); // 3-NN, double features, int labels

3. Fit the classifier:
    std::vector<std::vector<double>> X_train = { ... };
    std::vector<int> y_train = { ... };
    knn.fit(X_train, y_train);

4. Predict a single sample:
    std::vector<double> x = { ... };
    int label = knn.predict(x);

5. Predict multiple samples:
    std::vector<std::vector<double>> X_test = { ... };
    std::vector<int> labels = knn.predict(X_test);

API Reference
-------------
- Constructor:
    KNNClassifier(int k)
    // k: Number of neighbors to use.

- void fit(const std::vector<std::vector<T>>& X, const std::vector<Label>& y)
    // X: Training features (samples x features)
    // y: Training labels

- Label predict(const std::vector<T>& x) const
    // x: Feature vector to classify

- std::vector<Label> predict(const std::vector<std::vector<T>>& X) const
    // X: Batch of feature vectors

Implementation Details
----------------------
- Uses Euclidean distance for neighbor search.
- Majority voting for label prediction.
- Throws std::invalid_argument and std::runtime_error for error handling.

License
-------
This code is provided as-is for educational and research purposes.

Author
------
supremeashu