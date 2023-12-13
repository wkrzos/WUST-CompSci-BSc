

val composites = (n: Int) => {
  def map[A, B](f: A => B, list: List[A]): List[B] =
    list match {
      case Nil => Nil
      case h :: t => f(h) :: map(f, t)
    }

  def filter[A](f: A => Boolean, list: List[A]): List[A] =
    list match {
      case Nil => Nil
      case h :: t if f(h) => h :: filter(f, t)
      case _ :: t => filter(f, t)
    }

  def isComposite(x: Int): Boolean =
    filter((y: Int) => x % y == 0, List.range(2, Math.sqrt(x).ceil.toInt + 1)).nonEmpty

  filter(isComposite, List.range(4, n + 1))
}


composites1(2)
composites1(20)
composites1(50)
composites1(100)
composites1(200)
composites1(9999999)

composites1(-1)
composites1(0)