# Exponential function
In this file we'll be discussing the formula for nth derivative of the function `exp(f(x))` we all know and love.

## Linear inner function
- [ ] Now, let's start by writing first few derivatives of `exp(x)`:
```
0: exp(x)
1: exp(x)
2: exp(x)
```
Yeah, we won't get anywhere as all the derivatives of the exp(x) is just itself as:\
<sup>`d(exp(x))`</sup>/<sub>`dx`</sub> = `exp(x)⋅`<sup>`dx`</sup>/<sub>`dx`</sub>\
by using the chain rule.

- [ ] Okay, let's use `exp(a⋅x + b)` where a and b are constants:
```
0: exp(a⋅x + b)
1: a⋅exp(a⋅x + b)
2: a⋅a⋅exp(a⋅x + b) => a²⋅exp(a⋅x + b)
3: a³⋅exp(a⋅x + b)
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
