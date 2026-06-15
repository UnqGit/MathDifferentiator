**So...why make new formulae for the stuff nobody is going to need?**  
### Because I can.

Now, derivatives, that we all know and love have various ways to get to the result..  
For example the most basic one we were all probably taught is:

`(f(a) - f(a - h))/h`

And it would look like:
```python
def function_derivative(function, point, derivative_number):
    return function(point) if derivative_number == 0 else
        ((function_derivative(function, point, derivative_number - 1)
        -function_derivative(function, point - h, derivative_number - 1)) / h)
```

- Which gives us the result of nth derivative of a function at a specific point.  

> [!NOTE]
> Now it'd be great if it were sufficient...  
But the most major flaw with it is that it is `O(2ⁿ)`  
Now ofcourse we can find a iterative solution right?

### Yes, we can.

- So let's look at the zeroth derivative:  
`f(a)`  
Yep, that's it, zeroth derivative is itself.

- First:  
`(f(a) - f(a - h))/h`  
now let's call them *f₀* and *f₁*  
so, *f₁* is just `(f₀(a) - f₀(a - h))` over *h*  
I mean, that is the definition right? doing `(f(a) - f(a - h))/h` over the base function?  
what if we take *f₁* as our base function?  
well, we get:  
f₂(a) = `(f₁(a) - f₁(a - h))/h`  
and yes this is our 2nd derivative of the function *f₀*

- If we write f₂ in terms of f₀ we get:  
f₂(a) = `(((f₀(a) - f₀(a - h))/h) - ((f₀(a - h) - f₀(a - 2h))/h))/h`  
which on simplification, leads to:  
f₂(a) = `(f₀(a) - 2⋅f₀(a - h) + f₀(a - 2h))/h²`

- Now, let's skip ahead and get f₃ and f₄:  
f₃(a) = `(f₀(a) - 3⋅f₀(a - h) + 3⋅f₀(a - 2h) - f₀(a - 3h))/h³`  
f₄(a) = `(f₀(a) - 4⋅f₀(a - h) + 6⋅f₀(a - 2h) - 4⋅f₀(a - 3h) + f₀(a - 4h))/h⁴`  

- [ ] Let's just focus on the numerator:  
```
f₀(a) = f₀(a)  
f₁(a) = f₀(a) - f₀(a - h)  
f₂(a) = f₀(a) - 2⋅f₀(a - h) + f₀(a - 2h)  
f₃(a) = f₀(a) - 3⋅f₀(a - h) + 3⋅f₀(a - 2h) - f₀(a - 3h)  
f₄(a) = f₀(a) - 4⋅f₀(a - h) + 6⋅f₀(a - 2h) - 4⋅f₀(a - 3h) + f₀(a - 4h)
```
> [!IMPORTANT]
> Now, some of you may argue that *f(a) - f(a - h)* is not the actual used definition, it is `f(a + h) - f(a - h)`
> I agree with you, so let's rewrite it in ~rust~ I mean the actual used formula.  

- [ ] Newmerators are:  
```
f₀(a) = f₀(a)  
f₁(a) = f₀(a + h) - f₀(a - h)  
f₂(a) = f₀(a + 2h) - 2⋅f₀(a) + f₀(a - 2h)  
f₃(a) = f₀(a + 3h) - 3⋅f₀(a + h) + 3⋅f₀(a - h) - f₀(a - 3h)  
f₄(a) = f₀(a + 4h) - 4⋅f₀(a + 2h) + 6⋅f₀(a) - 4⋅f₀(a - 2h) + f₀(a - 4h)  
```
And the denominators subsequently are (2h)<sup>n</sup> instead of h<sup>n</sup>

> [!IMPORTANT]
> **If you are familiar with binomial series or the pascal's triangle, the formula might look a little **appetizing** ....we can compress the formula into this:**  
f<sub>n</sub>(a) = (**<sub>k=0</sub>ⁿ∑** (<sup>n</sup><sub>k</sub>)⋅(-1)<sup>k</sup>⋅f₀(a + (n-2⋅k)⋅h)) / (2h)<sup>n</sup>  
```python
def function_derivative(function, point, derivative_number):
    result = 0.0
    for i in range(derivative_number + 1):
         result += nCr(derivative, i) * ((-1)**i) * function(point + (derivative_number - 2*i)*h)
    return result / ((2*h) ** derivative_number)
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

f₀ = `u₀⋅v₀`  
So if we apply the product rule, we get:  
f₁ = `u₁⋅v₀ + u₀⋅v₁`  

- [ ] Deriving the further derivatives we will get these:  
```
f₀ = u₀⋅v₀  
f₁ = u₁⋅v₀ + u₀⋅v₁  
f₂ = u₂⋅v₀ + 2⋅u₁⋅v₁ + u₀⋅v₂  
f₃ = u₃⋅v₀ + 3⋅u₂⋅v₁ + 3⋅u₁⋅v₂ + u₀⋅v₃  
f₄ = u₄⋅v₀ + 4⋅u₃⋅v₁ + 6⋅u₂⋅v₂ + 4⋅u₁⋅v₃ + u₀⋅v₄
```
- [ ] If we separate all the coefficients again, we get:  
```
C₀ = 1  
C₁ = 1, 1  
C₂ = 1, 2, 1  
C₃ = 1, 3, 3, 1  
C₄ = 1, 4, 6, 4, 1
```
Or in another words, we get the pascal's triangle(binomial coefficients) again!  
> [!IMPORTANT]
> If we were to write it in a compact form, we would get:  
f<sub>n</sub> = **<sub>k=0</sub><sup>n</sup>∑** (<sup>n</sup><sub>k</sub>)⋅u<sub>n-k</sub>⋅v<sub>k</sub>

A really elegant and simple formula `O(n)` (given that we know all n+1 derivative values of u and v)  
In practice, would look something like this:  
```python
def multiplicative_derivative(u_list, v_list, derivative_number):
    result = 0.0
    for i in range(derivative_number + 1):
        result += nCr(derivative_number, i) * u_list[derivative_number - i] * v_list[i]
    return result
```

This was just an example, as this result is pretty well known and is reffered to as `leibniz's theorem`  
But now, we will formulate our own formulae!  
Keep in mind the pascal's triangle as most of if not all of our formulae will be using it; and we will have to do a lot of pattern matching!  

Let's first start with the [`exp(f(x))`](EXP.md) function.  
As you can see there was a significant role of `binomial coefficients` and `pattern matching` and the `leibniz's theorem`.

Which can also be observed in the derivations for higher order derivatives of [`logarithm`](LN.md).
