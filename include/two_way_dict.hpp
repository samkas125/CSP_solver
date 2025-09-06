#ifndef TWO_WAY_DICT_HPP
#define TWO_WAY_DICT_HPP

#include <map>
#include <vector>

/**
 * A bidirectional dictionary that maintains mappings in both directions.
 * This allows efficient lookup by key or by value.
 */
class TwoWayDict {
private:
    std::map<int, int> forward_map;
    std::map<int, int> reverse_map;

public:
    /**
     * Insert a key-value pair, removing any existing mappings for either key or value.
     * @param key The key to insert
     * @param value The value to associate with the key
     */
    void insert(int key, int value);

    /**
     * Remove a key and its associated value from the dictionary.
     * @param key The key to remove
     */
    void erase(int key);

    /**
     * Get the number of key-value pairs in the dictionary.
     * @return The size of the dictionary
     */
    int size() const;

    /**
     * Check if a key exists in the dictionary.
     * @param key The key to check
     * @return True if the key exists, false otherwise
     */
    bool contains_key(int key) const;

    /**
     * Get the value associated with a key.
     * @param key The key to look up
     * @return The associated value
     * @throws std::out_of_range if key doesn't exist
     */
    int get_value(int key) const;

    /**
     * Get the key associated with a value.
     * @param value The value to look up
     * @return The associated key
     * @throws std::out_of_range if value doesn't exist
     */
    int get_key(int value) const;

    /**
     * Get all keys in the dictionary.
     * @return A vector containing all keys
     */
    std::vector<int> get_keys() const;
};

#endif // TWO_WAY_DICT_HPP
