# Arctan and Arccos

## Arctan

Let's take our function $f = \arctan(u(x))$.  
Which will also equal:
```math
\tan(f) = u
```
Due to $\arctan$ and $\tan$ being inverses of each other.  
Derivating it will give us:
```math
\sec^2(f)f_1 = u_1
```
And since $\sec^2 = 1 + \tan^2$ and $\tan(f) = u$, we get:
```math
f_1 = \frac {u_1} {1 + u^2}
```
And indeed, this is the standard first derivative of $\arctan(u)$.

### Derivation

Let's look at the first derivative:
```math
f_1 = \frac {u_1} {1 + u^2}
```
multiply both sides with ${1+u^2}$:
```math
f_1(1 + u^2) = u_1
```
or:
```math
f_1 + f_1u^2 = u_1
```
let $v = u^2$:
```math
f_1 + f_1v = u_1
```
and differentiating $n-1$ times, we get:
```math
f_n + \sum_{k=0}^{n-1}f_{n-k}v_k = u_n
```
peeling out $k=0$ term from the summation which contains our desired $f_n$ term:
```math
f_n + f_nv + \sum_{k=1}^{n-1}f_{n-k}v_k = u_n
```
separating $f_n$ gives us our:

#### Formula
```math
f_n = \frac 1 {1+v} \left(u_n - \sum_{k=1}^{n-1}\binom {n - 1} k f_{n-k}v_k\right)
```
Where:
```math
v_n = \sum_{k=0}^n\binom nk u_ku_{n-k}
```

#### Implementation
Which we can implement like:
```python
import math

def arctan_derivatives(u_list, order):
    # u_list contains all the derivatives of u from order 0..n

    f_list = u_list # initialize f_i with u_i
    f_list[0] = math.atan(u_list[0])
    v_list = product_derivatives(u_list, u_list, order - 1) # derivatives of u^2

    # outer loop to calculate all derivatives of f
    for n in range(1, order + 1):

        # inner loop to calculate individual f{m}
        for k in range(1, n):
            f_list[n] -= nCr(n-1, k) * f_list[n-k] * v_list[k]
        f_list[n] /= 1 + v_list[0]

    return f_list
```

## Arccot:
Arccot can also be written as:
```math
\text{arccot} = \frac \pi 2 - \arctan
```
So we can implement it directly:
```python
def arccot_derivatives(u_list, order):
    f_list = [-f for f in arctan_derivatives(u_list, order)]
    f_list[0] += math.pi / 2.0

    return f_list
```
Or we can look at the first derivative which is:
```math
f_1 = -\frac{u_1}{1+u^2}
```
Which is the same algebraic structure we had in the arctan section.  
Which gives us:

#### Formula
```math
f_n = \frac {-1} {1+v} \left(u_n - \sum_{k=1}^{n-1}\binom {n - 1} k f_{n-k}v_k\right)
```
Where:
```math
v_n = \sum_{k=0}^n\binom nk u_ku_{n-k}
```

#### Implementation
```python
def arccot_derivatives(u_list, order):
    f_list = u_list
    f_list[0] = (math.pi / 2.0) - math.atan(u_list[0])

    v_list = product_derivatives(u_list, u_list, order - 1)
    for n in range(1, order + 1):
        for k in range(1, n):
            f_list[n] -= nCr(n-1, k) * f_list[n-k] * v_list[k]
        f_list[n] /= -(1 + v_list[0])

    return f_list
```