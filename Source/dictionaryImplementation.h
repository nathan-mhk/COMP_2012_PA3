// SUBMIT THIS FILE

template <typename K, typename V>
Dictionary<K, V>::Dictionary(const Dictionary& another) : array(another.size ? new KeyValue[another.size] : NULL), size(another.size) {
    // Deep copy
    for (int i = 0; i < size; ++i) {
        array[i].key = another.array[i].key;
        array[i].value = another.array[i].value;
    }
}

template <typename K, typename V>
V& Dictionary<K, V>::operator[](K key) {
    for (int i = 0; i < size; ++i) {
        if (array[i].key == key) {
            return array[i].value;
        }
    }
    
    // Create a copy of the old array
    KeyValue* temp = new KeyValue[++size];
    for (int i = 0; i <= size - 2; ++i) {
        temp[i].key = array[i].key;
        temp[i].value = array[i].value;
    }
    // Add the new item and replace the old one with it
    temp[size - 1].key = key;
    temp[size - 1].value = 0;
    delete[] array;
    array = temp;
    return array[size - 1].value;
}

template <typename K, typename V>
Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary& another) {
    // Deep assignment
    if (this != &another) {
        delete [] array;
        size = another.size;
        array = size ? new KeyValue[size] : NULL;
        for (int i = 0; i < size; ++i) {
            array[i].key = another.array[i].key;
            array[i].value = another.array[i].value;
        }
    }
    return (*this);
}

template <typename K, typename V>
K* Dictionary<K, V>::getKeyList() const {
    // Dynamically create an array of K and return it
    // Must retain the order
    // Do not need to delete it here
    K* temp = new K[size];
    for (int i = 0; i < size; ++i)
        temp[i] = array[i].key;
    return temp;
}

template <typename K, typename V>
V* Dictionary<K, V>::getValueList() const {
    // Same as getKeyList()
    V* temp = new V[size];
    for (int i = 0; i < size; ++i)
        temp[i] = array[i].value;
    return temp;
}

template <typename K, typename V>
void Dictionary<K, V>::clean() {
    delete [] array;
    array = NULL;
    size = 0;
}
