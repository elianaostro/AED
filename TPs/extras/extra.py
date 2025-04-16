import hashlib

def hash_value(value):
    return int(hashlib.md5(value.encode()).hexdigest(), 16)

def flajolet_martin(data):
    max_zeroes = 0
    for element in data:
        hash_val = hash_value(element) % (2**32)
        binary_representation = bin(hash_val)[2:]
        zero_count = len(binary_representation) - len(binary_representation.rstrip('0'))
        if zero_count > max_zeroes:
            max_zeroes = zero_count
    return 2**max_zeroes / 0.77531 

data = ["element1", "element2", "element3"]
print("Flajolet-Martin estimation:", flajolet_martin(data))

import random

def carter_wegman_hash(x, a, b, p=2**32-5, m=2**32):
    return ((a * x + b) % p) % m

def loglog(data, k=10):
    max_zeroes_list = [0] * k
    random_coeffs = [(random.randint(1, 2**32-6), random.randint(0, 2**32-6)) for _ in range(k)]

    for element in data:
        h_val = hash_value(element) % (2**32)
        for i in range(k):
            h_prime = carter_wegman_hash(h_val, random_coeffs[i][0], random_coeffs[i][1])
            binary_representation = bin(h_prime)[2:]
            zero_count = len(binary_representation) - len(binary_representation.rstrip('0'))
            if zero_count > max_zeroes_list[i]:
                max_zeroes_list[i] = zero_count

    harmonic_mean = sum([2**-z for z in max_zeroes_list]) / k
    return (1 / harmonic_mean) / 0.77531

data = ["element1", "element2", "element3"]
print("LogLog estimation:", loglog(data))
