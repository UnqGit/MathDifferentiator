# Higher Order Derivative Formulae

> A collection of recurrence relations for efficiently computing the nth derivative of composite functions.

Why spend months deriving formulas nobody asked for?

Because it's fun.

Because there are interesting patterns hiding underneath.

And because sometimes reinventing the wheel teaches you far more than simply using it.

---

Higher-order derivatives are usually obtained in one of three ways:

- symbolic differentiation
- automatic differentiation
- finite difference approximations

This project explores a *fourth* perspective: deriving direct recurrence relations for specific classes of composite functions.

Before diving into those derivations, it's worth looking at the finite difference approach and why it eventually becomes impractical for this goal.

$\rightarrow$ **Read:** [Finite Difference Methods](finite-difference.md)

Finite differences are elegant and surprisingly efficient after simplification, but they remain *numerical approximations* whose accuracy depends on choosing an appropriate step size. Higher derivatives magnify floating-point error, and functions with restricted domains introduce additional complications.

Instead of approximating derivatives using nearby sample points, the remainder of this project derives exact recurrence relations for families of composite functions that depend only on derivatives evaluated at the point itself.

Now, most of you who know about computing derivatives would say to just use [`symbolic differentiation`](https://en.wikipedia.org/wiki/Computer_algebra) programs or that `Faà di Bruno’s formula` is the obvious next step.  

But we will approach it in a fun way. We are going to derive our own formulae!

## Formulae we will derive:
- $u(x)\cdot v(x)$
- $\frac {u(x)} {v(x)}$
- $e^{f(x)}$
- $u(x)^{v(x)}$
- $\sqrt{u(x)}$
- $\ln(f(x))$
- Trigonometry:
    - $\sin(f(x))$ , $\cos(f(x))$
    - $\cot(f(x))$ , $\tan(f(x))$
    - $\csc(f(x))$ , $\sec(f(x))$
- Inverse Trigonometry:
    - $\sin^{-1}(f(x))$ , $\cos^{-1}(f(x))$
    - $\cot^{-1}(f(x))$ , $\tan^{-1}(f(x))$
    - $\csc^{-1}(f(x))$ , $\sec^{-1}(f(x))$
- Hyperbolic Trigonometry:
    - $\sinh(f(x))$ , $\cosh(f(x))$
    - $\coth(f(x))$ , $\tanh(f(x))$
    - **csch** $(f(x))$ , **sech** $(f(x))$

> Yes all are composite functions as it will give us more range and challange.

What will we get from doing it?  
Results which only require the point itself, no nearby points(and floating point issues related to $h$); really optimized solutions; and fun.

## Starting the journey
Starting from the top of the list and from the easiest one of all, we will take a look at the formula for $n^{th}$ derivative of $f = u\cdot v$, where $f$, $v$, and $u$ are all functions of $x$ in [product.md](product.md).

Keeping the spirits of arithmetic functions high, the next function we derive a recurrence relation for is $f = \frac uv$ in [quotient.md](quotient.md).  

Just like how on repeated addition we get multiplication, on repeated multiplication we get exponents, so let's move forward and do the [e<sup>u(x)</sup>](EXP.md) function.  
As you can see there was a significant role of `binomial coefficients` and `pattern matching` and the `leibniz's theorem`.

Which can also be observed in the derivations for higher order derivatives of [ln(u(x))](LN.md).
Now, that we are on the topic of power related functions let's take a look at [u(x)<sup>c</sup>](CONST_POW.md) and finally we have our final boss [u(x)<sup>v(x)</sup>](POW.md)

Now, that power functions are over, let's take a look at trigonometry and start with [tan(u(x)) & cot(u(x))](TANCOT.md).  
Now that you have taken a look at how we tackled $\tan(u(x))$ and $\cot(u(x))$ let's take a look at the basic ones(or not so basic ones as you will see) $\sin(u(x))$ and $\cos(u(x))$ [here](SINCOS.md).  
The only member of trigonometry family remaining are [sec(u(x)) & csc(u(x))](SECCSC.md).