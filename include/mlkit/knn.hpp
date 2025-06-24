#pragma once // Ensures this header is included only once during compilation (include guard)
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <stdexcept>
#include <map>

namespace mlkit {

    template<typename T, typename Label>
    class KNNClassifier {

    private:
        int k;
        std::vector<std::vector<T>> X_train;
        std::vector<Label> y_train;
        
        static T euclidean_distance(const std::vector<T>& a, const std::vector<T>& b) {
            T sum = 0;
            for (size_t i = 0; i < a.size(); ++i) {
                T diff = a[i] - b[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }
        
        static Label majority_vote(const std::vector<Label>& labels) {
            std::map<Label, int> counts;
            for (const auto& label : labels) {
                counts[label]++;
            }
            return std::max_element(counts.begin(), counts.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; })->first;
        }

    public:
        KNNClassifier(int k) : k(k) {
            if (k <= 0) throw std::invalid_argument("k must be positive");
        }

        void fit(const std::vector<std::vector<T>>& X, const std::vector<Label>& y) {
            if (X.size() != y.size()) throw std::invalid_argument("Mismatched X and y sizes");
            X_train = X;
            y_train = y;
        }

        Label predict(const std::vector<T>& x) const {
            if (X_train.empty()) throw std::runtime_error("Classifier has not been fitted");
            std::vector<std::pair<T, size_t>> distances;
            for (size_t i = 0; i < X_train.size(); ++i) {
                distances.emplace_back(euclidean_distance(x, X_train[i]), i);
            }
            std::nth_element(distances.begin(), distances.begin() + k, distances.end());
            std::vector<Label> k_labels;
            for (int i = 0; i < k; ++i) {
                k_labels.push_back(y_train[distances[i].second]);
            }
            return majority_vote(k_labels);
        }

        std::vector<Label> predict(const std::vector<std::vector<T>>& X) const {
            std::vector<Label> results;
            for (const auto& x : X) {
                results.push_back(predict(x));
            }
            return results;
        }

    };

} 
