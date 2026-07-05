# Fractional functions
Let's have a look at the functions of the format $f(x) = \frac {u(x)} {v(x)}$

## Reciprocal functions

### Simplest Reciprocal
Let's start by looking at $f(x) = \frac {1} {x}$.  
First few derivatives of the function is:
```math
\begin{align*}
f   &=   \frac {1} {x} \\
f_1 &= - \frac {1} {x^2} \\
f_2 &=   \frac {2} {x^3} \\
f_3 &= - \frac {6} {x^4} \\
f_4 &=   \frac {24} {x^5} \\
\end{align*}
```
The astute amongst you might have spotted it already there are factorials in here!  

#### Why Factorials Appear
Since 
```math
D (x^n) = nx^{n-1}\\
```
```math
D^m(x^n) = n(n-1)(n-2)\dots(n-(m-1))x^{n-m}
```
And since here $n=-1$, we have:
```math
D^m\left( \frac 1x \right) = (-1)(-2)(-3)\dots(-m)x^{-(m+1)}
```
Which boils down to:
```math
D^n \left( \frac 1x \right) = x^{-(n+1)}\prod_{k=1}^n -k
```

#### Formula
> [!IMPORTANT]
> So this can be easily evaluated as:  
$f_n = (-1)^n \frac {n!} {x^{n+1}}$

#### Practical Implementation
```python
def one_over_x_derivatives(point, order):
    # n!/x^(n+1)
    result = math.gamma(order + 1) / (x ** (order + 1))
    # since (-1)^n has only two possible states because n is a +ve integer.
    # it will be 1 if n is even and -1 if n is odd
    return result if order % 2 == 0 else -result
```

### General Reciprocal
Let's now do it for the function $f(x) = \frac 1 {u(x)}$.  
Starting by derivating the first few derivatives of the function:
```math
\begin{align*}
&f = \frac {1} {u} \\
&f_1 = - \frac {u_1} {u^2} \\
&f_2 = - \frac {u_2} {u^2} + 2\frac {u_1^2} {u^3} \\
&f_3 = - \frac {u_3} {u^2} + 6\frac {u_2u_1} {u^3} - 6\frac {u_1^3} {u^4} \\
&f_4 = - \frac {u_4} {u^2} + 8\frac {u_3u_1} {u^3} + 6\frac {u_2^2} {u^3} + 24\frac {u_1^4} {u^5} \\
\end{align*}
```

Hmmm, looks interesting but doesn't seem like it makes a formula, does it?  

By changing up from the start and writing $f_1 = - \frac {u_1f} {u}$ instead of $f_1 = - \frac {u_1} {u^2}$ and differentiating further, we have:
```math
\begin{align*}
&f = \frac {1} {u} \\
&f_1 = - \frac {u_1f} {u} \\
&f_2 = - \frac {u_2f} {u} - 2\frac {u_1f_1} {u} \\
&f_3 = - \frac {u_3f} {u} - 3\frac {u_2f_1} {u} - 3\frac {u_1f_2} {u} \\
&f_4 = - \frac {u_4f} {u} - 4\frac {u_3f_1} {u} - 6\frac {u_2f_2} {u} - 4\frac {u_1f_3} {u} \\
\end{align*}
```
Some of you might be able to see the formula emerging from it.  
If you look at the coefficients, they are:
```math
\begin{gather*}
C_1 = -1 \\
C_2 = -1,-2 \\
C_3 = -1,-3,-3 \\
C_4 = -1,-4,-6,-4 \\
\end{gather*}
```
For context, the pascal's triangle:
```math
\begin{gather*}
1\\
1,1\\
1,2,1\\
1,3,3,1\\
1,4,6,4,1\\
\cdots
\end{gather*}
```
The coefficients match from row 1 and onwards excluding the final term!  
If we look at the orders of $u$ in each of the $f_n$, we will see:
```math
\begin{gather*}
f_1 : 1\\
f_2 : 2,1\\
f_3 : 3,2,1\\
f_4 : 4,3,2,1\\
\end{gather*}
```
Each decrease from $n\to1$  
And if we look at the orders of $f$ used, we can see:
```math
\begin{gather*}
f_1 : 0\\
f_2 : 0,1\\
f_3 : 0,1,2\\
f_4 : 0,1,2,3\\
\end{gather*}
```
Each increases from $0\to n-1$  
So by seeing the pattern and trying to make a formula out of it.

