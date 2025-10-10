from fractions import Fraction
from math import factorial

def diff(arr):
    return [arr[i+1] - arr[i] for i in range(len(arr)-1)] # Difference array

def get_coef(evals):
    step = 0
    while not all(e == evals[0] for e in evals):
        evals = diff(evals)
        step += 1

    return step, evals[0] / factorial(step)

def interpolation(evals: list[Fraction], start = 0):
    '''
    Returns the coefficients of the polynomial that fits
    (start + j, evals[j]) for each j. The coefficients are
    returned in increasing order of degree.
    '''
    evals = evals[:]
    degree, _ = get_coef(evals)
    coefs = [ Fraction(0) for _ in range(degree + 1) ]

    if(degree + 1 == len(evals)):
        print('Not redundant points')

    while any(e != 0 for e in evals):
        step, coef = get_coef(evals)
        coefs[step] = coef

        for j in range(len(evals)): # subtract x^step * coef
            evals[j] -= coef * (start + j) ** step

    return coefs


# Test the interpolation function
import random

def poly_eval(coeffs, x):
    '''Evaluate polynomial with given coefficients at x'''
    res = Fraction(0)
    for c in reversed(coeffs):
        res = res * x + c
    return res

for _ in range(1000):
    # Build a random polynomial
    n = random.randint(1, 10)
    coefs = []
    for _ in range(n): 
        coefs.append(Fraction(random.randint(1, 8), random.randint(1, 8)))

    # Get some evaluations
    start = random.randint(-5, 5)
    extra = random.randint(0, 5)
    evals = [poly_eval(coefs, x) for x in range(start, start + n + extra)]

    # Interpolate and check
    interp_coefs = interpolation(evals, start)
    assert interp_coefs == coefs, f"Failed for {coefs} got {interp_coefs}"
