# Sec and Csc

Despite being in the trigonometric family, they don't get enough recognition.

I mean we can already solve these by doing:
```python
def sec_derivatives(u_list, order):
    return reciprocal_derivatives(cos_derivatives(u_list, order), order)

def csc_derivatives(u_list, order):
    return reciprocal_derivatives(sin_derivatives(u_list, order), order)
```
But let's give them some recognition.

## Sec

We have our function $f = \sec(u)$, the first few derivatives are:
```math
\begin{align*}
f &= \sec(u) \\
f_1 &= u_1\tan(u)\sec(u) \\
f_2 &= u_2\tan(u)\sec(u)+u_1^2\sec^3(u)+u_1^2\tan^2\sec(u) \\
f_3 &= u_3\tan(u)\sec(u)+3u_2u_1\sec^3(u)+3u_2u_1\tan^2(u)\sec(u)+2u_1^3\sec^3(u)\tan(u)+u_1^3\sec^3(u)\tan^2(u)+2u_1^3\sec(u)\tan^3(u)\\
\end{align*}
```
As you can see the number of terms explodes incredibly fast.

If we see the first derivative, is is
```math
f_1 = u_1\tan(u)\sec(u)
```
Squaring both sides gives us:
```math
f_1^2 = u_1^2\tan^2(u)\sec^2(u)
```
And by pythagorean identity $\tan^2 = \sec^2 - 1$, and because $f = \sec(u)$ we get:
```math
f_1^2 = u_1^2(f^2-1)f^2
```
Or:
```math
f_1^2 = (u_1f)^2f^2-(u_1f)^2
```
And consider $h = u_1f$ and apply Leibniz's rule and memoize $h$ and $f^2$ terms to make our recurrence relation still work in $O(n^2)$.

But that is very verbose and is not necesary.

Let's look at the first derivative again:
```math
f_1 = u_1\sec(u)\tan(u)
```
It is the same as:
```math
f_1 = u_1\sec^2(u)\sin(u)
```
And since $f = \sec(u)$:
```math
f_1 = u_1f^2\sin(u)
```
Let's consider $v = \sin(u)$ and since we know the $n^{th}$ derivative of $\sin$ i.e., $v_n$, we can precompute the values for required derivatives of $u_1v$ and memoize for $f^2$ in our main loop but that requires us to keep notice of 2 auxiliary variables but still $O(n^2)$. For $\sin$ derivatives $\rightarrow$ **refer:** [`sin-cos.md`](sin-cos.md)

Although these identities suggest specialized recurrences, none are appreciably simpler or more efficient than treating $\sec(u)$ as the reciprocal of $\cos(u)$. Since the reciprocal recurrence is already implemented, a dedicated secant recurrence offers little practical advantage.  
That is:
```math
f = \frac 1{\cos(u)}
```
That gives us our:
### Formula
```math
f_n = -\frac {1} {v} \sum_{k=0}^{n-1}\binom{n}{k}f_{k}v_{n-k}
```
using our reciprocal function equation $\rightarrow$ **refer:** [`quotient.md`](../quotient.md).  
Where:
```math
v = \cos(u) \\
v_n = D^n(\cos(u))
```
For $n^{th}$ derivatives of $\cos$ $\rightarrow$ **refer:** [`sin-cos.md`](sin-cos.md)
### Practical Implementation
```python
def sec_derivatives(u_list, order):
    return reciprocal_derivatives(
        cos_derivatives(u_list, order),
        order
    )
```
## Csc
We can go the same route for $\csc$ as well.

So, let's cut right to the chase and get our

### Formula
```math
f_n = -\frac {1} {v} \sum_{k=0}^{n-1}\binom{n}{k}f_{k}v_{n-k}
```
Where:
```math
v = \sin(u) \\
v_n = D^n(\sin(u))
```
### Practical Implementation
```python
def csc_derivatives(u_list, order):
    return reciprocal_derivatives(
        sin_derivatives(u_list, order),
        order
    )
```