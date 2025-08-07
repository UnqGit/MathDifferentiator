**So...why make new formulae for the stuff nobody is going to need?**  
### Because I can.

Now, derivatives, that we all know and love have various ways to get to the result..  
For example the most basic one we were all probably taught is:

(f(a) - f(a - h))/h

And it would look like:
```python
def function_derivative(function, point, derivative_number):
    return (function_derivative(function, point, derivative_number - 1) - function_derivative(function, point - h, derivative_number - 1)) / h
        if derivative_number != 0 else
        (function(point) - function(point - h)) / h
```

Which gives us the result of nth derivative of a function at a specific point.  
Now it'd be great if it were sufficient...  
But the most major flaw with it is that it is O(2<sup>n</sup>)  
Now ofc we can find a iterative solution right?

### Yes, we can.

So let's look at the zeroth derivative:  
f(a)  
Yep, that's it, zeroth derivative is itself.

First:  
(f(a)-f(a-h))/h  
now let's call them f<sub>0</sub> and f<sub>1</sub>  
so, f<sub>1</sub> is just (f<sub>0</sub>(a) - f<sub>0</sub>(a - h)) over h  
I mean, that is the definition right? doing (f(a) - f(a - h))/h over the base function?  
what if we take f<sub>1</sub> as our base function?  
well, we get:  
f<sub>2</sub>(a) = (f<sub>1</sub>(a) - f<sub>1</sub>(a - h))/h  
and yes this is our 2nd derivative of the function f<sub>0</sub>

If we write f<sub>2</sub> in terms of f<sub>0</sub> we get:  
f<sub>2</sub>(a) = (((f<sub>0</sub>(a) - f<sub>0</sub>(a - h))/h) - ((f<sub>0</sub>(a - h) - f<sub>0</sub>(a - 2h))/h))/h  
which on simplification, leads to:  
f<sub>2</sub>(a) = (f<sub>0</sub>(a) - 2f<sub>0</sub>(a - h) + f<sub>0</sub>(a - 2h))/h<sup>2</sup>

Now, let's skip ahead and get f<sub>3</sub> and f<sub>4</sub>:

f<sub>3</sub>(a) = (f<sub>0</sub>(a) - 3f<sub>0</sub>(a - h) + 3f<sub>0</sub>(a - 2h) - f<sub>0</sub>(a - 3h))/h<sup>3</sup>  
f<sub>4</sub>(a) = (f<sub>0</sub>(a) - 4f<sub>0</sub>(a - h) + 6f<sub>0</sub>(a - 2h) - 4f<sub>0</sub>(a - 3h) + f<sub>0</sub>(a - 4h))/h<sup>4</sup>  

Let's just focus on the numerator:  
f<sub>0</sub>(a) = f<sub>0</sub>(a)  
f<sub>1</sub>(a) = f<sub>0</sub>(a) - f<sub>0</sub>(a - h)  
f<sub>2</sub>(a) = f<sub>1</sub>(a) - f<sub>1</sub>(a - h)  
f<sub>3</sub>(a) = f<sub>0</sub>(a) - 3f<sub>0</sub>(a - h) + 3f<sub>0</sub>(a - 2h) - f<sub>0</sub>(a - 3h)  
f<sub>4</sub>(a) = f<sub>0</sub>(a) - 4f<sub>0</sub>(a - h) + 6f<sub>0</sub>(a - 2h) - 4f<sub>0</sub>(a - 3h) + f<sub>0</sub>(a - 4h)

Now, some of you may argue that f(a) - f(a - h) is not the actual used definition, it is f(a + h) - f(a - h)  
I agree with you, so let's rewrite it in ~rust~ I mean the actual used formula.  

Newmerators are:  
