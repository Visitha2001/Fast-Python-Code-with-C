import time
import threading

def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n-1)

def worker(n, n_repetitions):
    for i in range(n_repetitions):
        factorial(n)

if __name__ == "__main__":
    threads = [
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
        threading.Thread(target=worker, args=(20, 5000000)),
    ]
    start = time.perf_counter()
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()
    end = time.perf_counter()
    print(f"Time taken: {end - start}")