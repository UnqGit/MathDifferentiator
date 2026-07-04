# Exponential
In this file we'll be discussing the formula for nth derivative of the function $e^{f(x)}$ we all know and love.

## Linear Inner Function

### Simplest Linear Case
We have our function $f(x) = e^x$  
Let's start by writing first few derivatives of $e^x$:
```math
\begin{align*}
f_0 = e^x \\
f_1 = e^x \\
f_2 = e^x \\
\end{align*}
```
Yeah, we won't get anywhere as all the derivatives of the $e^x$ are itself:
```math
\frac {d} {dx} e^{x} = e^{x}\cdot1
```
by using the chain rule.  

### Arbitrary Linear Function
Okay, let's use $e^{ax+b}$ where $a$ and $b$ are constants:
```math
\begin{align*}
&f_0 = e^{ax + b} \\
&f_1 = a \cdot e^{ax + b} \\
&f_2 = a \cdot a \cdot e^{ax + b} = a^2 \cdot e^{ax + b} \\
&f_3 = a^3 \cdot e^{a\cdot x + b} \\
\end{align*}
```
#### Formula
> [!IMPORTANT]
> Okay, we have actual solution in this one:  
$f_{n} = a^n e^{(ax + b)}$

## Arbitrary Inner Function
Now, we have our function $f(x) = e^{u(x)}$  
It might seem hard to find a recurrence for it because of chain rule that will make the equations larger and larger each iteration.  
But it's actually quite simple, here is how:  

### Brute Forcing The Pattern
Let's consider that our function to be $f = e^u$  
Where $u = u(x)$ is some arbitrary differentiable function in $x$.  

So, all we have so far is:  
```math
f_0 = e^u
```

If we differentiate it, we will get:  
```math
\frac {d} {dx} f = e^u \cdot \frac {d} {dx} u
```
Or:
```math
f_1 = e^u \cdot u_1
```
Similarly, if we go up the ladder, we will get:  
```math
\begin{align*}
&f_2 = e^u\cdot u_1^2 + e^u\cdot u_2 \\

&f_3 = e^u\cdot u_1^3 + 3\cdot u_1u_2e^u + e^u\cdot u_3 \\

&f_4 = e^u\cdot u_1^4 + 6\cdot u_1^2u_2e^u + 3\cdot u_2^2e^u + 4\cdot u_3u_1e^u + e^u\cdot u_4 \\
\end{align*}
```

Let's do the next obvious thing and take the $e^u$ common:
```math
\begin{align*}
&f_0 = e^u \\
&f_1 = e^u(u_1) \\
&f_2 = e^u(u_1^2 + u_2) \\
&f_3 = e^u(u_1^3 + 3\cdot u_1u_2 + u_3) \\
&f_4 = e^u(u_1^4 + 6\cdot u_1^2u_2 + 3\cdot u_2^2 + 4\cdot u_3u_1 + u_4) \\
\end{align*}
```
It does look like it has *some* pattern but it is really hard to decipher.  

### Getting Smarter
Let's rewrite each function but using the previous definitions(eg: $f_0$, $f_1$).

That is, look at the first derivative, $f_1 = e^uu_1$ and we know that $f = e^u$, so we can write it as:  
```math
f_1 = fu_1
```
We will get $f_2$ by differentiating $f_1$, that is:  
```math
f_2 = f_1u_1 + fu_2
```
And $f_3$:
```math
f_3 = f_2u_1 + 2\cdot f_1u_2 + fu_3
```
Now, can you see the pattern? It's the same pattern we got when deriving the Leibniz's rule $\rightarrow$ **refer:** [`product.md`](..\product.md).  

