import time
import random
import sys
sys.setrecursionlimit(1000000)

def bubble_sort(arr):
    """Пузырьковая сортировка"""
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr

def quick_sort(arr):
    """Быстрая сортировка"""
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def merge_sort(arr):
    """Сортировка слиянием"""
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def measure_time(sort_func, arr):
    """Замер времени выполнения"""
    arr_copy = arr.copy()
    start = time.perf_counter()
    sort_func(arr_copy)
    end = time.perf_counter()
    return (end - start) * 1000  # мс

if __name__ == "__main__":
    sizes = [1000, 5000, 10000, 50000]
    print("Сравнение алгоритмов сортировки на Python")
    print("=" * 60)
    print(f"{'Размер':>8} | {'Quick (мс)':>10} | {'Merge (мс)':>10} | {'Bubble (мс)':>10}")
    print("-" * 60)
    
    for size in sizes:
        test_arr = [random.randint(1, 100000) for _ in range(size)]
        
        t_quick = measure_time(quick_sort, test_arr)
        t_merge = measure_time(merge_sort, test_arr)
        
        # Bubble только для маленьких размеров
        if size <= 5000:
            t_bubble = measure_time(bubble_sort, test_arr)
            print(f"{size:8} | {t_quick:10.2f} | {t_merge:10.2f} | {t_bubble:10.2f}")
        else:
            print(f"{size:8} | {t_quick:10.2f} | {t_merge:10.2f} | {'N/A':>10}")