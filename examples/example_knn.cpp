#include <iostream>
#include "mlkit/knn.hpp"

int main()
{
    // Instantiate KNN with k=5
    mlkit::KNNClassifier<double, int> knn(5);

    // Training data: 30 points across 3 classes (0, 1, 2)
    std::vector<std::vector<double>> X_train = {
        {1.0, 2.0}, {1.1, 2.1}, {0.9, 2.2}, {1.2, 1.9}, {1.0, 1.8}, {1.3, 2.3}, // class 0
        {5.0, 8.0},
        {5.1, 8.2},
        {4.9, 7.8},
        {5.2, 8.1},
        {5.0, 7.9},
        {5.3, 8.3}, // class 1
        {9.0, 1.0},
        {9.1, 1.1},
        {9.2, 0.9},
        {8.9, 1.2},
        {9.3, 1.3},
        {9.0, 0.8}, // class 2
        {2.0, 2.5},
        {2.1, 2.6},
        {1.8, 2.7},
        {2.2, 2.4},
        {2.3, 2.3},
        {2.1, 2.8}, // class 0
        {5.5, 8.5},
        {5.6, 8.6},
        {5.4, 8.4},
        {5.3, 8.2},
        {5.2, 8.0},
        {5.7, 8.7} // class 1
    };
    std::vector<int> y_train = {
        0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2,
        0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1};

    // Fit model
    knn.fit(X_train, y_train);

    // Test points from unknown regions
    std::vector<std::vector<double>> X_test = {
        {1.05, 2.0}, // Near class 0
        {5.1, 8.0},  // Near class 1
        {9.0, 1.0},  // Near class 2
        {2.2, 2.6},  // Should still be class 0
        {5.6, 8.6},  // Should be class 1
        {8.95, 1.1}, // Should be class 2
    };

    auto preds = knn.predict(X_test);

    // Print predictions
    for (size_t i = 0; i < preds.size(); ++i)
        std::cout << "Test Point " << i << " => Predicted Class: " << preds[i] << "\n";

    return 0;
}
