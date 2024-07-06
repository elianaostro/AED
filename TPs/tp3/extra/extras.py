import hashlib
import random
import math

# Constantes para el filtro de conteo
INITIAL_SIZE = 1000
NUM_HASHES = 3
RESIZE_THRESHOLD = 0.1
RESIZE_FACTOR = 2

class CountFilter:
    def __init__(self, size=INITIAL_SIZE, num_hashes=NUM_HASHES, resize_threshold=RESIZE_THRESHOLD, resize_factor=RESIZE_FACTOR):
        self.size = size
        self.num_hashes = num_hashes
        self.resize_threshold = resize_threshold
        self.resize_factor = resize_factor
        self.filter = [0] * size
        self.hash_seeds = [random.randint(0, 2**32 - 1) for _ in range(num_hashes)]
        self.element_count = 0

    def _hashes(self, element):
        return [hashlib.md5((str(seed) + element).encode()).hexdigest() for seed in self.hash_seeds]

    def _indices(self, hashes):
        return [int(h, 16) % self.size for h in hashes]

    def add(self, element):
        self.element_count += 1
        hashes = self._hashes(element)
        indices = self._indices(hashes)
        for index in indices:
            self.filter[index] += 1
        if self._false_positive_probability() > self.resize_threshold:
            self.resize(self.size * self.resize_factor)

    def remove(self, element):
        hashes = self._hashes(element)
        indices = self._indices(hashes)
        for index in indices:
            if self.filter[index] > 0:
                self.filter[index] -= 1
        self.element_count -= 1

    def contains(self, element):
        hashes = self._hashes(element)
        indices = self._indices(hashes)
        return all(self.filter[index] > 0 for index in indices)

    def _false_positive_probability(self):
        return (1 - math.exp(-self.num_hashes * self.element_count / self.size)) ** self.num_hashes

    def resize(self, new_size):
        old_elements = [i for i, count in enumerate(self.filter) if count > 0]
        self.size = new_size
        self.filter = [0] * new_size
        self.hash_seeds = [random.randint(0, 2**32 - 1) for _ in range(self.num_hashes)]
        for element in old_elements:
            self.add(str(element))  # Rehashing elements with new size


class UniqueList:
    def __init__(self, data_type, hash_function, compare_function, filter_size=INITIAL_SIZE, filter_num_hashes=NUM_HASHES, filter_resize_threshold=RESIZE_THRESHOLD, filter_resize_factor=RESIZE_FACTOR):
        self.data_type = data_type
        self.hash_function = hash_function
        self.compare_function = compare_function
        self.elements = []
        self.filter = CountFilter(size=filter_size, num_hashes=filter_num_hashes, resize_threshold=filter_resize_threshold, resize_factor=filter_resize_factor)

    def insert(self, element):
        element_bytes = self.data_type(element)
        element_hash = self.hash_function(element_bytes, len(element_bytes))
        
        if not self.filter.contains(element_hash):
            self.elements.append(element)
            self.filter.add(element_hash)
            return True
        else:
            for el in self.elements:
                if self.compare_function(el, element):
                    return False
            self.elements.append(element)
            self.filter.add(element_hash)
            return True

    def delete(self, element):
        element_bytes = self.data_type(element)
        element_hash = self.hash_function(element_bytes, len(element_bytes))
        
        if self.filter.contains(element_hash):
            for el in self.elements:
                if self.compare_function(el, element):
                    self.elements.remove(el)
                    self.filter.remove(element_hash)
                    return True
        return False

    def resize_filter(self, new_size):
        self.filter.resize(new_size)


# Ejemplo de uso:

def example_hash_function(data, length):
    return hashlib.sha256(data).hexdigest()

def example_compare_function(el1, el2):
    return el1 == el2

# Crear una lista única para almacenar strings
unique_list = UniqueList(lambda x: x.encode('utf-8'), example_hash_function, example_compare_function)

# Insertar elementos
print(unique_list.insert("hello"))  # True
print(unique_list.insert("world"))  # True
print(unique_list.insert("hello"))  # False

# Eliminar elementos
print(unique_list.delete("hello"))  # True
print(unique_list.delete("hello"))  # False

# Redimensionar el filtro de conteo manualmente
unique_list.resize_filter(2000)
