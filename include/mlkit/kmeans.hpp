#pragma once // Ensures this header is included only once during compilation (include guard)
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <map>
#include <set>
#include <random>

namespace mlkit
{

    template <typename T>
    class ClusteringAlgorithm
    {

    private:
        int k;
        int max_iterations;
        T tolerance;
        std::vector<std::vector<T>> X_train;
        std::vector<std::vector<T>> centroids;  // Fixed: changed from pair to vector for multi-dimensional support
        std::vector<int> labels;
        T inertia;

        static T euclidean_distance(const std::vector<T> &a, const std::vector<T> &b)
        {
            T sum = 0;
            for (size_t i = 0; i < a.size(); ++i)
            {
                T diff = a[i] - b[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }

    public:
        ClusteringAlgorithm(int k, int max_iterations = 100, T tolerance = 1e-4) 
            : k(k), max_iterations(max_iterations), tolerance(tolerance), inertia(0)
        {
            if (k <= 0)
                throw std::invalid_argument("k must be positive");
            if (max_iterations <= 0)
                throw std::invalid_argument("max_iterations must be positive");
        }

        static std::vector<int> generate_unique_num(int min, int max, int n)
        {
            if (n > (max - min + 1))
                throw std::invalid_argument("n is larger than the range of unique numbers");
            std::set<int> numbers;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(min, max);  // Fixed: use min, max instead of start, end

            while (numbers.size() < static_cast<size_t>(n))  // Fixed: use n instead of k
            {
                numbers.insert(distrib(gen));
            }

            return std::vector<int>(numbers.begin(), numbers.end());
        }

        void fit(const std::vector<std::vector<T>> &X)
        {
            if (X.empty() || X[0].empty())
                throw std::invalid_argument("Input data cannot be empty");
            if (k > static_cast<int>(X.size()))
                throw std::invalid_argument("k cannot be larger than number of data points");

            X_train = X;
            int n_features = X[0].size();
            
            // Initialize centroids randomly
            centroids.clear();
            centroids.resize(k);
            labels.resize(X.size());
            
            std::vector<int> random_indices = generate_unique_num(0, X.size() - 1, k);
            for (int i = 0; i < k; ++i) {
                centroids[i] = X[random_indices[i]];
            }

            // K-means iterations
            for (int iteration = 0; iteration < max_iterations; ++iteration) {
                std::vector<std::vector<T>> old_centroids = centroids;
                
                // Assign points to closest centroids
                for (size_t idx = 0; idx < X.size(); ++idx) {
                    std::vector<T> distances;
                    for (const auto &centroid : centroids) {
                        distances.push_back(euclidean_distance(X[idx], centroid));
                    }
                    auto min_it = std::min_element(distances.begin(), distances.end());
                    labels[idx] = std::distance(distances.begin(), min_it);
                }

                // Update centroids
                for (int i = 0; i < k; ++i) {
                    std::vector<T> new_centroid(n_features, T(0));
                    int count = 0;
                    
                    for (size_t j = 0; j < X.size(); ++j) {
                        if (labels[j] == i) {
                            for (int d = 0; d < n_features; ++d) {
                                new_centroid[d] += X[j][d];
                            }
                            ++count;
                        }
                    }
                    
                    if (count > 0) {
                        for (int d = 0; d < n_features; ++d) {
                            new_centroid[d] /= count;
                        }
                        centroids[i] = new_centroid;
                    }
                }
                
                // Check for convergence
                bool converged = true;
                for (int i = 0; i < k; ++i) {
                    if (euclidean_distance(centroids[i], old_centroids[i]) > tolerance) {
                        converged = false;
                        break;
                    }
                }
                
                if (converged) {
                    break;
                }
            }
            
            // Calculate inertia (within-cluster sum of squares)
            calculate_inertia();
        }

        std::vector<int> predict(const std::vector<std::vector<T>> &X) const
        {
            if (centroids.empty())
                throw std::runtime_error("Classifier has not been fitted");
                
            std::vector<int> predictions;
            predictions.reserve(X.size());
            
            for (const auto &x : X) {
                std::vector<T> distances;
                for (const auto &centroid : centroids) {
                    distances.push_back(euclidean_distance(x, centroid));
                }
                auto min_it = std::min_element(distances.begin(), distances.end());
                int min_index = std::distance(distances.begin(), min_it);
                predictions.push_back(min_index);
            }
            return predictions;
        }

        // Convenience method: fit and predict in one call
        std::vector<int> fit_predict(const std::vector<std::vector<T>> &X) {
            fit(X);
            return labels;
        }

        // Calculate within-cluster sum of squares (inertia)
        void calculate_inertia() {
            inertia = T(0);
            for (size_t i = 0; i < X_train.size(); ++i) {
                T distance = euclidean_distance(X_train[i], centroids[labels[i]]);
                inertia += distance * distance;
            }
        }

        // Getter methods
        std::vector<std::vector<T>> get_centroids() const {
            if (centroids.empty())
                throw std::runtime_error("Classifier has not been fitted");
            return centroids;
        }
        
        std::vector<int> get_labels() const {
            if (labels.empty())
                throw std::runtime_error("Classifier has not been fitted");
            return labels;
        }
        
        T get_inertia() const {
            if (centroids.empty())
                throw std::runtime_error("Classifier has not been fitted");
            return inertia;
        }
        
        int get_k() const {
            return k;
        }
        
        int get_max_iterations() const {
            return max_iterations;
        }
        
        T get_tolerance() const {
            return tolerance;
        }
    };
}
