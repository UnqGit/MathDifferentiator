#include <random>
#include <fstream>
#include <format>
#include <string>
#include <string_view>
#include <vector>
#include <span>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <iostream>

using container = std::vector<long double>;
using view = std::span<const long double>;

long double random_number_generator() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<long double> distribution(-1.0L, 1.0L);
    return distribution(gen);
}

std::vector<container> generate_random_lists(uint16_t order) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distribution(1, 100);

    std::vector<container> lists (distribution(gen), container(order + 1));
    for (auto &list : lists)
        for (auto &num : list)
            num = random_number_generator();
    return lists;
}

class BinomialCoeffs {
public:
    static BinomialCoeffs& instance() {
        static BinomialCoeffs inst;
        return inst;
    }

    void makeTill(uint16_t layer) {
        if (layer <= layerMade) return;
        if (layer % 2 == 1) {
            uint32_t tn = (layer + 1) / 2;
            values.resize(tn * (tn + 1));
        }
        else {
            uint32_t sqn = layer / 2 + 1;
            values.resize(sqn * sqn);
        }
        for (uint32_t i = layerMade + 1; i <= layer; i++) {
            makeLayer(i);
            layerMade++;
        }
    }

    long double operator()(uint32_t n, uint32_t r) const {
        if (r >= n / 2) r = n - r;
        return values[convertToIndex(n, r)];
    }

    BinomialCoeffs(const BinomialCoeffs&) = delete;
    BinomialCoeffs& operator=(const BinomialCoeffs&) = delete;

private:
    BinomialCoeffs() : values({1.0L}), layerMade(0) {}

    void makeLayer(uint32_t layer) {
        uint32_t idx = convertToIndex(layer, 0);
        uint32_t previdx = convertToIndex(layer - 1, 0);
        values[idx++] = 1;
        for (uint32_t i = 1; i < layer / 2 + 1; i++) {
            if (layer % 2 == 0 && i == layer / 2) {
                values[idx++] = 2 * values[previdx++];
            }
            else {
                values[idx++] = values[previdx] + values[previdx + 1];
                previdx++;
            }
        }
    }

    uint32_t convertToIndex(uint32_t n, uint32_t r) const {
        if (n % 2 == 0) return n * (n + 2) / 4 + r;
        else return (n + 1) * (n + 1) / 4 + r;
    }
    
    std::vector<long double> values;
    uint32_t layerMade;
};

BinomialCoeffs &nCr = BinomialCoeffs::instance();

using FuncPtr = container(*)(const container&, uint32_t);
void benchmark_function(std::string_view fileName, FuncPtr func, uint16_t maxOrder, uint16_t iterations) {
    std::ofstream file(fileName.data());
    auto rand_index = [](std::size_t size) {
        return static_cast<std::size_t>(std::floor(size * std::abs(random_number_generator())));
    };
    container whole_result; // so that compiler won't optimize away the result
    for (uint16_t order = 0; order <= maxOrder; order += 2) {
        long double accumulator{};
        auto u_lists = generate_random_lists(order);
        auto start = std::chrono::high_resolution_clock::now();
        for (uint16_t it = 0; it < iterations; it++) {
            container result = func(u_lists[rand_index(u_lists.size())], order);
            accumulator += result[rand_index(result.size())] * random_number_generator(); // taking a random input from the result, hopefully eliminating DCE
        }
        auto stop = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
        file << std::format("order={} average_time_per_function_call={:.6f}ms\n", order, static_cast<long double>(duration)/(1000 * iterations));
        whole_result.emplace_back(accumulator);
    }
    long double acc{};
    for (auto &i : whole_result) if (i > random_number_generator()) acc += i / 2;
    std::cout << acc << '\n';
}

container derivatives_1(const container &u, uint32_t order) {
    container f(order + 1);
    f[0] = std::sin(u[0]);
    if (order == 0) return f;
    
    long double cosu = std::cos(u[0]), tanu = std::tan(u[0]);
    f[1] = u[1] * cosu;

    for (uint32_t n = 2; n <= order; n++) {
        f[n] = u[n] * cosu - u[1] * f[n-1] * tanu;

        long double sum{};
        for (uint32_t k = 1; k < n - 1; k++) {
            long double inner_sum_1{};
            for (uint32_t r = 0; r <= k; r++)
            inner_sum_1 += nCr(k, r) * u[r + 1] * f[k-r];
            
            long double inner_sum_2{};
            for (uint32_t r = 0; r < n - k; r++)
                inner_sum_2 += nCr(n-k-1, r) * u[r + 1] * f[n-k-r-1];
            
            sum += u[k+1]*(u[n-k]-2*u[1]*f[0]*f[n-k-1]);
            sum -= f[k+1]*f[n-k];
            sum -= inner_sum_1 * inner_sum_2;
        }    
        f[n] -= sum / (2 * f[1]);
    }

    return f;
}

long double product_derivative(view u, view v, uint32_t order) {
    long double result = 0.0L;
    for (uint32_t k = 0; k <= order; k++)
        result += nCr(order, k) * u[order - k] * v[k];    
    return result;
}

container derivatives_2(const container &u, uint32_t order) {
    container f(order + 1);
    f[0] = std::sin(u[0]);

    if (order == 0) return f;
    
    long double cosu = std::cos(u[0]);
    f[1] = u[1] * cosu;

    if (order == 1) return f; // to avoid unnecessary calculations and allocations
    
    long double tanu = std::tan(u[0]);
    container h(order);
    view u1 = view(u).subspan(1);

    for (uint32_t n = 2; n <= order; n++) {
        h[n - 1] = product_derivative(u1, f, n - 1);

        long double sum{};
        for (uint32_t k = 1; k < n - 1; k++)
            sum += nCr(n-1, k) * (u[k+1] * u[n-k] - h[k] * h[n-k-1] - f[k+1] * f[n-k]);
        sum /= 2 * f[1];
        
        f[n] = u[n] / cosu - h[n-1] * tanu + sum;
    }
    return f;
}

container product_derivatives(view u, view v, uint32_t order) {
    container f(order+1);
    for (uint32_t n = 0; n <= order; n++) 
        f[n] = product_derivative(u, v, n);
    return f;
}

container derivatives_3(const container &u, uint32_t order) {
    container f(order+1);
    f[0] = std::sin(u[0]);

    if (order == 0) return f;
    
    f[1] = u[1] * std::cos(u[0]);
    if (order == 1) return f; // avoiding unnecessary calculations and allocations

    view u1 = view(u).subspan(1);
    container h = product_derivatives(u1, u1, order - 1);

    container v(order);
    v[0] = f[0] * f[0];

    for (uint32_t n = 2; n <= order; n++) {
        v[n-1] = product_derivative(f, f, n-1);

        for (uint32_t k = 1; k < n - 1; k++) 
            f[n] -= nCr(n-1, k) * (h[k] * v[n-k-1] + f[k+1] * f[n-k]);
        f[n] += h[n-1] * (1 - v[0]) - h[0] * v[n-1];
        f[n] /= 2 * f[1];
    }
    
    return f;
}

int main() {
    constexpr uint16_t order_o3 = 175;
    constexpr uint16_t order_o2 = 1000;
    constexpr uint16_t iterations = 100;

    nCr.makeTill(order_o2);

    benchmark_function("derivatives_1.txt", derivatives_1, order_o3, iterations);
    benchmark_function("derivatives_2.txt", derivatives_2, order_o2, iterations);
    benchmark_function("derivatives_3.txt", derivatives_3, order_o2, iterations);
}