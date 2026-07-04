# Logarithm
The function we all know and love, which is a `mirror image` of $\exp$ around the line $y = x$  
Meaning the inverse of $\exp$!

## Simplest Case

Just like all the other functions, let's start from the beginning and expand on it!  
Now, let's start with the first few derivatives of $f(x) = \ln(x)$:
```math
\begin{align*}
&f₀ = \ln(x) \\
&f₁ = \frac 1 x \\
&f₂ = -\frac 1 {x^2} \\
&f₃ = \frac 2 {x^3} \\
\end{align*}
```
After the first derivative we have $f_1 = \frac 1x$ for which, we already have a recurrence $\rightarrow$ **refer:** [`quotient.md`](quotient.md#simplest-reciprocal).  
As you can see it is just the derivatives of $\frac 1 x$ after the first derivative.  

### Formula
> [!IMPORTANT]
> That gives us:  
$f_n = (-1)^{n-1}\frac {(n-1)!} {x^{n}} : n \ge 1$  
$f_0 = \ln(x)$

## General Case

Let us cut right to the chase with $\ln(u(x))$ (where $u(x) > 0$) , you can find out the first few derivatives of $\ln(u(x))$ and try to figure out the formula that way (that is also how I actually did it).

So, we know the formula for the nth derivative of $e^{(u(x))}$ $\to$ **refer:** [`exponential.md`](power-functions/exponential.md).  
And we know that $e^{\ln(f)} = f$.  

So, if our function is $f(x) = \ln(u(x))$  
And we raise both sides to $e$, we get:  
$e^{f(x)} = e^{\ln(u(x))}$  

Which is:  
$e^{f(x)} = u(x) $  
Now, we can use the formulae for the $n^{th}$ derivative of $y = e^g$ to get the formula for $\ln(u(x))$.  
The formula if $y = e^g$:
```math
y_n = \sum_{k = 1}^{n}\binom{n-1}{k-1}y_{n-k}\cdot g_k
```
Replacing $g \leftrightarrow u$ and $y \leftrightarrow f$, we get:
```math
\begin{align*}
u &=e^f \\
u_n &= \sum_{k = 1}^{n}\binom{n-1}{k-1}u_{n-k}\cdot f_k\\
\end{align*}
```
Taking out the last term of the summation:
```math
u_n = uf_n + \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot f_k
```
Subtracting $\sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot f_k$ from both sides, we get:
```math
uf_n = u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot f_k
```
And dividing both sides with u, we get:
```math
f_n = \frac {u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot f_k} {u}
```

### Formula
> [!IMPORTANT]
> So we get the formula:  
$f_n = \frac {u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot f_k} {u} : n \ge 2$  
$f_1 = \frac {u_1} u$  
$f = \ln(u)$

> We could have also reached this result by derivating $\ln(u(x))$ once and applying the quotient rule [formula](QUO.md) we derivated on $\frac {d} {dx}\ln(u(x)) = \frac {u_1(x)} {u(x)}$.

### Practical Implementation
```python
def ln_derivatives(u_list, order):
    # u_list contains all the derivatives of u from 0 till n

    f_list = [0.0] * (order + 1) # saving space for all the derivatives
    f_list[0] = math.log(u_list[0])] # f0 = ln(u0(a))

    # outer loop to calculate all the derivatives from 0 to n
    for n in range(1, order + 1):
        # numerator = u{m} - sum{k=1,m-1} nCr{m-1, k-1} * u{m-k} * f{k}
        f_list[n] = u_list[n]
        for k in range(1, n):
            f_list[n] -= nCr(n-1,k-1) * u_list[n-k] * f_list[k]

        # numerator / u
        f_list[n] /= u_list[0]

    return f_list
```

## General Case With Arbitrary Base
The function $f(x) = \log_{v(x)}(u(x))$ is the topic of concern of this section.  
We have a neat little property in logarithm called the base changing theorem, that states:
```math
\log_b(a) = \frac {\log_c(a)} {\log_c(b)}
```
This let's us change the base to a more common base to work with, so with $a = u(x)$ and $b = v(x)$ and $c = e$, we get:
```math
\log_{v(x)}{(u(x))} = \frac {\ln(u(x))} {\ln(v(x))}
```
So if we take:
```math
\begin{align*}
h(x) &= \ln(u(x)) \\
g(x) &= \ln(v(x)) \\
\end{align*}
```
we get:
```math
f(x) = \frac {h(x)} {g(x)}
```
and after using the quotient formula that we had developed earlier, we get:
```math
f_n = \frac {h_n - \sum_{k=1}^n\binom{n}{k}h_{n-k}g_{k}} {g}
```
where:
```math
\begin{align*}
h_m &= \frac {u_m - \sum_{k = 1}^{m-1}\binom{m-1}{k-1}u_{m-k}\cdot h_k} {u} \\
\\
g_m &= \frac {v_m - \sum_{k = 1}^{m-1}\binom{m-1}{k-1}v_{m-k}\cdot g_k} {v} \\
\end{align*}
```
respectively, using the $\ln$ formula we derived earlier.  

### Formula
The formula only uses the tools we have derived earlier, practically speaking, we don't need an explicit formula that can and *will* be more complex than it needs to be.  

Calculating it without an explicit formula will be fairly simple:
```python
def log_arb_base_derivatives(u_list, v_list, order):
    # log_v(u) = ln(u) / ln(v)
    # h <-> ln(u)
    # g <-> ln(v)
    h_list = ln_derivatives(u_list, order)
    g_list = ln_derivatives(v_list, order)

    # f = h / g
    f_list = div_derivatives(h_list, g_list, order)
    return f_list
```
Since both `ln_derivatives` and `div_derivatives` are $O(n^2)$ this function here is also $O(n^2)$.