def es_heap(arr):
    for i in range(len(arr)):
        if i<arr[1]
    return True


def test(arr, expected, actual): 
    print("Testing array: ", arr)
    if(expected != actual):
        print('TEST FAILED')
    else: 
        print('TEST PASSED')

arr1 = [90, 15, 10, 7, 12, 2, 7]
test(arr1, True, es_heap(arr1))

arr2 = [9, 15, 10, 7, 12, 2, 7]
test(arr2, False, es_heap(arr2))

arr3 = [90, 15, 10, 7, 120, 2, 7]
test(arr3, False, es_heap(arr3))