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

container derivatives_1(const container &u_list, uint32_t order) {
    container f_list(order + 1);
    f_list[0] = std::sin(u_list[0]);
    if (order == 0) return f_list;
    
    long double cosu = std::cos(u_list[0]), tanu = std::tan(u_list[0]);
    f_list[1] = u_list[1] * cosu;

    for (uint32_t n = 2; n <= order; n++) {
        f_list[n] = u_list[n] * cosu - u_list[1] * f_list[n-1] * tanu;

        long double sum{};
        for (uint32_t k = 1; k < n - 1; k++) {
            long double inner_sum_1{};
            for (uint32_t r = 0; r <= k; r++)
            inner_sum_1 += nCr(k, r) * u_list[r + 1] * f_list[k-r];
            
            long double inner_sum_2{};
            
            for (uint32_t r = 0; r < n - k; r++)
                inner_sum_2 += nCr(n-k-1, r) * u_list[r + 1] * f_list[n-k-r-1];
            
            sum += u_list[k+1]*(u_list[n-k]-2*u_list[1]*f_list[0]*f_list[n-k-1]);
            sum -= f_list[k+1]*f_list[n-k];
            sum -= inner_sum_1 * inner_sum_2;
        }    
        f_list[n] -= sum / (2 * f_list[1]);
    }

    return f_list;
}

long double product_derivative(view u_list, view v_list, uint32_t order) {
    long double result = 0.0L;
    for (uint32_t k = 0; k <= order; k++)
        result += nCr(order, k) * u_list[order - k] * v_list[k];    
    return result;
}

container derivatives_2(const container &u_list, uint32_t order) {
    container f_list(order + 1);
    f_list[0] = std::sin(u_list[0]);

    if (order == 0) return f_list;
    
    long double cosu = std::cos(u_list[0]);
    f_list[1] = u_list[1] * cosu;

    if (order == 1) return f_list; // to avoid unnecessary calculations and allocations
    
    long double tanu = std::tan(u_list[0]);
    container h_list(order);
    view u1_list = view(u_list).subspan(1);

    for (uint32_t n = 2; n <= order; n++) {
        h_list[n - 1] = product_derivative(u1_list, f_list, n - 1);

        long double sum{};
        for (uint32_t k = 1; k < n - 1; k++)
            sum += nCr(n-1, k) * (u_list[k+1] * u_list[n-k] - h_list[k] * h_list[n-k-1] - f_list[k+1] * f_list[n-k]);
        sum /= 2 * f_list[1];
        
        f_list[n] = u_list[n] / cosu - h_list[n-1] * tanu + sum;
    }
    return f_list;
}

container product_derivatives(view u_list, view v_list, uint32_t order) {
    container f_list(order+1);
    for (uint32_t n = 0; n <= order; n++) 
        f_list[n] = product_derivative(u_list, v_list, n);
    return f_list;
}

container derivatives_3(const container &u_list, uint32_t order) {
    container f_list(order+1);
    f_list[0] = std::sin(u_list[0]);

    if (order == 0) return f_list;
    
    f_list[1] = u_list[1] * std::cos(u_list[0]);
    if (order == 1) return f_list; // avoiding unnecessary calculations and allocations

    view u1_list = view(u_list).subspan(1);
    container h_list = product_derivatives(u1_list, u1_list, order - 1);

    container v_list(order);
    v_list[0] = f_list[0] * f_list[0];

    for (uint32_t n = 2; n <= order; n++) {
        v_list[n-1] = product_derivative(f_list, f_list, n-1);

        for (uint32_t k = 1; k < n - 1; k++) 
            f_list[n] -= nCr(n-1, k) * (h_list[k] * v_list[n-k-1] + f_list[k+1] * f_list[n-k]);
        f_list[n] += h_list[n-1] * (1 - v_list[0]) - h_list[0] * v_list[n-1];
        f_list[n] /= 2 * f_list[1];
    }
    
    return f_list;
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