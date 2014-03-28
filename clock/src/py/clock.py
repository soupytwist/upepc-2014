from functools import reduce
from itertools import chain, combinations
import operator

def lcd(x):
    return 1 << x

BLANK = 0
ZERO  = lcd(0) | lcd(1) | lcd(3) | lcd(4) | lcd(5) | lcd(6)
ONE   = lcd(3) | lcd(6)
TWO   = lcd(0) | lcd(2) | lcd(3) | lcd(4) | lcd(5)
THREE = lcd(0) | lcd(2) | lcd(3) | lcd(5) | lcd(6)
FOUR  = lcd(1) | lcd(2) | lcd(3) | lcd(6)
FIVE  = lcd(0) | lcd(1) | lcd(2) | lcd(5) | lcd(6)
SIX   = lcd(0) | lcd(1) | lcd(2) | lcd(4) | lcd(5) | lcd(6)
SEVEN = lcd(0) | lcd(3) | lcd(6)
EIGHT = lcd(0) | lcd(1) | lcd(2) | lcd(3) | lcd(4) | lcd(5) | lcd(6)
NINE  = lcd(0) | lcd(1) | lcd(2) | lcd(3) | lcd(5) | lcd(6)

SEGMENTS = [lcd(i) for i in range(7)]
DIGITS = [ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE]
DISPLAYS = {
    ZERO: '0', ONE: '1', TWO: '2', THREE: '3', FOUR: '4', FIVE: '5', SIX: '6', SEVEN: '7', EIGHT: '8', NINE: '9', BLANK: ' '
}

CLOCKS = [(BLANK, second, third, fourth) for second in DIGITS[1:] for third in DIGITS[:6] for fourth in DIGITS] \
       + [(ONE, second, third, fourth) for second in DIGITS[:3] for third in DIGITS[:6] for fourth in DIGITS]

def display(clock):
    return "%s%s:%s%s" % tuple([DISPLAYS[dig] for dig in clock])

def mergebits(xs):
    return reduce(operator.or_, xs, 0)

def powerset(iterable):
    xs = list(iterable)
    return chain.from_iterable(combinations(xs,n) for n in range(len(xs)+1))

def digit_segments_maybe_on(digits):
    definitely_on = mergebits(digits)
    maybe_on  = [seg for seg in SEGMENTS if not (seg & definitely_on)]
    return [mergebits(xs) for xs in powerset(maybe_on)]

def clock_segments_maybe_on(clocks):
    clocks_digits = [[clock[i] for clock in clocks] for i in range(4)]
    return tuple(digit_segments_maybe_on(digits) for digits in clocks_digits)

def unmergeclocks(c1, c2):
    return tuple(c1[i] & ~c2[i] for i in range(4))

def mergeclocks(c1, c2):
    return tuple(c1[i] | c2[i] for i in range(4))

def andclocks(c1, c2):
    return tuple(c1[i] & c2[i] for i in range(4))

def test_on_tup(on, clocks):
    return any(andclocks(some_clock, on) in clocks for some_clock in CLOCKS)

def find_time(clocks):
    clocks_digits = [[clock[i] for clock in clocks] for i in range(4)]
    definitely_on = tuple(mergebits(digits) for digits in clocks_digits)
    
    on_lists = clock_segments_maybe_on(clocks)
    all_tups = [(a,b,c,d) for a in on_lists[0] for b in on_lists[1] for c in on_lists[2] for d in on_lists[3]]

    working = [mergeclocks(on, definitely_on) for on in all_tups if test_on_tup(mergeclocks(on, definitely_on), clocks)]

    if len(working) == 1:
        return display(mergeclocks(clocks[-1], working[0]))
    else:
        for wk in working:
            display(mergeclocks(clocks[-1], wk))
        return "?"
