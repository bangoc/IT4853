package org.Demo;

import com.carrotsearch.sizeof.RamUsageEstimator;

import java.util.ArrayList;
import java.util.Arrays;

public class FrontCoding {
    public static String FrontCodingEncode(String[] dict, int k) {
        StringBuilder b = new StringBuilder();
        int idx = 0;
        for (;;) {
            b.append((char) dict[idx].length());
            String s = dict[idx];
            for (int i = idx + 1; i < idx + k; ++i) {
                int j = 0;
                for (; j < Math.min(s.length(), dict[i].length()); ++j) {
                    if (s.charAt(j) != dict[i].charAt(j))
                        break;
                }
                if (j > 0) {
                    s = s.substring(0, j);
                } else {
                    s = "";
                    break;
                }
            }
            int common_len = s.length();
            b.append((char) common_len);
            b.append(dict[idx]);
            for (int i = idx + 1; i < idx + k; ++i) {
                String tmp = dict[i].substring(common_len);
                b.append((char) tmp.length());
                b.append(tmp);
            }
            idx += k;
            if (idx >= dict.length)
                break;
        }
        return b.toString();
    }

    public static String[] FrontCodingDecode(String encoded, int k) {
        ArrayList<String> dict = new ArrayList<>();
        int idx = 0;
        for (;;) {
            int len = (int)encoded.charAt(idx++);
            int common_len = (int)encoded.charAt(idx++);
            String s = encoded.substring(idx, idx + len);
            String commons = s.substring(0, common_len);
            dict.add(s);
            idx += len;
            for (int i = 1; i < k; ++i) {
                len = (int)encoded.charAt(idx++);
                s = encoded.substring(idx, idx + len);
                dict.add(commons + s);
                idx += len;
            }
            if (idx >= encoded.length())
                break;
        }
        String[] ret = new String[dict.size()];
        return dict.toArray(ret);
    }

    public static void main(String[] argv) {
        String[] dictionary = {"automata", "automate", "automatic", "automation",
                "automatism", "automatist", "automative", "automatization",
                "automatize", "automatized", "automatizes", "automatizing"};
        int k = 4;
        String encoded = FrontCodingEncode(dictionary, k);
        long sz1 = RamUsageEstimator.sizeOfAll(dictionary);
        long sz2 = RamUsageEstimator.sizeOfAll(encoded);
        double ratio = (double)sz2 / sz1;
        System.out.printf("Sz = %d  Sz2 = %d Ratio = %f%%\n", sz1, sz2, ratio * 100);
        String[] dictionary2 = FrontCodingDecode(encoded, k);
        System.out.println(Arrays.toString(dictionary2));
    }
}