#### Formula
> [!IMPORTANT]
> We will get:  
$f_n = -\frac {1} {u} \sum_{k=0}^{n-1}\binom{n}{k}f_{k}u_{n-k}$  
Or by index manipulation:  
$f_n = -\frac {1} {u} \sum_{k=1}^{n}\binom{n}{k}f_{n-k}u_{k}$  
where $n \ge 1$ and $u(a) \ne 0$  
$f = \frac 1u$

#### Practical Implementation
```python
def reciprocal_derivatives(u_list, order):
    # u_list holds all the derivatives of the function u (0 till n)
    # at some point 'a'
    f_list = [0.0] * (order+1) # making space for f0, f1, f2 ... f{n}
    f_list[0] = 1 / u_list[0] # f0 = 1/u

    # outer loop to calculate all f{1...n}
    for n in range(1, order):

        #inner loop to calculate individual f{m}
        for k in range(n):
            f_list[n] += nCr(n, k) * f_list[k] * u_list[n - k]

        # applying the factor of -1/u0
        f_list[n] /= -u_list[0]

    return f_list
```

Now, I recommend you derive the formula for $f(x) = \frac{u(x)} {v(x)}$ before we get into the next section, as there is also a very neat process to do so too.

## General Fractional Functions

The above section might have seemed a little *'hand wavy'* for some of you.  
Now let's actually derive this one using known results without any guessing game, so we can be sure the formula is concrete.

As we have already derived the *Leibniz's rule* in [`product.md`](product.md), we can use that to our advantage.  
Leibniz's rule: $f_n = \sum_{k=0}^n\binom{n}{k}u_{n-k}v_k$  

Here, our function is $f(x) = \frac {u(x)} {v(x)}$ ($v(x) \ne 0$).  
Let's multiply both sides with $v(x)$, which gives us: $f\cdot v = u$, using Leibniz's rule, we get:
```math
u_n = \sum_{k=0}^n\binom{n}{k}f_{n-k}v_k
```
Extract the first term $k=0$ which contains our desired value $f_n$:  
```math
u_n = \binom{n}{0}f_nv_0 + \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}
```
```math
u_n = f_nv + \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}
```
Rearranging the terms so that $f_nv$ is alone:
```math
f_nv = u_n - \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}
```
Divide both sides by $v$:
```math
f_n = \frac {u_n - \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}} {v}
```

#### Formula
> [!IMPORTANT]
> The final formula that comes out is:  
$f_n = \frac {u_n - \sum_{k=1}^n\binom{n}{k}f_{n-k}v_{k}} {v}$  
or:  
$f_n = \frac {u_n - \sum_{k=0}^{n-1}\binom{n}{k}v_{n-k}f_{k}} {v}$  

#### Practical Implementation
```python
def div_derivatives(u_list, v_list, order):
    # u_list and v_list are all the derivattives of u and v respectively
    # from order 0 till n at a particular point 'a'
    f_list = [0.0] * (order + 1) # making space for the derivatives of f

    # outer loop to calculate all f {0...n}
    for n in range(order + 1):

        # calculating individual f{m}
        for k in range(n):
            # subtracting terms from the summation part
            f_list[n] -= nCr(n, k) * v_list[n-k] * f_list[k]
        
        # adding the single u{n} part and dividing everything by v
        f_list[n] += u_list[n]
        f_list[n] /= v_list[0]

    return f_list
```

### Rederivating General Reciprocals
Getting back at the $f = \frac 1 u$.  
If in $f=\frac u v$ we consider $u\to1$, $v\to u$ and $n\ge1$, then we get:  
> using $f_n = \frac {u_n - \sum_{k=0}^{n-1}\binom{n}{k}v_{n-k}f_{k}} {v}$  

$f_n = -\frac{1}{u}\sum_{k=0}^{n-1}\binom{n}{k}u_{n-k}f_k$.

This is the same we got by the *look and guess* process. Confirming our earlier result.