//#pragma once
//
//#include <functional>
//#include <memory>
//#include <mutex>
//#include <unordered_map>
//#include <vector>
//
//class EventEmitter {
//public:
//    // Add a listener for a specific event
//    void on(const std::string& event, const std::function<void()>& listener) {
//        std::lock_guard<std::mutex> lock(mutex_);
//        listeners_[event].push_back(listener);
//    }
//
//    // Remove a listener for a specific event
//    void off(const std::string& event, const std::function<void()>& listener) {
//        std::lock_guard<std::mutex> lock(mutex_);
//        listeners_[event].erase(std::remove(listeners_[event].begin(), listeners_[event].end(), listener), listeners_[event].end());
//    }
//
//    // Emit an event, notifying all registered listeners
//    void emit(const std::string& event) {
//        std::lock_guard<std::mutex> lock(mutex_);
//        // Copy listeners to avoid potential issues with modification during callback execution
//        auto callbacks = listeners_[event];
//        for (const auto& callback : callbacks) {
//            callback();
//        }
//    }
//
//private:
//    std::unordered_map<std::string, std::vector<std::function<void()>>> listeners_;
//    std::mutex mutex_;
//};
