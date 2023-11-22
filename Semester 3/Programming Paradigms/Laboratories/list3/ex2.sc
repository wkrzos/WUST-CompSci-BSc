/*
* Write a composites function that generates all composite numbers in range [2, n].
* Use for statement and List.range only. You must not use recursion or functionals.
*/

/*
* Solution 1
* A modified version of the sieve of eratosthenes is used. Time complexity: O(n*log(log(n)))
* Outer Loop: runs for n-1 iterations
* Inner Loop: runs for n/i iterations for each i value
* T(n) = (n-1) + n/2 + n/3 + ... + 1
* ^ Harmonic series approximated by the complexity.
*/

def composites1(n: Int): List[Int] = {
  if (n < 4) List() // No composite numbers less than 4

  val sieve = Array.fill(n + 1)(false) // Initialize an array to track composite numbers
  var composites = List[Int]()

  for (i <- 2 to n) {
    if (!sieve(i)) {
      // i is prime, mark its multiples as composite
      for (j <- 2 * i to n by i) {
        sieve(j) = true
      }
    } else {
      // i is composite, add it to the list
      composites = i :: composites
    }
  }

  composites.reverse // Reversing the list for ascending order
}

composites1(2)
composites1(20)
composites1(50)
composites1(100)
composites1(200)
composites1(9999999)

composites1(-1)
composites1(0)

/*
* Solution 2
*
* isComposite - checks if the input (num) is a composite number. Function checks if for any number from 2 to num exists such a number that num % _ == 0
*
* composites - iterates through numbers from 2 to n. For each number it checks if it is composite using isComposite.
*
* complexity: about O(n^2)
* */

def isComposite(num: Int): Boolean = {
  (2 until num) exists (num % _ == 0)
}

def composites2(n: Int): List[Int] = {
  for {
    i <- List.range(2, n + 1) if isComposite(i)
  } yield i
}

composites2(2)
composites2(20)
composites2(50)
composites2(100)
composites2(200)
composites2(9999999)

composites2(-1)
composites2(0)






