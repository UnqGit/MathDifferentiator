# MathDifferentiator

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Python Version](https://img.shields.io/badge/Python-3.x-blue.svg)](https://python.org)

**MathDifferentiator** is a lightweight framework for efficiently computing higher-order derivatives of composite functions using recurrence relations.

Instead of symbolic differentiation or finite-difference approximations, MathDifferentiator propagates derivative sequences through compact recurrence relations, allowing efficient computation of derivatives of arbitrary order.

---

## 🚀 Quick Start
Get started in seconds and compute higher-order derivatives in just a few lines of code.

### Installation
Install the Python package:
```bash
pip install unqnumericaldiff
```
Or use the standalone C++ implementation from [`src/`](src/).

### Usage Example  
For an arbitrary function:
```Python
import unqnumericaldiff as diff

# LaTeX text containing the function
function_latex = r'\frac{\exp(-x^2+7x+2)}{x^3+45x}' # (e^(-x^2+7x+2)) / (x^3+45x)
point = -1.0
order = 20

# Compute the first 20 derivatives at x = -1
derivatives = diff.differentiate(function_latex, point, order)
```
Or composition:
```Python
import unqnumericaldiff as diff

# Plain ASCII text containing the function
u = '(x^2+5x)/(2x)'
order = 5
point = 2.5

# u_list contains the first five derivatives of u(x)
u_list = diff.differentiate(u, point, order)

# Finding the first five derivatives of sin(u(x))
derivatives = diff.sin_derivatives(u_list, order)

print(f"The first {order} derivatives of sin(u(x)) are: {derivatives}")
```

## 🛠️ Features
- Computes derivatives of all orders $0$ through $n$ for the following classes of functions evaluated at a given point:
    - Arithmetic:
        - Product: $u(x)\cdot v(x)$
        - Fractions & Quotients: $\frac {1} {u(x)}$ and $\frac{u(x)}{v(x)}$
    - Exponential & Power Functions:
        - Exponential: $e^{u(x)}$ and $a^{u(x)}$
        - Logarithms: $\ln(u(x))$ and $\log_{v(x)}(u(x))$
        - Constant powers: $\sqrt{u(x)}$ and $u(x)^c$
        - Variable powers: $u(x)^{v(x)}$
    - Trigonometry:
        - $\sin(u(x))$ & $\cos(u(x))$
        - $\cot(u(x))$ & $\tan(u(x))$
        - $\csc(u(x))$ & $\sec(u(x))$
    - Inverse Trigonometry:
        - $\sin^{-1}(u(x))$ & $\cos^{-1}(u(x))$
        - $\cot^{-1}(u(x))$ & $\tan^{-1}(u(x))$
        - $\csc^{-1}(u(x))$ & $\sec^{-1}(u(x))$
    - Hyperbolic Trigonometry:
        - $\sinh(u(x))$ & $\cosh(u(x))$
        - $\coth(u(x))$ & $\tanh(u(x))$
        - **csch** $(u(x))$ & **sech** $(u(x))$

- **Full sequences**: Computes all derivatives from order $0$ up to a desired order $n$ in $O(n^2)$.  
- **Targeted orders**: Computes the nth derivative in O(n) when all derivatives of the inner function and previously calculated derivatives of the function are available.  
- All algorithms operate directly on sequences of previously computed derivatives rather than symbolic expressions.  
- **Numerical stability**: Provides higher numerical stability since it doesn't require finite difference approximations.  
- Lower memory footprint than symbolic differentiation.

## 🎯 Motivation
Most symbolic approaches eventually produce extremely large intermediate expressions, often involving Bell polynomials or expansions of the Faà di Bruno formula.

This project instead derives compact recurrence relations that reuse previously computed derivatives, making practical implementations both simple and efficient.

The goal is not to replace computer algebra systems, but to provide elegant algorithms that are easy to implement and run in $O(n^2)$.

See [introduction.md](docs/introduction.md) for the story behind the project.

## ⚡ Performance & Benchmarks  
- **No finite-difference step size**: Eliminates the approximation error and numerical instability associated with choosing a finite-difference step.
- **Efficient**: The optimized C++ implementations can compute derivatives of order $0$ through $1000$ of $\sin(u(x))$ in roughly **4.6ms** on an *AMD Ryzen 7 8845HS*.

> See the [benchmark source code](benchmark/) and [sine documentation](docs/sin-cos.md) for full details.

## 📝 Documentation
At its core, the library derives recurrence relations for each supported elementary function, allowing higher-order derivatives to be computed efficiently from previously computed derivative values.  
Each recurrence relation is derived from classical calculus identities such as Leibniz's rule, rather than presented as a black-box algorithm.  
To see how these formulae are derived, refer to the documentation:
- [`Introduction`](docs/introduction.md)
- [`Product Rule`](docs/product.md)
- [`Quotient Rule`](docs/quotient.md)
- [`Logarithms`](docs/logarithm.md)
- [`Powers`](docs/power-functons/)
- [`Trigonometric Functions`](docs/trigonometry/)
- [`Inverse Trigonometric Functions`](docs/inverse-trigonometry/)
- [`Hyperbolic Functions`](docs/hyperbolic-functions/)

## 🤝 Contributing
Interested in mathematical algorithms or optimizations? We're always looking to expand the library with new functions (gamma functions, elliptic integrals, Airy functions, etc.).
1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingMath`)
3. Commit your Changes (`git commit -m 'Add inverse hyperbolic functions'`)
4. Push to the Branch (`git push origin feature/AmazingMath`)
5. Open a Pull Request

## 📜 License
Distributed under the MIT License. See [LICENSE](LICENSE.md) for more information.