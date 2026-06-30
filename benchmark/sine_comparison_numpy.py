import time
import numpy as np

MAX_ORDER = 100
O2_FACTOR = 10
ITERATIONS = 100

class BinomialCoeffs:
    def __init__(self, num: int):
        self.values = np.zeros((num + 1, num + 1), dtype=np.float64)
        
        self.values[:, 0] = 1.0
        
        for n in range(1, num + 1):
            self.values[n, 1:n+1] = self.values[n-1, 0:n] + self.values[n-1, 1:n+1]

    def get_row(self, n: int) -> np.ndarray:
        return self.values[n, :n + 1]

nCr = BinomialCoeffs(MAX_ORDER * O2_FACTOR)

def derivatives_1(u: np.ndarray, order: int) -> np.ndarray:
    f = np.zeros(order + 1, dtype=np.float64)
    f[0] = np.sin(u[0])
    
    if order == 0:
        return f
        
    cosu = np.cos(u[0])
    tanu = np.tan(u[0])
    f[1] = u[1] * cosu

    for n in range(2, order + 1):
        f[n] = u[n] * cosu - u[1] * f[n - 1] * tanu

        total_sum = 0.0
        for k in range(1, n - 1):
            coeffs_1 = nCr.get_row(k)
            coeffs_2 = nCr.get_row(n - k - 1)

            inner_sum_1 = np.sum(coeffs_1 * u[1:k + 2] * f[k::-1])
            
            inner_sum_2 = np.sum(coeffs_2 * u[1:n - k + 1] * f[n - k - 1::-1])
            
            term1 = u[k + 1] * (u[n - k] - 2.0 * u[1] * f[0] * f[n - k - 1])
            term2 = f[k + 1] * f[n - k]
            term3 = inner_sum_1 * inner_sum_2
            
            total_sum += term1 - term2 - term3
        
        f[n] -= total_sum / (2.0 * f[1])
    
    return f

def derivatives_2(u: np.ndarray, order: int) -> np.ndarray:
    f = np.zeros(order + 1, dtype=np.float64)
    f[0] = np.sin(u[0])

    if order == 0:
        return f
    
    cosu = np.cos(u[0])
    tanu = np.tan(u[0])
    f[1] = u[1] * cosu
    
    h = np.zeros(order, dtype=np.float64)

    for n in range(2, order + 1):
        
        coeffs_h = nCr.get_row(n - 1)
        h[n - 1] = np.sum(coeffs_h * u[1:n + 1] * f[n - 1::-1])

        if n > 2:
            coeffs_t = nCr.get_row(n - 1)[1:n - 1]
            
            total_sum = np.sum(coeffs_t * (
                u[2:n] * u[n - 1:1:-1] - 
                h[1:n - 1] * h[n - 2:0:-1] - 
                f[2:n] * f[n - 1:1:-1]
            ))
        else:
            total_sum = 0.0
            
        total_sum /= (2.0 * f[1])
        f[n] = u[n] / cosu - h[n - 1] * tanu + total_sum
    
    return f

def product_derivative(u: np.ndarray, v: np.ndarray, order: int) -> float:
    coeffs = nCr.get_row(order)
    return np.sum(coeffs * u[order::-1] * v[:order + 1])

def product_derivatives(u: np.ndarray, v: np.ndarray, order: int) -> np.ndarray:
    return np.array([product_derivative(u, v, n) for n in range(order + 1)])

def derivatives_3(u: np.ndarray, order: int) -> np.ndarray:
    f = np.zeros(order + 1, dtype=np.float64)
    f[0] = np.sin(u[0])

    if order == 0:
        return f
    
    f[1] = u[1] * np.cos(u[0])
    u1 = u[1:] 
    
    h = product_derivatives(u1, u1, order - 1)
    v = np.zeros(order, dtype=np.float64)
    v[0] = f[0] * f[0]

    for n in range(2, order + 1):
        v[n - 1] = product_derivative(f, f, n - 1)

        if n > 2:
            coeffs_t = nCr.get_row(n - 1)[1:n - 1]
            inner_sum = np.sum(coeffs_t * (
                h[1:n - 1] * v[n - 2:0:-1] + 
                f[2:n] * f[n - 1:1:-1]
            ))
        else:
            inner_sum = 0.0

        f[n] = (
            h[n - 1] * (1.0 - v[0]) - 
            h[0] * v[n - 1] -
            inner_sum
        ) / (2.0 * f[1])
    
    return f

def benchmark_function(func, u: np.ndarray, max_order: int):
    with open(func.__name__ + ".txt", "w") as file:
        for order in range(0, max_order + 1, 2):
            start: float = time.perf_counter()
            for _ in range(ITERATIONS):
                result = func(u, order)
            end: float = time.perf_counter()
            file.write(f"order={order} average_time_per_function_call={(((end-start)/ITERATIONS)*1000):.6f}ms\n")
    print(func.__name__ + " is done")

def benchmark():
    u_arr = np.random.uniform(-1.0, 1.0, size=(MAX_ORDER * O2_FACTOR + 1))
    
    benchmark_function(derivatives_1, u_arr, MAX_ORDER)
    benchmark_function(derivatives_2, u_arr, MAX_ORDER * O2_FACTOR)
    benchmark_function(derivatives_3, u_arr, MAX_ORDER * O2_FACTOR)

if __name__ == "__main__":
    benchmark()