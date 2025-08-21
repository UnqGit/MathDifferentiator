# Exponential function
In this file we'll be discussing the formula for nth derivative of the function `exp(f(x))` we all know and love.

## Linear inner function
- [ ] Now, let's start by writing first few derivatives of `exp(x)`:
```
f₀: exp(x)
f₁: exp(x)
f₂: exp(x)
```
Yeah, we won't get anywhere as all the derivatives of the exp(x) is just itself as:\
<sup>`d(exp(x))`</sup>/<sub>`dx`</sub> = `exp(x)⋅`<sup>`dx`</sup>/<sub>`dx`</sub>\
by using the chain rule.

- [ ] Okay, let's use `exp(a⋅x + b)` where a and b are constants:
```
f₀: exp(a⋅x + b)
f₁: a⋅exp(a⋅x + b)
f₂: a⋅a⋅exp(a⋅x + b) => a²⋅exp(a⋅x + b)
f₃: a³⋅exp(a⋅x + b)
```
> [!IMPORTANT]
> Okay, we have actual solution in this one:\
It will be: `f`<sub>`n`</sub> = `aⁿexp(a⋅x + b)`

## Arbitrary inner function
Now, let's say that the exponential function doesn't have just `x` or a linear equation, such as `a⋅x + b`\
It'd be pretty hard coming up with formulae for those...right? Well, not so fast;\
I will show you how!

Let's that out function is:\
f = `exp(u)`\
Where `u` is a function in `x`

So, all we have so far is:\
f₀ = `exp(u₀)`

If we differentiatie it, we will get:\
<sup>df₀</sup>/<sub>dx</sub> => exp(u₀)⋅<sup>du₀</sup>/<sub>dx</sub>\
using chain rule; and we will get:\
f₁ = `exp(u₀)⋅u₁`\
similarly, if we go up the ladder, we will get:\
f₂ = `exp(u₀)⋅u₁² + exp(u₀)⋅u₂`\
using chain rule and product rule.\
f₃ = `exp(u₀)⋅u₁³ + 3⋅u₁u₂exp(u₀) + exp(u₀)⋅u₃`\
f₄ = `exp(u₀)⋅u₁⁴ + 6⋅u₁²u₂exp(u₀) + 3⋅u₂²exp(u₀) + 4⋅u₃u₁exp(u₀) + exp(u₀)⋅u₄`

- [ ] Let's do the obvious next thing and take the `exp(u₀)` common:
```
f₀ = exp(u₀)
f₁ = exp(u₀)(u₁)
f₂ = exp(u₀)(u₁² + u₂)
f₃ = exp(u₀)(u₁³ + 3⋅u₁u₂ + u₃)
f₄ = exp(u₀)(u₁⁴ + 6⋅u₁²u₂ + 3⋅u₂² + 4⋅u₃u₁ + u₄)
```
Now, you may be asking where exactly is a pattern??\
I mean it surely does look like there is one but it's all over the place...so let's do it a differnet way!\
let's write each function again but using the shorthand definition(eg: f₀, f₁) of previous functions, shall we?\
f₀ = `exp(u₀)`\
f₁ = `f₀u₁`\
Now, since after differentiating f₁ we will get f₂, we can just differentiate the shortand version(the line above) to get:\
f₂ = `f₁u₁ + f₀u₂`\
furthermore:\
f₃ = `f₂u₁ + 2⋅f₁u₂ + f₀u₃`

Or we could have used the leibniz's theorem on the shorthand definition of `f₁`, which we had just derived in the [`README`](README.md).

> [!IMPORTANT]
> What if we try to compact that formula?\
we will get:\
f<sub>n</sub> = <sub>k=0</sub><sup>n-1</sup>∑ (<sup>n-1</sup><sub>k</sub>)⋅f<sub>n-1-k</sub>⋅u<sub>k+1</sub>\
Which can also be written as:\
f<sub>n</sub> = <sub>k=1</sub><sup>n</sup>∑ (<sup>n-1</sup><sub>k-1</sub>)⋅f<sub>n-k</sub>⋅u<sub>k</sub>

> [!NOTE]
> The formula above is only valid for when `n ≥ 1`.

