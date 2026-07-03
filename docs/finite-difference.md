# Finite Difference Methods

## Recursive Definition
Now, derivatives, that we all know and love, have various formulations...  
For example the most basic one we were all probably taught is: $\lim_{h \to 0^+}\frac{f(a) - f(a - h)} {h}$ (the backwards difference formula).

But let's play around the idea for a bit.

And in practice, it would look something like:
```python
def differentiate(function, order, point):
    if order == 0:
        return function(point) # f{0} = f itself

    derivative_at_point = differentiate(function, order - 1, point) # f{n-1}(a)
    derivative_at_left = differentiate(function, order - 1, point - h) # f{n-1}(a-h)
    difference = derivative_at_point - derivative_at_left # f{n-1}(a) - f{n-1}(a-h)

    return difference / h
```
It uses the known recursive definition: $`f_n(a) = \lim_{h \to 0^+} \frac {f_{n - 1}(a) - f_{n - 1}(a - h)} {h}`$  

$($ Or in this case the approimation: $`f_n(a) \approx \frac {f_{n - 1}(a) - f_{n - 1}(a - h)} {h}`$ $)$  

Which gives us the result of nth derivative of a function at a specific point.  

## Why Naive Recursion Fails Miserably
Here, $f_n(a)$ use $f_{n-1}(a)$ and $f_{n-1}(a-h)$, and they use $(f_{n-2}(a), f_{n-2}(a - h), f_{n-2}(a-h), f_{n-2}(a-2h))$ and each of those call another 2 functions, the number of evaluations double each layer, this explodes exponentially, which gives a time complexity of `O(2ⁿ)`.  
But wait, we have duplicates! The $f_{n-2}(a - h)$ term appears twice!  
which raises the question, can we find a solution that doesn't have duplicates and works faster than the $O(2^n)$?  
> [!NOTE]
> The finite difference formula is actually just an approximation since it samples the points around it to calculate what could be the derivative at the point. It merely converges to the result when $h \to 0$.  
$O(2^n)$ is the case, if we are not optimizing this naive function with the help of [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming) or [memoization](https://en.wikipedia.org/wiki/Memoization).  

## Eliminating Duplicate Work
let's look at the $0^{th}$ derivative: $f(a)$   
Yep, that's it, $0^{th}$ derivative is itself.

$1^{st}$: $\frac {f(a) - f(a - h)} {h}$  
now let's call them $f$ and $f_1$  
so, $f_1$ is just:
```math
\frac {f(a) - f(a-h)} {h}
```
what if we take $f_1$ as our base function?  
well, we get:  
```math
f_2(a) = \frac {f_1(a) - f_1(a - h)} {h}
```
and this is the $2^{nd}$ derivative of the function $f$.

If we write $f_2$ in terms of $f$ instead of $f_1$, we get:  
```math
f_2(a) = \frac { \frac {f(a) - f(a - h)} {h} - \frac {f(a - h) - f(a - 2h)} {h}} {h}
```
which on simplification, leads to:  
```math
f_2(a) = \frac {f(a) - 2f(a - h) + f(a - 2h)} {h^2}
```

Now, let's skip ahead and get $f_3$ and $f_4$:  

```math
f_3(a) = \frac {f(a) - 3f(a - h) + 3f(a - 2h) - f(a - 3h)} {h^3}
```

```math
f_4(a) = \frac {f(a) - 4f(a - h) + 6f(a - 2h) - 4f(a - 3h) + f(a - 4h)} {h^4}
```

**Let's just focus on the numerator:**  
```math
\begin{align*}
&f(a) = f(a)  \\
&f_1(a) = f(a) - f(a - h)  \\
&f_2(a) = f(a) - 2f(a - h) +  f(a - 2h)  \\
&f_3(a) = f(a) - 3f(a - h) + 3f(a - 2h) -  f(a - 3h)  \\
&f_4(a) = f(a) - 4f(a - h) + 6f(a - 2h) - 4f(a - 3h) + f(a - 4h)  
\end{align*}
```

Now, some of you may argue that central difference method is a better *approximation* than the backwards finite difference method, i.e., $\lim_{h \to 0^+} \frac {f(a + h) - f(a - h)} {h}$  

I agree with you, so let's rewrite it using central difference method.  

**Newmerators are:**  
```math
\begin{align*}
&f_0(a) = f(a)  \\
&f_1(a) = f(a + h) - f(a - h)  \\
&f_2(a) = f(a + 2h) - 2f(a) +  f(a - 2h)  \\
&f_3(a) = f(a + 3h) - 3f(a + h) + 3f(a - h) -  f(a - 3h)  \\
&f_4(a) = f(a + 4h) - 4f(a + 2h) + 6f(a) - 4f(a - 2h) + f(a - 4h)  
\end{align*}
```

And the denominators consequently are $(2h)^2$ instead of $h^2$

## Discovering Binomial Coefficients
If you look at the coefficients of the we can see that they resemble binomial coefficients or the Pascal's triangle, just with alternating signs.  
The function arguments in each term of any of the derivatives also make a arithmetic progression with a common difference of $2h$.

### The reason why binomial coefficients appear
Each differentiation computes (current - shifted), which is $(I - S)$.
Where $I$ is the identity operator and $S$(shift operator) is defined as:  
$Sf(x) = f(x-h)$  

Let's take $D_h = \frac {I - S} {h}$  

The nth derivative applies $D^n$ which is $\frac {(I - S)^n} {h^n}$.  

The binomial theorem gives us $(I - S)^n = \sum_{k=0}^n\binom{n}{k}(-1)^kS^k$
And since $S^kf(a) = f(a - kh)$, we get:  
```math
f_n(a) \approx \frac {\sum_{k=0}^n \binom{n}{k} (-1)^k f(a - kh)} {(2h)^n}
```
which is for the backwards finite difference approximation.

For the central difference method we have $f(a+h) - f(a-h)$ instead of $f(a) - f(a-h)$ which is $(S^{-1} - S)$ instead of $(I - S)$ whose repeated application yields $(S^{-1} - S)^n$ which takes us to our compact formula:  
```math
f_n(a) \approx \frac {\sum_{k=0}^n \binom{n}{k} (-1)^k f(a + (n - 2k)h)} {(2h)^n}
```
## Compact Formula
> [!IMPORTANT]
> **If you are familiar with binomial series or the [pascal's triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle), the coefficients might look a little appealing...we can compress the formula into this:**  
$f_n(a) \approx \frac {\sum_{k=0}^n \binom {n} {k} (-1)^k f(a + (n - 2k)h)} {(2h)^n}$  

## Practical Implementation
```python
def differentiate(function, order, point):
    numerator = 0.0 # variable that accumulates the numerator
    denominator = (2*h) ** order # (2h)^n

    # summation from k = 0 to n
    for k in range(order + 1):
        factor = nCr(order, k) * ((-1)**k) # nCr(n, k) * (-1)^k
        component = function(point + (order - 2 * k) * h) # f(a+(n-2k)h)
        numerator += factor * component

    return numerator / denominator
```

See? very simple!!  
Now, this may seem really good as it is `O(n)` $($ If the *function* is considered $O(1)$; $\binom nr$ are $O(1)$ with *memoization* $)$  

## Numerical Limitations

### Floating Point Cancellation
If we remember our derivative formulae correctly, it also says, $\lim_{h\to0^+}$  
But the thing is, this is **theoretical**, practically speaking we can't have infinitesimal variables.  
We can make $h$ small but that is still just an *illusion*, as the smaller the $h$ gets more floating point errors accumulate in the result. So, you have to *fine tune* $h$ for **every combination** of `function`, `point`, and `order`.  
Even after that, according to a test I did on a function, `order > 19` seems to be a limit after which the results are completely wrong.  

### Domain Restrictions
So, we have established that $h$ can't be an infinitesimal but there is one more major issue with that constraint, say for example we are calculating the derivative of the $\ln(x)$ *near* $x = 0$.  
As the order raises higher, there are more chances there are that *point - order⋅h* $(x-n\cdot h)$ will get smaller than $0$.  
That is a **massive** blunder. It goes out of domain of the logarithm $(x > 0)$.  

<br> <br>

If there are so many issues with finite difference methods, then how are we going to calculate the higher order derivatives without first deriving massive equations for the original function? That is what we are going to explore further in the [introduction.md](introduction.md)