# Arcsec and Arccos

## Arcsec

Let's start with the function $f = \text{arcsec}(u)$.  
Which also gives us:
```math
\sec(f) = u
```
Differentiating it, gives us:
```math
f_1\sec(f)\tan(f) = u_1
```
Which also means:
```math
f_1\sec^2(f)\sin(f) = u_1
```
or:
```math
f_1\sin(f) = u_1\cos^2(f)
```
And if we consider $v = \cos^2(f)$, we get:
```math
f_1\sin(f) = u_1v
```
and differentiating it $n-1$ terms gives us:
```math
\sum_{k=0}^{n-1} \binom{n-1}{k} f_{n-k}D^k(\sin(f)) = \sum_{k=0}^{n-1} \binom{n-1}{k} u_{n-k}v_{k}
```
Since $k=0$ gives us $f_n\sin(f)$, we can isolate $f_n$:
```math
f_n = \frac {1} {\sin(f)} \left(u_nv + \sum_{k=1}^{n-1} \binom{n-1}{k} u_{n-k}v_{k} - \sum_{k=1}^{n-1} \binom{n-1}{k} f_{n-k}D^k(\sin(f))\right)
```
or:

#### Formula
```math
f_n = \frac {1} {\sin(f)} \left(u_nv + \sum_{k=1}^{n-1} \binom{n-1}{k} (u_{n-k}v_{k} - f_{n-k}D^k(\sin(f)))\right)
```
Where:
```math
v_n = D^n(\cos^2(f))
```

#### Implementation
```python
import math

def arcsec_derivatives(u_list, order):
    # u_list contains the derivatives of u from order 0..n

    f_list = u_list # initialize f_i as u_i
    f_list[0] = math.acos(1 / u_list[0])  # f = arcsec(u)

    if order > 0:
        exp_polar_list = [0.0 + 0.0j] * order
        exp_polar_list[0] = complex(math.cos(f_list[0]), math.sin(f_list[0]))
        v_list = [0.0] * order
        v_list[0] = exp_polar_list[0].real ** 2  # v = cos^2(f)

        f_list[1] = u_list[1] * v_list[0] / math.sin(f_list[0])
        for n in range(2, order + 1):
            # calculation of (n-1)th derivative of e^(i*f)
            for k in range(n - 1):
                exp_polar_list[n - 1] += nCr(n-2, k) * f_list[n-k-1] * exp_polar_list[k]
            exp_polar_list[n-1] *= 1.0j

            # calculation of (n-1)th derivative of cos^2(f)
            for k in range(n):
                v_list[n-1] += nCr(n-1, k) * exp_polar_list[k].real * exp_polar_list[n-1-k].real
            
            f_list[n] *= v_list[0] # u_i * v
            for k in range(1, n):
                f_list[n] += nCr(n-1, k) * (u_list[n-k] * v_list[k] - f_list[n-k] * exp_polar_list[k].imag)

            f_list[n] /= exp_polar_list[0].imag  # divide by sin(f)

    return f_list
```
But we know that $\text{arcsec}(u) = \arccos(\frac 1u)$.  
And since we have the formula to calculate the $n^{th}$ derivatives of reciprocals and $\arccos$, we can use it to calculate the $n^{th}$ derivatives of $\text{arcsec}(u)$.

#### Implementation
```python
def arcsec_derivatives(u_list, order):
    return arccos_derivatives(reciprocal_derivatives(u_list, order), order)
```
And since it doesn't require an extra auxiliary variable (`v_list` here), and the required calculations are done on `u_list` before passing it to `arccos_derivatives`, this implementation is more efficient than the previous one.  
And from software engineering perspective, it is also more maintainable and readable.

## Arccsc
We can go with the same route as we did for $\text{arcsec}(u)$, but we can also use the fact that $\text{arccsc}(u) = \arcsin(\frac 1u)$, and since we have the formula to calculate the $n^{th}$ derivatives of reciprocals and $\arcsin$, we can use it to calculate the $n^{th}$ derivatives of $\text{arccsc}(u)$.

#### Implementation
```python
def arccsc_derivatives(u_list, order):
    return arcsin_derivatives(reciprocal_derivatives(u_list, order), order)
```