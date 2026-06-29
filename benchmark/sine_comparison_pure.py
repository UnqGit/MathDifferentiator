import time
import math
import random

MAX_ORDER = 100
O2_FACTOR = 5
ITERATIONS = 100

class BinomialCoeffs:
    def __init__(self, num: int):
        # Calculate the total size needed for the 1D flat array
        if num % 2 == 1:
            tn = (num + 1) // 2
            size = tn * (tn + 1)
        else:
            sqn = num // 2 + 1
            size = sqn * sqn
            
        # Initialize the flat array
        self.values = [0] * size
        self.values[0] = 1
        
        for layer in range(1, num + 1):
            idx = self._convert_to_index(layer, 0)
            previdx = self._convert_to_index(layer - 1, 0)
            
            self.values[idx] = 1
            idx += 1
            
            for i in range(1, layer // 2 + 1):
                # If even layer and we're at the exact middle element
                if layer % 2 == 0 and i == layer // 2:
                    self.values[idx] = 2 * self.values[previdx]
                else:
                    self.values[idx] = self.values[previdx] + self.values[previdx + 1]
                
                idx += 1
                previdx += 1

    def _convert_to_index(self, n: int, r: int) -> int:
        if n % 2 == 0:
            return n * (n + 2) // 4 + r
        else:
            return (n + 1) * (n + 1) // 4 + r

def create_binomialCoeffs(order: int):
    values = BinomialCoeffs(order)
    
    def coeffs(n: int, r: int) -> int:
        # Exploit symmetry for r > n // 2
        if r > n // 2:
            r = n - r
        return values.values[values._convert_to_index(n, r)]
        
    return coeffs

nCr = create_binomialCoeffs(MAX_ORDER*O2_FACTOR)

def derivatives_1(u_list: list[float], order: int) -> list[float]:
    f_list: list[float] = [0.0] * (order + 1)
    f_list[0] = math.sin(u_list[0])
    
    if order == 0:
        return f_list
        
    cosu: float = math.cos(u_list[0])
    tanu: float = math.tan(u_list[0])
    f_list[1] = u_list[1] * cosu

    for n in range(2, order + 1):
        f_list[n] = u_list[n] * cosu - u_list[1] * f_list[n - 1] * tanu

        total_sum: float = 0.0
        for k in range(1, n - 1):
            
            inner_sum_1: float = sum(
                nCr(k, r) * u_list[r + 1] * f_list[k - r] 
                for r in range(k + 1)
            )
            
            inner_sum_2: float = sum(
                nCr(n - k - 1, r) * u_list[r + 1] * f_list[n - k - r - 1] 
                for r in range(n - k)
            )
            
            term1: float = u_list[k + 1] * (u_list[n - k] - 2 * u_list[1] * f_list[0] * f_list[n - k - 1])
            term2: float = f_list[k + 1] * f_list[n - k]
            term3: float = inner_sum_1 * inner_sum_2
            
            total_sum += term1 - term2 - term3
        
        f_list[n] -= total_sum / (2 * f_list[1])
    
    return f_list

def derivatives_2(u_list: list[float], order: int) -> list[float]:
    f_list: list[float] = [0.0] * (order + 1)
    f_list[0] = math.sin(u_list[0])

    if order == 0:
        return f_list
    
    cosu: float = math.cos(u_list[0])
    tanu: float = math.tan(u_list[0])

    f_list[1] = u_list[1] * cosu
    
    h_list: list[float] = [0.0] * order

    for n in range(2, order + 1):

        h_list[n - 1] = sum(
            nCr(n - 1, k) * u_list[k + 1] * f_list[n - 1 - k]
            for k in range(n)
        )

        total_sum: float = sum(
            nCr(n - 1, k) * (
                (u_list[k + 1] * u_list[n - k]) - 
                (h_list[k] * h_list[n - k - 1]) - 
                (f_list[k + 1] * f_list[n - k])
            )
            for k in range(1, n - 1)
        )
        
        total_sum /= (2 * f_list[1])
        
        f_list[n] = u_list[n] / cosu - h_list[n - 1] * tanu + total_sum
    
    return f_list

def product_derivative(u_list: list[float], v_list: list[float], order: int) -> float:
    return sum(
        nCr(order, k) * u_list[order-k] * v_list[k]
        for k in range(order + 1)
    )

def product_derivatives(u_list: list[float], v_list: list[float], order: int) -> list[float]:
    return [product_derivative(u_list, v_list, n) for n in range(order + 1)]

def derivatives_3(u_list: list[float], order: int) -> list[float]:
    f_list: list[float] = [0.0] * (order + 1)
    f_list[0] = math.sin(u_list[0])

    if order == 0:
        return f_list
    
    f_list[1] = u_list[1] * math.cos(u_list[0])

    u1_list: list[float] = u_list[1:]
    h_list: list[float] = product_derivatives(u1_list, u1_list, order - 1)

    v_list: list[float] = [0.0] * order
    v_list[0] = f_list[0] * f_list[0]

    for n in range(2, order + 1):
        v_list[n-1] = product_derivative(f_list, f_list, n-1)

        f_list[n] = (
            h_list[n-1] * (1 - v_list[0]) - 
            h_list[0] * v_list[n-1] -
            sum(
                nCr(n-1, k) * (h_list[k] * v_list[n-k-1] + f_list[k+1] * f_list[n-k])
                for k in range(1, n-1)
            )
        ) / (2 * f_list[1])
    
    return f_list

def benchmark_function(func, u_list: list[float], max_order: int):
    with open(func.__name__ + ".txt", "w") as file:
        for order in range(0, max_order + 1, 2):
            start: float = time.perf_counter()
            for _ in range(ITERATIONS):
                result = func(u_list, order)
            end: float = time.perf_counter()
            file.write(f"order={order} average_time_per_function_call={(((end-start)/ITERATIONS)*1000):.6f}ms\n")
    print(func.__name__ + " is done")

def benchmark():
    u_list: list[float] = [random.uniform(-1.0, 1.0) for _ in range(MAX_ORDER * O2_FACTOR + 1)]
    benchmark_function(derivatives_1, u_list, MAX_ORDER)
    benchmark_function(derivatives_2, u_list, MAX_ORDER * O2_FACTOR)
    benchmark_function(derivatives_3, u_list, MAX_ORDER * O2_FACTOR)

if __name__ == "__main__":
    benchmark()