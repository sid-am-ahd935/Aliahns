import time
import random


def timeit(func= None, *args, **kwargs):
    a = time.time()
    returned_items = func(*args, **kwargs)
    b = time.time()
    return (returned_items, b - a)

generate_values = lambda n : [random.randint(-n, n) for i in range(n)]

# __________________________________________________________ #
#### ________   Change Only From Below Section   ________ ####

def main():
    from cython_sorting import cython_bubble_sort
    from python_sorting import python_bubble_sort

    values = generate_values(n= 10000)
    array1, t1 = timeit(
        cython_bubble_sort.sort,
        values.copy()
    )
    array2, t2 = timeit(
        python_bubble_sort.sort,
        values.copy()
    )

    print(f"Cython takes: {t1:0.3f} seconds")
    print(f"Python takes: {t2:0.3f} seconds")
    print(f"Cython is {t2/t1:0.2f}x faster than Python!")
    print(f"Same returned value: {array1 == array2}")
    # print(array2)


if __name__ == "__main__":
    main()