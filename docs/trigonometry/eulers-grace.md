# Euler's Grace

It is recommended that before going forth with the documentation, you take a look at the other trigonometric derivations.  
$\quad\rightarrow$ [`Sin and Cos`](sin-cos.md)  
$\quad\rightarrow$ [`Tan and Cot`](tan-cot.md)  
$\quad\rightarrow$ [`Sec and Csc`](sec-csc.md)  

## The Fundamental Error
In the $\sin$ and $\cos$ documentation, we derived the final formula to be:  
Sin:  
```math
f_n=\frac{u_n}{\cos(u)}-h_{n-1}\tan(u)+\frac{1}{2f_1}\sum_{k=1}^{n-2}\binom{n-1}k\left(u_{k+1}u_{n-k}-h_kh_{n-k-1}-f_{k+1}f_{n-k}\right)
```
Cos:
```math
f_n = -\frac{u_n}{\sin(u)} + h_{n-1}\cot(u) + \frac1{2f_1}\sum_{k=1}^{n-2}\binom{n-1}k\left(u_{k+1}u_{n-k}-h_kh_{n-k-1}-f_{k+1}f_{n-k}\right)
```
Where,
```math
h_m = \sum_{k=0}^m\binom mk u_{k+1}f_{m-k}
```
<br>

But there is one massive issue in these relations.  
If the first derivative, that is $f_1$ is $0$, then all further derivatives where $n \ge 2$ are undefined due to the division by $f_1$.  
And $\sec$ & $\csc$ since their derivatives are directly dependent on the derivatives of $\sec$ and $\csc$.

How do we solve this issue?  

## Solution
We know that $e^{ix} = \cos(x) + i\sin(x)$ by [Euler's formula](https://en.wikipedia.org/wiki/Euler%27s_formula)  
If we differentiate both sides $n$ times, we get:
```math
D^n(e^{ix}) = D^n(\cos(x)) + iD^n(\sin(x))
```
we can see that the real part of the $n^{th}$ derivative of $e^{ix}$ contains the $n^{th}$ derivative of $\cos(x)$ and imaginary part contains the same for $\sin(x)$.

That is:
```math
\Re\left(D^n(e^{iu(x)})\right) = D^n\left(\cos(u(x))\right) \\
\Im\left(D^n(e^{iu(x)})\right) = D^n\left(\sin(u(x))\right) \\
```

And if we differentiate $f = e^{iu}$, we get:
```math
f_1 = iu_1e^{iu}
```
And since $f=e^{iu}$, we have:
```math
f_1 = iu_1f
```
Differentiating both sides of the equation $n-1$ times to fin $f_n$ we get the:
### Formula
```math
\begin{align*}
f_n &= i\sum_{k=0}^{n-1}\binom{n-1}kf_ku_{n-k} \\
\\
f &= e^{iu} \\
\end{align*}
```
## Implementation
We can implement it in two ways:
### Implementation 1
```python
def complex_exp_derivatives(u_list, order):
    # u_list contains all the derivatives of u from order 0..n
    f_list = [0.0 + 0.0j] * (order + 1)
    f_list[0] = math.cos(u_list[0]) + 1.0j * math.sin(u_list[0])

    # outer loop to compute all the derivatives of f
    for n in range(1, order + 1):
        
        # inner loop to compute the individual derivative f{m}
        for k in range(n):
            f_list[n] += nCr(n-1, k) * f_list[k] * u_list[n - k]
        f_list[n] *= 1.0j

    return f_list

def sin_derivatives(u_list, order):
    # extract the imaginary part to extract the derivatives of sin
    f_list = [z.imag for z in complex_exp_derivatives(u_list, order)]
    return f_list

def cos_derivatives(u_list, order):
    # extract the real part to extract the derivatives of cos
    f_list = [z.real for z in complex_exp_derivatives(u_list, order)]
    return f_list
```
And so $\tan$ and $\cot$ which had their own specialized recurrence relations can also rely on this result as:
```python
def tan_derivatives(u_list, order):
    complex_derivatives_list = complex_exp_derivatives(u_list, order)
    return div_derivatives(
            [z.imag for z in complex_derivatives_list], # sin derivatives
            [z.real for z in complex_derivatives_list], # cos derivatives
            order
        )

def cot_derivatives(u_list, order):
    complex_derivatives_list = complex_exp_derivatives(u_list, order)
    return div_derivatives(
            [z.real for z in complex_derivatives_list], # cos derivatives
            [z.imag for z in complex_derivatives_list], # sin derivatives
            order
        )
```
### Implementation 2
What's different in this approach is that we keep separate arrays for real and imaginary parts of the complex numbers.
```python
def complex_exp_derivatives(u_list, order):
    real_list = [0.0] * (order + 1)
    imag_list = [0.0] * (order + 1)

    real_list[0] = math.cos(u_list[0])
    imag_list[0] = math.sin(u_list[0])

    for n in range(1, order + 1):

        z = 0.0 + 0.0j
        for k in range(n):
            z += nCr(n-1, k) * complex(real_list[k], imag_list[k]) * u_list[n-k]
        z *= 1.0j

        real_list[n], imag_list[n] = z.real, z.imag
    
    return (real_list, imag_list)

def sin_derivatives(u_list, order):
    _, f_list = complex_exp_derivatives(u_list, order)
    return f_list

def cos_derivatives(u_list, order):
    f_list, _ = complex_exp_derivatives(u_list, order)
    return f_list

def tan_derivatives(u_list, order):
    cos_list, sin_list = complex_exp_derivatives(u_list, order)
    return div_derivatives(sin_list, cos_list, order)

def cot_derivatives(u_list, order):
    cos_list, sin_list = complex_exp_derivatives(u_list, order)
    return div_derivatives(cos_list, sin_list, order)
```
<br> <br>
And with the help of Euler's formula, we have changed our $\sin$ and $\cos$ implementations to work even if $f_1 = 0$ and still keep our time complexity down at $O(n^2)$.