// Ex 1

def whileLoop(condition: => Boolean)(body: => Unit): Unit = {
  if (condition) {
    body
    whileLoop(condition)(body)
  }
}


var count = 0

whileLoop(count < 3) {
  println(count)
  count += 1
}
