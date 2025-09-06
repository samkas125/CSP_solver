#include "two_way_dict.hpp"

void TwoWayDict::insert(int key, int value) {
    // Remove existing mapping for the key if it exists
    if (forward_map.find(key) != forward_map.end()) {
        int old_value = forward_map[key];
        forward_map.erase(key);
        reverse_map.erase(old_value);
    }
    
    // Remove existing mapping for the value if it exists
    if (reverse_map.find(value) != reverse_map.end()) {
        int old_key = reverse_map[value];
        reverse_map.erase(value);
        forward_map.erase(old_key);
    }
    
    // Insert the new mapping
    forward_map[key] = value;
    reverse_map[value] = key;
}

void TwoWayDict::erase(int key) {
    if (forward_map.find(key) != forward_map.end()) {
        int value = forward_map[key];
        forward_map.erase(key);
        reverse_map.erase(value);
    }
}

int TwoWayDict::size() const {
    return forward_map.size();
}

bool TwoWayDict::contains_key(int key) const {
    return forward_map.find(key) != forward_map.end();
}

int TwoWayDict::get_value(int key) const {
    return forward_map.at(key);
}

int TwoWayDict::get_key(int value) const {
    return reverse_map.at(value);
}

std::vector<int> TwoWayDict::get_keys() const {
    std::vector<int> keys;
    keys.reserve(forward_map.size());
    for (const auto& pair : forward_map) {
        keys.push_back(pair.first);
    }
    return keys;
}
