# Constant Power Functions
In this file we will be discussing about the $n^{th}$ derivative of the function $f(x) = u(x)^c$  
The most familiar case that we encounter for this function is $c = \frac 1 2$. So let's take a look at it first.

## Square Root Case
Let's define $f = \sqrt u$  
### Derivation
Squaring both sides gives us $f^2 = u$ which is $f\cdot f = u$.  
If we differentiate both sides $n$ times, it is an application of Leibniz's rule $\rightarrow$ **refer:** [`product.md`](..\product.md).

That gives us:
```math
u_n = \sum_{k=0}^{n}\binom{n}{k}f_kf_{n-k}
```
Since, the first $k=0$ and the last $k=n$ term contain our desired $f_n$ terms, let's take them out of the summation:
```math
\begin{align*}
&u_n = ff_n+f_nf+\sum_{k=1}^{n-1}\binom{n}{k}f_kf_{n-k} \\
&u_n = 2ff_n+\sum_{k=1}^{n-1}\binom{n}{k}f_kf_{n-k} \\
\end{align*}
```
And with simple rearrangements, we have:
```math
f_n = \frac {u_n-\sum_{k=1}^{n-1}\binom{n}{k}f_kf_{n-k}} {2f}
```
Which is same as:
```math
f_n = \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}} {2f}
```
If you follow this

### Lemma
Let's say:
```math
\begin{align*}
S_1 &= \sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k} \\ 
S_2 &= \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k} \\ 
S_3 &= \sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k} \\ 
\end{align*}
```
By Pascal's triangle, we know that:
```math
\binom{n}{k} = \binom{n-1}{k}+\binom{n-1}{k-1}
```
So:
```math
S_1 = \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k} + \sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}
```
Or:
```math
S_1 = S_2 + S_3
```
Taking a new index $j = n-k$ in $S_2$, we get:
```math
\sum_{j=n-1}^{1}\binom{n-1}{n-j}f_{n-j}f_{j}
```
$\binom {n-1}{n-j} = \binom {n-1} {n-1-(n-j)}$:
```math
\sum_{j=n-1}^{1}\binom{n-1}{j-1}f_{n-j}f_{j}
```
$j \leftrightarrow k$:
```math
\sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{n-k}f_{k}
```
That is: $S_2 = S_3$

Which gives:
```math
S_1 = 2S_3
```
That is:
```math
\frac {u_{n} - \sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}} {2f} \equiv \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} {2f}
```
So we have our final
#### Formula:
> [!IMPORTANT]
$f_n = \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}} {2f}$  
Or:  
$f_n = \frac {u_{n} - \sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}} {2f}: n \ge 1$  
$f = \sqrt u$

#### Practical Implementation
```python
def sqrt_derivatives(u_list, order):
    # u_list contains all the derivatives of u from order 0 till n
    
    # preserves space for all the derivatives of f
    f_list = [0.0] * (order + 1)
    f_list[0] = math.sqrt(u_list[0]) #f0 = sqrt(u0)

    # outer loop to calculate all the derivatives 1 till n
    for n in range(1, order + 1):

        # inner loop to calculate individual f{m}
        for k in range(1, n):
            f_list[n] -= nCr(n,k) * f_list[k] * f_list[n-k]
        f_list[n] += u_list[n]
        f_list[n] /= 2.0 * f_list[0]

    return f_list
```
Now that we have taken a look at $f = \sqrt {u(x)}$, let's take a look at the more general case of this function: $f(x) = u(x)^c$ where $c$ is a constant.

## General Constant Power
### Following The Square Root Path
Firstly, we can't raise both sides of the equation $f(x) = u(x)^c$ to the power of $\frac 1 c$ as we did with $f=\sqrt u$ since it lands us on $f(x)^{\frac 1 c} = u(x)$ and since $c$ is a constant, we can consider $k=\frac 1 c$. So, we have $f(x)^k = u(x)$ which is the same as our original problem.  

### Utilizing Logarithm
Secondly, let's take a look at what happen if we go with the $\ln$ route.  
Let's take $\ln$ on both sides of the equation $f = u^c$, we have:
```math
\begin{align*}
&\ln(f) = \ln(u^c)\\
&\ln(f) = c\ln(u)
\end{align*}
```
And, if we consider $h = \ln(f)$ and $v = \ln(u)$, we have:
```math
h=c\cdot v
```
Differentiating both sides $n$ times gives us:
```math
\begin{align*}
&D^n(h) = D^n(c\cdot v)\\
&D^n(h) = cD^n(v)\\
&h_n = c\cdot v_n\\
\end{align*}
```  
We know that if we have a function $y = \ln(g)$, the $n^{th}$ derivative is:
```math
y_n = \frac {g_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}g_{n-k}\cdot y_k} {g} : n \ge 1
```
Plugging it into the equation $h_n = c\cdot v_n$ with the definitions of $h$ and $v$, we have:
```math
\frac {f_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}f_{n-k}\cdot h_k} {f} = c\cdot\frac {u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot v_k} {u}
```
Separating $f_n$ gives us:
```math
f_n = f\left(c\cdot\frac {u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot v_k} {u} + \frac {\sum_{k = 1}^{n-1}\binom{n-1}{k-1}f_{n-k}\cdot h_k} {f}\right)
```
Or:
```math
f_n = \frac {cu_nf} {u} + \frac 1 u \sum_{k=1}^{n-1}\binom{n-1}{k-1}\left(uf_{n-k}h_k-fu_{n-k}v_k\right):n\ge 1
```
The final result is a single summation but it requires us defining extra functions, which is not ideal.  

