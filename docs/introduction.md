# Higher Order Derivative Formulae

> A collection of **recurrence relations** for efficiently computing the nth derivative of composite functions.

Why spend months deriving formulas nobody asked for?

Because it's fun.

Because there are interesting patterns hiding underneath.

And because sometimes reinventing the wheel teaches you far more than simply using it.

---

## Intended audience
Who is this documentation for?
- Curious mathematicians
- Someone who wants to know the internals of this library
- CAS developers
- Someone implementing taylor integrators
- Someone interested in computational mathematics and symbolic algorithms

## Beyond Traditional Views
Higher-order derivatives are usually obtained in one of three ways:

- symbolic differentiation
- automatic differentiation
- finite difference approximations

This project explores a *fourth* perspective: deriving direct recurrence relations for specific classes of composite functions.

Before diving into those derivations, it's worth looking at the finite difference approach and why it eventually becomes impractical for this goal.

$\rightarrow$ **Read:** [`Finite Difference Methods`](finite-difference.md)

Finite differences are elegant and surprisingly efficient after simplification, but they remain *numerical approximations* whose accuracy depends on choosing an appropriate step size. Higher derivatives magnify floating-point error, and functions with restricted domains introduce additional complications.

Instead of approximating derivatives using nearby sample points, the remainder of this project derives exact recurrence relations for families of composite functions that depend only on derivatives evaluated at the point itself.

Now, most of you who know about computing derivatives would argue for [`symbolic differentiation`](https://en.wikipedia.org/wiki/Computer_algebra) programs or that `Faà di Bruno’s formula` is the obvious next step.  

But we will approach it in a fun way. We are going to derive our own formulae!

## Formulae we will derive:
- $u(x)\cdot v(x)$
- $\frac {u(x)} {v(x)}$
- $e^{u(x)}$
- $u(x)^{v(x)}$
- $\sqrt{u(x)}$
- $\ln(u(x))$
- Trigonometry:
    - $\sin(u(x))$ , $\cos(u(x))$
    - $\cot(u(x))$ , $\tan(u(x))$
    - $\csc(u(x))$ , $\sec(u(x))$
- Inverse Trigonometry:
    - $\sin^{-1}(u(x))$ , $\cos^{-1}(u(x))$
    - $\cot^{-1}(u(x))$ , $\tan^{-1}(u(x))$
    - $\csc^{-1}(u(x))$ , $\sec^{-1}(u(x))$
- Hyperbolic Trigonometry:
    - $\sinh(u(x))$ , $\cosh(u(x))$
    - $\coth(u(x))$ , $\tanh(u(x))$
    - **csch** $(u(x))$ , **sech** $(u(x))$

What will we get from doing it?  

No requirement for nearby sample points that magnify floating point errors.  

Avoids constructing enormous symbolic expressions altogether.

Efficient solutions for repeated high-order derivative evaluation. $\rightarrow$ **Read:** [`benchmark`](../benchmark/benchmark.md)

And most importantly, fun.

## Recurrence Relation
### What Is It?
A [`recurrence relation`](https://en.wikipedia.org/wiki/Recurrence_relation) is an equation according to which the $n^{th}$ term of a sequence(here derivatives) can be calculated using some combination of previous terms.  

A famous example of this is a factorial which is defined as $n! = n\cdot(n-1)!$ or $f_n = n\cdot f_{n-1}$, which requires only the previous term to calculate the $n^{th}$ term.  
Or, fibonacci sequence, which is defined as $f_n = f_{n-1} + f_{n-2}$ which requires the previous two terms.

### Why Recurrence Relation?
**Symbolic differentiation**  
A computer algebra system repeatedly applies the chain rule, expanding expressions into larger and larger trees. The expression can become enormous, even though much of it consists of repeated patterns.

**Automatic differentiation**  
Automatic differentiation is fantastic for first derivatives (and with extensions, higher derivatives), but computing high-order derivatives generally involves propagating increasingly complex derivative structures or truncated Taylor series.

**Finite differences**  
You estimate derivatives by sampling nearby points. This works well for low-order derivatives, but higher derivatives amplify numerical error and become very sensitive to the choice of step size.

**Recurrence relations**  
Instead of rebuilding the entire derivative every time, you compute
```math
D_0, D_1, D_2, \dots, D_n
```
where each new derivative is obtained from the previous ones.  
*It's essentially dynamic programming for differentiation.*

They're especially attractive when:
- You need **very high-order** derivatives.
- You're evaluating derivatives at **one point** rather than manipulating symbolic formulas,
- You're implementing **Taylor-series methods**.
- You care about avoiding symbolic expression growth.
- You're writing a numerical library for repeated derivative evaluation.

Which is exactly our end goal.

## Starting The Journey
Every derivation in this project starts from scratch. No Faà di Bruno's formula, no computer algebra, and no mysterious identities appearing out of thin air. Just repeated differentiation, a bit of algebra, and a lot of pattern hunting until a recurrence finally reveals itself.  

We begin with the humble product rule. It isn't the most exciting destination, but it teaches almost every trick we'll reuse later. From there the problems gradually become nastier: quotients, exponentials, logarithms, powers, and eventually the trigonometric families $\rightarrow$ [`product`](product.md).

From there, the natural next step is division. The quotient recurrence builds directly on the product formula while introducing a different style of recursive dependency $\rightarrow$ [`quotient`](quotient.md).  

Once arithmetic operations are in place, we move to exponential and logarithmic functions. These derivations reveal recurring appearances of binomial coefficients, convolution-like sums, and patterns that become increasingly difficult to spot by ordinary symbolic differentiation :  
$\quad\rightarrow$ [`exponential`](power-functions/exponential.md)  
$\quad\rightarrow$ [`logarithm`](logarithm.md)  

With those tools established, we tackle power functions. We first derive the recurrence for constant powers before combining everything into the considerably more involved general case $u(x)^{v(x)}$:  
$\quad\rightarrow$ [`constant power`](power-functions/constant-power.md)  
$\quad\rightarrow$ [`general power`](power-functions/general-power.md)  

Finally, we enter the world of trigonometric functions. Rather than beginning with sin and cos, we start with tan and cot, whose recurrences expose structures that make the later derivations feel much more natural. From there we derive formulas for sin and cos, and conclude the trigonometric family with sec and csc:  
$\quad\rightarrow$ [`tan and cot`](trigonometry/tan-cot.md)  
$\quad\rightarrow$ [`sin and cos`](trigonometry/sin-cos.md)  
$\quad\rightarrow$ [`sec and csc`](trigonometry/sec-csc.md)

Each chapter builds on techniques introduced earlier, so reading them roughly in order is recommended—even if you're only interested in a particular formula.