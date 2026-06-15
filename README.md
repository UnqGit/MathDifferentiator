**So...why make new formulae for the stuff nobody is going to need?**  
### Because I can.

Now, derivatives, that we all know and love have various ways to get to the result..  
For example the most basic one we were all probably taught is: $`\frac{f(a) - f(a - h)} {h}`$

And it would look like:
```python
def function_derivative(function, point, order):
    if order == 0:
        return function(point)

    derivative_at_point = function_derivative(function, point, order - 1)
    derivative_at_left = function_derivative(function, point - h, order - 1)
    difference = derivative_at_point - derivative_at_left

    return difference / h
```
It uses the known recursive definition of $`f^{(n)}(a) = \frac {f^{(n - 1)}(a) - f^{(n - 1)}(a - h)} {h}`$

- Which gives us the result of nth derivative of a function at a specific point.  

> [!NOTE]
> Now it'd be great if it were sufficient...  
But the most major flaw with it is that it is `O(2ⁿ)`  
Now ofcourse we can find a iterative solution right?

### Yes, we can.

- So let's look at the zeroth derivative: $f(a)$   
Yep, that's it, zeroth derivative is itself.

- First: $\frac {f(a) - f(a - h)} {h}$  
now let's call them $f_0$ and $f_1$  
so, $f_1$ is just $\frac {f_0(a) - f_0(a-h)} {h}$  
I mean, that is the definition right? doing $`\frac {f(a) - f(a - h)} {h}`$ over the base function?  
what if we take $f_1$ as our base function?  
well, we get:  
$f_2(a) = \frac {f_1(a) - f_1(a - h)} {h}$  
and yes this is our 2nd derivative of the function $f_0$

- If we write $f_2$ in terms of $f_0$ we get:  
$f_2(a) = \frac { \frac {f_0(a) - f_0(a - h)} {h} - \frac {f_0(a - h) - f_0(a - 2h)} {h}} {h}$  
which on simplification, leads to:  
$f_2(a) = \frac {f_0(a) - 2f_0(a - h) + f_0(a - 2h)} {h^2} $

- Now, let's skip ahead and get f₃ and f₄:  
$f_3(a) = \frac {f_0(a) - 3f_0(a - h) + 3f_0(a - 2h) - f_0(a - 3h)} {h^3}$  
$f_4(a) = \frac {f_0(a) - 4f_0(a - h) + 6f_0(a - 2h) - 4f_0(a - 3h) + f_0(a - 4h)} {h^4}$  

- [ ] Let's just focus on the numerator:  
$$
\begin{align*}
&f_0(a) = f_0(a)  \\
&f_1(a) = f_0(a) - f_0(a - h)  \\
&f_2(a) = f_0(a) - 2f_0(a - h) +  f_0(a - 2h)  \\
&f_3(a) = f_0(a) - 3f_0(a - h) + 3f_0(a - 2h) -  f_0(a - 3h)  \\
&f_4(a) = f_0(a) - 4f_0(a - h) + 6f_0(a - 2h) - 4f_0(a - 3h) + f_0(a - 4h)  
\end{align*}
$$
> [!IMPORTANT]
> Now, some of you may argue that *f(a) - f(a - h)* is not the actual used definition, it is `f(a + h) - f(a - h)`
> I agree with you, so let's rewrite it in ~rust~ I mean the actual used formula.  

- [ ] Newmerators are:  
$$
\begin{align*}
&f_0(a) = f_0(a)  \\
&f_1(a) = f_0(a + h) - f_0(a - h)  \\
&f_2(a) = f_0(a + 2h) - 2f_0(a) +  f_0(a - 2h)  \\
&f_3(a) = f_0(a + 3h) - 3f_0(a + h) + 3f_0(a - h) -  f_0(a - 3h)  \\
&f_4(a) = f_0(a + 4h) - 4f_0(a + 2h) + 6f_0(a) - 4f_0(a - 2h) + f_0(a - 4h)  
\end{align*}
$$

And the denominators subsequently are $(2h)^2$ instead of $h^2$

> [!IMPORTANT]
> **If you are familiar with binomial series or the pascal's triangle, the formula might look a little **appetizing** ....we can compress the formula into this:**  
$f_n(a) = \frac {\sum_{k=0}^n (_k^n) (-1)^k f_0(a + (n - 2k)h)} {(2h)^n}$  
```python
def function_derivative(function, point, order):
    result = 0.0

    for i in range(order + 1):
        factor = nCr(order, i) * ((-1)**i) # nCr(n, k) * (-1)^k
        component = function(point + (order - 2 * i) * h) # f(a+(n-2k)h)
        result += factor * component

    return result / ((2*h) ** order) # numerator / ((2h)^n)
```

