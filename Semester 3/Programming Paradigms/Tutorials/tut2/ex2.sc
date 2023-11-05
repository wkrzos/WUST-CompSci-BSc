def fib(x: Int): Int =
  if x == 0 then
    0
  else if x == 1 then
    1
  else fib (x - 2) + fib (x - 1)

def fibTail