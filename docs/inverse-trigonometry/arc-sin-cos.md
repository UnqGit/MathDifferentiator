# Arcsin and Arccos
We are finally stepping into the inverse realm of the trigonometric functions, the ones which undo the work of sin and cosine and answer the question what angle the result came from.

## Arcsin
The arcsin function is the inverse of our beloved sin function. That is:
```math
\begin{align*}
f &= \arcsin(u) \\
\sin(f) &= u \\
\end{align*}
```

### Derivation 1
Differentiating it, we get:
```math
f_1\cos(f) = u_1
```
Squaring both sides gives us:
```math
f_1^2\cos^2(f) = u_1^2
```
And since $\sin^2 + \cos^2 = 1$ and $\sin(f) = u$:
```math
f_1^2(1-u^2) = u_1^2
```
Or, simply put, our standard first derivative is:
```math
f_1 = \frac {u_1} {\sqrt {1-u^2}}
```
And since we have the formula for all the functions present here, it can be simply:

#### Implementation
```python
import math

def arcsin_derivatives(u_list, order):
    # u_list contains all the derivatives of u from order 0..n

    f_list = [math.asin(u_list[0])]

    if order > 0:
        den_list = product_derivatives(u_list, u_list, order - 1)
        den_list = [-u2 for u2 in den_list]
        den_list[0] += 1.0
        den_list = sqrt_derivatives(den_list, order - 1)

        f1_list = div_derivatives(u[1:], den_list, order - 1)
        f_list.extend(f1_list)

    return f_list
```
Which uses the product, square root and division derivative functions we derived. **Refer:**  
$\quad\rightarrow$ [`product.md`](../product.md)  
$\quad\rightarrow$ [`quotient.md`](../quotient.md)  
$\quad\rightarrow$ [`constant-power.md`](../power-functions/constant-power.md)

### Derivation 2
The above derivation does a lot of work, let's see if we can reduce it.  
The first derivative is:
```math
f_1 = \frac {u_1} {\sqrt {1-u^2}}
```
And the radical in the denominator will cause trouble for the chain rule, let's square both sides to get rid of it.
```math
f_1^2 = \frac {u_1^2} {1-u^2}
```
Multiply both sides with $1-u^2$:
```math
\begin{align*}
f_1^2(1 - u^2)&=u_1^2\\
f_1^2-f_1^2u^2 &= u_1^2\\
\end{align*}
```
Differentiating it $n-1$ times, we get:
```math
D^{n-1}(f_1^2) - D^{n-1}(f_1^2u^2) = D^{n-1}(u_1^2)
```
Taking $h = f_1^2$, $v = u^2$ and $g = u_1^2$, we have:
```math
h_{n-1}-D^{n-1}(hv)=g_{n-1}
```
And applying the Leibniz's rule, we have:
```math
h_{n-1}-\sum_{k=0}^{n-1}\binom{n-1}kh_kv_{n-k-1} = g_{n-1}
```
Where:
```math
\begin{align*}
h_n &= \sum_{k=0}^n \binom nk f_{k+1}f_{n-k+1}\\
v_n &= \sum_{k=0}^n \binom nk u_ku_{n-k} \\
g_n &= \sum_{k=0}^{n}\binom{n}{k}u_{k+1}u_{n-k+1} \\
\end{align*}
```
Here, $h_{n-1}$ contains the $f_n$ terms we desire to compute, so peeling that out of the summation, we get:
```math
2f_1f_n+\sum_{k=1}^{n-2}\binom{n-1}kf_{k+1}f_{n-k}-\sum_{k=0}^{n-1}\binom{n-1}kh_kv_{n-k-1} = g_{n-1}
```
We also have to extract the $h_{n-1}$ term from the second summation above and the $f_n$ terms from that, that is:
```math
2f_1f_n(1-v)+(1-v)\sum_{k=1}^{n-2}\binom{n-1}kf_{k+1}f_{n-k}-\sum_{k=0}^{n-2}\binom{n-1}kh_kv_{n-k-1} = g_{n-1}
```
And peel out the $k=0$ term from the second summations so join both summations:
```math
2f_1f_n(1-v)+(1-v)\sum_{k=1}^{n-2}\binom{n-1}kf_{k+1}f_{n-k}-hv_{n-1}-\sum_{k=1}^{n-2}\binom{n-1}kh_kv_{n-k-1} = g_{n-1}
```
Which makes the term $f_n$ equal to:
```math
f_n = \frac 1 {2f_1(1-v)} \left(g_{n-1} + hv_{n-1} +\sum_{k=1}^{n-2}\binom{n-1}k\left(h_kv_{n-k-1}-(1-v)f_{k+1}f_{n-k}\right)\right)
```
Or:

