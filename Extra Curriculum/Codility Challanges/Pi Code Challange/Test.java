package src;

public class Test {
    public static void main(String[] args) {

        // Example 1: "abc", "bcd" => "abcd" => 2
        int result1 = CompleteSolution.solution("abc", "bcd");
        System.out.println(result1); // expected output: 2

        // Example 2: "axxz", "yzwy" => "axyz" => 2
        int result2 = CompleteSolution.solution("axxz", "yzwy");
        System.out.println(result2); // expected output: 2

        // Example 3: "bacad", "abada" => "abdc" => 1
        int result3 = CompleteSolution.solution("bacad", "abada");
        System.out.println(result3); // expected output: 1

        // Example 4: "amz", "amz" => "amz" => 3
        int result4 = CompleteSolution.solution("amz", "amz");
        System.out.println(result4); // expected output: 3
    }
}
