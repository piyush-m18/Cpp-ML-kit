#include <iostream>
#include <iomanip>
#include "mlkit/kmeans.hpp"

int main()
{
    // Instantiate K-means with k=3 clusters
    mlkit::ClusteringAlgorithm<double> kmeans(3);

    // Training data: 30 points that naturally form 3 clusters
    std::vector<std::vector<double>> X_train = {
        {1.0, 2.0}, {1.1, 2.1}, {0.9, 2.2}, {1.2, 1.9}, {1.0, 1.8}, {1.3, 2.3}, // cluster around (1, 2)
        {2.0, 2.5}, {2.1, 2.6}, {1.8, 2.7}, {2.2, 2.4}, {2.3, 2.3}, {2.1, 2.8}, // cluster around (2, 2.5)
        
        {5.0, 8.0}, {5.1, 8.2}, {4.9, 7.8}, {5.2, 8.1}, {5.0, 7.9}, {5.3, 8.3}, // cluster around (5, 8)
        {5.5, 8.5}, {5.6, 8.6}, {5.4, 8.4}, {5.3, 8.2}, {5.2, 8.0}, {5.7, 8.7}, // cluster around (5.5, 8.5)
        
        {9.0, 1.0}, {9.1, 1.1}, {9.2, 0.9}, {8.9, 1.2}, {9.3, 1.3}, {9.0, 0.8}, // cluster around (9, 1)
    };

    std::cout << "K-means Clustering Example\n";
    std::cout << "==========================\n\n";

    // Fit model
    std::cout << "Fitting K-means model with " << X_train.size() << " data points...\n";
    kmeans.fit(X_train);

    // Get cluster assignments for training data
    auto labels = kmeans.get_labels();
    auto centroids = kmeans.get_centroids();
    double inertia = kmeans.get_inertia();

    // Print training results
    std::cout << "\nTraining Results:\n";
    std::cout << "Number of clusters: " << kmeans.get_k() << "\n";
    std::cout << "Inertia (WCSS): " << std::fixed << std::setprecision(4) << inertia << "\n\n";

    // Print cluster assignments for training data
    std::cout << "Training data cluster assignments:\n";
    for (size_t i = 0; i < X_train.size(); ++i) {
        std::cout << "Point [" << std::setw(4) << std::setprecision(1) << X_train[i][0] 
                  << ", " << std::setw(4) << std::setprecision(1) << X_train[i][1] 
                  << "] => Cluster " << labels[i] << "\n";
    }

    // Print centroids
    std::cout << "\nCluster Centroids:\n";
    for (size_t i = 0; i < centroids.size(); ++i) {
        std::cout << "Cluster " << i << " centroid: [" 
                  << std::setw(6) << std::setprecision(3) << centroids[i][0] << ", " 
                  << std::setw(6) << std::setprecision(3) << centroids[i][1] << "]\n";
    }

    // Test points from various regions
    std::vector<std::vector<double>> X_test = {
        {1.05, 2.0}, // Near first cluster
        {5.1, 8.0},  // Near second cluster  
        {9.0, 1.0},  // Near third cluster
        {2.2, 2.6},  // Should be assigned to first cluster
        {5.6, 8.6},  // Should be assigned to second cluster
        {8.95, 1.1}, // Should be assigned to third cluster
        {3.0, 5.0},  // Point between clusters
        {7.0, 4.0}   // Another point between clusters
    };

    auto predictions = kmeans.predict(X_test);

    // Print predictions
    std::cout << "\nPredictions for test points:\n";
    for (size_t i = 0; i < predictions.size(); ++i) {
        std::cout << "Test Point [" << std::setw(4) << std::setprecision(1) << X_test[i][0] 
                  << ", " << std::setw(4) << std::setprecision(1) << X_test[i][1] 
                  << "] => Predicted Cluster: " << predictions[i] << "\n";
    }

    // Show cluster statistics
    std::cout << "\nCluster Statistics:\n";
    std::vector<int> cluster_counts(3, 0);
    for (int label : labels) {
        cluster_counts[label]++;
    }
    
    for (int i = 0; i < 3; ++i) {
        std::cout << "Cluster " << i << ": " << cluster_counts[i] << " points\n";
    }

    return 0;
}