### Final Derivation
Thirdly and lastly, let's the write the first derivative using standard differentiation rules:
```math
f_1 = cu^{c-1}u_1
```
Since $a^{-b} = \frac 1 {a^b}$ and $a^{b+c} = a^ba^c$, we can write our equation as:
```math
f_1 = \frac {cu^cu_1} u
```
Since we know that $f=u^c$, we can replace them, and by multiplying both sides with $u$, we have:
```math
f_1u = cfu_1
```
Differentiating both sides $n-1$ times, gives us:
```math
\begin{align*}
&D^{n-1}(f_1u) = D^{n-1}(cfu_1)\\
&D^{n-1}(f_1u) = cD^{n-1}(fu_1)\\
\end{align*}
```
Which is just the application of leibniz's formula and since it is symmetric, we get:
```math
\begin{align*}
LHS &= \sum_{k=0}^{n-1}\binom {n-1} k D^k(f_1)D^{n-1-k}(u) \\
RHS &= c\sum_{k=0}^{n-1}\binom {n-1} k D^k(f)D^{n-1-k}(u_1) \\
\end{align*}
```
Or in our notation:
```math
\begin{align*}
LHS&=\sum_{k=0}^{n-1}\binom {n-1} k f_{k+1}u_{n-1-k} \\
RHS&=c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k} \\
\end{align*}
```
So now we have:
```math
\sum_{k=0}^{n-1}\binom {n-1} k f_{1+k}u_{n-1-k} = c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k}  
```
Taking out the last term $k = n-1$ from the LHS, we have:
```math
\begin{align*}
&f_nu + \sum_{k=0}^{n-2}\binom {n-1} k f_{1+k}u_{n-1-k} = c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k}\\
&f_nu = c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k} - \sum_{k=0}^{n-2}\binom {n-1} k f_{1+k}u_{n-k-1}\\
\end{align*}
```
Defining a new index $j = n-1-k$ and replacing it with $k$ in the second summation, we get:
```math
f_nu = c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k} - \sum_{k=1}^{n-1}\binom {n-1} k f_{n-k}u_{k}
```
Taking out the first term $k=0$ from the first summation, we get:
```math
\begin{align*}
&f_nu = cfu_n + c\sum_{k=1}^{n-1}\binom {n-1} k f_ku_{n-k} - \sum_{k=1}^{n-1}\binom {n-1} k f_{n-k}u_k\\
&f_nu = cfu_n + \sum_{k=1}^{n-1}\binom {n-1} k cf_ku_{n-k} - \sum_{k=1}^{n-1}\binom {n-1} k f_{n-k}u_k\\
\end{align*}
```
And so we have:
```math
f_nu = cfu_n + \sum_{k=1}^{n-1}\binom {n-1} k\left(cf_ku_{n-k}-f_{n-k}u_k\right)
```
Or if we define a new index $j = n-k$ and replace it in with $k$ in the first summation, we get:  
```math
f_nu=cfu_n+\sum_{k=1}^{n-1}f_{n-k}u_k\left(c\binom{n-1}{k-1}-\binom{n-1}{k}\right)
```
But:
```math
\begin{alignat*}{2}
\binom {n-1}{k-1} &= \frac {(n-1)!} {(k-1)!(n-k)!} &\qquad \binom {n-1}k &= \frac {(n-1)!} {k!(n-k-1)!}\\ \\
A&=\frac {(n-1)!} {(n-k)(k-1)!(n-k-1)!} &\qquad B&=\frac {(n-1)!} {k(k-1)!(n-k-1)!}\\
A &= B\frac{k}{n-k} &\qquad B &= A\frac {n-k} {k}\\ \\
\binom {n-1} {k-1}&=\binom{n-1}k\frac k {n-k} &\qquad \binom {n-1} {k} &= \binom {n-1} {k-1}\frac {n-k} k
\end{alignat*}
```
Choosing any as replacement(or not) and dividing both sides with $u$ we get these results:
```math
\begin{align*}
f_n&=\frac{cfu_n}u+\frac1u\sum_{k=1}^{n-1}\left(c\binom{n-1}{k-1}-\binom{n-1}{k}\right)f_{n-k}u_k\\
&=\frac{cfu_n}u+\frac1u\sum_{k=1}^{n-1}\binom{n-1}k\left(\frac{kc}{n-k}-1\right)f_{n-k}u_k\\
&=\frac{cfu_n}u+\frac1{u}\sum_{k=1}^{n-1}\binom{n-1}{k-1}\left(c-\frac nk+1\right)f_{n-k}u_k
\end{align*}
```
Finally in the end we finally have our 

#### Formula
> [!IMPORTANT]
$f_n = \frac{cfu_n}u+\frac1{u}\sum_{k=1}^{n-1}\binom{n-1}{k-1}\left(c-\frac nk+1\right)f_{n-k}u_k$  
Or:  
$f_n = \frac{cfu_n}u+\frac1u\sum_{k=1}^{n-1}\binom{n-1}k\left(\frac{kc}{n-k}-1\right)f_{n-k}u_k : n \ge 1$  
$f = u^c$

#### Practical Implementation
```python
def const_pow_derivatives(u_list, c, order):
    # u_list contains all the derivatives of the function u from order 0 to n
    # c is the power u is being raised to

    f_list = [0.0] * (order + 1) # reserving space for all the derivatives f{0..n}
    f_list[0] = math.pow(u_list[0], c) # f0 = u^c

    # outer loop to calculate all the derivatives of f
    for n in range(1, order + 1):
        # inner loop to calculate individual f{m}
        for k in range(1, n):
            inner_factor = c - n / k + 1
            f_list[n] += nCr(n-1,k-1) * f_list[n-k] * u_list[k] * inner_factor

        f_list[n] += c * f_list[0] * u_list[n]
        f_list[n] /= u_list[0]

    return f_list
```