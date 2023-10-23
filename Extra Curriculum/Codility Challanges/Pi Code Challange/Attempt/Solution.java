import java.util.HashSet;
import java.util.Set;

public class Solution {
    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: "abc", "bcd" => "abcd" => 2
        int result1 = solution.solution("abc", "bcd");
        System.out.println(result1); // expected output: 2

        // Example 2: "axxz", "yzwy" => "axyz" => 2
        int result2 = solution.solution("axxz", "yzwy");
        System.out.println(result2); // expected output: 2

        // Example 3: "bacad", "abada" => "abdc" => 1
        int result3 = solution.solution("bacad", "abada");
        System.out.println(result3); // expected output: 1

        // Example 4: "amz", "amz" => "amz" => 3
        int result4 = solution.solution("amz", "amz");
        System.out.println(result4); // expected output: 3
    }

    public int solution(String P, String Q) {
        int n = P.length();
        int minDistinct = Integer.MAX_VALUE;
        HashSet<Character> distinctLetters = new HashSet<>();
        
        for (int i = 0; i < n; i++) {
            for (char c1 : new char[]{P.charAt(i), Q.charAt(i)}) {
                for (char c2 : new char[]{P.charAt(i), Q.charAt(i)}) {
                    distinctLetters.add(c1);
                    distinctLetters.add(c2);
                    minDistinct = Math.min(minDistinct, distinctLetters.size());
                    distinctLetters.clear();
                }
            }
        }
        
        return minDistinct;
    }
}
