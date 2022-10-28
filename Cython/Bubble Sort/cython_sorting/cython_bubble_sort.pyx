# cython: language_level=3

from array import array
from cpython cimport array


cpdef int[:] c_sort(int[:] arr, int n):
    cdef int i, j

    for i in range(n):
        for j in range(n - i - 1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

    return arr


cpdef list sort(list arr):
    cdef int[:] c_arr = array("i", arr)
    cdef int[:] s_arr

    s_arr = c_sort(c_arr, len(arr))
    return list(s_arr)