We can use Leibniz's rule on the definition of $f_1$(that is: $fu_1$).  
Taking $u_1 \to v$ and applying product rule on $f\cdot v$, $n-1$ times.  
That takes us to:
```math
\begin{align*}

f_{1+m} &= \sum_{k=0}^{m}\binom{m}{k}f_kv_{m-k} \\

m \to n-1&: \\
\\
f_n &= \sum_{k=0}^{n-1}\binom{n-1}{k}f_kv_{n-1-k} \\

v_j \to u_{j+1}&: \\
\\
f_n &= \sum_{k=0}^{n-1}\binom{n-1}{k}f_ku_{n-k} \\

\end{align*}
```
Now, let introduce a new index $j = n - k$.  
Then $k = n - j$.  
- When $k = 0:$
```math
j = n
```
- When $k = n - 1:$
```math
j = 1
```
So, the sum becomes:
```math
f_n = \sum_{j = n}^{1}\binom{n-1}{n-j}f_{n-j}u_j
```
Since the limit is reversed, rewriting in increasing order gives us:
```math
f_n = \sum_{j = 1}^{n}\binom{n-1}{n-j}f_{n-j}u_j
```
Using the identity:
```math
\binom{m}{r} = \binom{m}{m-r}
```
Here,
```math
\binom{n-1}{n-j} = \binom{n-1}{(n-1)-(n-j)} = \binom{n-1}{j-1}
```
Substituting this, we get:
```math
f_n = \sum_{j = 1}^{n}\binom{n-1}{j-1}f_{n-j}u_j
```
$k \longleftrightarrow j:$
```math
f_n = \sum_{k = 1}^{n}\binom{n-1}{k-1}f_{n-k}u_k
```
#### Formula
> [!IMPORTANT]
> Now we have our compact formulae:  
$f_n = \sum_{k = 0}^{n - 1}\binom{n-1}{k}f_{k} u_{n-k}$  
And:  
$f_n = \sum_{k = 1}^{n}\binom{n-1}{k-1}f_{n-k} u_k$     
$\forall$ $n \ge 1$  
$f=e^u$

### Exponential Time Complexity?
If we translate the mathematical definition directly into a recursive function without storing previously computed values, the time complexity will be exponential.  
Let $T(n)$ be the time taken to compute $f_n$. The recurrence relation dictates that to compute $f_n$, we must compute $f_0, f_1, \dots, f_{n-1}$.
```math
T(n) = \sum_{k=0}^{n-1} T(k) + O(n)
```
(The $O(n)$ accounts for multiplying and summing the terms).   
If we evaluate $T(n) - T(n-1)$:
```math
\begin{align*}
&T(n) - T(n-1) = T(n-1) + O(1) \\
&T(n) = 2T(n-1)
\end{align*}
```
This yields a time complexity of $O(2^n)$. Because it recalculates the same subproblems repeatedly, this approach is extremely inefficient and will hang for relatively small values of $n$ (e.g., $n > 30$).  
What we can do is store the previously calculated subproblems, a.k.a dynamic programming.  

#### Practical Implementation
```python
def exp_derivative(u_list, order):
    # u_list is the derivatives of u calculated at some point 'a' from 0 till n.
    # which we will use for the calculation of exp(u(x))

    f_list = [0.0] * (order + 1) # making place for all derivatives(0 through n)
    f_list[0] = math.exp(u_list[0]) # 0th derivative(the function itself) : exp(u(a))
    
    # outer loop to calculate all f_0, f_1, f_2 ... f_n
    for n in range(1, order + 1):

        # inner loop to calculate the individual f_m
        # this inner loop is where we actually use our formula
        for k in range(1, n + 1):
            f_list[n] += nCr(n-1, k-1) * f_list[n-k] * u_list[k]
            # f_n = sum{1, n} nCr(n-1, k-1) * f{n-k} * u{k}

    return f_list
```
> nCr is a function that returns precomputed values for binomial coefficients

Now, if we know all the required derivatives of $u$ and $f$, that is $u_0 \to u_{n}$ and $f_0 \to f_{n-1}$ then calculating the $f_n$ is $O(n)$.  
But calculating all $f_0 \to f_n$ is actually $O(n^2)$.

_**`Isn't mathematics amazing?! ✨`**_

