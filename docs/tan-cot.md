# Tan and Cot

With this file, we will be starting with trigonometry, now out of the two, let's start with 

## $\tan(u(x))$
Let's first take $u(x) = ax + b$ where $a$ and $b$ are constants.

So the first few derivatives we have is:
```math
\begin{align*}
f &= \tan(ax+b) \\
f_1 &= \sec^2(ax+b) \\
&= a(1+f^2) \\
&= a + af^2 \\
\end{align*}
```
Differentiating $f_1 = a + af^2$, $n - 1$ times using the leibniz's rule, we have:  
```math
f_n = a\sum_{k=0}^{n-1}\binom{n-1}{k}f_kf_{n-k}
```
> [!IMPORTANT]
> And so we have:
$f_n = a\sum_{k=0}^{n-1}\binom{n-1}{k}f_kf_{n-k-1}:n\ge2$  
$f_1 = a + af^2$  
$f = \tan(ax+b)$

or practically:
```python
def tan_linear_derivatives(slope, point, intercept, order):
    # reserving space for all the derivatives of f
    f_list = [0.0] * (order + 1)
    f_list[0] = math.tan(slope * point + intercept) # f0 = tan(ax+b)
    if order > 0:
        f_list[1] = slope * (1 + f_list[0]**2) # f1 = a(1 + f^2)

    for n in range(2, order + 1):
        f_list[n] = slope * product_derivative(f_list, f_list, n)
    
    return f_list
```
It uses the `product_derivative` function we wrote in [README](README.md).  

Now, let's consider the general case, we have the function $f = \tan(u(x))$  
The first derivative is $f_1 = \sec^2(u)u_1$, and with the identity $\sec^2(x) = \tan^2(x) + 1$, we have: $f_1 = (1 + f^2)u_1$ or:
```math
f_1 = u_1 + f^2u_1
```
Let's consider $h = f^2$ which is equivalent to $h = f\cdot f$ and by using the leibniz's general formula we have:
```math
h_n = \sum_{k=0}^n\binom{n}{k}f_kf_{n-k}
```
which gives us $f_1 = u_1 + u_1h$ and taking $g = u_1h$, and using leibniz's formula again, we get:
```math
g_n = \sum_{k=0}^n\binom{n}{k}h_ku_{n-k+1}
```
and now we have $f_1 = u_1 + g$ differentiating both sides $n-1$ times gives us:
```math
\begin{align*}
f_n &= u_n + g_{n-1} \\
f_n &= u_n + \sum_{k=0}^{n-1}\binom{n-1}{k}h_ku_{n-k} \\
f_n &= u_n + \sum_{k=0}^{n-1}\binom{n-1}{k}u_{n-k}\left(\sum_{r=0}^k\binom{k}{r}f_rf_{k-r}\right) \\
\end{align*}
```
> [!IMPORTANT]
> So the formula we have:  
$f_n = u_n + \sum_{k=0}^{n-1}\binom{n-1}{k}u_{n-k}\left(\sum_{r=0}^k\binom{k}{r}f_rf_{k-r}\right):n\ge1$  
$f = \tan(u)$

In practice:
```python
def tan_derivatives(u_list, order):
    # u_list is the list of all the derivatives of u from order 0 to n

    # reserve space for holding all the derivatives of f
    f_list = [0.0] * (order + 1)
    f_list[0] = math.tan(u_list[0]) # f0 = tan(u)

    # outer loop to calculate all the derivatives of f
    for n in range(1, order + 1):
        
        # inner loop to calculate individual f{m}
        for k in range(n):

            inner_factor = product_derivative(f_list, f_list, k)            
            f_list[n] += nCr(n - 1, k) * u_list[n - k] * inner_factor
        
        f_list[n] += u_list[n]
    
    return f_list
```
But WAIT! if you look at it closely, if we we are calculating $f_{n+1}$ we do the calculations for $(f^2)\dots(f^2)_{n-1}$ that we already did for $f_n$, we are doing redundant work!  
If we store previous values of $h_k$, we have:
```python
def tan_derivatives(u_list, order):
    # u_list is the list of all the derivatives of u from order 0 to n

    # reserve space for holding all the derivatives of f
    f_list = [0.0] * (order + 1)
    f_list[0] = math.tan(u_list[0]) # f0 = tan(u)

    h_list = [0.0] * (order) # will be used to memoize the derivatives of f^2

    # outer loop to calculate all the derivatives of f
    for n in range(1, order + 1):
        
        # calculating and storing the value for h{n-1}
        h_list[n-1] = product_derivative(f_list, f_list, n-1)

        f_list[n] = u_list[n]
        f_list[n] += product_derivative(h_list, u1_list, n-1)
    
    return f_list
```
> [!IMPORTANT]
> making our function:  
$f_n = u_n + \sum_{k=0}^{n-1}\binom{n-1}{k}h_ku_{n-k} : n \ge 1$  
$f = \tan(u)$  
where: $h_n = \sum_{k=0}^n\binom{n}{k}f_kf_{n-k}$  

That reduced our time complexity from $O(n^3) \to O(n^2)$ using memoization!

## $\cot(u(x))$
Now, let's take a look at $f = \cot(u)$, the standard first derivative of this function is:
```math
f_1 = -\csc^2(u)u_1
```
or again, by the pythagorean identity $\csc^2(x) = \cot^2(x) + 1$ we have $f_1 = -(1+f^2)u_1$ or:
```math
f_1 = -u_1 - f^2u_1
```
This is algebraically same as the $f_1$ equation in the above $\tan$ section but negated, so we can use the result of $\tan$'s $n\ge1$ case.
> [!IMPORTANT]
> That is:  
$f_n = -u_n - \sum_{k=0}^{n-1}\binom{n-1}{k}h_ku_{n-k} : n \ge 1$  
$f = \cot(u)$  
where: $h_n = \sum_{k=0}^n\binom{n}{k}f_kf_{n-k}$  

Implemented, it looks like:
```python
def cot_derivatives(u_list, order):
    # u_list is the list of all the derivatives of u from order 0 to n

    # reserve space for holding all the derivatives of f
    f_list = [0.0] * (order + 1)
    f_list[0] = 1 / math.tan(u_list[0]) # f0 = cot(u)

    h_list = [0.0] * (order) # will be used to memoize the derivatives of f^2
    u1_list = u[1:]

    # outer loop to calculate all the derivatives of f
    for n in range(1, order + 1):
        
        # calculating and storing the value for h{n-1}
        h_list[n-1] = product_derivative(f_list, f_list, n-1)

        f_list[n] = -u_list[n]
        f_list[n] -= product_derivative(h_list, u1_list, n-1)
        
    
    return f_list
```
And that is it for the tan and cot section, simple and precise.