See? very simple!!  
Now, this may seem really good as it is `O(n)` (**If** the function is `O(1)`) (nCr(s) can be cached, so let's just count them as `O(1)` as well)  
But ofcourse there are issues!!  
> [!NOTE]
> If we remember our derivative formulae correctly, it also, on a sidenote but a **very** important side note  
It also says, `lim`<sub>`h->0`<sup>`+`</sup></sub>  
But the thing is, `this is theoretical`, we are talking about practicality here and we can't have a variable with almost 0 size, we can have it really small  
But that is just an illusion as the smaller the h gets the more lossy the result gets and worse yet you have to fine tune the h for every `function + point + derivative_number`  
combination to get it to give us good results which also give us completely wrong results after `derivative_number > 19`  
and most of the time it will get to the point where you would need to have larger stepsize as the derivative_number gets larger and that's another issue in on itself!<br/><br/>
> So, we have established that h can't be infinitely small and there is one more major issue with that constraint...
say for example we are calculating the derivative of the `ln function near x = 0`  
The higher the derivative_number gets for this issue, the more chances there are that `point - derivative_number⋅h` will get smaller than 0, which is an issue  
because the logarithm function is not defined below `x = 0` and that is not a good and desirable behaviour to have...

- Now, most of you who have done differentiation would say to just use `automatic differentiation` programs or that I should use optimized `Faà di Bruno’s formula`  
But where is the fun in that, we are going to derive our own formulae!

### Formulae we will derive
- exp(`f(x)`)
- ln(`f(x)`)
- trig(`f(x)`)
- inverse trig(`f(x)`)
- hyperbolic(`f(x)`)
- `u(x)`<sup>`v(x)`</sup>  

> Yes all are composite functions as it will give us more range.

What will we get from doing it?  
Results which only require the point itself, no nearby points; really optimized solutions; and fun.

> [!TIP]
> Let's first for understanding look at the formula for nth derivative of `f = u⋅v`  
> Where f, v, and u are all functions.

$f_0 = u_0 \cdot v_0$  
So if we apply the product rule, we get:  
$f_1 = u_1 \cdot v_0 + u_0 \cdot v_1$  

- [ ] Deriving the further derivatives we will get these:  
$$
\begin{align*}
&f_0 = u_0 \cdot v_0  \\
&f_1 = u_1 \cdot v_0 + u_0 \cdot v_1  \\
&f_2 = u_2 \cdot v_0 + 2u_1 \cdot v_1 + u_0 \cdot v_2  \\
&f_3 = u_3 \cdot v_0 + 3u_2 \cdot v_1 + 3u_1 \cdot v_2 + u_0 \cdot v_3  \\
&f_4 = u_4 \cdot v_0 + 4 u_3 \cdot v_1 + 6 u_2 \cdot v_2 + 4 u_1 \cdot v_3 + u_0 \cdot v_4  \\
\end{align*}
$$
- [ ] If we separate all the coefficients again, we get:  
$$
\begin{align*}
C_0 = &1  \\
C_1 = 1&, 1  \\
C_2 = 1, &2, 1  \\
C_3 = 1, 3&, 3, 1  \\
C_4 = 1, 4, &6, 4, 1  \\
\end{align*}
$$
Or in another words, we get the pascal's triangle(binomial coefficients) again!  
> [!IMPORTANT]
> If we were to write it in a compact form, we would get:  
$f_n = \sum_{k = 0}^n(_k^n)\cdot u_{n-k}\cdot v_k$

A really elegant and simple formula `O(n)` (given that we know all n+1 derivative values of u and v)  
In practice, would look something like this:  
```python
def multiplicative_derivative(u_derivatives, v_derivatives, order):
    result = 0.0
    for i in range(order + 1):
        result += nCr(order, i) * u_derivatives[order - i] * v_derivatives[i]
    return result
```

This was just an example, as this result is pretty well known and is reffered to as `leibniz's theorem`  
But now, we will formulate our own formulae!  
Keep in mind the pascal's triangle as most of if not all of our formulae will be using it; and we will have to do a lot of pattern matching!  

Let's first start with the [`exp(f(x))`](EXP.md) function.  
As you can see there was a significant role of `binomial coefficients` and `pattern matching` and the `leibniz's theorem`.

Which can also be observed in the derivations for higher order derivatives of [`logarithm`](LN.md).