## Arbitrary Constant Base
Now that was just $e^{f(x)}$ which has the base $e$, also known as [Euler's number](https://en.wikipedia.org/wiki/E_(mathematical_constant)).

But what if the base was something like $2$ or $\pi$?

Let's see what are the changes we need to make to be able differentiate now.  
If we go back to the _good ol' highschool days_, one of the most important thing we were taught is that $\ln(f)$ is the inverse of $e^f$.

What that means is that $e^{\ln(x)}=x$, that means we can write $a^x$ as $e^{\ln(a^x)}$.  
And remember $\ln(x^y) = y\ln(x)$, so we can write $a^x$ as $e^{x\ln(a)}$

We have converted the question back to the base $e$.
> We have reduced the function back to $e^f$ with the inner function scaled by the factor of $\ln(a)$.

**Let's write the first few derivatives of the function $a^{u(x)}$:**
```math
\begin{align*}
&f_0 = e^{u\cdot \ln(a)} \\
&f_1 = \ln(a)\cdot fu_1 \\
\end{align*}
```
Which gives us:
```math
{f_n} = \ln(a)D^{n-1}(fu_1)
```
$D^{n-1}(fu_1)$ is exactly what we computed in the previous section, that gives us our
#### Formula
> [!IMPORTANT]  
$f_n = \ln(a)\sum_{k = 0}^{n - 1}\binom{n-1}{k}f_{k} u_{n-k}$  
Or:  
$f_n = \ln(a)\sum_{k = 1}^{n}\binom{n-1}{k-1}f_{n-k} u_k$     
$\forall$ $n \ge 1$  
$f=e^{u\ln(a)}$  

#### Practical Implementation
```python
def const_base_pow_derivative(base, u_list, order):
    # u_list is the derivatives of u(x) from 0 to n calculated at a point x

    f_list = [0.0] * (order + 1) # making space for all f{n} 0 till n
    base_factor = math.log(base) # ln(a)
    f_list[0] = math.exp(u_list[0] * base_factor) # f0 = e^(ln(a)*u0(x))

    # outer loop for calculating all derivatives 0 till n of the function a^(u(x))
    for n in range(1, order + 1):

        # inner loop for calculating individual f{m}
        for k in range(1, n + 1):
            f_list[n] += nCr(n-1, k-1) * f_list[n-k] * u_list[k]
            # f{n} = sum{1, n} nCr(n-1, k-1) * f{n-k} * u{k}
        
        # multiplying the entire summation with ln(a)
        f_list[n] *= base_factor

    # returning all the derivatives from 0 to n
    return f_list
```

#### Logarithm Pitfall
You might be wondering that $\ln(a)$ is not defined when $a < 0$ and our function will fail and you'd be correct!  

We know that derivative of a function gives us the instantaneous rate of change of a function at that particular point: $f'(x) = \lim_{h \to 0+} \frac {f(a + h) - f(a)} {h}$ which requires $f$ exist for all sufficiently small $h$.  

*This function*, $a^u:a<0$ however, is not defined for *any* open interval $(x - \epsilon, x + \epsilon)$ of the real line which the standard differentiation rules require and so we cannot calculate the derivative of this function.  

**Or simply put, in real numbers($\mathbb{R}$), an exponential function with a negative base is impossible to differentiate.**  

But, if we step into the $\mathbb{C}$ plane instead of $\mathbb{R}$ number line, then the function becomes continuous.  
And our formula works as it's supposed to.

#### It Goes Deeper
When I said we were *using Leibniz's rule* $n-1$ *times*, we were effectively computing [bell polynomials](https://en.wikipedia.org/wiki/Bell_polynomials) for this specialized case, have a look at those and you'd be more amazed :D.  
If you want to fall further into the rabbit hole, look into [Faà di Bruno](https://en.wikipedia.org/wiki/Francesco_Fa%C3%A0_di_Bruno) and [Faà di Bruno formula](https://en.wikipedia.org/wiki/Fa%C3%A0_di_Bruno%27s_formula).

> That's it for $\exp$...or is it?