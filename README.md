**So...why make new formulae for the stuff nobody is going to need?**  
### Because I can.

Now, derivatives, that we all know and love, have various formulations...  
For example the most basic one we were all probably taught is: $`\lim_{k \to 0^+}\frac{f(a) - f(a - h)} {h}`$ (the backwards difference formula).

> [!NOTE]
> The finite difference formula is actually just an approximation since it samples the points around it to calculate what could be the derivative at the point. It merely converges to the result when `h->0`.  
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
It uses the known recursive definition: $`f^{(n)}(a) = \lim_{k \to 0^+} \frac {f^{(n - 1)}(a) - f^{(n - 1)}(a - h)} {h}`$  

$($ Or in this case the approimation: $`f^{(n)}(a) \approx \frac {f^{(n - 1)}(a) - f^{(n - 1)}(a - h)} {h}`$ $)$  

- Which gives us the result of nth derivative of a function at a specific point.  

Here, $f^{(n)}(a)$ use $f^{(n-1)}(a)$ and $f^{(n-1)}(a-h)$, and they use $(f^{(n-2)}(a), f^{(n-2)}(a - h), f^{(n-2)}(a-h), f^{(n-2)}(a-2h))$ and each of those call another 2 functions, the number of evaluations double each layer, this explodes exponentially, which gives a time complexity of `O(2ⁿ)`.
> [!NOTE] That is the case, if we are not optimizing this naive function with the help of [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming) or memoization.  

But wait, we have duplicates! The $f^{(n-2)}(a - h)$ term appears twice!  
which raises the question, can we find a solution that doesn't have duplicates and works faster than the O(2ⁿ)?  

### Yes, we can.

- So let's look at the zeroth derivative: $f(a)$   
Yep, that's it, zeroth derivative is itself.

- First: $\frac {f(a) - f(a - h)} {h}$  
now let's call them $f$ and $f^{(1)}$  
so, $f^{(1)}$ is just $\frac {f(a) - f(a-h)} {h}$  
I mean, that is the definition right? doing $`\frac {f(a) - f(a - h)} {h}`$ over the base function?  
what if we take $f^{(1)}$ as our base function?  
well, we get:  
$f^{(2)}(a) = \frac {f^{(1)}(a) - f^{(1)}(a - h)} {h}$  
and yes this is our 2nd derivative of the function $f$

- If we write $f^{(2)}$ in terms of $f$ we get:  

    $f^{(2)}(a) = \frac { \frac {f(a) - f(a - h)} {h} - \frac {f(a - h) - f(a - 2h)} {h}} {h}$  

    which on simplification, leads to:  

    $f^{(2)}(a) = \frac {f(a) - 2f(a - h) + f(a - 2h)} {h^2} $

- Now, let's skip ahead and get f₃ and f₄:  

    $f^{(3)}(a) = \frac {f(a) - 3f(a - h) + 3f(a - 2h) - f(a - 3h)} {h^3}$  

    $f^{(4)}(a) = \frac {f(a) - 4f(a - h) + 6f(a - 2h) - 4f(a - 3h) + f(a - 4h)} {h^4}$  

#### Let's just focus on the numerator:  
```math
\begin{align*}
&f(a) = f(a)  \\
&f^{(1)}(a) = f(a) - f(a - h)  \\
&f^{(2)}(a) = f(a) - 2f(a - h) +  f(a - 2h)  \\
&f^{(3)}(a) = f(a) - 3f(a - h) + 3f(a - 2h) -  f(a - 3h)  \\
&f^{(4)}(a) = f(a) - 4f(a - h) + 6f(a - 2h) - 4f(a - 3h) + f(a - 4h)  
\end{align*}
```

Now, some of you may argue that central difference method is a better *approximation* than the backwards finite difference method, i.e., $\lim_{h \to 0^+} \frac {f(a + h) - f(a - h)} {h}$  

I agree with you, so let's rewrite it using ~rust~ I mean the central difference method.  

#### Newmerators are:  
```math
\begin{align*}
&f(a) = f(a)  \\
&f^{(1)}(a) = f(a + h) - f(a - h)  \\
&f^{(2)}(a) = f(a + 2h) - 2f(a) +  f(a - 2h)  \\
&f^{(3)}(a) = f(a + 3h) - 3f(a + h) + 3f(a - h) -  f(a - 3h)  \\
&f^{(4)}(a) = f(a + 4h) - 4f(a + 2h) + 6f(a) - 4f(a - 2h) + f(a - 4h)  
\end{align*}
```

And the denominators subsequently are $(2h)^2$ instead of $h^2$

> [!IMPORTANT]
> **If you are familiar with binomial series or the pascal's triangle, the formula might look a little **appetizing** ....we can compress the formula into this:**  
$f^{(n)}(a) \approx \frac {\sum_{k=0}^n (_k^n) (-1)^k f(a + (n - 2k)h)} {(2h)^n}$  

#### The reason why binomial coefficients appear
Each differentiation computed (current - shifted), which is $(I - S)$.
Where $I$ is the identity operator and $S$ is defined as:  
$Sf(x) = f(x-h)$  

Let's take $D_h = \frac {I - S} {h}$  

The nth derivative applies $D^n$ which is $\frac {(I - S)^n} {h^n}$.  
The binomial theorem gives us $(I - S)^n = \sum_{k=0}^n(_k^n)(-1)^kS^k$
And since $S^kf(a) = f(a - kh)$, we get:  
```math
f^{(n)}(a) \approx \frac {\sum_{k=0}^n (_k^n) (-1)^k f(a - kh)} {(2h)^n}
```
which is for the backwards finite difference approximation.

