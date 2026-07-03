# Constant Power Functions
In this file we will be discussing about the $n^{th}$ derivative of the function $f(x) = u(x)^c$  
The most familiar case that we encounter for this function is $c = \frac 1 2$. So let's take a look at it first.
## $\sqrt {u(x)}$:
Let's get on!  
Let's define $f = \sqrt u$  
Squaring both sides gives us $f^2 = u$ which is $f\cdot f = u$.  
If we differentiate both sides $n$ times, it is an application of leibniz's formula on the left, which gives us:
```math
u_n = \sum_{k=0}^{n}\binom{n}{k}f_kf_{n-k}
```
Since, the first $(k=0)$ and the last $(k=n)$ term contain our desired $f_n$ terms, let's take them out of the summation:
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
Now, you can skip to the [final result](#result) or go through with the following derivation which is just a *scenic route* that gets to the same result but with some index shifting and binomial manipulations that are also used in the general case derivation, so it may be worth taking a look at how these are done.  
Let's start!  
The first derivatives of the function $f = \sqrt u$, will be:
```math
f_1 = \frac {u_1} {2\sqrt u}
```
Since $f = \sqrt u$ it also equals:
```math
f_1 = \frac {u_1} {2f}
```
Multiplying both sides by $f$ we get:
```math
f_1f = \frac 1 2 u_1
```  
Let's define $h = f_1$ and $v = u_1$, now we have:  
```math
hf = \frac 1 2 v
```
By leibniz formula, we know that if we have some function $y = h\cdot f$, it's nth derivative is equal to:
```math
y_n = \sum_{k=0}^{n}\binom{n}{k}f_{k}h_{n-k}
```
On the **RHS**, differentiating n times will yield us $\frac 1 2 v_n$.  
After these operations, we have:
```math
\frac 1 2 v_n = \sum_{k=0}^{n}\binom{n}{k}f_{k}h_{n-k}
```
If we define an operator $D = \frac d {dx}$ and we have some function $f =  D^ku$, differentiating both sides w.r.t. $x$, n times, will result in $D^nf = D^{n+k}u$ or in our notation $f_n = u_{n+k}$.  
By this knowledge, we can replace $h_m \longrightarrow f_{m+1}$ and $v_m \longrightarrow u_{m+1}$, and now we have:
```math
\frac 1 2 u_{n+1} = \sum_{k=0}^{n}\binom{n}{k}f_{k}f_{n-k+1}
```
Replacing $n \longrightarrow n-1$, we get:  
```math
\frac 1 2 u_{n} = \sum_{k=0}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
```
If we take the $k = 0$ term out of the summation, we get:
```math
\frac 1 2 u_{n} = f\cdot f_n + \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
```  
Subtracting $\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}$ from both sides, we get:
```math
\begin{equation}
f\cdot f_n = \frac 1 2 u_{n} - \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
\end{equation}
```
On the **RHS**, taking the LCM of 2, we get:
```math
\frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} 2
```
If we take the summation as $S_1$:
```math
2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}
```
And let's take $S_2$:
```math
\sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}
```  
By Pascal's triangle, we know that:
```math
\binom{n}{k} = \binom{n-1}{k}+\binom{n-1}{k-1}
```
So:
```math
S_2 = \sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k} + \sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}
```
Let's take $S_3$ as:
```math
\sum_{k=1}^{n-1}\binom{n-1}{k-1}f_{k}f_{n-k}
```
Taking a new index $j = n-k$, we get:
```math
\sum_{j=1}^{n-1}\binom{n-1}{j}f_{n-j}f_{j}
```
And because multiplication is commutative, we have $S_1 = 2S_3$ and $S_2=2S_3$ respectively, we have the result $S_1 = S_2$. $\left(2\right)$  
Now, in equation $(1)$, if we divide both sides by $f$, we get:
```math
f_n = \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} {2f}
```
Or with our substitution using equation $(2)$:
```math
f_n = \frac {u_{n} - \sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}} {2f}
```
So even though we arrived at different conclusions, we still got the same
#### result:
> [!IMPORTANT]
> And so our final recurrence relation for $\sqrt {u(x)}$ is:  
$f_n = \frac {u_{n} - 2\sum_{k=1}^{n-1}\binom{n-1}{k}f_{k}f_{n-k}} {2f}$  
Or:  
$f_n = \frac {u_{n} - \sum_{k=1}^{n-1}\binom{n}{k}f_{k}f_{n-k}} {2f}$  
$: n \ge 2$  
$f_1 = \frac {u_1} {2f}$  
$f = \sqrt u$

