# Hyperbolic Functions
We are all familiar with the trigonometric (or circular) functions, which arise naturally from the geometry of the unit circle and admit elegant representations in the [`complex plane`](https://en.wikipedia.org/wiki/Complex_plane) through Euler's formula.

Hyperbolic functions, in contrast, arise from the geometry of the unit hyperbola. Although they are most commonly defined through exponential functions, they also admit an analogous representation in the [`split-complex (hyperbolic) number system`](https://en.wikipedia.org/wiki/Split-complex_number).

---

## Real Plane definitions
Each of the hyperbolic functions have their definitions with the Euler's number with the following relations:
- $\sinh(x) = \frac {e^x-e^{-x}} 2$
- $\cosh(x) = \frac {e^x+e^{-x}} 2$
- $\tanh(x) = \frac {e^x-e^{-x}} {e^x+e^{-x}}$
- $\coth(x) = \frac {e^x+e^{-x}} {e^x-e^{-x}}$
- $\text{csch}(x) = \frac 2 {e^x-e^{-x}}$
- $\text{sech}(x) = \frac 2 {e^x+e^{-x}}$

### Solution?
And since we already have the solution for the $n^{th}$ derivative of $\exp$ function, $\rightarrow$ **refer:** [`exponential.md`](../power-functions/exponential.md).  
We can easily solve these by plugging it in!

#### Implementation
```python
def hyperbolic_exp_helper(u_list, order):
    neg_u_list = [-u for u in u_list]
    pos_exp_list = exp_derivatives(u_list, order)
    neg_exp_list = exp_derivatives(neg_u_list, order)

    return (pos_exp_list, neg_exp_list)

def sinh_derivatives(u_list, order):
    pos_exp_list, neg_exp_list = hyperbolic_exp_helper(u_list, order)
    f_list = [0.0] * (order + 1)
    for i in range(order + 1):
        f_list[i] = (pos_exp_list[i] - neg_exp_list[i]) / 2

    return f_list

def cosh_derivatives(u_list, order):
    pos_exp_list, neg_exp_list = hyperbolic_exp_helper(u_list, order)
    f_list = [0.0] * (order + 1)
    for i in range(order + 1):
        f_list[i] = (pos_exp_list[i] + neg_exp_list[i]) / 2

    return f_list

# ... And the rest
```

## Relations With Trigonometry
And there are a particular set of relations between trigonometric functions and their hyperbolic counterparts. Those being:  
- $\sinh(x) = -i\sin(ix)$
- $\cosh(x) = \cos(ix)$
- $\tanh(x) = -i\tan(ix)$
- $\coth(x) = i\cot(ix)$
- $\text{sech}(x) = \sec(ix)$
- $\text{csch}(x) = i\csc(ix)$

### Better Solution?
So if we try to find the $n^{th}$ derivative of any hyperbolic function we can define them in this structure:

#### Implementation Structure
```python
def hyperbolic_function(u_list, order):
    # u_list contains the derivatives of u from order 0..n
    
    # multiply all the derivatives of u with iota
    imag_u_list = [1.0j * u for u in u_list]

    # get the derivatives of the trigonometric counterpart of this hyperbolic function
    related_trig_list = related_trigonometric_function(imag_u_list, order)

    # multiply with -i to get the final result
    f_list = [conversion_factor * f for f in related_trig_list]
    # where conversion factor depends on the function, 
    # for example, it is -i for sin and 1 for cos

    return f_list
```
But this requires a lot more finesse than the the previous implementation.

## Origin Of Relations
The relations with the trigonometric functions might seem elegant and they are but where do they originate from?  
They come from the Euler's formula:
```math
e^{ix} = \cos(x)+i\sin(x)
```
It is a complex number.  
The split complex numbers must have their own formula resembling the Euler's formula.

And they do, it is:
```math
e^{jx} = \cosh(x)+j\sinh(x)
```
It is a split complex number $a+bj$, just like the complex numbers $a+bi$.  
> This formula comes from the expansion of power series.

What is $j$ here?  
In the complex number system, we have $i$ which has the definition of $i^2 = -1$.  
In the split complex number system however, $j$ is defined as $j^2 = 1$ but $j \ne 1$.

### Solution
Just like how we solved for the $n^{th}$ derivatives of trigonometric functions in [`Euler's Grace`](../trigonometry/eulers-grace.md) using Euler's formula, we can derive the $n^{th}$ derivative of a hyperbolic function using its equation:
```math
e^{ju} = \cosh(u)+j\sinh(u)
```
Here:
```math
\cosh(u) = \Re(e^{ju})
```
And:
```math
\sinh(u) = \text{Split}(e^{ju})
```
Where $\text{Split}(a+jb) = b$  
If we differentiate both sides of the equation $n$ times, we get:
```math
D^n(e^{ju}) = D^n(\cosh(u)) + jD^n(\sinh(u))
```
From here we can conclude that $\Re(D^n(e^ju)) = D^n(\cosh(u))$ and $\text{Split}(D^n(e^ju)) = D^n(\sinh(u))$.

If we consider a function $f = e^{ju}$.  
If we differentiate both sides of the equation, we get:
```math
f_1 = ju_1e^{ju}
```
And we know that $f = e^{ju}$, we get:
```math
f_1 = ju_1f
```
And if we differentiate this equation $n-1$ times to reach f_n, we get:
```math
f_n = jD^{n-1}(u_1f)
```
On the LHS we have a direct use for the Leibniz's rule and we have solved this exact algebraic structure for $\exp$ and trigonometric functions, and the final result we will have is:
```math
f_n = j\sum_{k=0}^{n-1}\binom{n-1}{k}f_ku_{n-k}
```
For the mentioned docs $\rightarrow$ **refer:**  
- [`product.md`](../product.md)
- [`exponential.md`](../power-functions/exponential.md)
- [`eulers-grace.md`](../trigonometry/eulers-grace.md)

### Implementation
For the implementation to work we will first have to define a split complex data structure akin to the complex numbers.
```python
# no exception handling as it is a prototype for showcasing the point
class SplitComplex:
    def __init__(self, real, split):
        self.real = real
        self.split = split
    
    def __add__(self, other):
        if isinstance(other, SplitComplex):
            real = self.real + other.real
            split = self.split + other.split
        elif isinstance(other, (int, float)):
            real = self.real + other
            split = self.split
        return SplitComplex(real, split)

    def __mul__(self, other):
        if isinstance(other, SplitComplex):
            real = self.real * other.real + self.split * other.split
            split = self.real * other.split + self.split * other.real
        elif isinstance(other, (int, float)):
            real = self.real * other
            split = self.split * other
        return SplitComplex(real, split)
    
    # Other functionality
```

And then we can use this for the derivatives of $e^{ju}$ as:

#### Implementation 1
```python
import math

def hyperbolic_exp_derivatives(u_list, order):
    f_list = [SplitComplex(0.0, 0.0) for _ in range(order + 1)]
    f_list[0] = SplitComplex(math.cosh(u_list[0]), math.sinh(u_list[0]))

    for n in range(1, order + 1):
        
        for k in range(n):
            f_list[n] += nCr(n - 1, k) * u_list[n - k] * f_list[k]
        f_list[n] *= SplitComplex(0.0, 1.0)
    
    return f_list
```
And inherently the hyperbolic functions:
```python
def sinh_derivatives(u_list, order):
    hyp_list = hyperbolic_exp_derivatives(u_list, order)
    # extract the sinh derivatives
    return [f.split for f in hyp_list]

def tanh_derivatives(u_list, order):
    hyp_list = hyperbolic_exp_derivatives(u_list, order)
    sinh_list = [f.split for f in hyp_list]
    cosh_list = [f.real for f in hyp_list]
    return div_derivatives(sinh_list, cosh_list, order)

def sech_derivatives(u_list, order):
    hyp_list = hyperbolic_exp_derivatives(u_list, order)
    cosh_list = [f.real for f in hyp_list]
    return reciprocal_derivatives(cosh_list, order)

# And the remaining functions...
```
Which uses the `div_derivatives` and `reciprocal_derivatives`. For their derivtion, $\rightarrow$ **refer:** [`quotient.md`](../quotient.md)

#### Implementation 2
Or instead of providing a result with a list of split complex numbers, we can provide a result with two lists of real and split values, like:
```python
import math

def hyperbolic_exp_derivatives(u_list, order):
    real_list = [0.0] * (order + 1)
    split_list = [0.0] * (order + 1)

    real_list[0] = math.cosh(u_list[0])
    split_list[0] = math.sinh(u_list[0])

    for n in range(1, order + 1):
        s = SplitComplex(0.0, 0.0)
        for k in range(n):
            s += nCr(n - 1, k) * u_list[n - k] * SplitComplex(real_list[k], split_list[k])
        s *= SplitComplex(0.0, 1.0)
        real_list[n] = s.real
        split_list[n] = s.split
    
    return (real_list, split_list)
```
And the hyperbolic functions now become:
```python
def sinh_derivatives(u_list, order):
    _, sinh_list = hyperbolic_exp_derivatives(u_list, order)
    return sinh_list

def tanh_derivatives(u_list, order):
    cosh_list, sinh_list = hyperbolic_exp_derivatives(u_list, order)
    return div_derivatives(sinh_list, cosh_list, order)

def sech_derivatives(u_list, order):
    cosh_list, _ = hyperbolic_exp_derivatives(u_list, order)
    return reciprocal_derivatives(cosh_list, order)

# And the remaining functions...
```
## Note
Here, all the methods would be $O(n^2)$ and that doesn't mean our idea of method 3 is anyway better than the first method of solving this problem, chances are that both of them are perform about the same from performance standpoint.  
For a simple implementation, the first method will suffice but if different algebraic number systems are needed for the implementation, method 3 might be the way to go.

Only way to deduce what method to choose is to know one's own requirements and benchmarks on the target machine.