For the central difference method we have $f(a+h) - f(a-h)$ instead of $f(a) - f(a-h)$ which is $S^{-1} - S$ instead of $I - S$ whose repeated application yields $(S^{-1} - S)^n$ which takes us to our compact formula:  
```math
f^{(n)}(a) \approx \frac {\sum_{k=0}^n (_k^n) (-1)^k f(a + (n - 2k)h)} {(2h)^n}
```
<br>

[Pascal's triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle)/binomial coefficients(if you are unaware):
```math
\begin{gather*}
1 \\
1,1 \\
1,2,1 \\
1,3,3,1 \\
1,4,6,4,1 \\
...
\end{gather*}
```

In practice, our new formula would look like:
```python
def differentiate(function, order, point):
    result = 0.0

    for i in range(order + 1):
        factor = nCr(order, i) * ((-1)**i) # nCr(n, k) * (-1)^k
        component = function(point + (order - 2 * i) * h) # f(a+(n-2k)h)
        result += factor * component

    return result / ((2*h) ** order) # numerator / ((2h)^n)
```

See? very simple!!  
Now, this may seem really good as it is `O(n)` (**If** the *function* is considered `O(1)`) (nCr(s) can be memoized, so let's just count them as `O(1)` as well)  
But OFCOURSE, there are issues!!  
> [!NOTE]
> If we remember our derivative formulae correctly, it also *(on a sidenote but a **very** important side note)* says, `lim`<sub>`h->0`<sup>`+`</sup></sub>  
But the thing is, **this is theoretical**, we are talking about practicality here; and we can't have a variable being infinitesimals, we can make it small(but still measurable).  
That is still just an illusion, as the smaller the h gets more floating point errors accumulate in the result. So, you have to fine tune *h* for **every combination** of `function, point, and order`.  
And after some time, you'd find yourself increasing the size of *h* when finding derivatives of higher *order* due to precision issues.  
Even after that, according to a test I did on a function, `order > 19` seems to be a limit after which the results are completely wrong.  

So, we have established that h can't be an infinitesimal but there is one more major issue with that constraint...
say for example we are calculating the derivative of the *ln near x = 0*.  
The higher the order gets for this issue, the more chances there are that *point - order⋅h* will get smaller than 0.  
Which is a blunder! It goes out of domain of the logarithm(x > 0).  
That is not a desirable behaviour...

- Now, most of you who have done differentiation/scientific computing would say to just use [`symbolic differentiation`](https://en.wikipedia.org/wiki/Computer_algebra) programs or that I should use optimized `Faà di Bruno’s formula`  
But where is the fun in that? We are going to derive our own formulae!

### Formulae we will derive:
- exp(`f(x)`)
- ln(`f(x)`)
- trig(`f(x)`)
- inverse trig(`f(x)`)
- hyperbolic(`f(x)`)
- `u(x)`<sup>`v(x)`</sup>  

> Yes all are composite functions as it will give us more range and challange.

What will we get from doing it?  
Results which only require the point itself, no nearby points(and floating point *h* issues); really optimized solutions; and fun.

> [!TIP]
> Let's first for understanding look at the formula for nth derivative of `f = u⋅v`  
> Where f, v, and u are all functions of x.

$f = u \cdot v$  
So if we apply the product rule, we get:  
$f^{(1)} = u^{(1)} \cdot v + u \cdot v^{(1)}$  

#### Deriving the further derivatives we will get these:  
```math
\begin{align*}
&f = u \cdot v  \\
&f^{(1)} = u^{(1)} \cdot v + u \cdot v^{(1)}  \\
&f^{(2)} = u^{(2)} \cdot v + 2u^{(1)} \cdot v^{(1)} + u \cdot v^{(2)}  \\
&f^{(3)} = u^{(3)} \cdot v + 3u^{(2)} \cdot v^{(1)} + 3u^{(1)} \cdot v^{(2)} + u \cdot v^{(3)}  \\
&f^{(4)} = u^{(4)} \cdot v + 4 u^{(3)} \cdot v^{(1)} + 6 u^{(2)} \cdot v^{(2)} + 4 u^{(1)} \cdot v^{(3)} + u \cdot v^{(4)}  \\
\end{align*}
```
#### If we separate all the coefficients again, we get:  
```math
\begin{gather*}
C_0 = 1  \\
C_1 = 1, 1  \\
C_2 = 1, 2, 1  \\
C_3 = 1, 3, 3, 1  \\
C_4 = 1, 4, 6, 4, 1  \\
\end{gather*}
```
Or in another words, we get the pascal's triangle(binomial coefficients) again!  
> [!IMPORTANT]
> If we were to write it in a compact form, we would get:  
$`f^{(n)} = \sum_{k = 0}^n(_k^n)\cdot u^{(n-k)}\cdot v^{(k)}`$

A really elegant and simple formula `O(n)` (given that we know all n+1 derivative values of u and v)  
In practice, will look something like this:  
```python
def product_derivative(u_derivatives, v_derivatives, order):
    # u_derivatives is the list of derivatives of u from 0 upto `order` like:
    # [u0(a), u1(a), u2(a)...u{n}(a)]
    # same with v_derivatives

    result = 0.0

    for i in range(order + 1): 
        # nCr(n, k) * u{n-k} * v{k}
        result += nCr(order, i) * u_derivatives[order - i] * v_derivatives[i]
    
    return result
```

This was just an example, as this result is pretty well known and is referred to as `leibniz's theorem`  
But now, we will formulate our own formulae!  
Most of (if not all) of our formulae will be using the Pascal's triangle as a hint anchor, so keep it in mind.  
And get ready to do a lot of pattern matching!  

Let's first start with the [`exp(f(x))`](EXP.md) function.  
As you can see there was a significant role of `binomial coefficients` and `pattern matching` and the `leibniz's theorem`.

Which can also be observed in the derivations for higher order derivatives of [`logarithm`](LN.md).