#### Formula
```math
f_n = \frac 1 {2u_1\sqrt{1-u^2}} \left(g_{n-1} + hv_{n-1} +\sum_{k=1}^{n-2}\binom{n-1}k\left(h_kv_{n-k-1}-(1-v)f_{k+1}f_{n-k}\right)\right)
```
Where:
```math
\begin{align*}
h_n &= \sum_{k=0}^n \binom nk f_{k+1}f_{n-k+1}\\
v_n &= \sum_{k=0}^n \binom nk u_ku_{n-k} \\
g_n &= \sum_{k=0}^{n}\binom{n}{k}u_{k+1}u_{n-k+1} \\
\end{align*}
```

#### Implementation
```python
import math

def arcsin_derivatives(u_list, order):
    f_list = [0.0] * (order + 1)
    f_list[0] = math.asin(u_list[0])

    if order == 0:
        return f_list
    
    div_factor = 2.0 * u_list[1] * math.sqrt(1 - u_list[0] * u_list[0])
    f_list[1] = 2.0 * u_list[1] / div_factor

    u1_list = u_list[1:]
    v_list = product_derivatives(u_list, u_list, order - 1)
    h_list = [0.0] * (order + 1)
    h_list[0] = f_list[1] * f_list[1]

    for n in range(2, order + 1):
        f1_list = f_list[1:]
        h_list[n-1] = product_derivatives(f1_list, f1_list, n-1)

        f_list[n] = product_derivative(u1_list, u1_list, n-1) + h_list[0] * v_list[n-1]

        for k in range(1, n-1):
            term1 = h_list[k] * v_list[n-k-1]
            term2 = f_list[k+1] * f_list[n-k]

            f_list[n] += nCr(n-1,k) * (term1 - (1 - v_list[0]) * term2)
        f_list[n] /= div_factor
    
    return f_list
```
Now, this is not in any way, shape or form better than the first derivation, this can be considered even worse from the implementation standpoint, as it is a lot harder to understand and maintain.

### Derivation 3
Let's look at this equation:
```math
f_1^2\cos^2(f) = u_1^2
```
Or:
```math
f_1\cos(f) = u_1
```
That we had whilst computing $f_1$.  
So instead of:
```math
f_1 = \frac {u_1} {\sqrt {1-u^2}}
```
We can also write it as:
```math
f_1 = \frac {u_1} {\cos(f)}
```
And taking $v = \cos(f)$ and differentiating both sides $n-1$ times, we get:

#### Formula
```math
f_n = \frac 1 {v} \left(u_n - \sum_{k=1}^{n-1}\binom{n-1}{k}f_{n-k}v_k\right)
```
For $v_n$ $\rightarrow$ **refer:** [`eulers-grace.md`](../trigonometry/eulers-grace.md).

#### Implementation
```python
import math

def arcsin_derivatives(u_list, order):
    f_list = u_list # initialize each index i with u_i
    f_list[0] = math.asin(u_list[0])

    if order > 0:
        polar_exp_list = [0.0 + 0.0j] * (order)
        polar_exp_list[0] = complex(math.cos(f_list[0]), math.sin(f_list[0]))
        f_list[1] /= polar_exp_list[0].real

        for n in range(2, order + 1):
            for k in range(n-1): # calculation of D^{n-1}(e^{if})
                polar_exp_list[n-1] += nCr(n-2, k) * polar_exp_list[k] * f_list[n-k-1]
            polar_exp_list[n-1] *= 1.0j

            for k in range(1, n):
                f_list -= nCr(n-1, k) * f_list[n-k] * polar_exp_list[k].real
            f_list[n] /= polar_exp_list[0].real

    return f_list
```

This implementation is completely self-contained unlike the first method and is not bloated like the second method.

## Arccos
Since $\arccos = \frac \pi {2} - \arcsin$, we can directly use its implementation.
### Implementation
```python
def arccos_derivatives(u_list, order):
    f_list = [-f for f in arcsin_derivatives(u_list, order)]
    f_list[0] += math.pi / 2.0

    return f_list
```
or we can write:
```math
f_1 = -\frac {u_1} {\sin(f)}
```
And use the third method's implementation with some modifications as:
```python
def arccos_derivatives(u_list, order):
    f_list = u_list # initialize each index i with u_i
    f_list[0] = math.acos(u_list[0])

    if order > 0:
        polar_exp_list = [0.0 + 0.0j] * (order)
        polar_exp_list[0] = complex(math.cos(f_list[0]), math.sin(f_list[0]))
        f_list[1] /= -polar_exp_list[0].imag

        for n in range(2, order + 1):
            for k in range(n-1): # calculation of D^{n-1}(e^{if})
                polar_exp_list[n-1] += nCr(n-2, k) * polar_exp_list[k] * f_list[n-k-1]
            polar_exp_list[n-1] *= 1.0j

            for k in range(1, n):
                f_list -= nCr(n-1, k) * f_list[n-k] * polar_exp_list[k].imag
            f_list[n] /= -polar_exp_list[0].imag

    return f_list
```