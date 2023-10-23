// Exercise 1
def reverse4(x: Any, y: Any, z: Any, w: Any): (Any, Any, Any, Any) = (w, z, y, x)

def testReverse4(): Unit = {
  // Test 1: Standard element reversal
  val result1 = reverse4(0, 1, 2, 3)
  assert(result1 == (3, 2, 1, 0))

  // Test 2: Reversing elements with values of 0
  val result2 = reverse4(0, 0, 0, 0)
  assert(result2 == (0, 0, 0, 0))

  // Test 3: Reversing elements with negative values
  val result3 = reverse4(-1, -2, -3, -4)
  assert(result3 == (-4, -3, -2, -1))

  // Test 4: Reversing elements with different types
  val result4 = reverse4(1.0, true, 1, "A")
  assert(result4 == ("A", 1, true, 1.0))

  // Test 5: Reversing elements with different types
  val result5 = reverse4(1.5, "Hello", 'c', 42)
  assert(result5 == (42, 'c', "Hello", 1.5))
}

// Exercise 2
def sumRange(s: Int, e: Int): Int = {
  def aux(acc: Int, current: Int): Int = {
    if (current > e - 1) acc
    else aux(acc + current, current + 1)
  }
  aux(0, s)
}

def prodRange(s: Int, e: Int): Int = {
  def aux(acc: Int, current: Int): Int = {
    if (current > e - 1) acc
    else if (s == 0) 0
    else aux(acc * current, current + 1)
  }
  if (s == 0) 0
  else aux(1, s)
}

def sumProd(s: Int, e: Int): (Int, Int) = {
  val sumOfRange = sumRange(s, e)
  val prodOfRange = prodRange(s, e)
  (sumOfRange, prodOfRange)
}

def testSumProd(): Unit = {
  // Test 1: Positive numbers
  val result1 = sumProd(1, 5)
  assert(result1 == (10, 24))

  // Test 2: Only zeros
  val result2 = sumProd(0, 0)
  assert(result2 == (0, 0))

  // Test 3: Negative numbers with an even number of factors
  val result3 = sumProd(-4, 0)
  assert(result3 == (-10, 24))

  // Test 4: Negative numbers with an odd number of factors
  val result4 = sumProd(-4, -1)
  assert(result4 == (-9, -24))

  // Test 5: Range from negative to positive
  val result5 = sumProd(-4, 5)
  assert(result5 == (0, 0))
}

//Excercise 3
def isPerfect(n: Int): Boolean = {
  def isPerfectHelper(i: Int, sum: Int): Boolean = {
    if (i >= n) {
      sum == n
    } else {
      if (n % i == 0) {
        isPerfectHelper(i + 1, sum + i)
      } else {
        isPerfectHelper(i + 1, sum)
      }
    }
  }

  isPerfectHelper(1, 0)
}


// Tests
def testIsPerfect(): Unit = {
  // Test 1: 6 is a perfect number
  val result1 = isPerfect(6)
  assert(result1)

  // Test 2: 28 is a perfect number
  val result2 = isPerfect(28)
  assert(result2)

  // Test 3: 12 is not a perfect number
  val result3 = isPerfect(12)
  assert(!result3)

  // Test 4: 496 is a perfect number
  val result4 = isPerfect(496)
  assert(result4)

  // Test 5: 7 is not a perfect number
  val result5 = isPerfect(7)
  assert(!result5)
}

// Exercise 4
def insert(list: List[Any], node: Any, position: Int): List[Any] = {
  def aux(lst: List[Any], elem: Any, pos: Int): List[Any] = (lst, pos) match {
    case (_, 0) => elem :: lst
    case (Nil, _) => List(elem)
    case (hd :: tl, _) if pos <= 0 => elem :: lst
    case (hd :: tl, _) => hd :: aux(tl, elem, pos - 1)
  }
  aux(list, node, position)
}

def testInsert(): Unit = {
  // Test 1: Inserting an element at the beginning of an empty list
  val result1 = insert(Nil, "A", 0)
  assert(result1 == List("A"))

  // Test 2: Inserting an element at the beginning of a non-empty list
  val result2 = insert(List("B", "C"), "A", 0)
  assert(result2 == List("A", "B", "C"))

  // Test 3: Inserting an element at the end of the list
  val result3 = insert(List("A", "B"), "C", 2)
  assert(result3 == List("A", "B", "C"))

  // Test 4: Inserting an element out of the list's range - it should land at the end
  val result4 = insert(List("A", "B"), "C", 10)
  assert(result4 == List("A", "B", "C"))

  // Test 5: Inserting an element at the first position (index 1)
  val result5 = insert(List("A", "B", "C"), "X", 1)
  assert(result5 == List("A", "X", "B", "C"))

  // Test 6: Inserting an element at the middle position (index 2)
  val result6 = insert(List("A", "B", "C"), "Y", 2)
  assert(result6 == List("A", "B", "Y", "C"))

  // Test 7: Inserting an element at the penultimate position (index 2)
  val result7 = insert(List("A", "B", "C"), "Z", 2)
  assert(result7 == List("A", "B", "Z", "C"))

  // Test 8: Inserting an element at the end of the list where the position equals the list's length
  val result8 = insert(List("A", "B", "C"), "D", 3)
  assert(result8 == List("A", "B", "C", "D"))

  // Test 9: Inserting an element at the beginning of the list when the position is negative
  val result9 = insert(List("B", "C"), "A", -1)
  assert(result9 == List("A", "B", "C"))

  // Test 10: Inserting an element at the second position when the position is negative
  val result10 = insert(List("A", "C"), "B", -2)
  assert(result10 == List("B", "A", "C"))

  // Test 11: Inserting an element at the end of the list when the position is highly negative
  val result11 = insert(List("A", "B"), "C", -10)
  assert(result11 == List("C", "A", "B"))
}

// Running the tests
testReverse4()
println("All tests passed.")

testSumProd()
println("All tests passed.")

testIsPerfect()
println("All tests passed.")

testInsert()
println("All tests passed.")