In code:
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
## $u(x)^c$
Firstly, we can't raise both sides of the equation $f(x) = u(x)^c$ to the power of $\frac 1 c$ as we did with $f=\sqrt u$ since it lands us on $f(x)^{\frac 1 c} = u(x)$ and since $c$ is a constant, we can consider $k=\frac 1 c$. So, we have $f(x)^k = u(x)$ which is our original problem.  

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
y_n = \frac {g_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}g_{n-k}\cdot y_k} {g} : n \ge 2
```
Pluging it into the equation $h_n = c\cdot v_n$ with the definitions of $h$ and $v$, we have:
```math
\frac {f_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}f_{n-k}\cdot h_k} {f} = c\cdot\frac {u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot v_k} {u}
```
Seperating $f_n$ gives us:
```math
f_n = f\left(c\cdot\frac {u_n - \sum_{k = 1}^{n-1}\binom{n-1}{k-1}u_{n-k}\cdot v_k} {u} + \frac {\sum_{k = 1}^{n-1}\binom{n-1}{k-1}f_{n-k}\cdot h_k} {f}\right)
```
Or:
```math
f_n = \frac {cu_nf} {u} + \frac 1 u \sum_{k=1}^{n-1}\binom{n-1}{k-1}\left(uf_{n-k}h_k-fu_{n-k}v_k\right):n\ge2
```
If we differentiate $\ln(f)=c\ln(u)$ directly, we get:
```math
\begin{align*}
&\frac {f_1} {f} = \frac {cu_1} {u}\\
&f_1 = \frac {cu_1f} u\\
\end{align*}
```
The final result is a single summation but it requires us defining extra functions, which is not ideal!  

Thirdly and lastly, let's write out the first derivative to our original function $f=u^c$ which we know by the differential identity $\frac d {dx} x^c = cx^{c-1}$, and with chain rule we have:
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
\begin{alignat*}{2}
LHS &= \sum_{k=0}^{n-1}\binom {n-1} k D^k(f_1)D^{n-1-k}(u) &\qquad&=
\sum_{k=0}^{n-1}\binom {n-1} k D^k(u)D^{n-1-k}(f_1) \\
RHS &= c\sum_{k=0}^{n-1}\binom {n-1} k D^k(f)D^{n-1-k}(u_1) &\qquad&= c\sum_{k=0}^{n-1}\binom {n-1} k D^k(u_1)D^{n-1-k}(f)\\
\end{alignat*}
```
Or in our notation:
```math
\begin{alignat*}{2}
LHS&=\sum_{k=0}^{n-1}\binom {n-1} k f_{k+1}u_{n-1-k} &\qquad&=
\sum_{k=0}^{n-1}\binom {n-1} k u_kf_{n-k}\\
RHS&=c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k} &\qquad&=
c\sum_{k=0}^{n-1}\binom {n-1} k u_{k+1}f_{n-1-k}\\
\end{alignat*}
```
Let's call them $LHS(a), LHS(b)$ and $RHS(a), RHS(b)$.  
Taking $LHS(a)$ and $RHS(a)$, we get:
```math
\sum_{k=0}^{n-1}\binom {n-1} k f_{1+k}u_{n-1-k} = c\sum_{k=0}^{n-1}\binom {n-1} k f_ku_{n-k}  
```
Taking out the last term $(k = n-1)$ from the LHS, we have:
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
Taking out the first term $(k=0)$ from the first summation, we get:
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
\binom {n-1}{k-1} &= \frac {(n-1)!} {(k-1)!(n-k)!} &\qquad \binom {n-1}k &= \frac {(n-1)!} {k!(n-k-1)!}\\
A&=\frac {(n-1)!} {(n-k)(k-1)!(n-k-1)!} &\qquad B&=\frac {(n-1)!} {k(k-1)!(n-k-1)!}\\
A &= B\frac{k}{n-k} &\qquad B &= A\frac {n-k} {k}\\
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
Personally speaking, I prefer them in the reverse order they are presented above and after all the fuss, in the end we finally have our result!
> [!IMPORTANT]
> The result being:  
$f_n = \frac{cfu_n}u+\frac1{u}\sum_{k=1}^{n-1}\binom{n-1}{k-1}\left(c-\frac nk+1\right)f_{n-k}u_k$  
Or:  
$f_n = \frac{cfu_n}u+\frac1u\sum_{k=1}^{n-1}\binom{n-1}k\left(\frac{kc}{n-k}-1\right)f_{n-k}u_k$  
for $n \ge 2$  
$f_1 = \frac{cfu_1}u$  
$f = u^c$

In implementation:
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

And so we are finally done with it! Let's go back to [README](README.md) to continue with the rest of the functions!