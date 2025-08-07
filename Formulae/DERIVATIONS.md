**So...why make new formulae for the stuff nobody is going to need?**  
### Because I can.

Now, derivatives, that we all know and love have various ways to get to the result..  
For example the most basic one we were all probably taught is:

(f(a) - f(a - h))/h

And it would look like:
```python
def function_derivative(function, point, derivative_number):
    return (function(point) - function(point - h)) / h
        if derivative_number == 0 else
        ((function_derivative(function, point, derivative_number - 1)
        -function_derivative(function, point - h, derivative_number - 1)) / h)
```

- Which gives us the result of nth derivative of a function at a specific point.  
Now it'd be great if it were sufficient...  
But the most major flaw with it is that it is O(2<sup>n</sup>)  
Now ofc we can find a iterative solution right?

### Yes, we can.

- vSo let's look at the zeroth derivative:  
f(a)  
Yep, that's it, zeroth derivative is itself.

- First:  
(f(a)-f(a-h))/h  
now let's call them f<sub>0</sub> and f<sub>1</sub>  
so, f<sub>1</sub> is just (f<sub>0</sub>(a) - f<sub>0</sub>(a - h)) over h  
I mean, that is the definition right? doing (f(a) - f(a - h))/h over the base function?  
what if we take f<sub>1</sub> as our base function?  
well, we get:  
f<sub>2</sub>(a) = (f<sub>1</sub>(a) - f<sub>1</sub>(a - h))/h  
and yes this is our 2nd derivative of the function f<sub>0</sub>

- If we write f<sub>2</sub> in terms of f<sub>0</sub> we get:  
f<sub>2</sub>(a) = (((f<sub>0</sub>(a) - f<sub>0</sub>(a - h))/h) - ((f<sub>0</sub>(a - h) - f<sub>0</sub>(a - 2h))/h))/h  
which on simplification, leads to:  
f<sub>2</sub>(a) = (f<sub>0</sub>(a) - 2f<sub>0</sub>(a - h) + f<sub>0</sub>(a - 2h))/h<sup>2</sup>

- Now, let's skip ahead and get f<sub>3</sub> and f<sub>4</sub>:  
f<sub>3</sub>(a) = (f<sub>0</sub>(a) - 3f<sub>0</sub>(a - h) + 3f<sub>0</sub>(a - 2h) - f<sub>0</sub>(a - 3h))/h<sup>3</sup>  
f<sub>4</sub>(a) = (f<sub>0</sub>(a) - 4f<sub>0</sub>(a - h) + 6f<sub>0</sub>(a - 2h) - 4f<sub>0</sub>(a - 3h) + f<sub>0</sub>(a - 4h))/h<sup>4</sup>  

- Let's just focus on the numerator:  
f<sub>0</sub>(a) = f<sub>0</sub>(a)  
f<sub>1</sub>(a) = f<sub>0</sub>(a) - f<sub>0</sub>(a - h)  
f<sub>2</sub>(a) = f<sub>0</sub>(a) - 2f<sub>0</sub>(a - h) + f<sub>0</sub>(a - 2h)  
f<sub>3</sub>(a) = f<sub>0</sub>(a) - 3f<sub>0</sub>(a - h) + 3f<sub>0</sub>(a - 2h) - f<sub>0</sub>(a - 3h)  
f<sub>4</sub>(a) = f<sub>0</sub>(a) - 4f<sub>0</sub>(a - h) + 6f<sub>0</sub>(a - 2h) - 4f<sub>0</sub>(a - 3h) + f<sub>0</sub>(a - 4h)

- Now, some of you may argue that f(a) - f(a - h) is not the actual used definition, it is f(a + h) - f(a - h)  
I agree with you, so let's rewrite it in ~rust~ I mean the actual used formula.  

- Newmerators are:  
f<sub>0</sub>(a) = f<sub>0</sub>(a)  
f<sub>1</sub>(a) = f<sub>0</sub>(a + h) - f<sub>0</sub>(a - h)  
f<sub>2</sub>(a) = f<sub>0</sub>(a + 2h) - 2f<sub>0</sub>(a) + f<sub>0</sub>(a - 2h)  
f<sub>3</sub>(a) = f<sub>0</sub>(a + 3h) - 3f<sub>0</sub>(a + h) + 3f<sub>0</sub>(a - h) - f<sub>0</sub>(a - 3h)  
f<sub>4</sub>(a) = f<sub>0</sub>(a + 4h) - 4f<sub>0</sub>(a + 2h) + 6f<sub>0</sub>(a) - 4f<sub>0</sub>(a - 2h) + f<sub>0</sub>(a - 4h)

And the denominators subsequently are (2h)<sup>n</sup> instead of h<sup>n</sup>

**If you are familiar with binomial series or the pascal's triangle, the formula might look a little **appetizing** ....we can compress the formula into this:**
```python
def function_derivative(function, point, derivative_number):
    result = 0.0
    for i in range(derivative_number + 1):
         result += nCr(derivative, i) * ((-1)**derivative_number) * function(point + derivative_number*h - 2*i*h)
    return result / ((2*h) ** derivative_number)
```

See? very simple!!  
Now, this may seem really good as it is O(n) (**if** the function is O(1)) (nCr(s) can be cached, so let's just count them as O(1) as well)  
But ofcourse there are issues!!  
If we remember our derivative formulae correctly, it also, on a sidenote but a **very** important side note  
It also says, lim<sub>h -> 0</sub>  
But the thing is, this is theoretical, we are talking about practicality here and we can't have a variable with almost 0 size, we can have it really small  
But that is just an illusion as the smaller the h gets the more lossy the result gets and worse yet you have to fine tune the h for every function + point + derivative_number  
to get it to give us good results which also give us completely wrong results after derivative_number > 19  
and most of the time it will get to the point where you would need to have larger stepsize as the derivative_number gets larger and that's another issue in on itself!  

So, we have established that h can't be infinitely small and there is one more major issue with that constraint...
say for example we are calculating the derivative of the **ln** function near x = 0  
The higher the derivative_number gets for this issue, the more chances there are that 'point - (derivative_number * h)' will get smaller than 0, which is an issue  
because the logarithm function is not defined below x = 0 and that is not a good and desirable behaviour to have...

- Now, most of you who have done differentiation would say to just use automatic differentiation programs or that I should use optimized Faà di Bruno’s formula  
But where is the fun in that, we are going to derive our own formulae!

### Formulae we will derive
- exp(f(x))
- ln(f(x))
- trig(f(x))
- inverse trig(x)
- hyperbolic(x)
- u(x)<sup>v(x)</sup>

What will we get from doing it?  
Results which only require the point itself, no nearby points; really optimized solutions; and fun.
