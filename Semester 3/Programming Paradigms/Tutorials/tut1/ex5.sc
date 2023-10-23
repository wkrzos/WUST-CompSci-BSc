def palindrome[A](list: List[A]): Boolean = {
  // Define a recursive function to reverse a list
  def reverseList(lst: List[A]): List[A] = {
    lst match {
      case Nil => Nil // If the list is empty, return an empty list (base case)
      case head :: tail => reverseList(tail) ::: List(head) // Reverse the tail and append the head to it
    }
  }

  list == reverseList(list) // Check if the input list is equal to its reverse
}

// Test the palindrome function with some example lists
val result1 = palindrome(List(1, 2, 3, 2, 1)) // Should return true, as this list is a palindrome
val result2 = palindrome(List(1, 2, 3, 4, 5)) // Should return false, as this list is not a palindrome
