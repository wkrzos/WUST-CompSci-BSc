public class Main {
    public static void main(String[] args) {

        // Example 1
        int result1 = CompleteSolution.solution("abc", "bcd");
        System.out.println(result1); // expected output: 2

        // Example 2
        int result2 = CompleteSolution.solution("axxz", "yzwy");
        System.out.println(result2); // expected output: 2

        // Example 3
        int result3 = CompleteSolution.solution("bacad", "abada");
        System.out.println(result3); // expected output: 1

        // Example 4
        int result4 = CompleteSolution.solution("amz", "amz");
        System.out.println(result4); // expected output: 3

        // Example 5: "ab", "ba" => "ab" => 1
        int result5 = CompleteSolution.solution("ab", "ba");
        System.out.println(result5); // expected output: 1

        // Example 6
        int result = CompleteSolution.solution("aafsjkhflaskjhdflsafhlaksdhf", "asfewfwaefhvnxncvbxcbvexvbjq");
        System.out.println(result); // expected output: ?

        // Example 7
        int result7 = CompleteSolution.solution("aa", "bba");
        System.out.println(result7); // expected output: 1 ?
    }
}
