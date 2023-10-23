import java.util.Arrays;

public class MainJavaRefined {

    public static void main(String[] args) {
        solution("ab", "ba");
    }

    public static void DepthFirstSearch(int have, int now, int state, final boolean[][] mark, int num, int[] ans) {

        if (num >= ans[0]) {
            return;
        }

        int mask = 1 << now;
        if (mask > have) {
            ans[0] = num;
            return;
        }

        if ((mask & have) == 0) {
            DepthFirstSearch(have, now + 1, state, mark, num, ans);
        } else {
            int temp = 0, d = 0;
            for (int i = now + 1; i < 26; ++i) {
                if (mark[i][now] && (have & (1 << i)) > 0) {
                    temp |= 1 << i;
                    ++d;
                }
            }
            DepthFirstSearch(have ^ temp, now + 1, state | temp, mark, num + d, ans);
            DepthFirstSearch(have, now + 1, state | mask, mark, num + 1, ans);
        }
    }

    public static int solution(String P, String Q) {

        boolean[][] mark = new boolean[26][26];
        int n = P.length();
        for (int i = 0; i < n; ++i) {
            int p = P.charAt(i) - 'a', q = Q.charAt(i) - 'a';
            mark[p][q] = mark[q][p] = true;
        }

        int temp = 0;
        for (int i = 0; i < 26; ++i) {
            if (mark[i][i]) {
                ++temp;
                Arrays.fill(mark[i], false);
            }
        }

        int have = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (mark[i][j]) {
                    have |= 1 << i;
                    break;
                }
            }
        }
        
        int[] ans = new int[] { n };
        DepthFirstSearch(have, 0, 0, mark, temp, ans);
        System.out.println(ans[0]);
        return ans[0];
    }
}