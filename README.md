**So...why make new formulae for the stuff nobody is going to need?**  
### Because I can.
> [!NOTE]
> I will be using the notation $f_n$ for showcasing the $n^{th}$ derivative of a function $f$ instead of the $f^{(n)}$ notation because it will be clearer to showcase the ideas.

Now, derivatives, that we all know and love, have various formulations...  
For example the most basic one we were all probably taught is: $`\lim_{k \to 0^+}\frac{f(a) - f(a - h)} {h}`$ (the backwards difference formula).


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

Here, $f_n(a)$ use $f_{n-1}(a)$ and $f_{n-1}(a-h)$, and they use $(f_{n-2}(a), f_{n-2}(a - h), f_{n-2}(a-h), f_{n-2}(a-2h))$ and each of those call another 2 functions, the number of evaluations double each layer, this explodes exponentially, which gives a time complexity of `O(2ⁿ)`.  
But wait, we have duplicates! The $f_{n-2}(a - h)$ term appears twice!  
which raises the question, can we find a solution that doesn't have duplicates and works faster than the $O(2^n)$?  
> [!NOTE]
> The finite difference formula is actually just an approximation since it samples the points around it to calculate what could be the derivative at the point. It merely converges to the result when $h \to 0$.  
$O(2^n)$ is the case, if we are not optimizing this naive function with the help of [dynamic programming](https://en.wikipedia.org/wiki/Dynamic_programming) or [memoization](https://en.wikipedia.org/wiki/Memoization).  


### Yes, we can.

- So let's look at the zeroth derivative: $f(a)$   
Yep, that's it, zeroth derivative is itself.

- First: $\frac {f(a) - f(a - h)} {h}$  
now let's call them $f$ and $f_1$  
so, $f_1$ is just $\frac {f(a) - f(a-h)} {h}$  
I mean, that is the definition right? doing $`\frac {f(a) - f(a - h)} {h}`$ over the base function?  
what if we take $f_1$ as our base function?  
well, we get:  
$f_2(a) = \frac {f_1(a) - f_1(a - h)} {h}$  
and yes this is our 2nd derivative of the function $f$

- If we write $f_2$ in terms of $f$ instead of $f_1$, we get:  

    $f_2(a) = \frac { \frac {f(a) - f(a - h)} {h} - \frac {f(a - h) - f(a - 2h)} {h}} {h}$  

    which on simplification, leads to:  

    $f_2(a) = \frac {f(a) - 2f(a - h) + f(a - 2h)} {h^2} $

- Now, let's skip ahead and get $f_3$ and $f_4$:  

    $f_3(a) = \frac {f(a) - 3f(a - h) + 3f(a - 2h) - f(a - 3h)} {h^3}$  

    $f_4(a) = \frac {f(a) - 4f(a - h) + 6f(a - 2h) - 4f(a - 3h) + f(a - 4h)} {h^4}$  

#### Let's just focus on the numerator:  
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

#### Newmerators are:  
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

> [!IMPORTANT]
> **If you are familiar with binomial series or the pascal's triangle, the coefficients might look a little appealing...we can compress the formula into this:**  
$f_n(a) \approx \frac {\sum_{k=0}^n \binom {n} {k} (-1)^k f(a + (n - 2k)h)} {(2h)^n}$  

#### The reason why binomial coefficients appear
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
<br>

[Pascal's triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle)/binomial coefficients(if you are unaware):
```math
\begin{gather*}
1 \\
1,1 \\
1,2,1 \\
1,3,3,1 \\
1,4,6,4,1 \\
\cdots
\end{gather*}
```

In practice, our new formula would look like:
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
Now, this may seem really good as it is `O(n)` (**If** the *function* is considered `O(1)`) (nCr(s) can be memoized, so let's just count them as `O(1)` as well)  
But OFCOURSE, there are issues!!  
> [!NOTE]
> If we remember our derivative formulae correctly, it also *(on a sidenote but a **very** important side note)* says, $\lim_{h\to0^+}$  
But the thing is, **this is theoretical**, practically speakinh we can't have a variable being infinitesimals, we can make it small(but still measurable).  
That is still just an illusion, as the smaller the h gets more floating point errors accumulate in the result. So, you have to *fine tune* $h$ for **every combination** of `function, point, and order`.  
And after some time, you'd find yourself increasing the size of $h$ when finding derivatives of higher *order* due to precision issues.  
Even after that, according to a test I did on a function, `order > 19` seems to be a limit after which the results are completely wrong.  

So, we have established that h can't be an infinitesimal but there is one more major issue with that constraint...
say for example we are calculating the derivative of the $\ln(x)$ *near* $x = 0$.  
The higher the order gets for this issue, the more chances there are that *point - order⋅h* $(x-n\cdot h)$ will get smaller than 0.  
Which is a massive blunder! It goes out of domain of the logarithm $(x > 0)$.  

- Now, most of you who have done/know about differentiation/scientific computing would say to just use [`symbolic differentiation`](https://en.wikipedia.org/wiki/Computer_algebra) programs or that I should use optimized `Faà di Bruno’s formula`  
But where is the fun in that? We are going to derive our own formulae!

### Formulae we will derive:
- $e^{f(x)}$
- $u(x)^{v(x)}$
- $\sqrt{u(x)}$
- $\ln(f(x))$
- Trigonometry:
    - $\sin(f(x))$ , $\cos(f(x))$
    - $\cot(f(x))$ , $\tan(f(x))$
    - $\csc(f(x))$ , $\sec(f(x))$
- inverse trigonometry:
    - $\sin^{-1}(f(x))$ , $\cos^{-1}(f(x))$
    - $\cot^{-1}(f(x))$ , $\tan^{-1}(f(x))$
    - $\csc^{-1}(f(x))$ , $\sec^{-1}(f(x))$
- hyperbolic trigonometry:
    - $\sinh(f(x))$ , $\cosh(f(x))$
    - $\coth(f(x))$ , $\tanh(f(x))$
    - **csch** $(f(x))$ , **sech** $(f(x))$

> Yes all are composite functions as it will give us more range and challange.

What will we get from doing it?  
Results which only require the point itself, no nearby points(and floating point issues related to $h$); really optimized solutions; and fun.

> [!TIP]
> Let's first for understanding look at the formula for nth derivative of `f = u⋅v`  
> Where f, v, and u are all functions of x.

$f = u \cdot v$  
So if we apply the product rule, we get:  
$f_1 = u_1 \cdot v + u \cdot v_1$  

#### Deriving the further derivatives we will get these:  
```math
\begin{align*}
&f = u \cdot v  \\
&f_1 = u_1 \cdot v + u \cdot v_1  \\
&f_2 = u_2 \cdot v + 2u_1 \cdot v_1 + u \cdot v_2  \\
&f_3 = u_3 \cdot v + 3u_2 \cdot v_1 + 3u_1 \cdot v_2 + u \cdot v_3  \\
&f_4 = u_4 \cdot v + 4 u_3 \cdot v_1 + 6 u_2 \cdot v_2 + 4 u_1 \cdot v_3 + u \cdot v_4  \\
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
$`f_n = \sum_{k = 0}^n\binom{n}{k} u_{n-k}\cdot v_{k}`$

A really elegant and simple formula `O(n)` (given that we know all $n+1(0\dots n)$ derivative values of $u$ and $v$)  
In practice, will look something like this:  
```python
def product_derivative(u_list, u_list, order):
    # u_list is the list of derivatives of u from 0 upto `order` like:
    # [u0(a), u1(a), u2(a)...u{n}(a)]
    # same with v_list

    result = 0.0

    for k in range(order + 1):
        # nCr(n, k) * u{n-k} * v{k}
        result += nCr(order, k) * u_list[order - k] * v_list[k]
    
    return result
```
Or if we are going to calculate all the derivatives from $0 \to n$ then:
```python
def product_derivatives(u_list, v_list, order):
    # calculate individual product derivative orders and create a list
    f_list = [product_derivative(u_list, v_list, n) for n in range(order + 1)]
    return f_list
```
This was just an example, as this result is pretty well known and is referred to as `leibniz's theorem`  
But now, we will formulate our own formulae!  
Most of (if not all) of our formulae will be using the Pascal's triangle as a hint anchor, so keep it in mind.  
And get ready to do a lot of pattern matching!  

Let's first start with the [e<sup>f(x)</sup>](EXP.md) function.  
As you can see there was a significant role of `binomial coefficients` and `pattern matching` and the `leibniz's theorem`.

Which can also be observed in the derivations for higher order derivatives of [ln(f(x))](LN.md).
Now, that we are on the topic of power related functions let's take a look at [u(x)<sup>c</sup>](CONST_POW.md)  
And finally staying on the topic we have our final boss [u(x)<sup>v(x)</sup>](POW.md)

Now, that power functions are over, let's take a look at trigonometry and start with [tan(u(x))](TAN.md)