Which can be used in a practical setting as:
```python
def exp_derivative(u_list, derivative_number):
    f_list = [0.0]*(derivative_number+1)
    f_list[0] = math.exp(u_list[0])
    for n in range(1, derivative_number+1):
        result = 0.0
        for k in range(1, n+1):
            result += nCr(n-1, k-1)*f_list[n-k]*u_list[k]
        f_list[n] = result
    return f_list
```
If you look at it from afar, it might look like `O(n²)` but if you remember we were calculating only a single `nth` derivative in the other functions but here we are calculating all the derivatives from `0 to n` in `O(n²)` that means that it will be `O(n)` if we know the required previous derivatives of the functions `u` and `f`.

_**`Isn't mathematics amazing?! ✨`**_

# Different constant bases
Now that was just `exp(f(x))` which as you know has the base `e` also known as `euler's number`, the value of which equates to `2.71.....`

But what if the base was something else like 2 or pi anything for that matter??

Let's see what are the changes we need to make to be able to find the n differentiation values!\
If we go back to the highschool days, one of the most imortant thing we are taught is\
that ln and exp are inverse of each other...

what that means is that `exp(ln(x))` would be equal to x or `exp(ln(4))` would equal 4, WAIT, let's go back to the exp(ln(4)), you see something?\
it's exp(ln(2<sup>2</sup>)) which equates to 2<sup>2</sup>!!(not factorial)

Let's say instead of `2`<sup>`2`</sup> we had `2`<sup>`x`</sup>, let's do that again:\
`exp(ln(2`<sup>`x`</sup>`))` but now instead of simplifying, let's use the log property of `ln(a`<sup>`b`</sup>`) = b⋅ln(a)`\
we get:\
`exp(x⋅ln(2))`
> Now the new inner function is `x⋅ln(2)`

- [] Let's write the first few derivatives of this function(`a` is the constant base and `u(x)` is the function which `a` is raised to):
```
f₀: exp(u₀⋅ln(a))
f₁: u₁ln(a)⋅exp(u₀ln(a))
f₂: (u₁ln(a))²⋅exp(u₀ln(a)) + u₂ln(a)⋅exp(u₀ln(a))
f₃: (u₁ln(a))³⋅exp(u₀ln(a)) + 2u₂u₁ln(a)⋅exp(u₀ln(a)) + u₂u₁(ln(a))² + u₃ln(a)⋅exp(u₀ln(a))
```

Not much help is it? the powers are increasing, we have more multiples\
- [] Let's write it while taking things common:
```
f₀: exp(u₀⋅ln(a))
f₁: u₁ln(a)⋅exp(u₀ln(a))
f₂: exp(u₀ln(a))⋅(ln(a)⋅(u₂ + u₁²ln(a)))
f₃: exp(u₀ln(a))⋅(ln(a)⋅(u₃ + 2u₂u₁ + ln(a)⋅(u₂u₁ + u₁³ln(a))))
```

Not much help either, very random huh?\
- [] Let's do it our way:
```
f₀: exp(u₀⋅ln(a))
f₁: ln(a)⋅f₀u₁
f₂: ln(a)⋅(f₁u₁ + f₀u₂)
f₃: ln(a)⋅(f₂u₁ + 2⋅f₁u₂ + f₀u₃)
```

Now, the astute amongst you might be able to point out that it is the exact same formula as the one with euler's number as base but with just a ln(a) factor.\

> [!IMPORTANT]
> Which would give us:\
f<sub>n</sub> = ln(a)<sub>k=0</sub><sup>n-1</sup>∑ (<sup>n-1</sup><sub>k</sub>)⋅f<sub>n-1-k</sub>⋅u<sub>k+1</sub>\
Which can also be written as:\
f<sub>n</sub> = ln(a)<sub>k=1</sub><sup>n</sup>∑ (<sup>n-1</sup><sub>k-1</sub>)⋅f<sub>n-k</sub>⋅u<sub>k</sub>

> [!NOTE]
> Where:\
f₀: exp(u₀⋅ln(a))
and ln(a) is the natural logarithm of the constant base `a`
in the argument `a`<sup>`u(x)`</sup>
and for it to work `ln(x)` should be defined at the point of base `a`
so n >= 1

And that in practice, would look like:\
```python
def const_base_pow_derivative(base, u_list, derivative_number):
    f_list = [0.0]*(derivative_number+1)
    base_factor = math.log(base)
    f_list[0] = math.exp(u_list[0] * base_factor)
    for n in range(1, derivative_number+1):
        result = 0.0
        for k in range(1, n+1):
            result += nCr(n-1, k-1)*f_list[n-k]*u_list[k]
        f_list[n] = result * base_factor
    return f_list
```

And now we are done with EXP....or you would think so but it will come in handy once more in future and you'd be amazed!